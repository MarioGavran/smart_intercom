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
#include <stdlib.h>
#include "../Inc/main.h"
#include "../Inc/fsmc_driver.h"
#include "stm32f4xx_hal_gpio.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "adc.h"
#include "uart_driver.h"
#include "i2c_driver.h"
#include "ov7670.h"
#include "../ov7670_driver/Inc/OV7670.h"
#include "misc.h"
#include "tensorflow/lite/micro/examples/person_detection/main_functions.h"

#include "tensorflow/lite/micro/examples/person_detection/testdata/person_image_data.h"
#include "tensorflow/lite/micro/examples/person_detection/testdata/no_person_image_data.h"
#include <tensorflow/lite/micro/examples/person_detection/testdata/person_image_data1.h>

#include <feri_logo_image.h>
#include <ietk_logo_image.h>


void app_main_init();
void app_main_loop();
void tflite_micro_loop();
void tflite_micro_setup();

extern int8_t g_person_score;
extern int8_t g_no_person_score;



#ifdef __cplusplus
}
#endif

#endif /* INC_APP_MAIN_H_ */
