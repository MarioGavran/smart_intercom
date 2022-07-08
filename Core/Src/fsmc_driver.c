/*
 * fsmc_driver.c
 *
 *  Created on: Mar 9, 2021
 *      Author: Mario
 */

#include "../Inc/fsmc_driver.h"


FSMC_LCD_TypeDef* LCD_FSMC = (FSMC_LCD_TypeDef*)0x6001FFFEU;



/*******************************************************************************************************************************
 * name       :FSMC_WR_REG
 * date       :
 * function   :
 * parameters :
 * retvalue   :N/A
 *******************************************************************************************************************************/
void FSMC_WR_REG(uint32_t Reg)
{
	LCD_FSMC->REG = Reg;
}



/*******************************************************************************************************************************
* name       :FSMC_WR_DAT
* date       :
* function   :
* parameters :N/A
* retvalue   :N/A
*******************************************************************************************************************************/
void FSMC_WR_DAT(uint16_t Dat)
{
	LCD_FSMC->DAT = Dat;
}

uint16_t FSMC_RD_DAT(void)
{
	return LCD_FSMC->DAT;
}


/*******************************************************************************************************************************
* name       :LCD_SetWindow
* date       :May 10.2020
* function   :Defines accesible area in frame memory that MCU can access. The function is used in
							LCD_SetDirection function. It calls to FSMC_WR_REG(RAMWR) function at the end.
* parameters :XS(x start address), YS(y start address), XE(x end address) and YE(y end address)
* retvalue   :N/A
*******************************************************************************************************************************/
void LCD_SetWindow(uint16_t Xs, uint16_t Ys, uint16_t Xe, uint16_t Ye)
{
	FSMC_WR_REG(CASET_XS_H);		FSMC_WR_DAT(Xs >> 8);
	FSMC_WR_REG(CASET_XS_L);		FSMC_WR_DAT(Xs & 0x00FFU);
	FSMC_WR_REG(CASET_XE_H);		FSMC_WR_DAT(Xe >> 8);
	FSMC_WR_REG(CASET_XE_L);		FSMC_WR_DAT(Xe & 0x00FFU);
	FSMC_WR_REG(RASET_YS_H);		FSMC_WR_DAT(Ys >> 8);
	FSMC_WR_REG(RASET_YS_L);		FSMC_WR_DAT(Ys & 0x00FFU);
	FSMC_WR_REG(RASET_YE_H);		FSMC_WR_DAT(Ye >> 8);
	FSMC_WR_REG(RASET_YE_L);		FSMC_WR_DAT(Ye & 0x00FFU);

	FSMC_WR_REG(RAMWR);
}



/*******************************************************************************************************************************
* name       :LCD_SetDirection
* date       :May 10.2020
* function   :The function sets the desired orientation direction and than defines accessable area
							of the frame memory. The x and y axis change according to selected orientation
							direction, hance the defined accessible frame memory area must be changed to support
							the selected orientation.
* parameters :Direction(Use Orientation Direction Definitions defined in FSMC_NT35510.h)
* retvalue   :N/A
*******************************************************************************************************************************/
void LCD_SetDirection(uint8_t Direction)
{
	switch(Direction)
	{
		case 0:

			FSMC_WR_REG(MADCTL); FSMC_WR_DAT(0x0000U);
			LCD_SetWindow(0, 0, 479, 799);
		break;
		case 1:

			FSMC_WR_REG(MADCTL); FSMC_WR_DAT(0x00C0U);
			LCD_SetWindow(0, 0, 479, 799);
		break;
		case 2:

			FSMC_WR_REG(MADCTL); FSMC_WR_DAT(0x0060U);
			LCD_SetWindow(0, 0, 799, 479);
		break;
		case 3:

			FSMC_WR_REG(MADCTL); FSMC_WR_DAT(0x00A0U);
			LCD_SetWindow(0, 0, 799, 479);
		break;
	}
}



/*******************************************************************************************************************************
* name       :LCD_Clear
* date       :May 10.2020
* function   :Rewrite the whole screen with a single color. Does not require
							LCD_SetWindow function call to set accesible frame memory area, because it clears
							the whole screen, which is already defined by the LCD_SetDirection function call.
							LCD_SetDirection function is called during LCD initialization and after every
							orientation direction change.
* parameters :Color(Desired screen color)
* retvalue   :N/A
*******************************************************************************************************************************/
void LCD_ClearScreen(uint16_t Color)
{
  uint32_t i;

	for(i=0; i<(480*800); i++)
	{
		FSMC_WR_DAT(Color);
	}
}



/*******************************************************************************************************************************
* name       :LCD_ClearArea
* date       :May 10.2020
* function   :Rewrite defined accesible frame memory area with a single color. It calls to
							LCD_SetWindow function to set the accesible frame memory area, because it clears
							only the desired screen area. Does not need to call FSMC_WR_REG(RAMWR) because it
							is allready called by the LCD_SetWindow function call.
* parameters :Xs(x start address), Ys(y start address), Xe(x end address), Ye(y end address) and
							Color(Desired area color)
* retvalue   :N/A
*******************************************************************************************************************************/
void LCD_ClearArea(uint16_t Xs, uint16_t Ys, uint16_t Xe, uint16_t Ye, uint16_t Color)
{
  uint32_t i;
	LCD_SetWindow(Xs, Ys, Xe, Ye);
	FSMC_WR_REG(RAMWR);
	for(i=0; i  <((Xe - Xs) * (Ye - Ys) - 1); i++)
	{
		FSMC_WR_DAT(Color);
	}
}



/*******************************************************************************************************************************
* name       :LCD_DrawPoint
* date       :May 10.2020
* function   :Prints point on the screen. Does not need to call FSMC_WR_REG(RAMWR) because it is
							allready called by the LCD_SetWindow function call.
* parameters :X(x address of the center of the point), Y(y address of the center of the point)
							Color(point color), Size(point size)
* retvalue   :N/A
*******************************************************************************************************************************/
void LCD_DrawPoint(uint16_t X, uint16_t Y, uint16_t Color, uint8_t Size)
{
  uint32_t i;
	LCD_SetWindow(X, Y, X + (Size - 1), Y + (Size - 1));
	for(i=0; i < (Size) * (Size); i++)
	{
		FSMC_WR_DAT(Color);
	}
}



/*******************************************************************************************************************************
* name       :LCD_DrawLine
* date       :May 10.2020
* function   :
* parameters :Xs(x start address), Ys(y start address), Xe(x end address), Ye(y end address), Color(line color), Size(line size)
* retvalue   :N/A
*******************************************************************************************************************************/
void LCD_DrawLine(uint16_t Xs, uint16_t Ys, uint16_t Xe, uint16_t Ye, uint16_t Color, uint8_t Size)
{


	int16_t	deltaX = Xe - Xs;
	if(deltaX<0)
		deltaX = deltaX * (-1);

	int16_t	deltaY = Ye - Ys;
	if(deltaY<0)
		deltaX = deltaY * (-1);

	int8_t		signX = (Xs < Xe) ? (1) : (-1);
	int8_t		signY = (Ys < Ye) ? (1) : (-1);
	int16_t		error = deltaX - deltaY;

	for (;;)
	{
		LCD_DrawPoint(Xs, Ys, Color, Size);

		if(Xs == Xe && Ys == Ye)
			break;

		int16_t error2 = error;

		if(error2 > -deltaY)
		{
			error -= deltaY;
			Xs += signX;
		}

		if(error2 < deltaX)
		{
			error += deltaX;
			Ys += signY;
		}
	}
}



/*******************************************************************************************************************************
* name       :LCD_PrintCh
* date       :May 10.2020
* function   :Prints character on the display. Uses the ASCIItable 2D array defined in the
							FSMC_NT35510.h file to represent text characters.
* parameters :X(x start address), Y(y start address), Color(character color), Bcolor(background
							color), Character(use standard ASCII values for characters) and Size(characters size)
* retvalue   :N/A
********************************************************************************************************************************/
void LCD_PrintCh(uint16_t X, uint16_t Y, uint16_t Color, uint16_t Bcolor, uint8_t Character, uint8_t Size)
{
	uint8_t i, j, k, p=0;
	uint16_t c=0;
	LCD_SetWindow(X, Y, X+(8 * Size - 1), Y+(8  *Size - 1));									// Define area by character size.

	for(i=0; i<8; i++)																							// 8 row-loops because there are 8 row-bytes per character.
	{
		for(j=0; j < Size; j++)																					// Print each row size times.
		{
			for(k=0; k < 8; k++)																					// 8 column-loops because there are 8 column-bits per row-byte
			{
				if((ASCIItable[Character][i]>>(7-k)) & 0x01)
					c=Color;
				else
					c=Bcolor;
				for(p = 0; p < Size; p++)																			// Print each column-bit size times.
				{
					FSMC_WR_DAT(c);
				}
			}
		}
	}
}



/********************************************************************************************************************************
* name       :LCD_PrintStr
* date       :May 10.2020
* function   :Prints string of text using LCD_PrintCh function.
* parameters :x(x start address), y(y start address), color(character color), bcolor(background
							color), string(pointer to an array of characters, standard ASCII values) and size
							(character size)
* retvalue   :N/A
********************************************************************************************************************************/
void LCD_PrintStr(uint16_t X, uint16_t Y, uint16_t Color, uint16_t Bcolor, uint8_t* String, uint8_t Size)
{
	X=X-8*Size;
	while(*String)
		LCD_PrintCh(X = X + 8 * Size, Y, Color, Bcolor, *String++, Size);
}



/*******************************************************************************************************************************
 * name       :FSMC_WR_DAT
 * date       :
 * function   :
 * parameters :
 * retvalue   :N/A
 *******************************************************************************************************************************/
void NT35510_Init(void)
{
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

	NRST_LOW;													// Reset on.
	HAL_Delay(300);											// Short delay needed on power up
	NRST_HIGH;													// Reset off.
	HAL_Delay(800);											// Short delay needed on power up

	// Manufacture Command Set selection
	FSMC_WR_REG(MAUCCTR_0);			FSMC_WR_DAT(0x0055U);
	FSMC_WR_REG(MAUCCTR_1);			FSMC_WR_DAT(0x00AAU);
	FSMC_WR_REG(MAUCCTR_2);			FSMC_WR_DAT(0x0052U);
	FSMC_WR_REG(MAUCCTR_3);			FSMC_WR_DAT(0x0008U);		// Enable Manufacture Command Set
	FSMC_WR_REG(MAUCCTR_4);			FSMC_WR_DAT(0x0001U);		// Select page 1

	// AVDD 5.2V
	FSMC_WR_REG(SETAVDD_NORM);		FSMC_WR_DAT(0x000DU);
	FSMC_WR_REG(SETAVDD_IDLE);		FSMC_WR_DAT(0x000DU);
	FSMC_WR_REG(SETAVDD_PART);		FSMC_WR_DAT(0x000DU);

	// AVDD ratio
	FSMC_WR_REG(BT1CTR_NORM);		FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(BT1CTR_IDLE);		FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(BT1CTR_PART);		FSMC_WR_DAT(0x0034U);

	// AVEE  -5.2V
	FSMC_WR_REG(SETAVEE_NORM);		FSMC_WR_DAT(0x000DU);
	FSMC_WR_REG(SETAVEE_IDLE);		FSMC_WR_DAT(0x000DU);
	FSMC_WR_REG(SETAVEE_PART);		FSMC_WR_DAT(0x000DU);

	// AVEE ratio
	FSMC_WR_REG(BT2CTR_NORM);		FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(BT2CTR_IDLE);		FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(BT2CTR_PART);		FSMC_WR_DAT(0x0034U);

	// VCL  -2.5V
	FSMC_WR_REG(SETVCL_NORM);		FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(SETVCL_IDLE);		FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(SETVCL_PART);		FSMC_WR_DAT(0x0000U);

	// VCL ratio
	FSMC_WR_REG(BT3CTR_NORM);		FSMC_WR_DAT(0x0024U);
	FSMC_WR_REG(BT3CTR_IDLE);		FSMC_WR_DAT(0x0024U);
	FSMC_WR_REG(BT3CTR_PART);		FSMC_WR_DAT(0x0024U);

	// VGH  15V
	FSMC_WR_REG(VGHCTR);			FSMC_WR_DAT(0x01);
	FSMC_WR_REG(SETVGH_NORM);		FSMC_WR_DAT(0x000FU);
	FSMC_WR_REG(SETVGH_IDLE);		FSMC_WR_DAT(0x000FU);
	FSMC_WR_REG(SETVGH_PART);		FSMC_WR_DAT(0x000FU);

	// VGH  ratio
	FSMC_WR_REG(BT4CTR_NORM);		FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(BT4CTR_IDLE);		FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(BT4CTR_PART);		FSMC_WR_DAT(0x0034U);

	// VGL_REG  -10V
	FSMC_WR_REG(0xB500);			FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(0xB500);			FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(0xB501);			FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(0xC200);			FSMC_WR_DAT(0x0003U);

	// VGLX  ratio
	FSMC_WR_REG(BT5CTR_NORM);		FSMC_WR_DAT(0x0024U);
	FSMC_WR_REG(BT5CTR_IDLE);		FSMC_WR_DAT(0x0024U);
	FSMC_WR_REG(BT5CTR_PART);		FSMC_WR_DAT(0x0024U);

	// VGMP/VGSP 4.5V/0V
	FSMC_WR_REG(SETVGP_0);			FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(SETVGP_1);			FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(SETVGP_2);			FSMC_WR_DAT(0x0000U);

	// VGMN/VGSN -4.5V/0V
	FSMC_WR_REG(SETVGN_0);			FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(SETVGN_1);			FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(SETVGN_2);			FSMC_WR_DAT(0x0000U);

	// VCOM  -1.325V
	FSMC_WR_REG(SETVCMOFF_0);		FSMC_WR_DAT(0x0000);
	FSMC_WR_REG(SETVCMOFF_1);		FSMC_WR_DAT(0x0089);
/*
	// Gamma Setting
	FSMC_WR_REG(GMRCTR1_BASE | 0x0000U);	FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0001U);	FSMC_WR_DAT(0x002DU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0002U);	FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0003U);	FSMC_WR_DAT(0x002EU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0004U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0005U);    FSMC_WR_DAT(0x0032U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0006U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0007U);    FSMC_WR_DAT(0x0044U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0008U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0009U);    FSMC_WR_DAT(0x0053U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x000AU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x000BU);    FSMC_WR_DAT(0x0088U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x000CU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x000DU);    FSMC_WR_DAT(0x00B6U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x000EU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x000FU);    FSMC_WR_DAT(0x00F3U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0010U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0011U);    FSMC_WR_DAT(0x0022U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0012U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0013U);    FSMC_WR_DAT(0x0064U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0014U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0015U);    FSMC_WR_DAT(0x0092U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0016U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0017U);    FSMC_WR_DAT(0x00D4U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0018U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0019U);    FSMC_WR_DAT(0x0007U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x001AU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x001BU);    FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x001CU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x001DU);    FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x001EU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x001FU);    FSMC_WR_DAT(0x005FU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0020U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0021U);    FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0022U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0023U);    FSMC_WR_DAT(0x0094U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0024U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0025U);    FSMC_WR_DAT(0x00A6U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0026U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0027U);    FSMC_WR_DAT(0x00BBU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0028U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0029U);    FSMC_WR_DAT(0x00CAU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x002AU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x002BU);    FSMC_WR_DAT(0x00DBU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x002CU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x002DU);    FSMC_WR_DAT(0x00E8U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x002EU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x002FU);    FSMC_WR_DAT(0x00F9U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0030U);    FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0031U);    FSMC_WR_DAT(0x001FU);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0032U);    FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMRCTR1_BASE | 0x0033U);    FSMC_WR_DAT(0x007FU);

	FSMC_WR_REG(GMGCTR1_BASE | 0x0000U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0001U);    FSMC_WR_DAT(0x002DU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0002U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0003U);    FSMC_WR_DAT(0x002EU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0004U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0005U);    FSMC_WR_DAT(0x0032U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0006U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0007U);    FSMC_WR_DAT(0x0044U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0008U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0009U);    FSMC_WR_DAT(0x0053U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x000AU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x000BU);    FSMC_WR_DAT(0x0088U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x000CU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x000DU);    FSMC_WR_DAT(0x00B6U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x000EU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x000FU);    FSMC_WR_DAT(0x00F3U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0010U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0011U);    FSMC_WR_DAT(0x0022U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0012U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0013U);    FSMC_WR_DAT(0x0064U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0014U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0015U);    FSMC_WR_DAT(0x0092U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0016U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0017U);    FSMC_WR_DAT(0x00D4U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0018U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0019U);    FSMC_WR_DAT(0x0007U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x001AU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x001BU);    FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x001CU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x001DU);    FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x001EU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x001FU);    FSMC_WR_DAT(0x005FU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0020U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0021U);    FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0022U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0023U);    FSMC_WR_DAT(0x0094U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0024U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0025U);    FSMC_WR_DAT(0x00A6U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0026U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0027U);    FSMC_WR_DAT(0x00BBU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0028U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0029U);    FSMC_WR_DAT(0x00CAU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x002AU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x002BU);    FSMC_WR_DAT(0x00DBU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x002CU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x002DU);    FSMC_WR_DAT(0x00E8U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x002EU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x002FU);    FSMC_WR_DAT(0x00F9U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0030U);    FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0031U);    FSMC_WR_DAT(0x001FU);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0032U);    FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMGCTR1_BASE | 0x0033U);    FSMC_WR_DAT(0x007FU);

	FSMC_WR_REG(GMBCTR1_BASE | 0x0000U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0001U);    FSMC_WR_DAT(0x002DU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0002U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0003U);    FSMC_WR_DAT(0x002EU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0004U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0005U);    FSMC_WR_DAT(0x0032U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0006U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0007U);    FSMC_WR_DAT(0x0044U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0008U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0009U);    FSMC_WR_DAT(0x0053U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x000AU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x000BU);    FSMC_WR_DAT(0x0088U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x000CU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x000DU);    FSMC_WR_DAT(0x00B6U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x000EU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x000FU);    FSMC_WR_DAT(0x00F3U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0010U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0011U);    FSMC_WR_DAT(0x0022U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0012U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0013U);    FSMC_WR_DAT(0x0064U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0014U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0015U);    FSMC_WR_DAT(0x0092U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0016U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0017U);    FSMC_WR_DAT(0x00D4U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0018U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0019U);    FSMC_WR_DAT(0x0007U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x001AU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x001BU);    FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x001CU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x001DU);    FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x001EU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x001FU);    FSMC_WR_DAT(0x005FU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0020U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0021U);    FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0022U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0023U);    FSMC_WR_DAT(0x0094U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0024U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0025U);    FSMC_WR_DAT(0x00A6U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0026U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0027U);    FSMC_WR_DAT(0x00BBU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0028U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0029U);    FSMC_WR_DAT(0x00CAU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x002AU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x002BU);    FSMC_WR_DAT(0x00DBU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x002CU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x002DU);    FSMC_WR_DAT(0x00E8U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x002EU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x002FU);    FSMC_WR_DAT(0x00F9U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0030U);    FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0031U);    FSMC_WR_DAT(0x001FU);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0032U);    FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMBCTR1_BASE | 0x0033U);    FSMC_WR_DAT(0x007FU);

	FSMC_WR_REG(GMRCTR2_BASE | 0x0000U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0001U);    FSMC_WR_DAT(0x002DU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0002U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0003U);    FSMC_WR_DAT(0x002EU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0004U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0005U);    FSMC_WR_DAT(0x0032U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0006U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0007U);    FSMC_WR_DAT(0x0044U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0008U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0009U);    FSMC_WR_DAT(0x0053U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x000AU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x000BU);    FSMC_WR_DAT(0x0088U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x000CU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x000DU);    FSMC_WR_DAT(0x00B6U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x000EU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x000FU);    FSMC_WR_DAT(0x00F3U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0010U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0011U);    FSMC_WR_DAT(0x0022U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0012U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0013U);    FSMC_WR_DAT(0x0064U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0014U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0015U);    FSMC_WR_DAT(0x0092U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0016U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0017U);    FSMC_WR_DAT(0x00D4U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0018U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0019U);    FSMC_WR_DAT(0x0007U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x001AU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x001BU);    FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x001CU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x001DU);    FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x001EU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x001FU);    FSMC_WR_DAT(0x005FU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0020U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0021U);    FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0022U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0023U);    FSMC_WR_DAT(0x0094U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0024U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0025U);    FSMC_WR_DAT(0x00A6U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0026U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0027U);    FSMC_WR_DAT(0x00BBU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0028U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0029U);    FSMC_WR_DAT(0x00CAU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x002AU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x002BU);    FSMC_WR_DAT(0x00DBU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x002CU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x002DU);    FSMC_WR_DAT(0x00E8U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x002EU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x002FU);    FSMC_WR_DAT(0x00F9U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0030U);    FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0031U);    FSMC_WR_DAT(0x001FU);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0032U);    FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMRCTR2_BASE | 0x0033U);    FSMC_WR_DAT(0x007FU);

	FSMC_WR_REG(GMGCTR2_BASE | 0x0000U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0001U);    FSMC_WR_DAT(0x002DU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0002U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0003U);    FSMC_WR_DAT(0x002EU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0004U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0005U);    FSMC_WR_DAT(0x0032U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0006U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0007U);    FSMC_WR_DAT(0x0044U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0008U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0009U);    FSMC_WR_DAT(0x0053U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x000AU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x000BU);    FSMC_WR_DAT(0x0088U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x000CU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x000DU);    FSMC_WR_DAT(0x00B6U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x000EU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x000FU);    FSMC_WR_DAT(0x00F3U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0010U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0011U);    FSMC_WR_DAT(0x0022U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0012U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0013U);    FSMC_WR_DAT(0x0064U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0014U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0015U);    FSMC_WR_DAT(0x0092U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0016U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0017U);    FSMC_WR_DAT(0x00D4U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0018U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0019U);    FSMC_WR_DAT(0x0007U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x001AU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x001BU);    FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x001CU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x001DU);    FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x001EU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x001FU);    FSMC_WR_DAT(0x005FU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0020U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0021U);    FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0022U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0023U);    FSMC_WR_DAT(0x0094U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0024U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0025U);    FSMC_WR_DAT(0x00A6U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0026U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0027U);    FSMC_WR_DAT(0x00BBU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0028U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0029U);    FSMC_WR_DAT(0x00CAU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x002AU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x002BU);    FSMC_WR_DAT(0x00DBU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x002CU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x002DU);    FSMC_WR_DAT(0x00E8U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x002EU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x002FU);    FSMC_WR_DAT(0x00F9U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0030U);    FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0031U);    FSMC_WR_DAT(0x001FU);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0032U);    FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMGCTR2_BASE | 0x0033U);    FSMC_WR_DAT(0x007FU);

	FSMC_WR_REG(GMBCTR2_BASE | 0x0000U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0001U);    FSMC_WR_DAT(0x002DU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0002U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0003U);    FSMC_WR_DAT(0x002EU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0004U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0005U);    FSMC_WR_DAT(0x0032U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0006U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0007U);    FSMC_WR_DAT(0x0044U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0008U);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0009U);    FSMC_WR_DAT(0x0053U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x000AU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x000BU);    FSMC_WR_DAT(0x0088U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x000CU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x000DU);    FSMC_WR_DAT(0x00B6U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x000EU);    FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x000FU);    FSMC_WR_DAT(0x00F3U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0010U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0011U);    FSMC_WR_DAT(0x0022U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0012U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0013U);    FSMC_WR_DAT(0x0064U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0014U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0015U);    FSMC_WR_DAT(0x0092U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0016U);    FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0017U);    FSMC_WR_DAT(0x00D4U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0018U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0019U);    FSMC_WR_DAT(0x0007U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x001AU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x001BU);    FSMC_WR_DAT(0x0008U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x001CU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x001DU);    FSMC_WR_DAT(0x0034U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x001EU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x001FU);    FSMC_WR_DAT(0x005FU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0020U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0021U);    FSMC_WR_DAT(0x0078U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0022U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0023U);    FSMC_WR_DAT(0x0094U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0024U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0025U);    FSMC_WR_DAT(0x00A6U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0026U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0027U);    FSMC_WR_DAT(0x00BBU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0028U);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0029U);    FSMC_WR_DAT(0x00CAU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x002AU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x002BU);    FSMC_WR_DAT(0x00DBU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x002CU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x002DU);    FSMC_WR_DAT(0x00E8U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x002EU);    FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x002FU);    FSMC_WR_DAT(0x00F9U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0030U);    FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0031U);    FSMC_WR_DAT(0x001FU);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0032U);    FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(GMBCTR2_BASE | 0x0033U);    FSMC_WR_DAT(0x007FU);
*/
	//**************************************************************************************************************************//

	// Select Page 0
	FSMC_WR_REG(MAUCCTR_0);			FSMC_WR_DAT(0x0055U);
	FSMC_WR_REG(MAUCCTR_1);			FSMC_WR_DAT(0x00AAU);
	FSMC_WR_REG(MAUCCTR_2);			FSMC_WR_DAT(0x0052U);
	FSMC_WR_REG(MAUCCTR_3);			FSMC_WR_DAT(0x0008U);		// Enable Manufacture Command Set
	FSMC_WR_REG(MAUCCTR_4);			FSMC_WR_DAT(0x0000U);		// Select page 0

	// DISPLAY CONTROL
	FSMC_WR_REG(DOPCTR_0);			FSMC_WR_DAT(0x00CCU);
	FSMC_WR_REG(DOPCTR_1);			FSMC_WR_DAT(0x0000U);

	FSMC_WR_REG(DPRSLCTR);			FSMC_WR_DAT(0x0050U);			// Display Resolution 480RGB x 800

	// SOURCE HOLD TIME
	FSMC_WR_REG(SDHDTCTR);			FSMC_WR_DAT(0x0005U);

	// Set Gate EQ
	FSMC_WR_REG(GSEQCTR_ST);		FSMC_WR_DAT(0x0070U);
	FSMC_WR_REG(GSEQCTR_CK);		FSMC_WR_DAT(0x0070U);

	// Source EQ control (Mode 2)
	FSMC_WR_REG(SDEQCTR_MOD );	FSMC_WR_DAT(0x0001U);
	FSMC_WR_REG(SDEQCTR_EQS1);	FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(SDEQCTR_EQS2);	FSMC_WR_DAT(0x0003U);
	FSMC_WR_REG(SDEQCTR_EQS3);	FSMC_WR_DAT(0x0003U);

	// INVERSION MODE
	FSMC_WR_REG(INVCTR_NORM);		FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(INVCTR_IDLE);		FSMC_WR_DAT(0x0000U);
	FSMC_WR_REG(INVCTR_PART);		FSMC_WR_DAT(0x0000U);

	// Timing control
	FSMC_WR_REG(0xC900);				FSMC_WR_DAT(0x00D0U);
	FSMC_WR_REG(0xC901);				FSMC_WR_DAT(0x0002U);
	FSMC_WR_REG(0xC902);				FSMC_WR_DAT(0x0050U);
	FSMC_WR_REG(0xC903);				FSMC_WR_DAT(0x0050U);
	FSMC_WR_REG(0xC904);				FSMC_WR_DAT(0x0050U);

	//**************************************************************************************************************************//
	// User Command Set
	FSMC_WR_REG(TEON);   				FSMC_WR_DAT(0x0000U);			// V-Blanking information only


	FSMC_WR_REG(COLMOD);   			FSMC_WR_DAT(0x0055U);		// RGB and MCU Interface Data format 16-Bits
	FSMC_WR_REG(MADCTL);   			FSMC_WR_DAT(0x0000U);		// MADCTL: MY MX MV RGB MH RSMX RSMY


	FSMC_WR_REG(SLPOUT);   						// Sleep Out

	HAL_Delay(120);

	FSMC_WR_REG(DISPON);   						// Display On

	HAL_Delay(200);

	LCD_SetDirection(VERTICAL_UP);		// Vertical-up display orientation as default
}





