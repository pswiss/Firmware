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

// Interrupt configurations


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