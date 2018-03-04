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
#include <camera.h>


void board_init(void)
{
	ioport_init();
	ioport_set_pin_dir(PIN_WIFI_RESET,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_WIFI_RESET,LOW);
	
	ioport_set_pin_dir(PIN_WIFI_NETWORK_STATUS,IOPORT_DIR_INPUT);
	//ioport_set_pin_level(PIN_WIFI_NETWORK_STATUS,LOW);
	
	ioport_set_pin_dir(PUSH_BUTTON,IOPORT_DIR_INPUT);
	//ioport_set_pin_level(PUSH_BUTTON,HIGH);
	
	ioport_set_pin_dir(WIFI_COM_COMPLETE,IOPORT_DIR_INPUT);
	//ioport_set_pin_level(WIFI_COM_COMPLETE,LOW);

	// Configure TWI Pins
	/*gpio_configure_pin(TWI_DATA_GPIO,TWI0_DATA_FLAGS);
	gpio_configure_pin(TWI0_CLK_GPIO,TWI_CLK_FLAGS);
	gpio_configure_pin(PIN_PCK0,PIN_PCK0_FLAGS);
	gpio_configure_pin(OV_SW_OVT_GPIO, OV_SW_OVT_FLAGS);
	gpio_configure_pin(OV_RST_GPIO, OV_RST_FLAGS);
	gpio_configure_pin(OV_FSIN_GPIO, OV_FSIN_FLAGS);
	gpio_configure_pin(OV_HSYNC_GPIO, OV_HSYNC_FLAGS);
	gpio_configure_pin(OV_VSYNC_GPIO, OV_VSYNC_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D2, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D3, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D4, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D5, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D6, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D7, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D8, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D9, OV_DATA_BUS_FLAGS);*/

}
