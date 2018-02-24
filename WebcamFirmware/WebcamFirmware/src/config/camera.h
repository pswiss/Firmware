/*
 * camera.h
 *
 * Created: 2/14/2018 9:07:19 PM
 *  Author: Wenjia
 
 camera.h contains
 Camera pin definitions
 Camera TWI parameters
 Camera function and variable declarations
 */ 


#ifndef CAMERA_H_
#define CAMERA_H_

#include <asf.h>

// Image sensor VSYNC pin.
#define OV7740_VSYNC_PIO	       OV_VSYNC_PIO
#define OV7740_VSYNC_ID		       OV_VSYNC_ID
#define OV7740_VSYNC_MASK              OV_VSYNC_MASK
#define OV7740_VSYNC_TYPE              OV_VSYNC_TYPE

// Image sensor Power pin.
#define OV_POWER_PIO                   OV_SW_OVT_PIO
#define OV_POWER_MASK                  OV_SW_OVT_MASK

/* TWI board defines. */
#define ID_BOARD_TWI                   ID_TWI0
#define BOARD_TWI                      TWI0
#define BOARD_TWI_IRQn                 TWI0_IRQn

/* SRAM board defines. */
#define CAP_DEST                       SRAM_BASE

/* LCD board defines. */
#define IMAGE_WIDTH                    (320UL)
#define IMAGE_HEIGHT                   (240UL)

// Image sensor data pin.
#define OV7740_DATA_BUS_PIO            OV_DATA_BUS_PIO

void vsync_handler(uint32_t ul_id, uint32_t ul_mask);

void init_vsync_interrupts(void);

void configure_twi(void);

void pio_capture_init(Pio *p_pio, uint32_t ul_id);

uint8_t pio_capture_to_buffer(Pio *p_pio, uint8_t *uc_buf, uint32_t ul_size);

void init_camera(void);

void configure_camera(void);

uint8_t start_capture(void);

uint8_t find_image_len(void);

uint8_t *g_p_uc_cap_dest_buf;

uint16_t g_us_cap_rows = IMAGE_HEIGHT;

uint16_t g_us_cap_line = (IMAGE_WIDTH * 2);

#endif /* CAMERA_H_ */