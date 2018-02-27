#include <asf.h>
#include "wifi.h"
#include "timer_interface.h"

int main (void)
{
	// boilerplate
	sysclk_init();
	wdt_disable(WDT);
	board_init();

	configure_tc();
	tc_start(TC0, 0);
	
	// Configure all of the wifi stuff
	configure_usart_wifi();
	configure_wifi_comm_pin();
	configure_wifi_web_setup_pin();
	
	//ioport_set_pin_level(PIN_WIFI_RESET,LOW); //reset WIFI

	
	while(1){
		write_image_to_file();
		delay_ms(5000);
	}
	
}
