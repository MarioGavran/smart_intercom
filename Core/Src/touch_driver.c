/*
 * touch_driver.c
 *
 *  Created on: Jan 4, 2022
 *      Author: enio
 */
#include "touch_driver.h"



volatile touch_state_t g_touch_state = TOUCH_IDLE;
touch_coordinates_t g_touch_coordinates = {0};

static uint32_t touch_timer_start = 0;



/******************************************************
 * EXTI handler and configuration structures used for
 * defining TOUCH_YU pin that needs to change from
 * interrupt mode to ADC mode and vice versa.
******************************************************/
EXTI_HandleTypeDef hexti_touch_YU = {
		.Line = EXTI_LINE_3,
		.PendingCallback = EXTI3_TOUCH_Callback
};

EXTI_ConfigTypeDef extiConfig_touch_YU = {
		.Line = EXTI_LINE_3,
		.Mode = EXTI_MODE_INTERRUPT,
		.Trigger = EXTI_TRIGGER_FALLING,
		.GPIOSel = EXTI_GPIOA
};





/******************************************************
 * Select TOUCH_XR channel for ADC conversion
******************************************************/
void adc_select_x(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	ADC_ChannelConfTypeDef sConfig = {0};

	GPIO_InitStruct.Pin = TOUCH_XR_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
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
 * Select TOUCH_YU channel for ADC conversion
******************************************************/
void adc_select_y(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	ADC_ChannelConfTypeDef sConfig = {0};

	GPIO_InitStruct.Pin = TOUCH_YU_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
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
void adc_select_channel(uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	ADC_ChannelConfTypeDef sConfig = {0};
	GPIO_TypeDef *GPIO_Port;
	uint32_t ADC_Channel;

	switch(GPIO_Pin)
	{
	case TOUCH_XR_Pin:
		GPIO_Port = TOUCH_XR_GPIO_Port;
		ADC_Channel = TOUCH_XR_ADC_CHANNEL;
		break;
	case TOUCH_YU_Pin:
		GPIO_Port = TOUCH_YU_GPIO_Port;
		ADC_Channel = TOUCH_YU_ADC_CHANNEL;
		break;
	default:
		GPIO_Port = TOUCH_YU_GPIO_Port;
		ADC_Channel = TOUCH_YU_ADC_CHANNEL;
		break;
	}

	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIO_Port, &GPIO_InitStruct);

	sConfig.Channel = ADC_Channel;
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
uint16_t adc_median_measurement(void)
{
	uint8_t adc_cnt = 0;
	uint16_t adc_values[11] = {0};

	for(adc_cnt = 0; adc_cnt < 11; adc_cnt++)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 500);
		adc_values[adc_cnt] = HAL_ADC_GetValue(&hadc1);
	}
	qsort(adc_values,
			sizeof(adc_values)/sizeof(*adc_values),
			sizeof(*adc_values), comp);
	return adc_values[7];
}


/////
uint16_t x_adc_iir_measurement()
{
	uint8_t adc_cnt = 0;
	uint16_t adc_values[11] = {0};

	for(adc_cnt = 0; adc_cnt < 11; adc_cnt++)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 500);
		adc_values[adc_cnt] = x_iir_filter(HAL_ADC_GetValue(&hadc1), false);
	}

	x_iir_filter(0, true);

	return adc_values[7];
}


/////
uint16_t y_adc_iir_measurement()
{
	uint8_t adc_cnt = 0;
	uint16_t adc_values[11] = {0};

	for(adc_cnt = 0; adc_cnt < 11; adc_cnt++)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 500);
		adc_values[adc_cnt] = y_iir_filter(HAL_ADC_GetValue(&hadc1), false);
	}

	y_iir_filter(0, true);

	return adc_values[7];
}



/******************************************************
 *
******************************************************/
uint16_t adc_mean_measurement(void)
{
	uint8_t adc_cnt = 0;
	uint16_t adc_value = 0;

	for(adc_cnt = 0; adc_cnt < 20; adc_cnt++)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 500);
		adc_value += HAL_ADC_GetValue(&hadc1);
	}
	adc_value /= 20;

	return adc_value;
}



/******************************************************
 * Reconfigures TOUCH pins to measure x and y ADC
 * channels. The pin configuration for measuring x or y
 * channel and pin assignment is shown in the table
 * below.
 * Returns touch_coordinates_t type parameter with
 * median value of 5 consecutive measurements.
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
	uint32_t ret_x = 0;
	uint32_t ret_y = 0;

	// TOUCH_XR output-high
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
	//HAL_Delay(5);

	// TOUCH_YU as ADC
	adc_select_y();

	for(int i=0; i<20; i++)
		ret_y += y_adc_iir_measurement();
	ret.y = ret_y / 20;

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
	//HAL_Delay(5);

	// TOUCH_XR as ADC
	adc_select_x();

	for(int i=0; i<20; i++)
		ret_x += x_adc_iir_measurement();
	ret.x = ret_x / 20;

	return ret;
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
	GPIOA->MODER &= ~GPIO_MODER_MODER2_Msk;
	GPIOA->MODER |= GPIO_MODER_MODER2_0;
	GPIOA->ODR &= ~TOUCH_XR_Pin;

	// TOUCH_YU as interrupt input
	GPIO_InitStruct.Pin = TOUCH_YU_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Clear PR flag occurring during TOUCHED state
	HAL_EXTI_ClearPending(&hexti_touch_YU, EXTI_TRIGGER_RISING_FALLING);

	// Enable interrupt on YU
	HAL_EXTI_SetConfigLine(&hexti_touch_YU, &extiConfig_touch_YU);
	HAL_NVIC_SetPriority(TOUCH_YU_EXTI_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TOUCH_YU_EXTI_IRQn);
	HAL_EXTI_ClearPending(&hexti_touch_YU, EXTI_TRIGGER_RISING_FALLING);
}




/******************************************************
 * EXTI IRQ callback
******************************************************/
void EXTI3_TOUCH_Callback()
{
	// Disable interrupt on TOUCH_YU pin
	HAL_EXTI_ClearPending(&hexti_touch_YU, EXTI_TRIGGER_RISING_FALLING);
	HAL_EXTI_ClearConfigLine(&hexti_touch_YU);
	HAL_NVIC_ClearPendingIRQ(TOUCH_YU_EXTI_IRQn);
	HAL_NVIC_DisableIRQ(TOUCH_YU_EXTI_IRQn);
	// Init analog mode on TOUCH_YU pin
	adc_select_y();
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

	// Clear PR flag raised by configuring TOUCH_YD pin
	// to output-low during GPIO initialization at startup
	HAL_EXTI_ClearPending(&hexti_touch_YU, EXTI_TRIGGER_RISING_FALLING);

	// Enable interrupt
	HAL_EXTI_SetConfigLine(&hexti_touch_YU, &extiConfig_touch_YU);
	HAL_NVIC_SetPriority(TOUCH_YU_EXTI_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TOUCH_YU_EXTI_IRQn);
}

char buff_test[17] = {0};
/******************************************************
 * Simple state machine with IDLE, TOUCHED and RELEASED
 * states.
 *
 * IDLE		-> IDLE		** by default
 * IDLE		-> TOUCHED	** by interrupt on YU
 * TOUCHED	-> RELEASED	** after timeout & release
 * TOUCHED	-> TOUCHED	** if touch not released
 * RELEASED	-> IDLE		** unconditionally
******************************************************/
void touch_process()
{
	touch_coordinates_t touch_coordinates = {0};

	switch(g_touch_state)
	{
	case TOUCH_IDLE:
		//g_touch_coordinates.x = 0;
		//g_touch_coordinates.y = 0;
		break;

	case TOUCH_TOUCHED:
		g_touch_coordinates = touch_read_coordinates();
		//if(touch_coordinates.x < 4390)
			//g_touch_coordinates = touch_coordinates;

		// TOUCH_XL output-low
		GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;
		GPIOA->MODER |= GPIO_MODER_MODER5_0;
		GPIOA->ODR &= ~TOUCH_XL_Pin;

		uint16_t x_val = 0;

		for(int i=0; i<10; i++)
			x_val += x_adc_iir_measurement();

		x_val  /= 10;

		if(x_val < 10)
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




static const float a[3] =
{
		0.032, 0.063, 0.032
};

static const float b[3] =
{
		0, 1.592, -0.735
};


uint16_t iir_filter(uint16_t x_in, bool reset)
{
	static uint16_t x[3] = {0};
	static uint16_t y[3] = {0};

	uint16_t x_new = x_in;
	uint16_t y_new = 0;

	if(reset)
	{
		x[0] = 0; x[1] = 0; x[2] = 0;
		y[0] = 0; y[1] = 0; y[2] = 0;
		return 0;
	}

	x[2] = x[1];
	x[1] = x[0];
	x[0] = x_new;

	y[2] = y[1];
	y[1] = y[0];

	y_new = x[0]*a[0] + x[1]*a[1] + x[2]*a[2] +
			y[1]*b[1] + y[2]*b[2];

	y[0] = y_new;

	return y_new;
}

uint16_t x_iir_filter(uint16_t x_in, bool reset)
{
	static uint16_t x[3] = {0};
	static uint16_t y[3] = {0};

	uint16_t x_new = x_in;
	uint16_t y_new = 0;

	if(reset)
	{
		x[0]=0; x[2]=0; x[2]=0;
		y[0]=0; y[1]=0; y[2]=0;
		return 0;
	}

	x[2] = x[1];
	x[1] = x[0];
	x[0] = x_new;

	y[2] = y[1];
	y[1] = y[0];

	y_new = x[0]*a[0] + x[1]*a[1] + x[2]*a[2] +
			y[1]*b[1] + y[2]*b[2];

	y[0] = y_new;

	return y_new;
}

uint16_t y_iir_filter(uint16_t x_in, bool reset)
{
	static uint16_t x[3] = {0};
	static uint16_t y[3] = {0};

	uint16_t x_new = x_in;
	uint16_t y_new = 0;

	if(reset)
	{
		x[0]=0; x[2]=0; x[2]=0;
		y[0]=0; y[1]=0; y[2]=0;
		return 0;
	}

	x[2] = x[1];
	x[1] = x[0];
	x[0] = x_new;

	y[2] = y[1];
	y[1] = y[0];

	y_new = x[0]*a[0] + x[1]*a[1] + x[2]*a[2] +
			y[1]*b[1] + y[2]*b[2];

	y[0] = y_new;

	return y_new;
}

