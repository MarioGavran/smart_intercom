/*
 * app_main.cpp
 *
 *  Created on: Jun 12, 2021
 *      Author: enio
 */
#include "../Inc/app_main.h"


int8_t g_person_score = 0;
int8_t g_no_person_score = 0;







//#define CMSIS_NN

//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
void tflite_micro_loop()
{
	loop();
}

//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
void tflite_micro_setup()
{
	setup();
}
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
void app_main_init()
{
	unsigned int l,ll = 0;

	NT35510_Init();

	LCD_ClearScreen(0xFFFFU);
	LCD_SetDirection(HORIZONTAL_RIGHT);

	//==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~
	// ~=~=~ FERI logo ~=~=~
	LCD_ClearScreen(0xFFFFU);
	LCD_SetWindow(240, 184, 240 + FERI_LOGO_IMG_W -1, 184 + FERI_LOGO_IMG_H -1);
	for(l = 0; l < FERI_LOGO_IMG_SIZE; l+=2)
	{
		FSMC_WR_DAT(((g_feri_logo_image[l] << 8) & 0xFF00U) | (g_feri_logo_image[l+1] & 0x00FFU));
	}
/*	HAL_Delay(1000);

	// IETK logo
	LCD_ClearScreen(0xFFFFU);
	LCD_SetWindow(310, 195, 310 + IETK_LOGO_IMG_W -1, 195 + IETK_LOGO_IMG_H -1);

	for(l = 0; l < IETK_LOGO_IMG_SIZE; l+=2)
	{
		FSMC_WR_DAT(((g_ietk_logo_image[l] << 8) & 0xFF00U) | (g_ietk_logo_image[l+1] & 0x00FFU));
	}
	HAL_Delay(1000);

	// ~=~=~ IETK logo slide ~=~=~
	for(ll = 0; ll <= 56; ll++)
	{
		// Print IETK logo
		LCD_SetWindow(310, 195 +ll, 310 + IETK_LOGO_IMG_W -1, 195 + IETK_LOGO_IMG_H + ll - 1);
		for(l = 0; l < IETK_LOGO_IMG_SIZE; l+=2)
		{
			FSMC_WR_DAT(((g_ietk_logo_image[l] << 8) & 0xFF00U) | (g_ietk_logo_image[l+1] & 0x00FFU));
		}
		HAL_Delay(20);
		// Slide 1 step
		LCD_SetWindow(310, 195 + ll, 310 + IETK_LOGO_IMG_W -1, 195 + 1 -1 + ll);
		// Clear
		for(l = 0; l < IETK_LOGO_IMG_W * 2; l+=2)
		{
			FSMC_WR_DAT(0xFFFFU);
		}
	}
	// ~=~=~ Add FERI logo at the end ~=~=~
	LCD_SetWindow(240, 140, 240 + FERI_LOGO_IMG_W -1, 140 + FERI_LOGO_IMG_H -1);
	for(l = 0; l < FERI_LOGO_IMG_SIZE; l+=2)
	{
		FSMC_WR_DAT(((g_feri_logo_image[l] << 8) & 0xFF00U) | (g_feri_logo_image[l+1] & 0x00FFU));
	}
	HAL_Delay(1000);
*/	LCD_SetWindow(0, 0, 799, 479);
	LCD_ClearScreen(0x1CFCU);
	//==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~==~~

	/*
	// Draw frame:
	LCD_DrawLine(10, 10, 790, 10, 0xF800U,4);		// up
	LCD_DrawLine(10, 10, 10, 470, 0x07E0U,4);		// left
	LCD_DrawLine(790, 10, 790, 470, 0x001FU,4);		// right
	LCD_DrawLine(10, 470, 790, 470, 0xF800U,4);		// down
	*/


	//ov7670_init1();
	//ov7670_test_pattern(2);


/*	OV7670_RST_LOW;
	HAL_Delay(300);
	OV7670_RST_HIGH;
	HAL_Delay(300);

	ov7670_initialization();*/

	ov7670_init1();
	HAL_Delay(300);

	TIM1->DIER |= TIM_DIER_TDE;
	HAL_TIM_Base_Start(&htim1);

	HAL_NVIC_SetPriority(OV7670_VSYNC_EXTI_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(OV7670_VSYNC_EXTI_IRQn);

	touch_init();

}



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
void app_main_loop()
{
	uint8_t buff[15] = {0};
	uint32_t milis = 0;
	uint32_t milis2 = 0;
	int i,j,z = 0;
	int k = -2;



	LCD_SetDirection(VERTICAL_UP);
	LCD_SetWindow(20, 20, 340-1, 260-1); // 320 x 240
	//tflite_micro_setup();

	while(1)
	{
		/*tflite_micro_loop();

		if(g_person_score < 0)
			sprintf(buff, "-");
		else
			sprintf(buff, "\n");
		sprintf(buff + strlen(buff), "%03d", abs(g_person_score));
		LCD_PrintStr(20, 400, 0xffff, 0x0000, buff, 5);

		if(g_no_person_score < 0)
			sprintf(buff, "-");
		else
			sprintf(buff, "\n");
		sprintf(buff + strlen(buff),"%03d",abs(g_no_person_score));
		LCD_PrintStr(20, 450, 0xffff, 0x0000, buff, 5);
*/
		uart_tx_process();
		uart_rx_process();
		touch_process();

		if((g_touch_coordinates.x != 0) && (g_touch_coordinates.y != 0) &&
				(g_touch_coordinates.x < 3100) && (g_touch_coordinates.y <= 3100))
		{
			sprintf(buff, "%04d, %04d", g_touch_coordinates.x, g_touch_coordinates.y);
			LCD_PrintStr(20, 480, 0, 0x841FU, buff, 4);
		}
/*
		LCD_SetWindow(20 , 280, 20+96-1, 280+96-1); // 320 x 240

		//-********************************************************************************************************************
		for(z = 0; z < 96*96*2; z+=2)
		{
			// Calculate gray-scale from RGB data
			char gray = (
					(((g_person_image_data1[z] & 0xF8U) >> 3) +													//red
					(((g_person_image_data1[z] & 0x07U) << 2) | ((g_person_image_data1[z+1] & 0xC0U) >> 6)) +	//green
					(((g_person_image_data1[z+1] & 0x1FU)))														//blue
					) / 3);

			// Assemble gray-scale into RGB565 format
			uint16_t graysc = (
					((gray << 11) & 0xF800U) |
					((gray << 6)  & 0x07C0U) |
					((gray << 0)  & 0x001FU));

			g_cam_gray_frame[k] = gray << 3;	// scale up

			k++;
			if(k >= OV7670_GRAY_SIZE)
				k = 0;

			FSMC_WR_DAT(graysc);
		}
*/		//*********************************************************************************************************************

		LCD_SetWindow(20, 20, 340-1, 260-1); // 320 x 240
		for(j = 0; j <= OV7670_FRAME_SIZE_QVGA - 2; j+=2)
		{
			/*
			// Black & White Video
			uint16_t gray =(((g_cam_buff[j] & 0xF8U) >> 3) +										//red
							(((g_cam_buff[j] & 0x07U) << 3) | ((g_cam_buff[j+1] & 0xC0U) >> 6)) +	//green
							((g_cam_buff[j+1] & 0x1FU))												//blue
					) / 3;

			uint16_t graysc =
					(((gray << 11) & 0xF800U) |
					((gray << 6) & 0x07C0U) |
					(gray & 0x001FU));
			FSMC_WR_DAT(graysc);
			*/

			//int red =	(g_cam_buff[j] & 0xF8U) >> 3;
			//int green =	((g_cam_buff[j] & 0x07U) << 3) | ((g_cam_buff[j+1] & 0xC0U) >> 6);
			//int blue =	((g_cam_buff[j+1] & 0x1FU));
			FSMC_WR_DAT(((g_cam_buff[j] << 8) & 0xFF00U) | (g_cam_buff[j+1] & 0x00FFU));
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
				uart_write("hello");
			}
		}
		if(HAL_GetTick() > milis2 + 100)
		{
			milis2 = HAL_GetTick();
			if(milis2 >= (0xFFFFFFFFU - 100U)) //?
			{
				milis2 = 0;
			}
			else
			{// every 10 miliseconds

//				touch_coordinates1 = touch_process();

//				uint16_t x = (800.0/4096)*touch_coordinates1.x;
//				uint16_t y = (480.0/4096)*touch_coordinates1.y;
//				LCD_DrawPoint(x, 480-y, 0, 4);
			}
		}
	}
}


