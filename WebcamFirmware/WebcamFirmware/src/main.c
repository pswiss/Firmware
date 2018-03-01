// Include necessary libraries
#include <asf.h>
#include "wifi.h"
#include "camera.h"
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
	
	//initialize camera and start capture
	init_camera();
	start_capture();
	
	ioport_set_pin_level(PIN_WIFI_RESET,LOW); //reset WIFI
	delay_ms(50);
	ioport_set_pin_level(PIN_WIFI_RESET,HIGH); //turn Wifi Back on
	
	while(ioport_get_pin_level(PIN_WIFI_RESET)==0){
		if(wifi_setup_flag == true){
			ioport_set_pin_level(PUSH_BUTTON,LOW);
			wifi_setup_flag = false;
		}
	}
	
			
	while(1){
		if(wifi_setup_flag == true){
			ioport_set_pin_level(PUSH_BUTTON,LOW);
			wifi_setup_flag = false;
		}
		else{
			int b = ioport_get_pin_level(PIN_WIFI_NETWORK_STATUS); //check if connected to a network
			if(b == 1){												//if yes, are there any open streams?
				write_wifi_command("streams",5);
				if(receivedMessage!=NO_MESSAGE){
					start_capture();
					write_image_to_file();
				}
				else{
					delay_ms(1000);
				}
			}
			else{
				ioport_set_pin_level(PIN_WIFI_RESET,LOW); //reset WIFI
				delay_ms(50);
				ioport_set_pin_level(PIN_WIFI_RESET,HIGH); //turn Wifi Back on
			}
		}	
	}
	
	
	//send the image to wifi if length is nonzero
	/*if(find_image_len()){
		//send image to wifi
	}*/
}
