/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>


void board_init(void)
{
	// Configure the ioports
	ioport_init();
	ioport_set_pin_dir(PIN_WIFI_RESET,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_WIFI_RESET,HIGH);
}
