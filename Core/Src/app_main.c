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





int8_t g_person_score = 0;



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
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


	ov7670_init();
}

//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~_Min_Stack_Size
void app_main_loop()
{
	uint8_t buff[10] = {0};
	//uint8_t i2cDatToSnd[5] = {0};
	//uint8_t i2cDatToRec[5] = {0};
	uint32_t milis = 0;
	uint32_t milis2 = 0;
	int j,z,k = 0;

	LCD_SetDirection(VERTICAL_UP);
	LCD_SetWindow(20, 20, 340-1, 260-1); // 320 x 240
	tflite_micro_setup();



	while(1)
	{
		tflite_micro_loop();
		sprintf(buff,"%03d",abs(g_person_score));
		LCD_PrintStr(20, 20, 0xffff, 0x0000, buff, 5);

		//uart_tx_process();
		//uart_rx_process();

		LCD_SetWindow(20 , 280, 20+96-1, 280+96-1); // 320 x 240
		for(j = 72; j <= 72 + 96; j++)
		{
			for(z = 112*2; z < 112*2 + 96*2; z+=2)
			{
				uint8_t gray =
						(((g_cam_buff[(j-1)*320*2+z] & 0xF8U) >> 3) +	//red
								(((g_cam_buff[(j-1)*320*2+z] & 0x07U) << 3) | ((g_cam_buff[(j-1)*320*2+z+1] & 0xC0U) >> 6)) +	//green
								((g_cam_buff[(j-1)*320*2+z+1] & 0x1FU))	//blue
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












