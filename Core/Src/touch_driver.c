/*
 * touch_driver.c
 *
 *  Created on: Jan 4, 2022
 *      Author: enio
 */
#include "touch_driver.h"



touch_state_t g_touch_state = TOUCH_IDLE;
touch_coordinates_t g_touch_coordinates = {0};

static uint32_t touch_timer_start = 0;



/******************************************************
 * EXTI handler and configuration structures used for
 * defining TOUCH_YU pin that needs to change from
 * interrupt mode to ADC mode and vice versa.
******************************************************/
static EXTI_HandleTypeDef hexti_touch_YU = {
		.Line = EXTI_LINE_3,
		.PendingCallback = EXTI3_TOUCH_Callback
};

static EXTI_ConfigTypeDef extiConfig_touch_YU = {
		.Line = EXTI_LINE_3,
		.Mode = EXTI_MODE_INTERRUPT,
		.Trigger = EXTI_TRIGGER_FALLING,
		.GPIOSel = EXTI_GPIOA
};





/******************************************************
 *
******************************************************/
void adc_select_y(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	ADC_ChannelConfTypeDef sConfig = {0};

	GPIO_InitStruct.Pin = TOUCH_YU_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(TOUCH_YU_GPIO_Port, &GPIO_InitStruct);

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
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	ADC_ChannelConfTypeDef sConfig = {0};

	GPIO_InitStruct.Pin = TOUCH_XR_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(TOUCH_XR_GPIO_Port, &GPIO_InitStruct);


	sConfig.Channel = TOUCH_XR_ADC_CHANNEL;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
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
	uint16_t adc_values[5] = {0};

	// TOUCH_XR output-high
	HAL_GPIO_DeInit(TOUCH_XR_GPIO_Port, TOUCH_XR_Pin);
	GPIOA->MODER &= ~GPIO_MODER_MODER2_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER2_0;
	GPIOA->ODR |= TOUCH_XR_Pin;
	// TOUCH_XL output-low
	GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
	GPIOA->ODR &= ~TOUCH_XL_Pin;
	// TOUCH_YD inout-open
	GPIOA->MODER &= ~GPIO_MODER_MODER4_Msk;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD4_Msk;
	HAL_Delay(5);
	// TOUCH_YU as ADC
	adc_select_y();
	for(adc_cnt = 0; adc_cnt < 5; adc_cnt++)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 500);
		adc_values[adc_cnt] = HAL_ADC_GetValue(&hadc1);
	}
	qsort(adc_values,
			sizeof(adc_values)/sizeof(*adc_values),
			sizeof(*adc_values), comp
			);
	ret.x = adc_values[2];

	// TOUCH_YU output-high
	GPIOA->MODER &= ~GPIO_MODER_MODER3_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER3_0;
	GPIOA->ODR |= TOUCH_YU_Pin;
	// TOUCH_YD output-low
	GPIOA->MODER &= ~GPIO_MODER_MODER4_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER4_0;
	GPIOA->ODR &= ~TOUCH_YD_Pin;
	// TOUCH_XL input-open
	GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5_Msk;
	HAL_Delay(5);
	// TOUCH_XR as ADC
	HAL_GPIO_DeInit(TOUCH_XR_GPIO_Port, TOUCH_XR_Pin);
	adc_select_x();
	for(adc_cnt = 0; adc_cnt < 5; adc_cnt++)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 500);
		adc_values[adc_cnt] = HAL_ADC_GetValue(&hadc1);
	}
	qsort(adc_values,
			sizeof(adc_values)/sizeof(*adc_values),
			sizeof(*adc_values), comp);
	ret.y = adc_values[2];

	return ret;
}



/******************************************************
 *
******************************************************/
void init_TOUCH_YU_as_adc(void)
{
	// Disable interrupt on TOUCH_YU pin
	HAL_EXTI_ClearConfigLine(&hexti_touch_YU);
	HAL_NVIC_DisableIRQ(TOUCH_YU_EXTI_IRQn);

	// Init analog mode on TOUCH_YU pin
	adc_select_y();
}



/******************************************************
 *
******************************************************/
void init_TOUCH_YU_as_interrupt(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// TOUCH_YD as input-open
	GPIOA->MODER &= ~GPIO_MODER_MODER4_Msk;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD4_Msk;

	// TOUCH_XL output-low
	GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
	GPIOA->ODR &= ~TOUCH_XL_Pin;

	// TOUCH_XR output-low
	HAL_GPIO_DeInit(TOUCH_XR_GPIO_Port, TOUCH_XR_Pin);
	GPIOA->MODER &= ~GPIO_MODER_MODER2_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER2_0;
	GPIOA->ODR &= ~TOUCH_XR_Pin;

	// TOUCH_YU as interrupt input
	HAL_GPIO_DeInit(TOUCH_YU_GPIO_Port, TOUCH_YU_Pin);
	GPIO_InitStruct.Pin = TOUCH_YU_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	HAL_EXTI_SetConfigLine(&hexti_touch_YU, &extiConfig_touch_YU);
	HAL_NVIC_SetPriority(TOUCH_YU_EXTI_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TOUCH_YU_EXTI_IRQn);
}




/******************************************************
 *
******************************************************/
void EXTI3_TOUCH_Callback()
{
	init_TOUCH_YU_as_adc();
	g_touch_state = TOUCH_TOUCHED;
	touch_timer_start = HAL_GetTick();
}



/******************************************************
 *
******************************************************/
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


/******************************************************
 *
******************************************************/
void touch_process()
{
	switch(g_touch_state)
	{
	case TOUCH_IDLE:
		g_touch_coordinates.x = 0;
		g_touch_coordinates.y = 0;
		break;

	case TOUCH_TOUCHED:
		if(HAL_GetTick() - touch_timer_start < TOUCH_TIMEOUT)
		{
			g_touch_coordinates = touch_read_coordinates();
		}
		else
		{
			g_touch_state = TOUCH_RELEASED;
		}
		break;

	case TOUCH_RELEASED:
		init_TOUCH_YU_as_interrupt();
		g_touch_state = TOUCH_IDLE;
		break;
	}
}

