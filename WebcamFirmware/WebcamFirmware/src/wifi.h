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
#include "camera.h"

// Pin Definitions: USART
/** USART0 pin RX */
#define PIN_USART0_RXD    {PIO_PA5A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RXD_IDX        (PIO_PA5_IDX)
#define PIN_USART0_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin TX */
#define PIN_USART0_TXD    {PIO_PA6A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_TXD_IDX        (PIO_PA6_IDX)
#define PIN_USART0_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin CTS */
#define PIN_USART0_CTS    {PIO_PA8A_CTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_CTS_IDX        (PIO_PA8_IDX)
#define PIN_USART0_CTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin RTS */
#define PIN_USART0_RTS    {PIO_PA7A_RTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RTS_IDX        (PIO_PA7_IDX)
#define PIN_USART0_RTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)

// Communication Constants
#define BOARD_ID_USART				ID_USART0
#define BOARD_USART					USART0
#define BOARD_USART_BAUDRATE		115200
#define WIFI_USART_HANDLER			USART0_Handler
#define USART_IRQn					USART0_IRQn
#define ALL_INTERRUPT_MASK			0xffffffff
#define MAX_INPUT_WIFI				1000

// Command Complete Pin configuration: PA12
#define WIFI_COM_COMPLETE_ID		ID_PIOA
#define WIFI_COM_COMPLETE_PIO		PIOA
#define WIFI_COM_COMPLETE_MSK		PIO_PA12
#define WIFI_COM_COMPLETE_TYPE		PIO_INPUT
#define WIFI_COM_COMPLETE_ATTR		PIO_PULLUP | PIO_IT_RISE_EDGE
// removed: PIO_DEBOUNCE

// Wifi network connected pin configuration
//#define PIN_WIFI_NETWORK_STATUS		PIO_PA11_IDX

// Wifi Reset Pin
//#define PIN_WIFI_RESET PIO_PB1_IDX

// Wifi Setup Button Pin Configuration: PA0 on the breakout board
/* Push button pin configuration. */
#define PUSH_BUTTON_ID                 ID_PIOA
#define PUSH_BUTTON_PIO                PIOA
#define PUSH_BUTTON_PIN_MSK            PIO_PA0
// Use the edge interrupt mode to trigger on rise AND fall
#define PUSH_BUTTON_ATTR               PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_EDGE


////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables
volatile uint32_t received_byte_wifi;
volatile bool new_rx_wifi;
volatile uint8_t buffer_wifi[MAX_INPUT_WIFI];
volatile uint32_t input_pos_wifi;
volatile uint8_t counts;
// Variables: interrupt flag
volatile bool wifi_setup_flag;

volatile uint32_t uintreceivedMessage;
volatile uint8_t g_p_uc_cap_dest_buf[IMAGE_BUFFER_SIZE];


// Messages
#define NO_MESSAGE					0

#define NOT_CONNECTED				1
#define msg_NOT_CONNECTED			"Client not connected"

#define START_TRANSFER				2
#define msg_START_TRANSFER			"Start transfer"

#define TRANSFER_COMPLETE			3
#define msg_COMPLETE				"Complete"

#define CLIENT_NOT_CONNECTED		4
#define msg_CLIENT_NOT_CONNECTED	"Client not connected"

#define COMMAND_FAILED				5
#define msg_COMMAND_FAILED			"Command failed"


#define msg_WEBSOCKET_DISCONNECTED	"Websocket disconnected"
#define msg_UNKNOWN_COMMAND			"Unknown command"

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