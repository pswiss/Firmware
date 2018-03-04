
#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED


/** Enable Com Port. */
#define CONF_BOARD_UART_CONSOLE

//! [tc_define_peripheral]
/* Use TC Peripheral 0. */
#define TC             TC0
#define TC_PERIPHERAL  0
//! [tc_define_peripheral]

//! [tc_define_ch1]
/* Configure TC0 channel 1 as waveform output. */
#define TC_CHANNEL_WAVEFORM 1
#define ID_TC_WAVEFORM      ID_TC1
#define PIN_TC_WAVEFORM     PIN_TC0_TIOA1
#define PIN_TC_WAVEFORM_MUX PIN_TC0_TIOA1_MUX
//! [tc_define_ch1]

//! [tc_define_ch2]
/* Configure TC0 channel 2 as capture input. */
#define TC_CHANNEL_CAPTURE 2
#define ID_TC_CAPTURE ID_TC2
#define PIN_TC_CAPTURE PIN_TC0_TIOA2
#define PIN_TC_CAPTURE_MUX PIN_TC0_TIOA2_MUX
//! [tc_define_ch2]

//! [tc_define_irq_handler]
/* Use TC2_Handler for TC capture interrupt. */
#define TC_Handler  TC2_Handler
#define TC_IRQn     TC2_IRQn
//! [tc_define_irq_handler]

#define PIN_WIFI_RESET				PIO_PB1_IDX	//WIFI_RESET PIN
#define PIN_WIFI_NETWORK_STATUS		PIO_PA11_IDX //Network Status Pin
#define PUSH_BUTTON					PIO_PA0_IDX //Web Setup Pin
#define WIFI_COM_COMPLETE			PIO_PA12_IDX //Wifi Command Complete Pin

#endif /* CONF_BOARD_H_INCLUDED */