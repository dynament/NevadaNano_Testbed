/* Includes ------------------------------------------------------------------*/
#include <main.h>

#include <NevadaNano.h>
#include <stdio.h>
#include <string.h>
#include <hardware/watchdog.h>
#include <pico/binary_info.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
struct repeating_timer timer_counter;
struct repeating_timer timer_heartbeat;

// UART
uint8_t  g_aucRxBufferMaster [ P2P_BUFFER_MASTER_SIZE ]   __attribute__( ( aligned ( 16 ) ) );
uint8_t  g_aucRxBufferSlave  [ P2P_BUFFER_SLAVE_SIZE  ]   __attribute__( ( aligned ( 16 ) ) );
uint8_t  g_SensorStatus      [ 24 ];
volatile uint16_t g_uiRxBufferMasterGet = 0;
volatile uint16_t g_uiRxBufferMasterPut = 0;
volatile uint16_t g_uiRxBufferSlaveGet  = 0;
volatile uint16_t g_uiRxBufferSlavePut  = 0;

volatile bool     g_b_ucPcCommsFlag     = false;
volatile bool     g_b_ucSensorCommsFlag = false;
volatile uint16_t g_uiCommsTimeout      = 0;

/* Private function prototypes -----------------------------------------------*/
uint8_t  MakeString     ( uint8_t* buffer );
uint8_t  read_frame     ( uart_inst_t* uart , uint8_t* buffer );
uint16_t crc16          ( uint16_t crc , const uint16_t *table , uint8_t* buffer , uint8_t length );
void     forward_frame  ( void );
void     MUX_Set        ( uint8_t sensor );
void     send_exception ( uint8_t address , uint8_t function_code , uint8_t code );

/* User code -----------------------------------------------------------------*/
// Timer interrupts
bool timer_counter_isr ( struct repeating_timer *t )
{
    static uint8_t countPC     = 0;
    static uint8_t countSensor = 0;

    if ( 1 == g_b_ucPcCommsFlag )
    {
        LED_YELLOW_ON;  // PC comms data led on
    }
    else
    {
        // Nothing to do
    }
    
    if ( 1 == g_b_ucSensorCommsFlag )
    {
        LED_RED_ON; // Sensor comms data led on
    }
    else
    {
        // Nothing to do
    }

    countPC++;
    if ( countPC > 19 )
    {
        LED_YELLOW_OFF; // PC comms data led off
        countPC           = 0;
        g_b_ucPcCommsFlag = false;
    }
    else
    {
        // Nothing to do
    }
    
    countSensor++;
    if ( countSensor > 19 )
    {
        LED_RED_OFF;    // Sensor comms data led off
        countSensor           = 0;
        g_b_ucSensorCommsFlag = false;
    }
    else
    {
        // Nothing to do
    }

    if ( 0 < g_uiCommsTimeout )
    {
        g_uiCommsTimeout--;
    }
    else
    {
        // Nothing to do
    }
}

static bool timer_heartbeat_isr ( struct repeating_timer *t )
{
    if ( gpio_get ( LED_PICO_PIN ) )
    {
        LED_PICO_OFF;
    }
    else
    {
        LED_PICO_ON;
    }
}

// UART_RX interrupt handler
static void uart_rx_isr ( )
{
    if ( uart_is_readable ( UART_PC ) )
    {
        g_b_ucPcCommsFlag = true;
        g_aucRxBufferMaster [ g_uiRxBufferMasterPut ] = uart_getc ( UART_PC );  // Store character in buffer
        g_uiRxBufferMasterPut++;

        if ( P2P_BUFFER_MASTER_SIZE == g_uiRxBufferMasterPut )
        {
            g_uiRxBufferMasterPut = 0; // At end wrap to beginning
        }

        if ( UART_UARTRSR_FE_BITS == ( uart_get_hw ( UART_PC ) -> rsr ) )
        {
            // Clear framing error
            hw_clear_bits ( &uart_get_hw ( UART_PC ) -> rsr , UART_UARTRSR_FE_BITS );
        }

        if ( UART_UARTRSR_OE_BITS == ( uart_get_hw ( UART_PC ) -> rsr ) )
        {
            // Clear overrun error
            hw_clear_bits ( &uart_get_hw ( UART_PC ) -> rsr , UART_UARTRSR_OE_BITS );
        }
    }

    else if ( uart_is_readable ( UART_SEN ) )
    {
        g_b_ucSensorCommsFlag = true;
        g_aucRxBufferSlave [ g_uiRxBufferSlavePut++ ] = uart_getc ( UART_SEN ); // Store character in buffer

        if ( P2P_BUFFER_SLAVE_SIZE == g_uiRxBufferSlavePut )
        {
            g_uiRxBufferSlavePut = 0; // At end wrap to beginning
        }

        if ( UART_UARTRSR_FE_BITS == ( uart_get_hw ( UART_SEN ) -> rsr ) )
        {
            // Clear framing error
            hw_clear_bits ( &uart_get_hw ( UART_SEN ) -> rsr , UART_UARTRSR_FE_BITS );
        }

        if ( UART_UARTRSR_OE_BITS == ( uart_get_hw ( UART_SEN ) -> rsr ) )
        {
            // Clear overrun error
            hw_clear_bits ( &uart_get_hw ( UART_SEN ) -> rsr , UART_UARTRSR_OE_BITS );
        }
    }

    else
    {
        // Nothing to do
    }
}

void main ( void )
{
    // Useful information for picotool
    bi_decl ( bi_program_description ( "RP2040 Premier" ) );

    // Initialise standard stdio types
    stdio_init_all ( );

    // Set up watchdog
    watchdog_enable ( WATCHDOG_MILLISECONDS , 1 );

    // Initialize all configured peripherals
    // Set up GPIO
    gpio_init    ( A0_PIN         );
    gpio_init    ( A1_PIN         );
    gpio_init    ( A2_PIN         );
    gpio_init    ( EN1_PIN        );
    gpio_init    ( EN2_PIN        );
    gpio_init    ( EN3_PIN        );
    gpio_init    ( LED_PICO_PIN   );
    gpio_init    ( LED_RED_PIN    );
    gpio_init    ( LED_YELLOW_PIN );
    gpio_init    ( RELAY_PIN      );
    gpio_set_dir ( A0_PIN         , GPIO_OUT );
    gpio_set_dir ( A1_PIN         , GPIO_OUT );
    gpio_set_dir ( A2_PIN         , GPIO_OUT );
    gpio_set_dir ( EN1_PIN        , GPIO_OUT );
    gpio_set_dir ( EN2_PIN        , GPIO_OUT );
    gpio_set_dir ( EN3_PIN        , GPIO_OUT );
    gpio_set_dir ( LED_PICO_PIN   , GPIO_OUT );
    gpio_set_dir ( LED_RED_PIN    , GPIO_OUT );
    gpio_set_dir ( LED_YELLOW_PIN , GPIO_OUT );
    gpio_set_dir ( RELAY_PIN      , GPIO_OUT );

    A0_LOW;
    A1_LOW;
    A2_LOW;
    EN1_LOW;
    EN2_LOW;
    EN3_LOW;
    LED_PICO_OFF;
    LED_RED_OFF;
    LED_YELLOW_OFF;
    RELAY_OFF;

    // Set up timer interrupts
    add_repeating_timer_ms (  10 , timer_counter_isr   , NULL , &timer_counter   );
    add_repeating_timer_ms ( 500 , timer_heartbeat_isr , NULL , &timer_heartbeat );

    // Set up UART hardware
    uart_init         ( UART_PC         , UART_BAUD_RATE );
    gpio_set_function ( UART_PC_RX_PIN  , GPIO_FUNC_UART );
    gpio_set_function ( UART_PC_TX_PIN  , GPIO_FUNC_UART );
    uart_init         ( UART_SEN        , UART_BAUD_RATE );
    gpio_set_function ( UART_SEN_RX_PIN , GPIO_FUNC_UART );
    gpio_set_function ( UART_SEN_TX_PIN , GPIO_FUNC_UART );
    // Set UART parameters
    uart_set_hw_flow      ( UART_PC  , false     , false              );    // Disable CTS / RTS
    uart_set_format       ( UART_PC  , DATA_BITS , STOP_BITS , PARITY );    // Data format
    uart_set_fifo_enabled ( UART_PC  , false                          );    // Turn off FIFO ( handled character by character )
    uart_set_hw_flow      ( UART_SEN , false     , false              );    // Disable CTS / RTS
    uart_set_format       ( UART_SEN , DATA_BITS , STOP_BITS , PARITY );    // Data format
    uart_set_fifo_enabled ( UART_SEN , false                          );    // Turn off FIFO ( handled character by character )
    // Set up UART_RX interrupt
    irq_set_exclusive_handler ( UART1_IRQ , uart_rx_isr  );
    irq_set_enabled           ( UART1_IRQ , true         );
    uart_set_irq_enables      ( UART_PC   , true , false );  // Enable UART interrupt ( RX only )
    irq_set_exclusive_handler ( UART0_IRQ , uart_rx_isr  );
    irq_set_enabled           ( UART0_IRQ , true         );
    uart_set_irq_enables      ( UART_SEN  , true , false );  // Enable UART interrupt ( RX only )

    g_b_ucPcCommsFlag     = false;
    g_b_ucSensorCommsFlag = false;
    memset ( g_SensorStatus , 0 , 24 );

    // Turn on power to sensors
    sleep_ms ( 500 );
    RELAY_ON;

    // Clear comms buffer on spurious characters
    g_uiRxBufferMasterGet = 0;
    g_uiRxBufferMasterPut = 0;
    g_uiRxBufferSlaveGet  = 0;
    g_uiRxBufferSlavePut  = 0;

    // NevadaNano warmup routine
    // 1. Wait at least 3 seconds from power up                                  g_SensorInstalled
    // 2. 0x41 - Read Version number ( only respond after 3 seconds ? )          1
    // 3. 0x61 - Start continuous measurement ( if 0x41 responds with no fault ) 2
    // 4. Wait at least 2 seconds for first measurement cycle to complete
    // 5. 0x01 - Request full data string ( 'ANSWER' )

    // Infinite loop
    for ( ; ; )
    {
        watchdog_update ( );

        if ( g_uiRxBufferMasterPut )
        {
            forward_frame ( );
        }
        else
        {
            sleep_ms ( 100 );
        }
    }
}

uint8_t MakeString ( uint8_t* buffer )
{
    // uint8_t Address      = buffer [ 0 ];
    uint8_t StringLength = 0;

    // Request serial number on command or if sensor has not been identified yet
    if ( ( GET_SENSOR_SN == buffer [ 1 ] ) || ( SENSOR_NOT_DETECTED == g_SensorStatus [ buffer [ 0 ] ] ) )
    {
        StringLength = sizeof ( GetSensorSN );
        memcpy ( buffer , GetSensorSN , StringLength );
    }
    else if ( ( START_MEAS == buffer [ 1 ] ) || ( SENSOR_COMMS_GOOD == g_SensorStatus [ buffer [ 0 ] ] ) )
    {
        StringLength = sizeof ( StartMeas );
        memcpy ( buffer , StartMeas , StringLength );
    }
    else if ( ( GET_DATA_PACK == buffer [ 1 ] ) || ( SENSOR_CONTINUOUS_MODE == g_SensorStatus [ buffer [ 0 ] ] ) )
    {
        StringLength = sizeof ( GetDataPack );
        memcpy ( buffer , GetDataPack , StringLength );
    }
    else
    {
        // Invalid command
        StringLength = 0;
    }

    return StringLength;
}

uint8_t read_frame ( uart_inst_t* uart , uint8_t* buffer )
{
    absolute_time_t Start   = get_absolute_time();
    uint8_t  BufferTemp [ P2P_BUFFER_MASTER_SIZE ] = { 0 };
    uint8_t  i              = 0;
    uint8_t  Timeout_ms     = 50;  // 1.5 char times ~0.4ms at 38400 baud
    uint16_t CRC_Received   = 0;
    uint16_t CRC_Calculated = 0;
    
    for ( ; ; )
    {
        if ( ( UART_PC == uart ) && ( g_uiRxBufferMasterPut != i ) )
        {
            buffer [ i ] = g_aucRxBufferMaster [ i ];
            i++;
            Start = get_absolute_time ( );  // Reset timeout
        }
        else if ( ( UART_SEN == uart ) && ( g_uiRxBufferSlavePut != i ) )
        {
            buffer [ i ] = g_aucRxBufferSlave [ i ];
            i++;
            Start = get_absolute_time ( );  // Reset timeout
        }
        else if ( Timeout_ms < ( absolute_time_diff_us ( Start , get_absolute_time ( ) ) / 1000 ) )
        {
            break;
        }
        else
        {
            // Nothing to do
        }
    }

    if ( 2 > i )    // Valid messages must be at least 2 bytes
    {
        return 0;
    }
    else
    {
        // Nothing to do
    }

    if ( UART_PC == uart )
    {
        CRC_Received   = 1;
        CRC_Calculated = 1;
    }
    else if ( UART_SEN == uart )
    {
        memcpy ( BufferTemp , buffer , i );
        CRC_Received     = BufferTemp [ 4 ] | ( BufferTemp [ 5 ] << 8 );
        BufferTemp [ 4 ] = 0;
        BufferTemp [ 5 ] = 0;
        CRC_Calculated   = crc16 ( CRC16_INIT_REM , crc16Table , BufferTemp , i );
    }

    if ( CRC_Received != CRC_Calculated )
    {
        return 0;   // Invalic CRC
    }
    else
    {
        // Nothing to do
    }

    return i;   // Success
}

// CRC Calculation ( MODBUS CRC16 )
uint16_t crc16 ( uint16_t crc , const uint16_t *table , uint8_t *buffer , uint8_t length )  //, uint16_t startValue)
{
    // uint16_t crc;
    // uint8_t *p;
    // int ii;
    // crc = CRC16_START_VALUE;

    // for( p = buffer , ii = 0 ; ii < length ; ii++ )
    while ( length-- )
    {
        crc = ( uint16_t ) ( ( crc << 8 ) ^ table [ ( crc >> 8 ) ^ *buffer++ ] );
    }

    return ( uint16_t ) ( crc ^ CRC16_FINAL_XOR );
}
/*
uint16_t crc16 ( uint16_t crc , const uint16_t *table , uint8_t* buffer , uint8_t length )
{
    length -= 3;    // Last 3 bytes are CRC and TAIL so do not use in calculation 

    while ( length-- )
    {
        crc = table [ ( ( crc >> 8 ) ^ *buffer++ ) ] ^ ( crc << 8 );
    }

    return ( crc ^ CRC16_FINAL_XOR );
}
*/
void forward_frame ( void )
{
    absolute_time_t Start = 0;
    uint8_t  PC_Buffer  [ P2P_BUFFER_MASTER_SIZE ];
    uint8_t  SEN_Buffer [ P2P_BUFFER_MASTER_SIZE ];
    uint8_t  i        = 0;
    uint8_t  Address  = 0;
    uint8_t  Response = 0;

    Response = read_frame ( UART_PC , PC_Buffer ); // String from PC, message for sensor prepended with MUX address

    if ( 0 == Response )
    {
        send_exception ( 0 , 0 , 0x03 );    // Invalid CRC
        return;
    }

    Address = PC_Buffer [ 0 ];
    if ( ( 1 > Address ) || ( 24 < Address ) )
    {
        send_exception ( Address , PC_Buffer [ 1 ] , 0x02 );  // Invalid MUX address
        memset ( PC_Buffer  , 0 , sizeof ( PC_Buffer  ) );
        memset ( SEN_Buffer , 0 , sizeof ( SEN_Buffer ) );
        g_uiRxBufferMasterPut = 0;
        g_uiRxBufferSlavePut  = 0;
        return;
    }

    Response = MakeString ( PC_Buffer );
    MUX_Set ( Address );
    sleep_ms ( 10 );    // Settling delay

    memset ( SEN_Buffer , 0 , sizeof ( SEN_Buffer ) );
    g_uiRxBufferSlavePut = 0;

    for ( i = 0 ; i < Response ; i++ )
    {
        uart_putc_raw ( UART_SEN , PC_Buffer [ i ] );
        g_b_ucPcCommsFlag = true;
    }

    memset ( PC_Buffer , 0 , sizeof ( PC_Buffer ) );
    g_uiRxBufferMasterPut = 0;

    // RX from sensor
    Response = 0;
    Start    = get_absolute_time();

    while ( absolute_time_diff_us ( Start , get_absolute_time ( ) ) < 500000 )  // Break on timeout or complete
    {
        sleep_us ( 100 );
        Response = read_frame ( UART_SEN , SEN_Buffer + 1 );    // Data string from sensor, position shifted to right to accommodate address byte
        if ( 0 != Response )
        {
            g_b_ucSensorCommsFlag = true;

            // if ( SEN_Buffer [ 1 ] == 0xFB ) // Valid HEAD byte
            // {
                SEN_Buffer [ 0 ] = Address;    // Replace sensor ID with MUX address
                if ( GET_SENSOR_SN == SEN_Buffer [ 1 ] )
                {
                    g_SensorStatus [ Address ] = SENSOR_COMMS_GOOD;
                }
                else if ( START_MEAS == SEN_Buffer [ 1 ] )
                {
                    g_SensorStatus [ Address ] = SENSOR_CONTINUOUS_MODE;
                }
                else
                {
                    // Nothing to do
                }

                for ( i = 0 ; i < ( Response + 1 ) ; i++ )
                {
                    uart_putc_raw ( UART_PC , SEN_Buffer [ i ] );
                    g_b_ucPcCommsFlag = true;
                }

                memset ( PC_Buffer  , 0 , sizeof ( PC_Buffer  ) );
                memset ( SEN_Buffer , 0 , sizeof ( SEN_Buffer ) );
                g_uiRxBufferMasterPut = 0;
                g_uiRxBufferSlavePut  = 0;
                return;
            // }
            // else
            // {
                // send_exception ( Address , PC_Buffer [ 1 ] , 0x04 );    // Operation failed
                // memset ( PC_Buffer  , 0 , sizeof ( PC_Buffer  ) );
                // memset ( SEN_Buffer , 0 , sizeof ( SEN_Buffer ) );
                // g_uiRxBufferMasterPut = 0;
                // g_uiRxBufferSlavePut  = 0;
                // return;
            // }
        }
        else
        {
            g_SensorStatus [ Address ] = SENSOR_NOT_DETECTED;
            memset ( PC_Buffer  , 0 , sizeof ( PC_Buffer  ) );
            memset ( SEN_Buffer , 0 , sizeof ( SEN_Buffer ) );
            g_uiRxBufferMasterPut = 0;
            g_uiRxBufferSlavePut  = 0;
        }
    }

    send_exception ( Address , PC_Buffer [ 1 ] , 0x0B );   // Timeout or no response
    memset ( PC_Buffer , 0 , sizeof ( PC_Buffer ) );
    memset ( SEN_Buffer , 0 , sizeof ( SEN_Buffer ) );
    g_uiRxBufferMasterPut = 0;
    g_uiRxBufferSlavePut  = 0;
}

void MUX_Set ( uint8_t sensor )
{
    switch ( sensor )
    {
        case 1:
            A2_LOW;
            A1_LOW;
            A0_LOW;
            EN1_HIGH;
            EN2_LOW;
            EN3_LOW;
        break;

        case 2:
            A2_LOW;
            A1_LOW;
            A0_HIGH;
            EN1_HIGH;
            EN2_LOW;
            EN3_LOW;
        break;

        case 3:
            A2_LOW;
            A1_HIGH;
            A0_LOW;
            EN1_HIGH;
            EN2_LOW;
            EN3_LOW;
        break;

        case 4:
            A2_LOW;
            A1_HIGH;
            A0_HIGH;
            EN1_HIGH;
            EN2_LOW;
            EN3_LOW;
        break;

        case 5:
            A2_HIGH;
            A1_LOW;
            A0_LOW;
            EN1_LOW;
            EN2_LOW;
            EN3_HIGH;
        break;

        case 6:
            A2_LOW;
            A1_LOW;
            A0_LOW;
            EN1_LOW;
            EN2_LOW;
            EN3_HIGH;
        break;

        case 7:
            A2_HIGH;
            A1_LOW;
            A0_LOW;
            EN1_HIGH;
            EN2_LOW;
            EN3_LOW;
        break;

        case 8:
            A2_HIGH;
            A1_LOW;
            A0_HIGH;
            EN1_HIGH;
            EN2_LOW;
            EN3_LOW;
        break;

        case 9:
            A2_HIGH;
            A1_HIGH;
            A0_LOW;
            EN1_HIGH;
            EN2_LOW;
            EN3_LOW;
        break;

        case 10:
            A2_HIGH;
            A1_HIGH;
            A0_HIGH;
            EN1_HIGH;
            EN2_LOW;
            EN3_LOW;
        break;

        case 11:
            A2_HIGH;
            A1_LOW;
            A0_HIGH;
            EN1_LOW;
            EN2_LOW;
            EN3_HIGH;
        break;

        case 12:
            A2_LOW;
            A1_LOW;
            A0_HIGH;
            EN1_LOW;
            EN2_LOW;
            EN3_HIGH;
        break;

        case 13:
            A2_LOW;
            A1_LOW;
            A0_LOW;
            EN1_LOW;
            EN2_HIGH;
            EN3_LOW;
        break;

        case 14:
            A2_LOW;
            A1_LOW;
            A0_HIGH;
            EN1_LOW;
            EN2_HIGH;
            EN3_LOW;
        break;

        case 15:
            A2_LOW;
            A1_HIGH;
            A0_LOW;
            EN1_LOW;
            EN2_HIGH;
            EN3_LOW;
        break;

        case 16:
            A2_LOW;
            A1_HIGH;
            A0_HIGH;
            EN1_LOW;
            EN2_HIGH;
            EN3_LOW;
        break;

        case 17:
            A2_HIGH;
            A1_HIGH;
            A0_LOW;
            EN1_LOW;
            EN2_LOW;
            EN3_HIGH;
        break;

        case 18:
            A2_LOW;
            A1_HIGH;
            A0_LOW;
            EN1_LOW;
            EN2_LOW;
            EN3_HIGH;
        break;

        case 19:
            A2_HIGH;
            A1_LOW;
            A0_LOW;
            EN1_LOW;
            EN2_HIGH;
            EN3_LOW;
        break;

        case 20:
            A2_HIGH;
            A1_LOW;
            A0_HIGH;
            EN1_LOW;
            EN2_HIGH;
            EN3_LOW;
        break;

        case 21:
            A2_HIGH;
            A1_HIGH;
            A0_LOW;
            EN1_LOW;
            EN2_HIGH;
            EN3_LOW;
        break;

        case 22:
            A2_HIGH;
            A1_HIGH;
            A0_HIGH;
            EN1_LOW;
            EN2_HIGH;
            EN3_LOW;
        break;

        case 23:
            A2_HIGH;
            A1_HIGH;
            A0_HIGH;
            EN1_LOW;
            EN2_LOW;
            EN3_HIGH;
        break;

        case 24:
            A2_LOW;
            A1_HIGH;
            A0_HIGH;
            EN1_LOW;
            EN2_LOW;
            EN3_HIGH;
        break;

        default:
            // Invalid number
            A2_LOW;
            A1_LOW;
            A0_LOW;
            EN1_LOW;
            EN2_LOW;
            EN3_LOW;
        break;
    }
}

void send_exception ( uint8_t address , uint8_t function_code , uint8_t code )
{
    uint8_t i = 0;
    uint8_t Frame [ 5 ];
    uint16_t CRC = 0;

    Frame [ 0 ] = address;
    Frame [ 1 ] = function_code | 0x80;
    Frame [ 2 ] = code;
    CRC = crc16 ( CRC16_INIT_REM , crc16Table , Frame , 5 );
    Frame [ 3 ] = CRC & 0xFF;
    Frame [ 4 ] = CRC >> 8;

    for ( i = 0 ; i < 5 ; i++ )
    {
        uart_putc_raw ( UART_PC , Frame [ i ] );
        g_b_ucPcCommsFlag = true;
    }
}

/* End of file ---------------------------------------------------------------*/
