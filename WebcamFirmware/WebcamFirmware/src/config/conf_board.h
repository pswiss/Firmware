
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

#define WIFI_RESET PIO_PB1	//WIFI_RESET PIN
#define LED_PIN PIO_PA20_IDX //LED pin

#endif /* CONF_BOARD_H_INCLUDED */
<<<<<<< HEAD
=======
=======

/**
 * \file
 *
 * \brief User board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
>>>>>>> 35382b5780f20f8d3e3c3efb972b441692691d9c

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

#include <asf.h>

#endif // CONF_BOARD_H
//>>>>>>> 0af65929c79cc102d58e2b1b06ea417080552b0c
