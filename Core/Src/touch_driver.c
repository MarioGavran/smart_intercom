/*
 * touch_driver.c
 *
 *  Created on: Jan 4, 2022
 *      Author: enio
 */
#include "touch_driver.h"



touch_state_t g_touch_state = TOUCH_IDLE;
touch_coordinates_t g_touch_coordinates = {0};

/******************************************************
 *
******************************************************/
void adc_select_y(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = TOUCH_YU_ADC_CHANNEL;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
}



/******************************************************
 *
******************************************************/
void adc_select_x(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = TOUCH_XR_ADC_CHANNEL;
	sConfig.Rank = 1;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
}



/******************************************************
 *
 * __________________________________________
 * || function || X+   | X-   | Y+   | Y-   |
 * ==========================================
 * ||   PIN    || PA3  | PA4  | PA2  | PA5  |
 * ------------------------------------------
 * ||  read X  || adc  | open | high | low  |
 * ||  read Y  || high | low  | adc  | open |
 * ------------------------------------------
******************************************************/
touch_coordinates_t touch_read_coordinates()
{
	touch_coordinates_t ret = {0};
	uint8_t adc_cnt = 0;
	uint16_t adc_values = 0;//[5] = {0};

	// TOUCH_XR output-high
	GPIOA->MODER &= ~GPIO_MODER_MODER2_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER2_0;
	GPIOA->ODR |= GPIO_ODR_OD2;
	// TOUCH_XL output-low
	GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
	GPIOA->ODR &= ~TOUCH_XL_Pin;
	// TOUCH_YD inout-open
	GPIOA->MODER &= ~GPIO_MODER_MODER4_Msk;
	//HAL_Delay(5);
	// TOUCH_YU as ADC
	GPIOA->MODER |= GPIO_MODER_MODER3_Msk;
	for(adc_cnt = 0; adc_cnt < 5; adc_cnt++)
	{
		adc_select_y();
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 500);
		adc_values += HAL_ADC_GetValue(&hadc1);
	}
	adc_values = adc_values/5;
	//qsort(adc_values, sizeof(adc_values)/sizeof(*adc_values), sizeof(*adc_values), comp);
	ret.x = adc_values;//[2];

	// TOUCH_YU output-high
	GPIOA->MODER &= ~GPIO_MODER_MODER3_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER3_0;
	GPIOA->ODR |= GPIO_ODR_OD3;
	// TOUCH_YD output-low
	GPIOA->MODER &= ~GPIO_MODER_MODER4_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER4_0;
	GPIOA->ODR &= ~TOUCH_YD_Pin;
	// TOUCH_XL input-open
	GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;
	//HAL_Delay(5);
	// TOUCH_XR as ADC
	GPIOA->MODER |= GPIO_MODER_MODER2_Msk;//YU analog
	for(adc_cnt = 0; adc_cnt < 5; adc_cnt++)
	{
		adc_select_x();
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 500);
		adc_values += HAL_ADC_GetValue(&hadc1);
	}
	adc_values = adc_values / 5;
	//qsort(adc_values, sizeof(adc_values)/sizeof(*adc_values), sizeof(*adc_values), comp);
	ret.y = adc_values;//[2];

	return ret;
}



void init_TOUCH_YU_as_adc(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// Disable interrupt on TOUCH_YU pin
	HAL_NVIC_DisableIRQ(TOUCH_YU_EXTI_IRQn);

	// Init analog mode on TOUCH_YU pin
    GPIO_InitStruct.Pin = TOUCH_YU_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(TOUCH_YU_GPIO_Port, &GPIO_InitStruct);
}



void init_TOUCH_YU_as_interrupt(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// TOUCH_YD as input-open
	GPIOA->MODER &= ~GPIO_MODER_MODER4_Msk;

	// TOUCH_XL output-low
	GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
	GPIOA->ODR &= ~TOUCH_XL_Pin;

	// TOUCH_YU as interrupt input
	GPIO_InitStruct.Pin = TOUCH_YU_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(TOUCH_YU_EXTI_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TOUCH_YU_EXTI_IRQn);
}



void EXTI3_TOUCH_Callback()
{
	init_TOUCH_YU_as_adc();
	g_touch_state = TOUCH_TOUCHED;
}



void touch_init()
{
	// TOUCH_YD as input-open
	GPIOA->MODER &= ~GPIO_MODER_MODER4_Msk;

	// TOUCH_XL output-low
	GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
	GPIOA->ODR &= ~TOUCH_XL_Pin;

	// Enable interrupt
	HAL_NVIC_SetPriority(TOUCH_YU_EXTI_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TOUCH_YU_EXTI_IRQn);
}



void touch_process()
{
	switch(g_touch_state)
	{
	case TOUCH_IDLE:
		g_touch_coordinates.x = 0;
		g_touch_coordinates.y = 0;
		//g_touch_state = TOUCH_IDLE;
		break;

	case TOUCH_TOUCHED:
		//init_TOUCH_XR_as_adc();
		g_touch_coordinates = touch_read_coordinates();
		g_touch_state = TOUCH_RELEASED;
		break;

	case TOUCH_RELEASED:
		init_TOUCH_YU_as_interrupt();
		g_touch_state = TOUCH_IDLE;
		break;
	}
}

