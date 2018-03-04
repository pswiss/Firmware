/*
 * camera.c
 *
 * Created: 2/14/2018 9:07:46 PM
 *  Author: Wenjia
 
 
 camera.c contains
 void vsync_handler(uint32_t ul_id, uint32_t ul_mask)
 void init_vsync_interrupts(void)
 void configure_twi(void);
 void pio_capture_init(Pio *p_pio, uint32_t ul_id)
 uint8_t pio_capture_to_buffer(Pio *p_pio, uint8_t *uc_buf, uint32_t ul_size)
 void init_camera(void)
 void configure_camera(void);
 uint8_t start_capture(void)
 ?uint8_t find_image_len(void)
 
 */ 

#include <camera.h>

//uint8_t *g_p_uc_cap_dest_buf;
volatile uint8_t g_p_uc_cap_dest_buf[IMAGE_BUFFER_SIZE];

//uint16_t g_us_cap_rows = IMAGE_HEIGHT;

//uint16_t g_us_cap_line = (IMAGE_WIDTH * 2);

volatile uint16_t g_us_cap_size = 40000;


/* Vsync signal information (true if it's triggered and false otherwise) */
static volatile uint32_t g_ul_vsync_flag = false;

/**
 * \brief Handler for vertical synchronisation using by the OV2640 image
 * sensor.
 */
void vsync_handler(uint32_t ul_id, uint32_t ul_mask)
{
	unused(ul_id);
	unused(ul_mask);
	
	g_ul_vsync_flag = true;
}

/**
 * \brief Intialize Vsync_Handler.
 */
void init_vsync_interrupts(void)
{
		/* Initialize PIO interrupt handler, see PIO definition in camera.h
	**/
	pio_handler_set(OV2640_VSYNC_PIO, OV2640_VSYNC_ID, OV2640_VSYNC_MASK,
			OV2640_VSYNC_TYPE, vsync_handler);

	/* Enable PIO controller IRQs */
	NVIC_EnableIRQ((IRQn_Type)OV2640_VSYNC_ID);
}

/**
void configure_twi(void);
this function is included in the init_camera function
*/
/* TWI clock frequency in Hz (400KHz) */
#define TWI_CLK     (400000UL)


/**
 * \brief Initialize PIO capture for the OV2640 image sensor communication.
 *
 * \param p_pio PIO instance to be configured in PIO capture mode.
 * \param ul_id Corresponding PIO ID.
 */
void pio_capture_init(Pio *p_pio, uint32_t ul_id)
{
		/* Enable periphral clock */
		pmc_enable_periph_clk(ul_id);

		/* Disable pio capture */
		p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_PCEN);

		/* Disable rxbuff interrupt */
		p_pio->PIO_PCIDR |= PIO_PCIDR_RXBUFF;

		/* 32bit width*/
		p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_DSIZE_Msk);
		p_pio->PIO_PCMR |= PIO_PCMR_DSIZE_WORD;

		/* Only HSYNC and VSYNC enabled */
		p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_ALWYS);
		p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_HALFS);

		#if !defined(DEFAULT_MODE_COLORED)
		/* Samples only data with even index */
		p_pio->PIO_PCMR |= PIO_PCMR_HALFS;
		p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_FRSTS);
		#endif
}


/**
 * \brief Capture OV2640 data to a buffer.
 *
 * \param p_pio PIO instance which will capture data from OV2640 iamge sensor.
 * \param p_uc_buf Buffer address where captured data must be stored.
 * \param ul_size Data frame size.
 */
uint8_t pio_capture_to_buffer(Pio *p_pio, uint8_t *uc_buf, uint32_t ul_size)
{
		/* Check if the first PDC bank is free */
		if ((p_pio->PIO_RCR == 0) && (p_pio->PIO_RNCR == 0)) {
			p_pio->PIO_RPR = (uint32_t)uc_buf;
			p_pio->PIO_RCR = ul_size;
			p_pio->PIO_PTCR = PIO_PTCR_RXTEN;
			return 1;
			} else if (p_pio->PIO_RNCR == 0) {
			p_pio->PIO_RNPR = (uint32_t)uc_buf;
			p_pio->PIO_RNCR = ul_size;
			return 1;
			} else {
			return 0;
		}
}


/**
 * \brief Initialize PIO capture and the OV2640 image sensor.
 */
void init_camera(void)
{
	twi_options_t opt;

	/* Init Vsync handler*/
	init_vsync_interrupts();

	gpio_configure_pin(TWI_DATA_GPIO,TWI0_DATA_FLAGS);
	gpio_configure_pin(TWI0_CLK_GPIO,TWI_CLK_FLAGS);

	gpio_configure_pin(PIN_PCK1,PIN_PCK1_FLAGS);
	gpio_configure_pin(PIN_PCK0,PIN_PCK0_FLAGS);

	//gpio_configure_pin(OV_SW_OVT_GPIO, OV_SW_OVT_FLAGS);
	//gpio_configure_pin(OV_RST_GPIO, OV_RST_FLAGS);
	gpio_configure_pin(OV_FSIN_GPIO, OV_FSIN_FLAGS);
	gpio_configure_pin(OV_HSYNC_GPIO, OV_HSYNC_FLAGS);
	gpio_configure_pin(OV_VSYNC_GPIO, OV_VSYNC_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D0, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D1, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D2, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D3, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D4, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D5, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D6, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D7, OV_DATA_BUS_FLAGS);

	/* Init PCK1 to work at 24 Mhz */
	/* 96/4=24 Mhz */
	/// PLLB is started at 96Mhz in main function and divided by 4 to 24Mhz to drive PCK1
	PMC->PMC_PCK[1] = (PMC_PCK_PRES_CLK_4 | PMC_PCK_CSS_PLLB_CLK);
	PMC->PMC_SCER = PMC_SCER_PCK1;
	while (!(PMC->PMC_SCSR & PMC_SCSR_PCK1)) {
	}

	

	/* Init PIO capture*/
	pio_capture_init(OV_DATA_BUS_PIO, OV_DATA_BUS_ID);

	/* Turn on ov2640 image sensor using power pin */
	//ov_power(true, OV_POWER_PIO, OV_POWER_MASK);
	/*camera will always be on, by setting pa20 high*/
	ioport_set_pin_level(pin_camera_ret,HIGH);


	/* Enable TWI peripheral */
	pmc_enable_periph_clk(ID_BOARD_TWI);

	/* Init TWI peripheral */
	opt.master_clk = sysclk_get_cpu_hz();
	opt.speed      = TWI_CLK;
	twi_master_init(BOARD_TWI, &opt);

	/* Configure TWI interrupts */
	NVIC_DisableIRQ(BOARD_TWI_IRQn);
	NVIC_ClearPendingIRQ(BOARD_TWI_IRQn);
	NVIC_SetPriority(BOARD_TWI_IRQn, 0);
	NVIC_EnableIRQ(BOARD_TWI_IRQn);

	/* ov2640 Initialization */
	while (ov_init(BOARD_TWI) == 1) {
	}

	/* ov2640 configuration */
	/*ov_configure(BOARD_TWI, QVGA_YUV422_20FPS);*/
	ov_configure(BOARD_TWI, JPEG_640x480);

	/* Wait 3 seconds to let the image sensor to adapt to environment */
	delay_ms(3000);
}

/*
void configure_camera(void);
this function is included in the init_camera function above
*/

uint8_t start_capture(void)
{
	
		/* Set capturing destination address*/
	//g_p_uc_cap_dest_buf = (uint8_t *)CAP_DEST;

	/* Set cap_rows value*/
	//g_us_cap_rows = IMAGE_HEIGHT;

	/* Enable vsync interrupt*/
	pio_enable_interrupt(OV2640_VSYNC_PIO, OV2640_VSYNC_MASK);

	/* Capture acquisition will start on rising edge of Vsync signal.
	 * So wait g_vsync_flag = 1 before start process
	 */
	while (!g_ul_vsync_flag) {
	}

	/* Disable vsync interrupt*/
	pio_disable_interrupt(OV2640_VSYNC_PIO, OV2640_VSYNC_MASK);

	/* Enable pio capture*/
	pio_capture_enable(OV2640_DATA_BUS_PIO);

	/* Capture data and send it to external SRAM memory thanks to PDC
	 * feature */
	/*pio_capture_to_buffer(OV2640_DATA_BUS_PIO, g_p_uc_cap_dest_buf,
			(g_us_cap_line * g_us_cap_rows) >> 2);
*/
	pio_capture_to_buffer(OV2640_DATA_BUS_PIO, g_p_uc_cap_dest_buf,
	(g_us_cap_size) >> 2);
	
	/* Wait end of capture*/
	while (!((OV2640_DATA_BUS_PIO->PIO_PCISR & PIO_PCIMR_RXBUFF) ==
			PIO_PCIMR_RXBUFF)) {
	}

	/* Disable pio capture*/
	pio_capture_disable(OV2640_DATA_BUS_PIO);

	/* Reset vsync flag*/
	g_ul_vsync_flag = false;
}

uint8_t find_image_len(void)
{
	int i=0;
	if(g_p_uc_cap_dest_buf[0]=='ff'& g_p_uc_cap_dest_buf[1]=='d8'){
		while(!(g_p_uc_cap_dest_buf[i]=='ff'& g_p_uc_cap_dest_buf[i+1]=='d9')){
			i++;
		}
		return(i+2);
	}
	else{
		return(0);
	}
}


