// Author: Petras Swissler
// Task 3
////////////////////////////////////////////////////////////////////////////////////////////////////
/* File: wifi.h
This file contains various #define statements that are used to define the specific configuration
of the pin used for wifi interfaceoiasjdfpijasdf
////////////////////////////////////////////////////////////////////////////////////////////////////
*/


#ifndef WIFI_H_
#define WIFI_H_

// boilerplate include
#include <asf.h>

// Include necessary libraries
#include <string.h>

// Pin Definitions
#define PIN_CTS 

// Interrupt configurations

// Communication Constants
#define BOARD_ID_USART             ID_USART0
#define BOARD_USART                USART0
#define BOARD_USART_BAUDRATE       115200
#define USART_Handler              USART0_Handler
#define USART_IRQn                 USART0_IRQn
#define ALL_INTERRUPT_MASK  0xffffffff



////////////////////////////////////////////////////////////////////////////////////////////////////
// Wifi Responses
#define wifiResponse00 'Command Not Found'


////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables


////////////////////////////////////////////////////////////////////////////////////////////////////
// function prototypes
void WIFI_USART_HANDLER(void);
void process_incoming_byte_wifi(uint8_t);
void wifi_command_response_handler(uint32_t, uint32_t);
void process_data_wifi (void);
void wifi_web_setup_handler(uint32_t, uint32_t);
void configure_usart_wifi(void);
void configure_wifi_comm_pin(void);
void configure_wifi_web_setup_pin(void);
void write_wifi_command(char* , uint8_t);
void write_image_to_file(void);

#endif /* WIFI_H_ */