// Include necessary libraries
#include <asf.h>
#include "wifi.h"
#include "camera.h"
#include "timer_interface.h"
#include "conf_clock.h"
#include "conf_board.h"

// Global variables because we're mechanical engineers
volatile uint32_t receivedMessage;


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
	
	
	ioport_set_pin_level(PIN_WIFI_RESET,LOW); //reset WIFI
	delay_ms(10);
	ioport_set_pin_level(PIN_WIFI_RESET,HIGH); //turn Wifi Back on
	
	
	
	//initialize camera and start capture
	
	//pmc_enable_pllack(7, 0x1,1);
	init_camera();

	//start_capture();

	while(ioport_get_pin_level(PIN_WIFI_NETWORK_STATUS)==LOW){
		if(wifi_setup_flag == true){
			
			write_wifi_command("setup web\r\n", 5);
			//ioport_set_pin_level(PUSH_BUTTON,LOW);
			wifi_setup_flag = false;
		}
	}
	
	
			
	while(1){
		if(wifi_setup_flag == true){
			write_wifi_command("setup web\r\n", 5);
			wifi_setup_flag = false;
		}
		else{
			bool wifiNetworkConnected = ioport_get_pin_level(PIN_WIFI_NETWORK_STATUS); //check if connected to a network
			if(wifiNetworkConnected == true){												//if yes, are there any open streams?
				char sendString[80];
				for(int ii = 0; ii<80; ii++){
					sendString[ii] = 0;
				}
				sprintf(sendString, "stream_poll 0\r\n");
				write_wifi_command(&sendString,5);
				if(receivedMessage!=COMMAND_FAILED){
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

				while(ioport_get_pin_level(PIN_WIFI_NETWORK_STATUS)==LOW){
					if(wifi_setup_flag == true){
						
						write_wifi_command("setup web\r\n", 5);
						//ioport_set_pin_level(PUSH_BUTTON,LOW);
						wifi_setup_flag = false;
					}
				}
			}
		}	
	}
}
