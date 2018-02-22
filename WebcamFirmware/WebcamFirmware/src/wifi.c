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


// Variables for wifi communications
volatile uint32_t recieved_byte_wifi = 0;
volatile bool new_rx_wifi = false;
volatile uint8_t buffer_wifi[MAX_INPUT_WIFI];
volatile uint32_t input_pos_wifi = 0;


/////////////////////////////////////////////////////////////////////
/*
Handler for incoming data from the WiFi. Should call
process incoming byte wifi when a new byte arrives
*/
void WIFI_USART_HANDLER(void) 
{
	uint32_t ul_status;
	
	/* Read USART status. */
	ul_status = usart_get_status(BOARD_USART);

	/* Receive buffer is full. */
	if (ul_status & US_CSR_RXBUFF) {
		usart_read(BOARD_USART, &recieved_byte_wifi);
		new_rx_wifi = true;
		process_incoming_byte_wifi((uint8_t)recieved_byte_wifi);
	}
}



/*
Stores every incoming byte (in byte) from the AMW136 in a buffer.
*/
void process_incoming_byte_wifi(uint8_t in_byte) 
{
	buffer_wifi[input_pos_wifi] = in_byte;
	input_pos_wifi++;
}


/*
Handler for command complete rising-edge interrupt from AMW136.
When this is triggered, it is time to process the response of the AMW136.
*/
void wifi_command_response_handler(uint32_t ul_id, uint32_t ul_mask) 
{
	unused(ul_id);
	unused(ul_mask);

	process_data_wifi();
	
	// reset the buffer
	input_pos_wifi = 0;
	for(uint32_t ii = 0 ;ii < MAX_INPUT_WIFI; ii++){
		buffer_wifi[ii] = 0;
	}
	
}

/*
Processes the response of the AMW136, which should be stored in the buffer
filled by process incoming byte wifi. This processing should be looking for certain
responses that the AMW136 should give, such as start transfer when it is ready to
receive the image.
*/
void process_data_wifi (void) 
{
	// Compare the recieved string with some other string
	if(strstr(buffer_wifi, "StringToCompare")){
		// Do something
	}
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
	// Configure the RX / TX pins
	/* Configure USART RXD pin */
	gpio_configure_pin(PIN_USART0_RXD_IDX, PIN_USART0_RXD_FLAGS);
	/* Configure USART TXD pin */
	gpio_configure_pin(PIN_USART0_TXD_IDX, PIN_USART0_TXD_FLAGS);
	/* Configure USART CTS pin */
	gpio_configure_pin(PIN_USART0_CTS_IDX, PIN_USART0_CTS_FLAGS);
	/* Configure USART RTS pin */
	gpio_configure_pin(PIN_USART0_RTS_IDX, PIN_USART0_RTS_FLAGS);
	
	// might just pull wifi_cts low

	
	
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

	usart_enable_interrupt(BOARD_USART, US_IER_RXRDY);

	/* Configure and enable interrupt of USART. */
	NVIC_EnableIRQ(USART_IRQn);
	
	
}

/*
Configuration of command complete rising-edge interrupt.
*/
void configure_wifi_comm_pin(void) 
{
	/* Configure PIO clock. */
	
	pmc_enable_periph_clk(WIFI_COM_COMPLETE_ID);
	
	/* Adjust PIO debounce filter using a 10 Hz filter. */
	pio_set_debounce_filter(WIFI_COM_COMPLETE_PIO, WIFI_COM_COMPLETE_MSK, 10);

	/* Initialize PIO interrupt handler, see PIO definition in conf_board.h
	**/
	pio_handler_set(WIFI_COM_COMPLETE_PIO, WIFI_COM_COMPLETE_ID, WIFI_COM_COMPLETE_MSK,
			WIFI_COM_COMPLETE_ATTR, wifi_command_response_handler);

	/* Enable PIO controller IRQs. */
	NVIC_EnableIRQ((IRQn_Type)WIFI_COM_COMPLETE_ID);

	/* Enable PIO interrupt lines. */
	pio_enable_interrupt(WIFI_COM_COMPLETE_PIO, WIFI_COM_COMPLETE_MSK);
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
	// send a message via USART:
	usart_write_line(BOARD_USART, "string to write\r\n");
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