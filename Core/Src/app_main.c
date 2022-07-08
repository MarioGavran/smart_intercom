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

	//HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, GPIO_PIN_SET);

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
	int i=0;
	int j,z = 0;
	int k = -2;


	LCD_SetDirection(HORIZONTAL_RIGHT);

	tflite_micro_setup();


	while(1)
	{
		tflite_micro_loop();

		if(g_person_score < 0)
			sprintf(buff, "-");
		else
			sprintf(buff, " ");
		sprintf(buff + strlen(buff), "%03d", abs(g_person_score));
		LCD_PrintStr(20+64*4+192*2+1, 20, 0xffff, 0x0000, buff, 3);


		uart_tx_process();
		uart_rx_process();
		touch_process();

		//if((g_touch_coordinates.x != 0) && (g_touch_coordinates.y != 0) &&
		//		(g_touch_coordinates.x < 3100) && (g_touch_coordinates.y <= 3100))
		//{
/*			sprintf(buff, "%04d, %04d", g_touch_coordinates.x, g_touch_coordinates.y);
			LCD_PrintStr(20, 480, 0, 0x841FU, buff, 3);
		//}
			if(g_touch_state == TOUCH_IDLE)
				LCD_PrintStr(20, 520, 0, 0x841FU, "IDLE    ", 3);
			else if(g_touch_state == TOUCH_TOUCHED)
				LCD_PrintStr(20, 520, 0, 0x841FU, "TOUCHED ", 3);
			else if(g_touch_state == TOUCH_RELEASED)
				LCD_PrintStr(20, 520, 0, 0x841FU, "RELEASED", 3);
*/
/**/

		//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
		uint8_t hb = 0;
		uint8_t lb = 0;
		int a = 0;

		LCD_SetWindow(0, 0, 320*2-1, 240*2-1); // 320 x 240
		j=0;
		for(i=0; i < QVGA_HEIGHT; i++)
		{
			for(j=j; j < QVGA_WIDTH*2 + i*QVGA_WIDTH*2; j+=2)
			{
				FSMC_WR_DAT(((g_cam_buff[j] << 8) & 0xFF00U) | (g_cam_buff[j+1] & 0x00FFU));
				FSMC_WR_DAT(((g_cam_buff[j] << 8) & 0xFF00U) | (g_cam_buff[j+1] & 0x00FFU));
			}

			j-=(QVGA_WIDTH*2);

			for(j=j; j < QVGA_WIDTH*2 + i*QVGA_WIDTH*2; j+=2)
			{
				FSMC_WR_DAT(((g_cam_buff[j] << 8) & 0xFF00U) | (g_cam_buff[j+1] & 0x00FFU));
				FSMC_WR_DAT(((g_cam_buff[j] << 8) & 0xFF00U) | (g_cam_buff[j+1] & 0x00FFU));
			}
			//j=j+QVGA_WIDTH*2;
		}

		LCD_DrawLine(64*2, 48, 64*2+192*2, 48, 0, 1);
		LCD_DrawLine(64*2, 48+192*2, 64*2+192*2, 48+192*2, 0, 1);
		LCD_DrawLine(64*2, 48, 64*2, 48+192*2, 0, 1);
		LCD_DrawLine(64*2+192*2, 48, 64*2+192*2, 48+192*2, 0, 1);


		LCD_SetWindow(20+64*2*2+192*2 , 50, 20+64*2*2+192*2+96-1, 50+96-1); // 96 x 96


		//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
		for(z = 24*320*2 + 64*2; z < OV7670_FRAME_SIZE_QVGA; z+=4)
		{
			if(z >= (320*2*(24+192) - 64*2))
				break;

			if((z+64*2) % (320*2) == 0)
				z+=128*2 + 320*2;
			// Calculate gray-scale from RGB data
			char gray = (
					(((g_cam_buff[z] & 0xF8U) >> 3) +												//red
							(((g_cam_buff[z] & 0x07U) << 2) | ((g_cam_buff[z+1] & 0xC0U) >> 6)) +	//green
							(((g_cam_buff[z+1] & 0x1FU)))											//blue
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



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
		if(HAL_GetTick() > milis + 1000)
		{
			milis = HAL_GetTick();
			if(milis >= (0xFFFFFFFFU - 1000U))
			{
				milis = 0;
			}
			else
			{// every second
				uart_write("hello\r\n");
			}
		}
		if(HAL_GetTick() > milis2 + 10)
		{
			milis2 = HAL_GetTick();
			if(milis2 >= (0xFFFFFFFFU - 100U)) //?
			{
				milis2 = 0;
			}
			else
			{// every 10 miliseconds

				uint16_t x = (800.0 / 3880) * (g_touch_coordinates.x - 380);//3880,350
				uint16_t y = (480.0 / 3570) * (g_touch_coordinates.y - 480);//3640,480
				LCD_DrawPoint(y, 800 - x, 0, 4);
			}
		}
	}
}


