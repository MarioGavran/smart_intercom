/*
 * app_main.h
 *
 *  Created on: Mar 8, 2021
 *      Author: Mario
 */

#ifndef INC_APP_MAIN_H_
#define INC_APP_MAIN_H_
#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <string.h>
#include "../Inc/main.h"
#include "../Inc/fsmc_driver.h"
#include "../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "uart_driver.h"
#include "i2c_driver.h"
#include "OV7670.h"


void app_main_init();
void app_main_loop();
void EXTI0_HREF_Callback();
void EXTI1_VSYNC_Callback();

extern char g_cam_gray_frame[];
extern int8_t g_person_score;

#ifdef __cplusplus
}
#endif

#endif /* INC_APP_MAIN_H_ */
