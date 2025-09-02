/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include <hardware/pio_instructions.h>
#include <pico/stdlib.h>

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported function prototypes ----------------------------------------------*/
void BaudRate_Update ( uint16_t baudrate );
void Watchdog        ( void );

/* Exported defines ----------------------------------------------------------*/
// System setup
#define NOP                     pio_encode_nop ( )
#define WATCHDOG_MILLISECONDS   8000    // Maximum 8 300 ms
#define P2P_BUFFER_MASTER_SIZE  560
#define P2P_BUFFER_SLAVE_SIZE   560

// GPIO
#define A0_PIN              18
#define A1_PIN              19
#define A2_PIN              20
#define EN1_PIN             21
#define EN2_PIN             26
#define EN3_PIN             27
#define LED_PICO_PIN        25
#define LED_RED_PIN          7
#define LED_YELLOW_PIN       6
#define RELAY_PIN           22
#define UART_SEN_RX_PIN     16  // UART0_TX
#define UART_SEN_TX_PIN     17  // UART0_RX
#define UART_PC_RX_PIN       9  // UART1_RX
#define UART_PC_TX_PIN       8  // UART1_TX

#define A0_HIGH         gpio_put ( A0_PIN         , 1 )
#define A0_LOW          gpio_put ( A0_PIN         , 0 )
#define A1_HIGH         gpio_put ( A1_PIN         , 1 )
#define A1_LOW          gpio_put ( A1_PIN         , 0 )
#define A2_HIGH         gpio_put ( A2_PIN         , 1 )
#define A2_LOW          gpio_put ( A2_PIN         , 0 )
#define EN1_HIGH        gpio_put ( EN1_PIN        , 1 )
#define EN1_LOW         gpio_put ( EN1_PIN        , 0 )
#define EN2_HIGH        gpio_put ( EN2_PIN        , 1 )
#define EN2_LOW         gpio_put ( EN2_PIN        , 0 )
#define EN3_HIGH        gpio_put ( EN3_PIN        , 1 )
#define EN3_LOW         gpio_put ( EN3_PIN        , 0 )
#define LED_PICO_OFF    gpio_put ( LED_PICO_PIN   , 0 )
#define LED_PICO_ON     gpio_put ( LED_PICO_PIN   , 1 )
#define LED_RED_OFF     gpio_put ( LED_RED_PIN    , 0 )
#define LED_RED_ON      gpio_put ( LED_RED_PIN    , 1 )
#define LED_YELLOW_OFF  gpio_put ( LED_YELLOW_PIN , 0 )
#define LED_YELLOW_ON   gpio_put ( LED_YELLOW_PIN , 1 )
#define RELAY_OFF       gpio_put ( RELAY_PIN      , 0 )
#define RELAY_ON        gpio_put ( RELAY_PIN      , 1 )

// UART
#define DATA_BITS           8
#define PARITY              UART_PARITY_NONE
#define STOP_BITS           1
#define UART_SEN            uart0
#define UART_PC             uart1
#define UART_BAUD_RATE      38400
#define UART_BUFFER_LENGTH  500
#define UART_TIMEOUT        1000

#endif /* __MAIN_H */

/* End of file ---------------------------------------------------------------*/
