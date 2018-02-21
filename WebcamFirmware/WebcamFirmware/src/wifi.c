/*///////////////////////////////////////////////////////////////////
Authors: Petras Swissler, Sasha Portnova, Wenja Zhou
---------------------------------------------------------------------
wifi.c contains
?WiFi variable initializations.
?void WIFI USART HANDLER(void)
?void process incoming byte wifi(uint8 t in byte)
- void wifi command response handler(uint32 t ul id, uint32 t ul mask)
?void process data wifi (void)
?void wifi web setup handler(uint32 t ul id, uint32 t ul mask)
?void configure usart wifi(void)
?void configure wifi comm pin(void)
?void configure wifi web setup pin(void)
?void write wifi command(char* comm, uint8 t cnt)
?void write image to file(void)
//////////////////////////////////////////////////////////////////*/
#include "wifi.h"

volatile uint8_t buffer_wifi[5000];


/////////////////////////////////////////////////////////////////////
/*
Handler for incoming data from the WiFi. Should call
process incoming byte wifi when a new byte arrives
*/
void WIFI_USART_HANDLER(void) 
{

}



/*
Stores every incoming byte (in byte) from the AMW136 in a buffer.
*/
void process_incoming_byte_wifi(uint8_t in_byte) 
{
	
	
}


/*
Handler for command complete rising-edge interrupt from AMW136.
When this is triggered, it is time to process the response of the AMW136.
*/
void wifi_command_response_handler(uint32_t ul_id, uint32_t ul_mask) 
{
	
}

/*
Processes the response of the AMW136, which should be stored in the buffer
filled by process incoming byte wifi. This processing should be looking for certain
responses that the AMW136 should give, such as start transfer when it is ready to
receive the image.
*/
void process_data_wifi (void) 
{
	
}

/*
Handler for button to initiate web setup of AMW136. Should set a flag indicating a
request to initiate web setup
*/
void wifi_web_setup_handler(uint32_t ul_id, uint32_t ul_mask) 
{
	
}

/*
Configuration of USART port used to communicate with the AMW136.
*/
void configure_usart_wifi(void) 
{
	static uint32_t ul_sysclk;
	const sam_usart_opt_t usart_console_settings = {
		BOARD_USART_BAUDRATE,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		/* This field is only used in IrDA mode. */
		0
	};

	/* Get peripheral clock. */
	ul_sysclk = sysclk_get_peripheral_hz();

	/* Enable peripheral clock. */
	sysclk_enable_peripheral_clock(BOARD_ID_USART);

	/* Configure USART. */
	usart_init_hw_handshaking(BOARD_USART, &usart_console_settings, ul_sysclk);

	/* Disable all the interrupts. */
	usart_disable_interrupt(BOARD_USART, ALL_INTERRUPT_MASK);
	
	/* Enable TX & RX function. */
	usart_enable_tx(BOARD_USART);
	usart_enable_rx(BOARD_USART);

	/* Specify that stdout should not be buffered. */
#if defined(__GNUC__)
	setbuf(stdout, NULL);
#else
	/* Already the case in IAR's Normal DLIB default configuration: printf()
	 * emits one character at a time.
	 */
#endif

	/* Configure and enable interrupt of USART. */
	NVIC_EnableIRQ(USART_IRQn);
}

/*
Configuration of command complete rising-edge interrupt.
*/
void configure_wifi_comm_pin(void) 
{
	
}

/*
Configuration of button interrupt to initiate web setup.
*/
void configure_wifi_web_setup_pin(void) 
{
	
}

/*
Writes a command (comm) to the AMW136, and waits either for an acknowledgment
or a timeout. The timeout can be created by setting the global variable counts
to zero, which will automatically increment every second, and waiting while counts < cnt.
*/
void write_wifi_command(char* comm, uint8_t cnt) 
{
	
}

/*
Writes an image from the SAM4S8B to the AMW136. If the
length of the image is zero (i.e. the image is not valid), return. Otherwise, follow this protocol
(illustrated in Appendix B):
1. Issue the command “image transfer xxxx? where xxxx is replaced by the length of the
image you want to transfer.
2. After the AMW136 acknowledges that it received your command, start streaming the image.
3. After the image is done sending, the AMW136 should say “Complete? However, the “command complete?pin will not have a rising edge, so it will be hard to sense. You can still try
to sense it before moving on, or simply insert a slight delay
*/
void write_image_to_file(void) 
{
	
}