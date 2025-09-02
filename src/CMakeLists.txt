
add_executable(NevadaNano_TestBed
        main.c
        )

pico_enable_stdio_uart(NevadaNano_TestBed 0)
pico_enable_stdio_usb(NevadaNano_TestBed 1)
        
# pull in common dependencies
target_link_libraries(NevadaNano_TestBed
        pico_stdlib
        hardware_adc
        hardware_dma
        hardware_i2c
        hardware_pio
        hardware_spi
        hardware_watchdog
        hardware_uart
        hardware_irq
        hardware_sync
        )
        
# create map/bin/hex file etc.
pico_add_extra_outputs(NevadaNano_TestBed)
pico_add_hex_output(NevadaNano_TestBed)
pico_add_uf2_output(NevadaNano_TestBed)

include_directories(
	../inc
	)

## add url via pico_set_program_url
#//example_auto_set_url(adc)