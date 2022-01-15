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



#define TOUCH_TIMEOUT 50U



typedef struct{
	uint16_t x;
	uint16_t y;
}touch_coordinates_t;

typedef enum{
	TOUCH_IDLE = 0,
	TOUCH_TOUCHED,
	TOUCH_RELEASED
}touch_state_t;



extern touch_coordinates_t g_touch_coordinates;
extern EXTI_HandleTypeDef hexti_touch_YU;



void adc_select_x(void);
void adc_select_y(void);
touch_coordinates_t touch_read_coordinates();
void init_TOUCH_YU_as_adc(void);
void init_TOUCH_YU_as_interrupt(void);
void EXTI3_TOUCH_Callback();
void touch_init();
void touch_process();




#endif /* INC_TOUCH_DRIVER_H_ */
