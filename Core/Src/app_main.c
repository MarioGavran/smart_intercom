/*
 * app_main.cpp
 *
 *  Created on: Jun 12, 2021
 *      Author: enio
 */
#include "../Inc/app_main.h"


int8_t g_person_score = 0;
int8_t g_no_person_score = 0;

#define CMSIS_NN

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
	NT35510_Init();

	LCD_ClearScreen(0xFFFFU);
	LCD_SetDirection(HORIZONTAL_RIGHT);
	LCD_ClearScreen(0xFFFFU);
	LCD_SetWindow(240,184,560-1,295-1);

	for(int l = 0; l < 320*111*2; l+=2)
	{
		FSMC_WR_DAT(((g_logo_image[l] << 8) & 0xFF00U) | (g_logo_image[l+1] & 0x00FFU));
	}
	HAL_Delay(1000);
/*
	// Draw frame:
	LCD_DrawLine(10, 10, 790, 10, 0xF800U,4);		// up
	LCD_DrawLine(10, 10, 10, 470, 0x07E0U,4);		// left
	LCD_DrawLine(790, 10, 790, 470, 0x001FU,4);		// right
	LCD_DrawLine(10, 470, 790, 470, 0xF800U,4);		// down
*/


	ov7670_init();
}


//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
void app_main_loop()
{
	uint8_t buff[10] = {0};
	//uint8_t i2cDatToSnd[5] = {0};
	//uint8_t i2cDatToRec[5] = {0};
	uint32_t milis = 0;
	uint32_t milis2 = 0;
	int j,z = 0;
	int k = -2;
	int kk = 0;

	LCD_SetDirection(VERTICAL_UP);
	LCD_SetWindow(20, 20, 340-1, 260-1); // 320 x 240
	tflite_micro_setup();



	while(1)
	{
		tflite_micro_loop();

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

		uart_tx_process();
		uart_rx_process();

		LCD_SetWindow(20 , 280, 20+96-1, 280+96-1); // 320 x 240
/*
 *
		//*********************************************************************************************************************
		//*********************************************************************************************************************
		for(z = 0; z < 96*96; z++)
		{
			char gray = ((
					((g_person_image_data1[z] & 0xF8U) >> 11) +	//red
					((g_person_image_data1[z] & 0x7CU) << 6) +	//green
					((g_person_image_data1[z] & 0x1FU))	//blue
					) / 3) & 0xFFU;

			uint16_t graysc = (
					((gray << 11) & 0xF800U) |
					((gray << 6)  & 0x07C0U) |
					((gray << 0)  & 0x001FU));

			g_cam_gray_frame[z] = gray;

			FSMC_WR_DAT(graysc);
		}
 */

		//*********************************************************************************************************************
		//*********************************************************************************************************************

		//*********************************************************************************************************************
		//*********************************************************************************************************************
		/**/

		for(z = 0; z < 96*96*2; z+=2)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
			char gray = (
					(((g_person_image_data1[z] & 0xF8U) >> 3) +	//red
					(((g_person_image_data1[z] & 0x07U) << 2) | ((g_person_image_data1[z+1] & 0xC0U) >> 6)) +	//green
					(((g_person_image_data1[z+1] & 0x1FU)))	//blue
					) / 3);

			uint16_t graysc = (
					((gray << 11) & 0xF800U) |
					((gray << 6)  & 0x07C0U) |
					((gray << 0)  & 0x001FU));

			g_cam_gray_frame[kk] = gray << 3;

			kk++;
			if(kk >= OV7670_GRAY_SIZE)
				kk = 0;

			FSMC_WR_DAT(graysc);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
		}

			//*********************************************************************************************************************
			//*********************************************************************************************************************


	/*
		//*********************************************************************************************************************
	 	//*********************************************************************************************************************
		for(z = 0; z < 96*96; z++)
		{
			//char gray = ((
			//		((g_person_image_data1[z] & 0xE0U) >> 5) +	//red
			//		((g_person_image_data1[z] & 0x1CU) >> 2) +	//green
			//		((g_person_image_data1[z] & 0x03U) >> 0)	//blue
			//		) );

			uint16_t graysc = (
					((g_person_image_data1[z] << 11) & 0xF800U) |
					((g_person_image_data1[z] << 6)  & 0x07C0U) |
					((g_person_image_data1[z] << 0)  & 0x001FU));

			g_cam_gray_frame[z] = g_person_image_data1[z];
			FSMC_WR_DAT(graysc);
		}
		//*********************************************************************************************************************
		//*********************************************************************************************************************
*/











		LCD_SetWindow(20, 20, 340-1, 260-1); // 320 x 240
		for(j = 0; j <= OV7670_FRAME_SIZE_QVGA - 2; j+=2)
		{
			//
			// Black & White Video
			//uint16_t gray =
			//		(((g_cam_buff[j] & 0xF8U) >> 3) +	//red
			//				(((g_cam_buff[j] & 0x07U) << 3) | ((g_cam_buff[j+1] & 0xC0U) >> 6)) +	//green
			//				((g_cam_buff[j+1] & 0x1FU))	//blue
			//		) / 3;
//
			//uint16_t graysc =
			//		(((gray << 11) & 0xF800U) |
			//		((gray << 6) & 0x07C0U) |
			//		(gray & 0x001FU));
			// FSMC_WR_DAT(graysc);


			// RRRRR GGGGGG BBBBB
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
				sprintf(buff, "0x\r\n");
				uart_write(buff);
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
/**/
	}
}












