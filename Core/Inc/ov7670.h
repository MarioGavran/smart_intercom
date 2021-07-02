/*
 * ov7670.h
 *
 *  Created on: Apr 6, 2021
 *      Author: Mario
 */

#ifndef SRC_OV7670_H_
#define SRC_OV7670_H_

#include <stdint.h>
#include <stdbool.h>
#include "i2c_driver.h"



extern char g_cam_buff[];
extern char g_cam_gray_frame[];



#define OV7670_RST_HIGH				HAL_GPIO_WritePin(OV7670_RST_GPIO_Port, OV7670_RST_Pin, GPIO_PIN_SET)
#define OV7670_RST_LOW				HAL_GPIO_WritePin(OV7670_RST_GPIO_Port, OV7670_RST_Pin, GPIO_PIN_RESET)

#define OV7670_FRAME_SIZE_VGA		640*480*2	// not enough RAM
#define OV7670_FRAME_SIZE_QVGA		320*240*2	// 153600
#define OV7670_FRAME_SIZE_QQVGA		160*120*2

#define OV7670_GRAY_SIZE			96*96



//~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
typedef enum {
	QQQVGA_RGB565,
	QQVGA_RGB565,
	QVGA_RGB565
}ov7670_res_fmt_t;



void ov7670_saturation(int8_t s);
void ov7670_frame_control(int16_t hStart,  int16_t vStart);
void ov7670_subsampling_control(int8_t com14, int8_t downSample, int8_t pclk_div);
void ov7670_test_pattern(uint8_t kind);
void ov7670_write_register(unsigned char reg, unsigned char val);
uint8_t ov7670_read_register(unsigned char reg);
void ov7670_set_mode(ov7670_res_fmt_t resolution, uint16_t exposure);
void ov7670_init();

void EXTI0_HREF_Callback();
void EXTI1_VSYNC_Callback();

//..........NAME:...................ADDRESS....DEFAULT..R/W/RW......COMMENT.....................................................................................
#define		OV7670_GAIN 			0x00	// 00 		RW			AGC – Gain control gain setting
#define		OV7670_BLUE 			0x01	// 80 		RW			AWB – Blue channel gain setting
#define		OV7670_RED 				0x02	// 80 		RW			AWB – Red channel gain setting
#define		OV7670_VREF 			0x03	// 00 		RW			Vertical Frame Control: AGC[9:8], VSTOP[1:0], VSTRT[1:0]
#define		OV7670_COM1 			0x04	// 00 		RW			Common Control 1: CCIR656, AEC[1:0]
#define		OV7670_BAVE 			0x05	// 00 		RW			U/B Average Level
#define		OV7670_GbAVE 			0x06	// 00 		RW			Y/Gb Average Level
#define		OV7670_AECHH	 		0x07	// 00 		RW			Exposure Value - AEC[15:10]
#define		OV7670_RAVE 			0x08	// 00 		RW			V/R Average Level
#define		OV7670_COM2	 			0x09	// 01 		RW			Common Control 2: Soft sleep mode, Output drive capability
#define		OV7670_PID 				0x0A	// 76 		R			Product ID Number MSB
#define		OV7670_VER 				0x0B	// 73 		R			Product ID Number LSB
#define		OV7670_COM3	 			0x0C	// 00 		RW			Common Control 3: Output data MSB/LSB swap, Tri-state output clock & data, Scale & DCW enable
#define		OV7670_COM4	 			0x0D	// 00 		RW			Common Control 4: Average option (must be same value as COM17[7:6])
#define		OV7670_COM5 			0x0E	// 01 		RW			Common Control 5: reserved
#define		OV7670_COM6 			0x0F	// 43 		RW			Common Control 6: Output optical black line, Reset all timing on format change
#define		OV7670_AECH 			0x10	// 40 		RW			Exposure Value - AEC[9:2]
#define		OV7670_CLKRC 			0x11	// 80 		RW			Internal Clock pre-scalar
#define		OV7670_COM7 			0x12	// 00 		RW			Common Control 7: SCCB Register Reset, Output format(CIF,QVGA,QCIF,RGB), Color bar
#define		OV7670_COM8 			0x13	// 8F 		RW			Common Control 8: fast AGC/AEC, AEC Step size limit, Banding filter enable, AGC/AWB/AEC enable
#define		OV7670_COM9 			0x14	// 4A 		RW			Common Control 9: max AGC value, Freeze AGC/AEC
#define		OV7670_COM10 			0x15	// 00 		RW			Common Control 10: HREF/HSYNC, PCLK/VSYNC option, PCLK/HREF reverse, VSYNC/HSYNC neg
#define		OV7670_HSTART 			0x17	// 11 		RW			HSTRT[10:3]
#define		OV7670_HSTOP 			0x18	// 61 		RW			HSTOP[10:3]
#define		OV7670_VSTRT 			0x19	// 03 		RW			VSTRT[9:2]
#define		OV7670_VSTOP 			0x1A	// 7B 		RW			VSTOP[9:2]
#define		OV7670_PSHFT 			0x1B	// 00 		RW			Pixel Delay Select - delays D[7:0] relative to HREF in pixel units
#define		OV7670_MIDH 			0x1C	// 7F 		R			Manufacturer ID HIGH Byte
#define		OV7670_MIDL 			0x1D	// A2 		R			Manufacturer ID LOW Byte
#define		OV7670_MVFP 			0x1E	// 01 		RW			Mirror/VFlip Enable
#define		OV7670_LAEC 			0x1F	// 00 		RW			Reserved
#define		OV7670_ADCCTR0 			0x20	// 04 		RW			ADC Control: ADC range and reference adjustment
#define		OV7670_ADCCTR1 			0x21	// 02 		RW			Reserved
#define		OV7670_ADCCTR2 			0x22	// 01 		RW			Reserved
#define		OV7670_ADCCTR3 			0x23	// 00 		RW			Reserved
#define		OV7670_AEW 				0x24	// 75 		RW			AGC/AEC - Stable Operating Region (Upper Limit)
#define		OV7670_AEB 				0x25	// 63 		RW			AGC/AEC - Stable Operating Region (Lower Limit)
#define		OV7670_VPT 				0x26	// D4 		RW			AGC/AEC Fast Mode Operating Region
#define		OV7670_BBIAS 			0x27	// 80 		RW			B Channel Signal Output Bias
#define		OV7670_GbBIAS 			0x28	// 80 		RW			Gb Channel Signal Output Bias
#define		OV7670_EXHCH 			0x2A	// 00 		RW			Dummy Pixel Insert MSB: 4 MSB insert in h direction, HSYNC falling & rising edge delay 2 MSB
#define		OV7670_EXHCL 			0x2B	// 00 		RW			Dummy Pixel Insert LSB: 8 LSB insert in h direction
#define		OV7670_RBIAS 			0x2C	// 80 		RW			R Channel Signal Output Bias
#define		OV7670_ADVFL 			0x2D	// 00 		RW			LSB of Insert Dummy Lines in Vertical Direction
#define		OV7670_ADVFH 			0x2E	// 00 		RW			MSB of Insert Dummy Lines in Vertical Direction
#define		OV7670_YAVE 			0x2F	// 00 		RW			Y/G Channel Average Value
#define		OV7670_HSYST 			0x30	// 08 		RW			HSYNC Rising Edge Delay LSB
#define		OV7670_HSYEN 			0x31	// 30 		RW			HSYNC Falling Edge Delay LSB
#define		OV7670_HREF 			0x32	// 80 		RW			HREF Control: HREF edge offset to data output, HSTRT[2:0], HSTOP[2:0]
#define		OV7670_CHLF 			0x33	// 08 		RW			Array Current Control: Reserved
#define		OV7670_ARBLM 			0x34	// 11 		RW			Array Reference Control: Reserved
#define		OV7670_ADC 				0x37	// 3F 		RW			ADC Control: Reserved
#define		OV7670_ACOM 			0x38	// 01 		RW			ADC and Analog Common Mode Control: Reserved
#define		OV7670_OFON 			0x39	// 00 		RW			ADC Offset Control: Reserved
#define		OV7670_TSLB 			0x3A	// 0D 		RW			Line Buffer Test Option: Neg. image enable, UV out. value, Out. seq., Auto out. window
#define		OV7670_COM11 			0x3B	// 00 		RW			Common Control 11: Night mode, Min frame rate, D56_Auto, Banding filter, Exposure timing
#define		OV7670_COM12 			0x3C	// 68 		RW			Common Control 12: HREF option
#define		OV7670_COM13 			0x3D	// 88 		RW			Common Control 13: Gamma en., UV saturation level, UV swap
#define		OV7670_COM14 			0x3E	// 00 		RW			Common Control 14: DCW and scaling PCLK enable, Manual scaling enable, PCLK divider
#define		OV7670_EDGE 			0x3F	// 00 		RW			Edge Enhancement Adjustment
#define		OV7670_COM15 			0x40	// C0 		RW			Common Control 15: Data format, RGB 555/565 option
#define		OV7670_COM16 			0x41	// 08 		RW			Common Control 16: Denoise & YUV edge enhanc trhld auto-adj, AWB gain, Color matrix option
#define		OV7670_COM17 			0x42	// 00 		RW			Common Control 17: AEC window, DSP color bar enable
#define		OV7670_AWBC1 			0x43	// 14 		RW			Reserved
#define		OV7670_AWBC2 			0x44	// F0 		RW			Reserved
#define		OV7670_AWBC3 			0x45	// 45 		RW			Reserved
#define		OV7670_AWBC4 			0x46	// 61 		RW			Reserved
#define		OV7670_AWBC5 			0x47	// 51 		RW			Reserved
#define		OV7670_AWBC6 			0x48	// 79 		RW			Reserved
#define		OV7670_REG4B 			0x4B	// 00 		RW			Register 4B: UV average enable
#define		OV7670_DNSTH 			0x4C	// 00 		RW			De-noise Strength
#define		OV7670_DM_POS 			0x4D	// 00 		RW			Dummy row position
#define		OV7670_MTX1 			0x4F	// 40 		RW			Matrix Coefficient 1
#define		OV7670_MTX2 			0x50	// 34 		RW			Matrix Coefficient 2
#define		OV7670_MTX3 			0x51	// 0C 		RW			Matrix Coefficient 3
#define		OV7670_MTX4 			0x52	// 17 		RW			Matrix Coefficient 4
#define		OV7670_MTX5 			0x53	// 29 		RW			Matrix Coefficient 5
#define		OV7670_MTX6 			0x54	// 40 		RW			Matrix Coefficient 6
#define		OV7670_BRIGHT 			0x55	// 00 		RW			Brightness Control
#define		OV7670_CONTR 			0x56	// 40 		RW			Contrast Control
#define		OV7670_CONTR_CNTR		0x57	// 80 		RW			Contrast Center
#define		OV7670_MTXS 			0x58	// 1E 		RW			Matrix Coefficient Sign for Coefficient 5 - 0
#define		OV7670_AWBC7 			0x59	// 1E 		RW			AWB COntrol 7
#define		OV7670_AWBC8 			0x5A	// 1E 		RW			AWB COntrol 8
#define		OV7670_AWBC9 			0x5B	// 1E 		RW			AWB COntrol 9
#define		OV7670_AWBC10 			0x5C	// 1E 		RW			AWB COntrol 10
#define		OV7670_AWBC11 			0x5D	// 1E 		RW			AWB COntrol 11
#define		OV7670_AWBC12 			0x5E	// 1E 		RW			AWB COntrol 12
#define		OV7670_B_LMT 			0x5F	// 1E 		RW			AWB B Gain Range
#define		OV7670_R_LMT 			0x60	// 1E 		RW			AWB R Gain Range
#define		OV7670_G_LMT 			0x61	// 1E 		RW			AWB G Gain Range
#define		OV7670_LCC1 			0x62	// 00 		RW			Lens Correction Option 1: X Coordinate of Lens Correction Center Relative to Array Center
#define		OV7670_LCC2 			0x63	// 00 		RW			Lens Correction Option 2: Y Coordinate of Lens Correction Center Relative to Array Center
#define		OV7670_LCC3 			0x64	// 50 		RW			Lens Correction Option 3
#define		OV7670_LCC4 			0x65	// 30 		RW			Lens Correction Option 4
#define		OV7670_LCC5 			0x66	// 00 		RW			Lens Correction Option 5
#define		OV7670_MANU 			0x67	// 80 		RW			Manual U Value
#define		OV7670_MANV 			0x68	// 80 		RW			Manual V Value
#define		OV7670_GFIX 			0x69	// 00 		RW			Fix Gain Control: Gr, Gb, R and B channel
#define		OV7670_GGAIN 			0x6A	// 00 		RW			G Channel AWB Gain
#define		OV7670_DBLV 			0x6B	// 0A 		RW			DBLV: PLL control, Regulator control
#define		OV7670_AWBCTR3 			0x6C	// 02 		RW			AWB Control 3
#define		OV7670_AWBCTR2 			0x6D	// 55 		RW			AWB Control 2
#define		OV7670_AWBCTR1 			0x6E	// C0 		RW			AWB Control 1
#define		OV7670_AWBCTR0 			0x6F	// 9A 		RW			AWB Control 0
#define		OV7670_SCL_XSC 			0x70	// 3A 		RW			SCALING_XSC: Test_pattern[0]
#define		OV7670_SCL_YSC 			0x71	// 35 		RW			SCALING_YSC: Test_pattern[1]
#define		OV7670_SCL_DCWCTR 		0x72	// 11 		RW			DCW Control: Vertical average & dwn sampling, Horizontal average & dwn sampling
#define		OV7670_SCL_PCLK_DIV 	0x73	// 00 		RW			Scaling and PCLK divider
#define		OV7670_REG74 			0x74	// 00 		RW			Register 74: DG_Manu VREF/REG74, Digital gain manual control
#define		OV7670_REG75 			0x75	// 0F 		RW			Register 75: Edge enhancement lower limit
#define		OV7670_REG76 			0x76	// 01 		RW			Register 76: Black & White pixel correction enable, Edge enhancement higher limit
#define		OV7670_REG77 			0x77	// 10 		RW			Register 77: De-noise offset
#define		OV7670_SLOP 			0x7A	// 24 		RW			Gamma Curve Highest Segment Slope
#define		OV7670_GAM1 			0x7B	// 04 		RW			Gamma Curve 1st Segment Input End Point 0x04 Output Value
#define		OV7670_GAM2 			0x7C	// 07 		RW			Gamma Curve 2nd Segment Input End Point 0x08 Output Value
#define		OV7670_GAM3 			0x7D	// 10 		RW			Gamma Curve 3rd Segment Input End Point 0x10 Output Value
#define		OV7670_GAM4 			0x7E	// 28 		RW			Gamma Curve 4th Segment Input End Point 0x20 Output Value
#define		OV7670_GAM5 			0x7F	// 36 		RW			Gamma Curve 5th Segment Input End Point 0x28 Output Value
#define		OV7670_GAM6 			0x80	// 44 		RW			Gamma Curve 6th Segment Input End Point 0x30 Output Value
#define		OV7670_GAM7 			0x81	// 52 		RW			Gamma Curve 7th Segment Input End Point 0x38 Output Value
#define		OV7670_GAM8 			0x82	// 60 		RW			Gamma Curve 8th Segment Input End Point 0x40 Output Value
#define		OV7670_GAM9 			0x83	// 6C 		RW			Gamma Curve 9th Segment Input End Point 0x48 Output Value
#define		OV7670_GAM10 			0x84	// 78 		RW			Gamma Curve 10th Segment Input End Point 0x50 Output Value
#define		OV7670_GAM11 			0x85	// 8C 		RW			Gamma Curve 11th Segment Input End Point 0x60 Output Value
#define		OV7670_GAM12 			0x86	// 9E 		RW			Gamma Curve 12th Segment Input End Point 0x70 Output Value
#define		OV7670_GAM13 			0x87	// BB 		RW			Gamma Curve 13th Segment Input End Point 0x90 Output Value
#define		OV7670_GAM14 			0x88	// D2 		RW			Gamma Curve 14th Segment Input End Point 0xB0 Output Value
#define		OV7670_GAM15 			0x89	// E5 		RW			Gamma Curve 15th Segment Input End Point 0xD0 Output Value
#define		OV7670_RGB444 			0x8C	// 00 		RW			RGB444 enable, word format
#define		OV7670_DM_LNL 			0x92	// 00 		RW			Dummy Line low 8 bits
#define		OV7670_DM_LNH 			0x93	// 00 		RW			Dummy Line high 8 bits
#define		OV7670_LCC6 			0x94	// 50 		RW			Lens Correction Option 6
#define		OV7670_LCC7 			0x95	// 50 		RW			Lens Correction Option 7
#define		OV7670_BD50ST 			0x9D	// 99 		RW			50 Hz Banding Filter Value
#define		OV7670_BD60ST 			0x9E	// 7F 		RW			60 Hz Banding Filter Value
#define		OV7670_HAECC1 			0x9F	// C0 		RW			Histogram-based AEC/AGC Control 1
#define		OV7670_HAECC2 			0xA0	// 90 		RW			Histogram-based AEC/AGC Control 2
#define		OV7670_DSPC3 			0xA1	// 03 		RW			DSP Control 3
#define		OV7670_SCL_PCLK_DLY 	0xA2	// 02 		RW			Pixel Clock Delay
#define		OV7670_NT_CTRL 			0xA4	// 00 		RW			Auto frame rate adjustment
#define		OV7670_BD50MAX 			0xA5	// 0F 		RW			50Hz Banding Step Limit
#define		OV7670_HAECC3 			0xA6	// F0 		RW			Histogram-based AEC/AGC Control 3
#define		OV7670_HAECC4 			0xA7	// C1 		RW			Histogram-based AEC/AGC Control 4
#define		OV7670_HAECC5 			0xA8	// F0 		RW			Histogram-based AEC/AGC Control 5
#define		OV7670_HAECC6 			0xA9	// C1 		RW			Histogram-based AEC/AGC Control 6
#define		OV7670_HAECC7 			0xAA	// 14 		RW			Histogram-based AEC/AGC Control 7: AEC algorithm selection
#define		OV7670_BD60MAX 			0xAB	// 0F 		RW			60Hz Banding Step Limit
#define		OV7670_STR_OPT 			0xAC	// 00 		RW			Register AC: Strobe enable, R / G / B gain control, Xenon mode option, Mode select
#define		OV7670_STR_R 			0xAD	// 80 		RW			R Gain for LED Output Frame
#define		OV7670_STR_G 			0xAE	// 80 		RW			G Gain for LED Output Frame
#define		OV7670_STR_B 			0xAF	// 80 		RW			B Gain for LED Output Frame
#define		OV7670_ABLC1 			0xB1	// 00 		RW			ABLC enable
#define		OV7670_THL_ST 			0xB3	// 80 		RW			ABLC Target
#define		OV7670_THL_DLT 			0xB5	// 04 		RW			ABLC Stable Range
#define		OV7670_AD_CHB 			0xBE	// 00 		RW			Blue Channel Black Level Compensation
#define		OV7670_AD_CHR 			0xBF	// 00 		RW			Red Channel Black Level Compensation
#define		OV7670_AD_CHGb 			0xC0	// 00 		RW			Gb Channel Black Level Compensation
#define		OV7670_AD_CHGr 			0xC1	// 00 		RW			Gr Channel Black Level Compensation
#define		OV7670_SATCTR 			0xC9	// C0 		RW			Saturation Control



#define		TSLB_NEG				0x20    //< TSLB Negative image enable
#define		TSLB_YLAST				0x04    //< TSLB UYVY or VYUY, see COM13
#define		TSLB_AOW				0x01    //< TSLB Auto output window

#define  	COM3_SWAP				0x40	// Byte swap
#define  	COM3_SCALEEN			0x08	// Enable scaling
#define  	COM3_DCWEN	  			0x04	// Enable downsamp/crop/window

#define		COM7_RESET	  			0x80	// Register reset
#define		COM7_FMT_MASK			0x38
#define		COM7_FMT_VGA			0x00
#define		COM7_FMT_CIF			0x20	// CIF format
#define		COM7_FMT_QVGA			0x10	// QVGA format
#define		COM7_FMT_QCIF			0x08	// QCIF format
#define		COM7_RGB				0x04	// bits 0 and 2 - RGB format
#define		COM7_YUV				0x00	// YUV
#define		COM7_BAYER				0x01	// Bayer format
#define		COM7_PBAYER				0x05	// "Processed bayer"

#define		COM8_FASTAEC	 		0x80	// Enable fast AGC/AEC
#define		COM8_AECSTEP	  		0x40	// Unlimited AEC step size
#define		COM8_BFILT	  			0x20	// Band filter enable
#define		COM8_AGC	  			0x04	// Auto gain enable
#define		COM8_AWB	  			0x02	// White balance enable
#define		COM8_AEC	  			0x01	// Auto exposure enable

#define		COM8_FASTAEC			0x80    // COM8 Enable fast AGC/AEC algo,
#define		COM8_AECSTEP			0x40    // COM8 AEC step size unlimited
#define		COM8_BANDING			0x20    // COM8 Banding filter enable
#define		COM8_AGC				0x04    // COM8 AGC (auto gain) enable
#define		COM8_AWB				0x02    // COM8 AWB (auto white balance)
#define		COM8_AEC				0x01    // COM8 AEC (auto exposure) enable

#define COM10_HSYNC 				0x40    // COM10 HREF changes to HSYNC
#define COM10_PCLK_HB 				0x20    // COM10 Suppress PCLK on hblank
#define COM10_HREF_REV 				0x08   	// COM10 HREF reverse
#define COM10_VS_EDGE				0x04   	// COM10 VSYNC chg on PCLK rising
#define COM10_VS_NEG				0x02   	// COM10 VSYNC negative
#define COM10_HS_NEG				0x01   	// COM10 HSYNC negative

// Night mode, flicker, banding /
#define REG_COM11                   0x3b    // Control 11
#define COM11_NIGHT                 0x80    // NIght mode enable
#define COM11_NIGHT_MIN_RATE_1_1    0x00    // Normal mode same
#define COM11_NIGHT_MIN_RATE_1_2    0x20    // Normal mode 1/2
#define COM11_NIGHT_MIN_RATE_1_4    0x40    // Normal mode 1/4
#define COM11_NIGHT_MIN_RATE_1_8    0x60    // Normal mode 1/5
#define COM11_HZAUTO_ON             0x10    // Auto detect 50/60 Hz on
#define COM11_HZAUTO_OFF            0x00    // Auto detect 50/60 Hz off
#define COM11_60HZ                  0x00    // Manual 60Hz select
#define COM11_50HZ                  0x08    // Manual 50Hz select
#define COM11_EXP                   0x02

#define		COM13_GAMMA				0x80	// Gamma enable
#define		COM13_UVSAT				0x40	// UV saturation auto adjustment
#define 	COM13_UVSWAP			0x01	// V before U - w/TSLB

#define		COM16_AWBGAIN			0x08	// AWB gain enable

#define 	COM15_R10F0 	 	 	0x00	// Data range 10 to F0
#define 	COM15_R01FE 	 	 	0x80	//            01 to FE
#define 	COM15_R00FF 	 	 	0xc0	//            00 to FF
#define 	COM15_RGB565 	 	 	0x10	// RGB565 output
#define 	COM15_RGB555 	 	 	0x30	// RGB555 output


#endif /* SRC_OV7670_H_ */
