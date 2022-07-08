/*
 * touch_driver.h
 *
 *  Created on: Jan 4, 2022
 *      Author: enio
 */

#ifndef INC_TOUCH_DRIVER_H_
#define INC_TOUCH_DRIVER_H_

#include "stm32f413xx.h"
#include "adc.h"
#include "misc.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//ovo izbrisi
#include "fsmc_driver.h"
#include "uart_driver.h"



/**********************************************************************
 * IIR filer coefficients
**********************************************************************/
#define IIR_A0	0.032f
#define IIR_A1	0.063F
#define IIR_A2	0.032F

#define	IIR_B0	0F
#define IIR_B1	1.592F
#define IIR_B2	-0.735F



typedef struct{
	uint16_t x;
	uint16_t y;
}touch_coordinates_t;



typedef enum{
	TOUCH_IDLE = 0x01U,
	TOUCH_TOUCHED = 0x02U,
	TOUCH_RELEASED = 0x04U
}touch_state_t;



typedef enum{
	TOUCH_XR_PIN = TOUCH_XR_Pin,
	TOUCH_YU_PIN = TOUCH_YU_Pin
}touch_pin_t;



extern touch_coordinates_t g_touch_coordinates;
extern EXTI_HandleTypeDef hexti_touch_YU;
extern volatile touch_state_t g_touch_state;



void adc_select_channel(touch_pin_t GPIO_Pin);
uint16_t iir_filter(uint16_t in_new, uint16_t* iir_in, uint16_t* iir_out, bool reset);
uint16_t adc_iir_measurement(uint16_t* iir_in, uint16_t* iir_out);
touch_coordinates_t touch_read_coordinates();
void init_TOUCH_YU_as_interrupt(void);
void EXTI3_TOUCH_Callback();
void touch_init();
void touch_process();



#endif /* INC_TOUCH_DRIVER_H_ */
