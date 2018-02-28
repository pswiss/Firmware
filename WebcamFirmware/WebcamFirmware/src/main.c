#include <asf.h>
#include "wifi.h"
#include "camera.h"
#include "conf_board.h"

#include "timer_interface.h"

/** Timer counter frequency in Hz. */
#define TC_FREQ             1


static void configure_tc(void)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t ul_sysclk;

	/* Get system clock. */
	ul_sysclk = sysclk_get_cpu_hz();

	/* Configure PMC. */
	pmc_enable_periph_clk(ID_TC0);

	/** Configure TC for a 1Hz frequency and trigger on RC compare. */
	tc_find_mck_divisor(TC_FREQ, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
	tc_init(TC0, 0, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC0, 0, (ul_sysclk / ul_div) / TC_FREQ);

	/* Configure and enable interrupt on RC compare. */
	NVIC_EnableIRQ((IRQn_Type) ID_TC0);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
}


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
		ioport_get_pin_level(PUSH_BUTTON)
		if(wifi_setup_flag == true){
			write_wifi_command('web setup',500);
			wifi_setup_flag = false;
		}
	}
	
			
	while(1){
		if(wifi_setup_flag == true){
			write_wifi_command('web setup',500);
			wifi_setup_flag = false;
		}
		else{
			int a = ioport_get_pin_level(PIN_WIFI_NETWORK_STATUS); //check if connected to a network
			if(a == 1){												//if yes, are there any open streams?
				// are there any open streams???
				//if yes, write_image_to_file();
				//if no, delay_ms(500)
			}
		}	
	}
	
	
	//send the image to wifi if length is nonzero
	if(find_image_len()){
		//send image to wifi
	}
}
