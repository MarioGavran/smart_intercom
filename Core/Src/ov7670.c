#include "ov7670.h"
#include "uart_driver.h"
#include "tim.h"
#include <stdio.h>



char g_cam_buff[OV7670_FRAME_SIZE_QVGA] = {0};
char g_cam_gray_frame[96*96] = {0};

uint32_t g_offset = 0;



/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
* Parameters for each image frame format
* It should be referenced with 'ov7670_frame_fmt_t' enumeration.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
const ov7670_frame_param_t ov7670_frame_params[6] = {
		{
				.format		= FFMT_QCIF,
				.width		= QCIF_WIDTH,
				.height		= QCIF_HEIGHT,
				.frame_size = OV7670_FRAME_SIZE_QCIF,

				.hStart		= 456,
				.hStop		= 24,
				.vStart		= 14,
				.vStop		= 494
		},
		{
				.format		= FFMT_CIF,
				.width		= CIF_WIDTH,
				.height		= CIF_HEIGHT,
				.frame_size = OV7670_FRAME_SIZE_CIF,

				.hStart		= 170,
				.hStop		= 90,
				.vStart		= 14,
				.vStop		= 494
		},
		{
				.format		= FFMT_QQQVGA,
				.width		= QQQVGA_WIDTH,
				.height		= QQQVGA_HEIGHT,
				.frame_size	= OV7670_FRAME_SIZE_QQQVGA,

				.hStart		= 196,
				.hStop		= 52,
				.vStart		= 14,
				.vStop		= 494
		},
		{
				.format		= FFMT_QQVGA,
				.width		= QQVGA_WIDTH,
				.height		= QQVGA_HEIGHT,
				.frame_size = OV7670_FRAME_SIZE_QQVGA,

				.hStart		= 174,
				.hStop		= 30,
				.vStart		= 14,
				.vStop		= 494
		},
		{
				.format		= FFMT_QVGA,
				.width		= QVGA_WIDTH,
				.height 	= QVGA_HEIGHT,
				.frame_size = OV7670_FRAME_SIZE_QVGA,

				.hStart		= 168,
				.hStop		= 24,
				.vStart		= 12,
				.vStop		= 492
		},
		{
				.format		= FFMT_VGA,
				.width		= VGA_WIDTH,
				.height		= VGA_HEIGHT,
				.frame_size = OV7670_FRAME_SIZE_VGA,
		}

};



/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
* Register list for configuring the image frame format.
* First dimension should be referenced with 'ov7670_frame_fmt_t' enumeration.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
const ov7670_regval_list_t ov7670_FFMT_regval_list[6][4] =
{
		{	// QCIF
				{OV7670_COM14,			COM14_DCWEN | COM14_PCLKDIV_4},
				{OV7670_SCL_DCWCTR,		0x11}, //todo: zamjeni brojeve za definicije
				{OV7670_SCL_PCLK_DIV,	0xF1},
				{0xFF,	0xFF}
		},
		{	// CIF	// TODO: CIF ne radi
				{OV7670_COM14,			COM14_DCWEN | COM14_PCLKDIV_2},
				{OV7670_SCL_DCWCTR,		0x11}, //todo: zamjeni brojeve za definicije
				{OV7670_SCL_PCLK_DIV,	0xF1},
				{0xFF,	0xFF}
		},
		{	// QQQVGA
				{OV7670_COM14,			COM14_DCWEN /*| COM14_MSCLEN */| COM14_PCLKDIV_8},
				{OV7670_SCL_DCWCTR,		0x33},
				{OV7670_SCL_PCLK_DIV,	0xF3},
				{0xFF, 0xFF}
		},
		{	// QQVGA
				{OV7670_COM14,			COM14_DCWEN /*| COM14_MSCLEN */| COM14_PCLKDIV_4},
				{OV7670_SCL_DCWCTR,		0x22},//72
				{OV7670_SCL_PCLK_DIV,	0xF2},//73
				{0xFF, 0xFF}
		},
		{	// QVGA
				{OV7670_COM14,			COM14_DCWEN /*| COM14_MSCLEN */| COM14_PCLKDIV_2},
				{OV7670_SCL_DCWCTR,		0x11},
				{OV7670_SCL_PCLK_DIV,	0xF1},
				{0xFF, 0xFF}
		},
		{	// VGA
				{0xFF,	0xFF}
		}
};



/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
* Register list for configuring the bus format and color.
* First dimension should be referenced with 'ov7670_color_fmt_t' enumeration.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
const ov7670_regval_list_t ov7670_CFMT_regval_list[7][7] =
{
		{// RGB565 [RRRRRGGG GGGBBBBB]
				{OV7670_COM7,	COM7_RGB},						// RGB
				{OV7670_RGB444,	0x00U},							// No RGB444
				{OV7670_COM15,	COM15_R00FF | COM15_RGB565},	// Full range + RGB565
				{0xFF,	0xFF}
		},
		{// RGB555 [xRRRRRGG GGGBBBBB]
				{OV7670_COM7,	COM7_RGB},						// RGB
				{OV7670_RGB444,	0x00U},							// No RGB444
				{OV7670_COM15,	COM15_R00FF | COM15_RGB555},	// Full range + RGB555
				{0xFF,	0xFF}
		},
		{// RGB444 [xxxxRRRR GGGGBBBB]
				{OV7670_COM7,	COM7_RGB},						// RGB
				{OV7670_RGB444,	RGB444_EN},						// Enable RGB444
				{OV7670_COM15,	COM15_R00FF | COM15_RGB565},	// Full range. RGB444 active only with 565 bit set
				{0xFF,	0xFF}
		},
		{// GRB422 [GGGGGGGG RRRRRRRR GGGGGGGG BBBBBBBB], todo: Needs different UV swap and/or PCLK_DLY, for different resolutions
				{OV7670_COM7,	COM7_RGB},						// RGB
				{OV7670_RGB444,	0x00U},							// No RGB444
				{OV7670_COM15,	COM15_R00FF | COM15_GRB422},	// Full range + GRB422
				{OV7670_TSLB,	0x05},
				{0xFF,	0xFF}
		},
		{// YUY422 [YYYYYYYY UUUUUUUU YYYYYYYY VVVVVVVV], TODO: image is too bright
				{OV7670_COM7,	COM7_YUV},						// YUV
				{OV7670_RGB444,	0x00U},							// No RGB444
				{OV7670_COM15,	COM15_R00FF | COM15_YUV},		// Full range + YUV422
				{0xFF,	0xFF}
		},
		{// RAW_BAYER, todo: only VGA & QVGA ???
				{OV7670_COM7,	COM7_RBAYER},					// Raw Bayer
				{OV7670_RGB444,	0x00U},							// No RGB444
				{OV7670_COM15,	COM15_R00FF | COM15_BAYER},
				//{OV7670_COM13,	0x08},							// No gamma, magic rsvd bit
				//{OV7670_COM16,	0x3d},							// Edge enhancement, denoise
				//{OV7670_REG76,	0xe1},							// Pix correction, magic rsvd
				{0xFF,	0xFF}
		},
		{// PRO_BAYER todo: only VGA ???
				{OV7670_COM7,	COM7_PBAYER},					// Processed Bayer
				{OV7670_RGB444,	0x00U},							// No RGB444
				{OV7670_COM15,	COM15_R00FF | COM15_BAYER},
				//{OV7670_COM13,	0x08},							// No gamma, magic rsvd bit
				//{OV7670_COM16,	0x3d},							// Edge enhancement, denoise
				//{OV7670_REG76,	0xe1},							// Pix correction, magic rsvd
				{0xFF,	0xFF}
		}
};

const ov7670_regval_list_t ov7670_CMTX_regval_list[2][8] =
{
		{	// RGB565/555/444
				{OV7670_MTX1, 	0xb3},
				{OV7670_MTX2, 	0xb3},
				{OV7670_MTX3, 	0x00},
				{OV7670_MTX4, 	0x3d},
				{OV7670_MTX5, 	0xa7},
				{OV7670_MTX6, 	0xe4},
				{OV7670_MTXS, 	0x9e},
				{0xFF, 0xFF}
		},
		{	// YUYV
				{OV7670_MTX1, 	0x80},
				{OV7670_MTX2, 	0x80},
				{OV7670_MTX3, 	0x00},
				{OV7670_MTX4, 	0x22},
				{OV7670_MTX5, 	0x5e},
				{OV7670_MTX6, 	0x80},
				{OV7670_MTXS, 	0x9e},
				{0xFF, 0xFF}
		}
};

//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
ov7670_device_info_t g_ov7670_info = {
		.color_fmt = CFMT_RGB565,
		.frame_params = ov7670_frame_params[FFMT_QVGA],

		.frame_rate = FRATE_30FPS,
		.pclk = 10000000,
		.xclk = 20000000
};




/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
*
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
void ov7670_saturation(int8_t s)  //-2 to 2
{
	ov7670_write_register(OV7670_MTX1,	0x80 + 0x20 * s);
	ov7670_write_register(OV7670_MTX2, 	0x80 + 0x20 * s);
	ov7670_write_register(OV7670_MTX3, 	0x00);
	ov7670_write_register(OV7670_MTX4, 	0x22 + (0x11 * s) / 2);
	ov7670_write_register(OV7670_MTX5, 	0x5e + (0x2f * s) / 2);
	ov7670_write_register(OV7670_MTX6, 	0x80 + 0x20 * s);
	ov7670_write_register(OV7670_MTXS, 	0x9e);
}



/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
*
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
void ov7670_frame_control(int16_t hStart, int16_t hStop, int16_t vStart, int16_t vStop) // 154 14
{
	//int hStop = (hStart + 640) % 784; // 10
	ov7670_write_register(OV7670_HSTART,	hStart >> 3);//0x15); 17
	ov7670_write_register(OV7670_HSTOP,		hStop >> 3);//0x03);  18
	ov7670_write_register(OV7670_HREF, 		((hStop & 0b111) << 3) | (hStart & 0b111));//0x80); 32

	//int vStop = (vStart + 480); // 494
	ov7670_write_register(OV7670_VSTART, 	vStart >> 2);//0x03); 19
	ov7670_write_register(OV7670_VSTOP, 	vStop >> 2);//0x7b);  1a
	ov7670_write_register(OV7670_VREF, 		((vStop & 0b11) << 2) | (vStart & 0b11));//0x00); 03

}



/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
*
* A value of 0x20 or below indicates 1x scaling ratio and value of 0x40 or higher
* indicates 0.5x scaling ratio.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
void ov7670_scaling_control(uint16_t width, uint16_t height)
{
	uint16_t scl_xsc = 32 * ((float)g_ov7670_info.frame_params.width / width);
	if(scl_xsc > 0x40) scl_xsc = 0x40;
	else if(scl_xsc < 0x20) scl_xsc = 0x20;

	uint16_t scl_ysc = 32 * ((float)g_ov7670_info.frame_params.height / height);
	if(scl_ysc > 0x40) scl_ysc = 0x40;
	else if(scl_ysc < 0x20) scl_ysc = 0x20;

	g_ov7670_info.frame_params.width = width;
	g_ov7670_info.frame_params.height = height;

	ov7670_write_register(OV7670_COM3, ov7670_read_register(OV7670_COM3) | COM3_SCLEN);
	ov7670_write_register(OV7670_SCL_XSC, scl_xsc);
	ov7670_write_register(OV7670_SCL_YSC, scl_ysc);
}



/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
*
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
void ov7670_subsampling_control(int8_t com14, int8_t downSample, int8_t pclk_div)//19 11 f1
{
	ov7670_write_register(OV7670_COM3, 			0x04);		// 0c DCW enable

	ov7670_write_register(OV7670_COM14, 		com14);		// 3e pixel clock divided by 4, manual scaling enable, DCW and PCLK controlled by register
	ov7670_write_register(OV7670_SCL_XSC, 		0x3a);		// 70
	ov7670_write_register(OV7670_SCL_YSC, 		0x35);		// 71

	ov7670_write_register(OV7670_SCL_DCWCTR, 	downSample);// 72
	ov7670_write_register(OV7670_SCL_PCLK_DIV, 	pclk_div);	// 73pixel clock divided by 4
	ov7670_write_register(OV7670_SCL_PCLK_DLY, 	0x02);		// a2
}



/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
*
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
void ov7670_test_pattern(uint8_t kind)
{
	ov7670_write_register(OV7670_SCL_XSC,
			(ov7670_read_register(OV7670_SCL_XSC) & 0x7F) | ((kind & 0x01) << 7));
	ov7670_write_register(OV7670_SCL_YSC,
			(ov7670_read_register(OV7670_SCL_YSC) & 0x7F) | ((kind & 0x02) << 6));
}



/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
*
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
void ov7670_write_register(unsigned char reg, unsigned char val)
{
	i2c_write_reg(0x42U, reg, val);
}



/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
*
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
uint8_t ov7670_read_register(unsigned char reg)
{
	return i2c_read_reg(0x42U, reg);
}



/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
*
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
void ov7670_write_array(ov7670_regval_list_t *list)
{
	while((list->address != 0xFFU) && (list->value != 0xFFU))
	{
		ov7670_write_register(list->address, list->value);
		list++;
	}
}



/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
*
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
void ov7670_set_mode(uint16_t exposure)
{
	ov7670_write_register(OV7670_COM7,	COM7_RESET);	// 12, all registers default
	HAL_Delay(3);

	// CLOCK
	ov7670_write_register(OV7670_CLKRC,	0x80U);			// 11, No clock prescaler + MAGIC RSVD
	ov7670_write_register(OV7670_COM11,	COM11_AD56HZ | COM11_50HZ | COM11_EXPLES);	// 3b, Enable auto 50Hz detect + exposure timing can be less


	// FRAME FMT
	ov7670_write_register(OV7670_COM3, 			COM3_DCWEN);	// 0c DCW enable
	ov7670_write_array(ov7670_FFMT_regval_list[g_ov7670_info.frame_params.format]);
	ov7670_write_register(OV7670_SCL_PCLK_DLY, 	0x02);	// a2
	ov7670_frame_control(
			g_ov7670_info.frame_params.hStart,
			g_ov7670_info.frame_params.hStop,
			g_ov7670_info.frame_params.vStart,
			g_ov7670_info.frame_params.vStop);

	ov7670_write_register(OV7670_COM10, 	0x20U); 	// 15 No PCLK during horiz. blank


	// COLOR FMT
	ov7670_write_array(ov7670_CFMT_regval_list[g_ov7670_info.color_fmt]);
	ov7670_write_array(ov7670_CMTX_regval_list[g_ov7670_info.color_fmt == CFMT_GRB422 ? 1:0]);
	if(g_ov7670_info.color_fmt == CFMT_RAW_BAYER)
	{
		//ov7670_write_register(OV7670_COM14,	ov7670_read_register(OV7670_COM14)-1);	// GRB422 has 4bytes per pixel??. COM14 is first set by ov7670_write_array(ov7670_FFMT_regval_list[])
		//ov7670_write_register(OV7670_SCL_PCLK_DIV, 0xF8);	// Bypass clock divider for DSP scale contro
	}


	ov7670_write_register(0xB0U, 			0x84U); // something for colors
	//ov7670_saturation(0);
	ov7670_write_register(OV7670_COM8,		0xE7U); // 13 AGC AWB AEC on
	ov7670_write_register(OV7670_AWBCTR0,	0x9FU); // 6f AWB
	ov7670_write_register(OV7670_CLKRC, 	0x80U);	// 11

	HAL_Delay(50);

	uint8_t com1 = exposure & 0x03U;				// AEC[1:0]
	uint8_t aech = (exposure >> 2) & 0xFFU;			// AEC[9:2]
	uint8_t aechh = (exposure >> 10) & 0xFFU;		// AEC[15:10]

	ov7670_write_register(OV7670_COM1, 		(ov7670_read_register(OV7670_COM1) & ~0x03U) | com1);//04
	ov7670_write_register(OV7670_AECH, 		aech);//10
	ov7670_write_register(OV7670_AECHH, 	aechh);//07
}



/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
*
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
void ov7670_init1()
{
	OV7670_PWR_ON;

	OV7670_NRST_LOW;
	HAL_Delay(300);
	OV7670_NRST_HIGH;
	HAL_Delay(300);

	ov7670_set_mode(300);
	HAL_Delay(300);

	// Enable timer trigger DMA request
	TIM1->DIER |= TIM_DIER_TDE;
	HAL_TIM_Base_Start(&htim1);

	HAL_NVIC_SetPriority(OV7670_VSYNC_EXTI_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(OV7670_VSYNC_EXTI_IRQn);
}







/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
*
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
void EXTI0_HREF_Callback()
{
	// Falling edge
	HAL_DMA_Abort(&hdma_tim1_trig);
	HAL_DMA_Start(
			&hdma_tim1_trig,
			OV7670_DATA_PORT_ADD,
			(uint32_t)(g_cam_buff + g_offset),
			g_ov7670_info.frame_params.width * 2);
	if(g_cam_buff + g_offset >= g_cam_buff + OV7670_FRAME_SIZE_QVGA - 640)
		g_offset = 0;
	else
		g_offset += 640;	// Always +=640 because we want to point in a 'new row'
}



/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
*
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/
void EXTI1_VSYNC_Callback()
{
	// Rising edge
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
		HAL_DMA_Abort(&hdma_tim1_trig);// todo: ?
		HAL_DMA_Start(
				&hdma_tim1_trig,
				OV7670_DATA_PORT_ADD,
				(uint32_t)g_cam_buff,
				g_ov7670_info.frame_params.width * 2); // first line
		g_offset = 640;
	}
}
