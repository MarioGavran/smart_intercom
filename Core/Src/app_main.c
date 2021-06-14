/*
 * app_main.cpp
 *
 *  Created on: Jun 12, 2021
 *      Author: enio
 */




/*x42
 * app_main.c
 *
 *  Created on: Mar 8, 2021
 *      Author: Mario
 */
#include "../Inc/app_main.h"
#include "tensorflow/lite/micro/examples/person_detection/main_functions.h"

#define OV7670_RST_HIGH		HAL_GPIO_WritePin(OV7670_RST_GPIO_Port, OV7670_RST_Pin, GPIO_PIN_SET)
#define OV7670_RST_LOW		HAL_GPIO_WritePin(OV7670_RST_GPIO_Port, OV7670_RST_Pin, GPIO_PIN_RESET)

#define OV7670_FRAME_SIZE_VGA		640*480*2	// not enough RAM
#define OV7670_FRAME_SIZE_QVGA		320*240*2	// 153600
#define OV7670_FRAME_SIZE_QQVGA		160*120*2

#define OV7670_GRAY_SIZE			96*96




char cam_buff[OV7670_FRAME_SIZE_QVGA + 640] = {0};
char* g_cam_buff_temp = cam_buff;
char g_cam_gray_frame[96*96] = {0};

uint32_t g_offset = 0;
extern DMA_HandleTypeDef hdma_tim1_trig;
extern TIM_HandleTypeDef htim1;
uint8_t g_print_pic = 0;

int8_t g_person_score = 0;

//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~arena
void app_main_init()
{
	NT35510_Init();

	LCD_ClearScreen(0x7FFFU);
	LCD_SetDirection(HORIZONTAL_RIGHT);
	LCD_ClearScreen(0xffffU);

	// Draw frame:
	LCD_DrawLine(10, 10, 790, 10, 0xF800U,4);		// up
	LCD_DrawLine(10, 10, 10, 470, 0x07E0U,4);		// left
	LCD_DrawLine(790, 10, 790, 470, 0x001FU,4);		// right
	LCD_DrawLine(10, 470, 790, 470, 0xF800U,4);		// down


	//////////////////////////////////////////////////////////
	//HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	OV7670_RST_LOW;
	HAL_Delay(300);
	OV7670_RST_HIGH;
	HAL_Delay(300);

	///////////
	setMode(QVGA_RGB565);
	HAL_Delay(300);
	////////////

	TIM1->DIER |= TIM_DIER_TDE;// | TIM_DIER_TDE TIM_DIER_UDE;
	HAL_TIM_Base_Start(&htim1);

	HAL_NVIC_SetPriority(OV7670_VSYNC_EXTI_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(OV7670_VSYNC_EXTI_IRQn);
	//////////////////////////////////////////////////////////
}

//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~_Min_Stack_Size
void app_main_loop()
{
	uint8_t buff[10] = {0};
	//uint8_t i2cDatToSnd[5] = {0};
	//uint8_t i2cDatToRec[5] = {0};
	uint32_t milis = 0;
	uint32_t milis2 = 0;


	LCD_SetDirection(VERTICAL_UP);
	LCD_SetWindow(20, 20, 340-1, 260-1); // 320 x 240
	setup();

	int j,z,k = 0;

	while(1)
	{
		loop();
		sprintf(buff,"%d",g_person_score);
		LCD_PrintStr(20, 20, 0xffff, 0x0000, buff, 5);

		//uart_tx_process();
		//uart_rx_process();


		LCD_SetWindow(20 , 280, 20+96-1, 280+96-1); // 320 x 240
		for(j = 72; j <= 72 + 96; j++)
		{
			for(z = 112*2; z < 112*2 + 96*2; z+=2)
			{
				uint8_t gray =
						(((cam_buff[(j-1)*320*2+z] & 0xF8U) >> 3) +	//red
								(((cam_buff[(j-1)*320*2+z] & 0x07U) << 3) | ((cam_buff[(j-1)*320*2+z+1] & 0xC0U) >> 6)) +	//green
								((cam_buff[(j-1)*320*2+z+1] & 0x1FU))	//blue
						) / 3;

				uint16_t graysc =
						(((gray << 11) & 0xF800U) |
								((gray << 6) & 0x07C0U) |
								(gray & 0x001FU));

				g_cam_gray_frame[k] = gray;
				k++;
				if(k > OV7670_GRAY_SIZE)
					k = 0;

				FSMC_WR_DAT(graysc);
			}
		}

/*
		LCD_SetWindow(20, 20, 340-1, 260-1); // 320 x 240
		for(j = 0; j <= OV7670_FRAME_SIZE_QVGA - 2; j+=2)
		{
			//
			// Black & White Video
			//uint16_t gray =
			//		(((cam_buff[j] & 0xF8U) >> 3) +	//red
			//				(((cam_buff[j] & 0x07U) << 3) | ((cam_buff[j+1] & 0xC0U) >> 6)) +	//green
			//				((cam_buff[j+1] & 0x1FU))	//blue
			//		) / 3;
//
			//uint16_t graysc =
			//		(((gray << 11) & 0xF800U) |
			//		((gray << 6) & 0x07C0U) |
			//		(gray & 0x001FU));
			// FSMC_WR_DAT(graysc);


			// RRRRR GGGGGG BBBBB
			FSMC_WR_DAT(((cam_buff[j] << 8) & 0xFF00U) | (cam_buff[j+1] & 0x00FFU));
		}

		if(HAL_GetTick() > milis + 1000)
		{
			milis = HAL_GetTick();
			if(milis >= (0xFFFFFFFFU - 1000U))
			{
				milis = 0;
			}
			else
			{// every second
				//writeRegister(0x55, p++);
				//if ( p == 0xFF)
				//	p = 0;




				//sprintf(buff, "0x");
				//uint8_t dejta = i2c_read_reg(0x42, 0x0AU);
				//sprintf(buff + strlen(buff), "%02x", dejta);
				//dejta = i2c_read_reg(0x42, 0x0BU);
				//sprintf(buff + strlen(buff), "%02x", dejta);
				//uart_write(buff);
				//LCD_PrintStr(20, 20, 0, 0x841FU, buff, 5);
			}
		}
		if(HAL_GetTick() > milis2 + 5000)
		{
			milis2 = HAL_GetTick();
			if(milis2 >= (0xFFFFFFFFU - 5000U))
			{
				milis2 = 0;
			}
			else
			{
				//testPattern(p++);
				//if (p == 3)
				//	p=0;

				//uart_write("\r\n");
				//uart_write("bok\r\n");
			}
		}
*/
	}
}



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == OV7670_VSYNC_Pin)
		EXTI1_VSYNC_Callback();
	else if(GPIO_Pin == OV7670_HREF_Pin)
		EXTI0_HREF_Callback();
}



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
void EXTI0_HREF_Callback()
{	// Falling edge
	HAL_DMA_Abort(&hdma_tim1_trig);
	HAL_DMA_Start(&hdma_tim1_trig, (uint32_t) &(GPIOB->IDR), (uint32_t)(cam_buff + g_offset), 640);
	if(cam_buff + g_offset >= cam_buff + OV7670_FRAME_SIZE_QVGA - 640)//38080=38400-320
	{
		g_offset = 0;
	}
	else
	{
		g_offset += 640;
	}
}



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
void EXTI1_VSYNC_Callback()
{
	// Rising edge
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	if(OV7670_VSYNC_GPIO_Port->IDR & OV7670_VSYNC_Pin)
	{

		HAL_DMA_Abort(&hdma_tim1_trig);
		HAL_NVIC_DisableIRQ(OV7670_HREF_EXTI_IRQn);
	}
	// Falling edge
	else
	{
		HAL_NVIC_SetPriority(OV7670_HREF_EXTI_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(OV7670_HREF_EXTI_IRQn);
		HAL_DMA_Abort(&hdma_tim1_trig);
		HAL_DMA_Start(&hdma_tim1_trig, (uint32_t) &(GPIOB->IDR), (uint32_t)cam_buff, 640); // first line
		g_offset += 640;
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
}








