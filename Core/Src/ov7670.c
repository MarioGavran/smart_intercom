#include "../Inc/OV7670.h"
#include "uart_driver.h"
#include <stdio.h>




//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void saturation(int8_t s)  //-2 to 2
{
	//color matrix values
	writeRegister(OV7670_MTX1,	0x80 + 0x20 * s);
	writeRegister(OV7670_MTX2, 	0x80 + 0x20 * s);
	writeRegister(OV7670_MTX3, 	0x00);
	writeRegister(OV7670_MTX4, 	0x22 + (0x11 * s) / 2);
	writeRegister(OV7670_MTX5, 	0x5e + (0x2f * s) / 2);
	writeRegister(OV7670_MTX6, 	0x80 + 0x20 * s);
	writeRegister(OV7670_MTXS, 	0x9e);  //matrix signs
}


//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void frameControl(int16_t hStart,  int16_t vStart)
{
	int hStop = (hStart + 640) % 784;
	writeRegister(OV7670_HSTART,	hStart >> 3);
	writeRegister(OV7670_HSTOP,		hStop >> 3);
	writeRegister(OV7670_HREF, 		((hStop & 0b111) << 3) | (hStart & 0b111));

	int vStop = (vStart + 480);
	writeRegister(OV7670_VSTRT, 	vStart >> 2);
	writeRegister(OV7670_VSTOP, 	vStop >> 2);
	writeRegister(OV7670_VREF, 		((vStop & 0b11) << 2) | (vStart & 0b11));
	writeRegister(OV7670_COM10, 	0x20U);
}


//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void subsamplingControl(int8_t com14, int8_t downSample, int8_t pclk_div)
{
	writeRegister(OV7670_COM3, 			0x04);  //DCW enable

	writeRegister(OV7670_COM14, 		com14);       //pixel clock divided by 4, manual scaling enable, DCW and PCLK controlled by register
	writeRegister(OV7670_SCL_XSC, 		0x3a);
	writeRegister(OV7670_SCL_YSC, 		0x35);

	writeRegister(OV7670_SCL_DCWCTR, 	downSample);
	writeRegister(OV7670_SCL_PCLK_DIV, 	pclk_div); //pixel clock divided by 4
	writeRegister(OV7670_SCL_PCLK_DLY, 	0x02);
}


//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void testPattern(uint8_t kind) // 0-none, or 1,2,3
{
	writeRegister(OV7670_SCL_XSC, (readRegister(OV7670_SCL_XSC) & 0x7F) | ((kind & 0x01) << 7));
	writeRegister(OV7670_SCL_YSC, (readRegister(OV7670_SCL_YSC) & 0x7F) | ((kind & 0x02) << 6));
}


//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void writeRegister(unsigned char reg, unsigned char val)
{
	//uint8_t buff[25] = {0};

	//sprintf(buff, "0x%02x,0x%02x,", reg, i2c_read_reg(0x43, reg));
	i2c_write_reg(0x42U, reg, val);
	//sprintf(buff + strlen(buff), "0x%02x\r\n", i2c_read_reg(0x43, reg));
	//uart_write(buff);
}


//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
uint8_t readRegister(unsigned char reg)
{
	return i2c_read_reg(0x42U, reg);
}


//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void setMode(ov7670_res_fmt_t resolution)
{   // 0,1 or 2 for QQQ, QQ, or Q VGA.  All are RGB565
	int xres;
	int yres;


	if (resolution < 0 || resolution > 2) {
		resolution = 2;
	}

	writeRegister(OV7670_COM7,	0x80U);				// all registers default
	writeRegister(OV7670_CLKRC,	0x80U);				// double clock?? My spec sheet says Reserved
	writeRegister(OV7670_COM11,	0x08U | 0x02U);		// enable auto 50/60Hz detect + exposure timing can be less...
	writeRegister(OV7670_COM7,	0x04U);				// RGB
	writeRegister(OV7670_COM15,	0xC0U | 0x10U);		// RGB565

	switch (resolution) {
	case 0:
		xres = 80;
		yres = 60;
		subsamplingControl(0x1B, 0x33, 0xF3);
		frameControl(196, 14);
		break;
	case 1:
		xres = 160;
		yres = 120;
		subsamplingControl(0x1A, 0x22, 0xF2);
		frameControl(174, 14);
		break;
	case 2:
		xres = 320;
		yres = 240;
		subsamplingControl(0x19, 0x11, 0xF1);
		frameControl(154, 14);
		break;
	}

	//writeRegister(OV7670_COM10, 0x02); //VSYNC negative
	//writeRegister(OV7670_MVFP, 0x2b);  //mirror flip

	writeRegister(0xB0U, 			0x84U); // no clue what this is but it's most important for colors
	saturation(0);
	writeRegister(OV7670_COM8, 		0xE7U); // AGC AWB AEC all on
	writeRegister(OV7670_AWBCTR0, 	0x9FU); // Simple AWB

	// What is this comment about? I tried but don't see any difference.
	// Line 1029 of https://github.com/yandex/smart/blob/master/drivers/media/i2c/ov7670.c
	writeRegister(OV7670_CLKRC, 	0x80U);

	HAL_Delay(50);

	/**/
	uint16_t exposure = 200;
	uint8_t com1 = exposure & 0x03U;			// AEC[1:0]
	uint8_t aech = (exposure >> 2) & 0xFFU;		// AEC[9:2]
	uint8_t aechh = (exposure >> 10) & 0xFFU;	// AEC[15:10]

	writeRegister(OV7670_COM1, 		(readRegister(OV7670_COM1) & ~0x03U) | com1);
	writeRegister(OV7670_AECH, 		aech);
	writeRegister(OV7670_AECHH, 	aechh);
}







