#include "../Inc/OV7670.h"
#include "uart_driver.h"
#include "tim.h"
#include <stdio.h>



char g_cam_buff[OV7670_FRAME_SIZE_QVGA + 640] = {0};
char g_cam_gray_frame[96*96] = {0};

uint32_t g_offset = 0;



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void ov7670_saturation(int8_t s)  //-2 to 2
{
	//color matrix values
	ov7670_write_register(OV7670_MTX1,	0x80 + 0x20 * s);
	ov7670_write_register(OV7670_MTX2, 	0x80 + 0x20 * s);
	ov7670_write_register(OV7670_MTX3, 	0x00);
	ov7670_write_register(OV7670_MTX4, 	0x22 + (0x11 * s) / 2);
	ov7670_write_register(OV7670_MTX5, 	0x5e + (0x2f * s) / 2);
	ov7670_write_register(OV7670_MTX6, 	0x80 + 0x20 * s);
	ov7670_write_register(OV7670_MTXS, 	0x9e);  //matrix signs
}



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void ov7670_frame_control(int16_t hStart,  int16_t vStart)
{
	int hStop = (hStart + 640) % 784;
	ov7670_write_register(OV7670_HSTART,	hStart >> 3);
	ov7670_write_register(OV7670_HSTOP,		hStop >> 3);
	ov7670_write_register(OV7670_HREF, 		((hStop & 0b111) << 3) | (hStart & 0b111));

	int vStop = (vStart + 480);
	ov7670_write_register(OV7670_VSTRT, 	vStart >> 2);
	ov7670_write_register(OV7670_VSTOP, 	vStop >> 2);
	ov7670_write_register(OV7670_VREF, 		((vStop & 0b11) << 2) | (vStart & 0b11));
	ov7670_write_register(OV7670_COM10, 	0x20U);
}



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void ov7670_subsampling_control(int8_t com14, int8_t downSample, int8_t pclk_div)
{
	ov7670_write_register(OV7670_COM3, 			0x04);  //DCW enable

	ov7670_write_register(OV7670_COM14, 		com14);       //pixel clock divided by 4, manual scaling enable, DCW and PCLK controlled by register
	ov7670_write_register(OV7670_SCL_XSC, 		0x3a);
	ov7670_write_register(OV7670_SCL_YSC, 		0x35);

	ov7670_write_register(OV7670_SCL_DCWCTR, 	downSample);
	ov7670_write_register(OV7670_SCL_PCLK_DIV, 	pclk_div); //pixel clock divided by 4
	ov7670_write_register(OV7670_SCL_PCLK_DLY, 	0x02);
}



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void ov7670_test_pattern(uint8_t kind) // 0-none, or 1,2,3
{
	ov7670_write_register(OV7670_SCL_XSC, (ov7670_read_register(OV7670_SCL_XSC) & 0x7F) | ((kind & 0x01) << 7));
	ov7670_write_register(OV7670_SCL_YSC, (ov7670_read_register(OV7670_SCL_YSC) & 0x7F) | ((kind & 0x02) << 6));
}



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void ov7670_write_register(unsigned char reg, unsigned char val)
{
	//uint8_t buff[25] = {0};

	//sprintf(buff, "0x%02x,0x%02x,", reg, i2c_read_reg(0x43, reg));
	i2c_write_reg(0x42U, reg, val);
	//sprintf(buff + strlen(buff), "0x%02x\r\n", i2c_read_reg(0x43, reg));
	//uart_write(buff);
}



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
uint8_t ov7670_read_register(unsigned char reg)
{
	return i2c_read_reg(0x42U, reg);
}



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void ov7670_set_mode(ov7670_res_fmt_t resolution, uint16_t exposure)
{   // 0,1 or 2 for QQQ, QQ, or Q VGA.  All are RGB565
	if (resolution < 0)
		resolution = 0;
	else if(resolution > 2)
		resolution = 2;

	ov7670_write_register(OV7670_COM7,	0x80U);				// all registers default
	ov7670_write_register(OV7670_CLKRC,	0x80U);				// double clock?? My spec sheet says Reserved
	ov7670_write_register(OV7670_COM11,	0x08U | 0x02U);		// enable auto 50/60Hz detect + exposure timing can be less...
	ov7670_write_register(OV7670_COM7,	0x04U);				// RGB
	ov7670_write_register(OV7670_COM15,	0xC0U | 0x10U);		// RGB565

	switch (resolution) {
	case 0:
		ov7670_subsampling_control(0x1B, 0x33, 0xF3);
		ov7670_frame_control(196, 14);
		break;
	case 1:
		ov7670_subsampling_control(0x1A, 0x22, 0xF2);
		ov7670_frame_control(174, 14);
		break;
	case 2:
		ov7670_subsampling_control(0x19, 0x11, 0xF1);
		ov7670_frame_control(154, 14);
		break;
	}

	//ov7670_writeRegist(OV7670_COM10, 0x02); //VSYNC negative
	//ov7670_writeRegist(OV7670_MVFP, 0x2b);  //mirror flip

	ov7670_write_register(0xB0U, 			0x84U); // no clue what this is but it's most important for colors
	ov7670_saturation(0);
	ov7670_write_register(OV7670_COM8, 		0xE7U); // AGC AWB AEC all on
	ov7670_write_register(OV7670_AWBCTR0, 	0x9FU); // Simple AWB

	// What is this comment about? I tried but don't see any difference.
	// Line 1029 of https://github.com/yandex/smart/blob/master/drivers/media/i2c/ov7670.c
	ov7670_write_register(OV7670_CLKRC, 	0x80U);

	HAL_Delay(50);

	uint8_t com1 = exposure & 0x03U;			// AEC[1:0]
	uint8_t aech = (exposure >> 2) & 0xFFU;		// AEC[9:2]
	uint8_t aechh = (exposure >> 10) & 0xFFU;	// AEC[15:10]

	ov7670_write_register(OV7670_COM1, 		(ov7670_read_register(OV7670_COM1) & ~0x03U) | com1);
	ov7670_write_register(OV7670_AECH, 		aech);
	ov7670_write_register(OV7670_AECHH, 	aechh);
}



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void ov7670_init()
{
	//HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	OV7670_RST_LOW;
	HAL_Delay(300);
	OV7670_RST_HIGH;
	HAL_Delay(300);

	ov7670_set_mode(QVGA_RGB565, 200);
	HAL_Delay(300);

	TIM1->DIER |= TIM_DIER_TDE;// | TIM_DIER_TDE TIM_DIER_UDE;
	HAL_TIM_Base_Start(&htim1);

	HAL_NVIC_SetPriority(OV7670_VSYNC_EXTI_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(OV7670_VSYNC_EXTI_IRQn);
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
	HAL_DMA_Start(&hdma_tim1_trig, (uint32_t) &(GPIOB->IDR), (uint32_t)(g_cam_buff + g_offset), 640);
	if(g_cam_buff + g_offset >= g_cam_buff + OV7670_FRAME_SIZE_QVGA - 640)//38080=38400-320
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
		HAL_DMA_Start(&hdma_tim1_trig, (uint32_t) &(GPIOB->IDR), (uint32_t)g_cam_buff, 640); // first line
		g_offset += 640;
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
}

