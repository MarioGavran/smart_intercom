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

#define TOUCH_TIMEOUT 50U



typedef struct{
	uint16_t x;
	uint16_t y;
}touch_coordinates_t;

typedef enum{
	TOUCH_IDLE = 0x01U,
	TOUCH_TOUCHED = 0x02U,
	TOUCH_RELEASED = 0x04U
}touch_state_t;



extern touch_coordinates_t g_touch_coordinates;
extern EXTI_HandleTypeDef hexti_touch_YU;
extern volatile touch_state_t g_touch_state;


void adc_select_x(void);
void adc_select_y(void);
void adc_select_channel(uint16_t GPIO_Pin);
uint16_t adc_median_measurement(void);
uint16_t adc_mean_measurement(void);
touch_coordinates_t touch_read_coordinates();
void init_TOUCH_YU_as_interrupt(void);
void EXTI3_TOUCH_Callback();
void touch_init();
void touch_process();

uint16_t iir_filter(uint16_t x_in, bool reset);
uint16_t x_iir_filter(uint16_t x_in, bool reset);
uint16_t y_iir_filter(uint16_t x_in, bool reset);





#endif /* INC_TOUCH_DRIVER_H_ */
