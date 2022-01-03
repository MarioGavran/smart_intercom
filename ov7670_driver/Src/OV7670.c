#include "../Inc/OV7670.h"
#include "ov7670.h"

static int ov7670_read_i2c(struct ov7670_info *info, unsigned char reg, unsigned char *value);
static int ov7670_write_i2c(struct ov7670_info *info, unsigned char reg, unsigned char value);
static int ov7670_read(struct ov7670_info *info, unsigned char reg, unsigned char *value);
static int ov7670_write(struct ov7670_info *info, unsigned char reg, unsigned char value);
static int ov7670_update_bits(struct ov7670_info *info, unsigned char reg, unsigned char mask, unsigned char value);
static int ov7670_write_array(struct ov7670_info *info, struct regval_list *vals);
static int ov7670_reset(struct ov7670_info *info, u32 val);
static int ov7670_init(struct ov7670_info *info, u32 val);
static int ov7670_detect(struct ov7670_info *info);
static void ov7675_get_framerate(struct ov7670_info *info, struct v4l2_fract *tpf);
static int ov7675_apply_framerate(struct ov7670_info *info);
static int ov7675_set_framerate(struct ov7670_info *info, struct v4l2_fract *tpf);
static void ov7670_get_framerate_legacy(struct ov7670_info *info, struct v4l2_fract *tpf);
static int ov7670_set_framerate_legacy(struct ov7670_info *info, struct v4l2_fract *tpf);
static int ov7670_set_hw(struct ov7670_info *info, int hstart, int hstop, int vstart, int vstop);
static int ov7670_enum_mbus_code(struct ov7670_info *info, struct v4l2_subdev_mbus_code_enum *code);
static int ov7670_try_fmt_internal(struct ov7670_info *info,
		struct v4l2_mbus_framefmt *fmt,
		struct ov7670_format_struct **ret_fmt,
		struct ov7670_win_size **ret_wsize);
static int ov7670_apply_fmt(struct ov7670_info *info);
static int ov7670_set_fmt(struct ov7670_info *info, struct v4l2_subdev_format *format);
static int ov7670_get_fmt(struct ov7670_info *info,
			  struct v4l2_subdev_state *sd_state,
			  struct v4l2_subdev_format *format);
static int ov7670_g_frame_interval(struct ov7670_info *info, struct v4l2_subdev_frame_interval *ival);
static int ov7670_s_frame_interval(struct ov7670_info *info, struct v4l2_subdev_frame_interval *ival);
static int ov7670_enum_frame_interval(struct ov7670_info *info, struct v4l2_subdev_frame_interval_enum *fie);
static int ov7670_enum_frame_size(struct ov7670_info *info,
				  struct v4l2_subdev_state *sd_state,
				  struct v4l2_subdev_frame_size_enum *fse);
static int ov7670_store_cmatrix(struct ov7670_info *info, int matrix[CMATRIX_LEN]);
static int ov7670_sine(int theta);
static int ov7670_cosine(int theta);
static void ov7670_calc_cmatrix(struct ov7670_info *info, int matrix[CMATRIX_LEN], int sat, int hue);
static int ov7670_s_sat_hue(struct ov7670_info *info, int sat, int hue);
static unsigned char ov7670_abs_to_sm(unsigned char v);
static int ov7670_s_brightness(struct ov7670_info *info, int value);
static int ov7670_s_contrast(struct ov7670_info *info, int value);
static int ov7670_s_hflip(struct ov7670_info *info, int value);
static int ov7670_s_vflip(struct ov7670_info *info, int value);
static int ov7670_g_gain(struct ov7670_info *info, __s32 *value);
static int ov7670_s_gain(struct ov7670_info *info, int value);
static int ov7670_s_autogain(struct ov7670_info *info, int value);
static int ov7670_s_exp(struct ov7670_info *info, int value);
static int ov7670_s_autoexp(struct ov7670_info *info, enum v4l2_exposure_auto_type value);
static int ov7670_s_test_pattern(struct ov7670_info *info, int value);
static int ov7670_g_volatile_ctrl(struct ov7670_info *info, struct v4l2_ctrl *ctrl);
static int ov7670_s_ctrl(struct ov7670_info *info, struct v4l2_ctrl *ctrl);
static void ov7670_power_on(struct ov7670_info *info);
static void ov7670_power_off(struct ov7670_info *info);
static int ov7670_s_power(struct ov7670_info *info, int on);



enum ov7670_model {
	MODEL_OV7670 = 0,
	MODEL_OV7675,
};




/*************************************************************************************
 * The default register settings, as obtained from OmniVision.  There
 * is really no making sense of most of these - lots of "reserved" values
 * and such.
 *
 * These settings give VGA YUYV.
*************************************************************************************/
static struct regval_list ov7670_default_regs[] = {
	{ OV7670_COM7, COM7_RESET },

	/* Clock scale: 3 = 15fps, 2 = 20fps, 1 = 30fps*/
	{ OV7670_CLKRC, 0x01 },	/* OV: clock scale (30 fps) */
	{ OV7670_TSLB,  0x04 },	/* OV */
	{ OV7670_COM7, 	0x00 },	/* VGA */
	/* Set the hardware window.  These values from OV don't entirely
	 * make sense - hstop is less than hstart.  But they work...*/
	{ OV7670_HSTART,		0x13 },				{ OV7670_HSTOP,			0x01 },
	{ OV7670_HREF, 			0xb6 },				{ OV7670_VSTRT, 		0x02 },
	{ OV7670_VSTOP, 		0x7a },				{ OV7670_VREF, 			0x0a },

	{ OV7670_COM3, 			0x00 },				{ OV7670_COM14, 		0x00 },
	/* Mystery scaling numbers */
	{ OV7670_SCL_XSC,		0x3a },
	{ OV7670_SCL_YSC,		0x35 },
	{ OV7670_SCL_DCWCTR,	0x11 },				{ OV7670_SCL_PCLK_DIV,	0xf1 },//f0
	{ OV7670_SCL_PCLK_DLY, 	0x02 },				{ OV7670_COM10,			0x00 },

	/* Gamma curve values */
	{ OV7670_SLOP,			0x20 },				{ OV7670_GAM1, 			0x10 },
	{ OV7670_GAM2,			0x1e },				{ OV7670_GAM3, 			0x35 },
	{ OV7670_GAM4, 			0x5a },				{ OV7670_GAM5, 			0x69 },
	{ OV7670_GAM6, 			0x76 },				{ OV7670_GAM7, 			0x80 },
	{ OV7670_GAM8, 			0x88 },				{ OV7670_GAM9, 			0x8f },
	{ OV7670_GAM10,			0x96 },				{ OV7670_GAM11,			0xa3 },
	{ OV7670_GAM12, 		0xaf },				{ OV7670_GAM13,			0xc4 },
	{ OV7670_GAM14, 		0xd7 },				{ OV7670_GAM15, 		0xe8 },

	/* AGC and AEC parameters.  Note we start by disabling those features,
	   then turn them only after tweaking the values. */
	{ OV7670_COM8, 			COM8_FASTAEC | COM8_AECSTEP | COM8_BFILT },
	{ OV7670_GAIN, 			0x00 },				{ OV7670_AECH, 			0x00 },
	{ OV7670_COM4, 			0x40 }, 									/* magic reserved bit */
	{ OV7670_COM9, 			0x18 }, 									/* 4x gain + magic rsvd bit */
	{ OV7670_BD50MAX, 		0x05 },				{ OV7670_BD60MAX, 		0x07 },
	{ OV7670_AEW, 			0x95 },				{ OV7670_AEB, 			0x33 },
	{ OV7670_VPT, 			0xe3 },				{ OV7670_HAECC1, 		0x78 },
	{ OV7670_HAECC2, 		0x68 },				{ 0xa1, 				0x03 }, /* magic */
	{ OV7670_HAECC3, 		0xd8 },				{ OV7670_HAECC4, 		0xd8 },
	{ OV7670_HAECC5, 		0xf0 },				{ OV7670_HAECC6, 		0x90 },
	{ OV7670_HAECC7, 		0x94 },
	{ OV7670_COM8, COM8_FASTAEC|COM8_AECSTEP|COM8_BFILT|COM8_AGC|COM8_AEC },

	/* Almost all of these are magic "reserved" values.  */
	{ OV7670_COM5, 			0x61 },				{ OV7670_COM6, 			0x4b },
	{ 0x16, 				0x02 },				{ OV7670_MVFP, 			0x07 },
	{ OV7670_ADCCTR1, 		0x02 },				{ OV7670_ADCCTR2, 		0x91 },
	{ 0x29, 				0x07 },				{ OV7670_CHLF, 			0x0b },
	{ 0x35, 				0x0b },				{ OV7670_ADC, 			0x1d },
	{ OV7670_ACOM, 			0x71 },				{ OV7670_OFON, 			0x2a },
	{ OV7670_COM12, 		0x78 },				{ OV7670_DM_POS,		0x40 },
	{ 0x4e, 				0x20 },				{ OV7670_GFIX, 			0x00 },
	{ OV7670_DBLV, 			0x4a },				{ OV7670_REG74, 		0x10 },
	{ 0x8d, 				0x4f },				{ 0x8e, 				0x00 },
	{ 0x8f, 				0x00 },				{ 0x90, 				0x00 },
	{ 0x91, 				0x00 },				{ 0x96, 				0x00 },
	{ 0x9a, 				0x00 },				{ 0xb0, 				0x84 },
	{ OV7670_ABLC1, 		0x0c },				{ 0xb2, 				0x0e },
	{ OV7670_THL_ST, 		0x82 },				{ 0xb8, 				0x0a },

	/* More reserved magic, some of which tweaks white balance */
	{ OV7670_AWBC1,			0x0a },				{ OV7670_AWBC2, 		0xf0 },
	{ OV7670_AWBC3, 		0x34 },				{ OV7670_AWBC4, 		0x58 },
	{ OV7670_AWBC5, 		0x28 },				{ OV7670_AWBC6, 		0x3a },
	{ OV7670_AWBC7, 		0x88 },				{ OV7670_AWBC8, 		0x88 },
	{ OV7670_AWBC9, 		0x44 },				{ OV7670_AWBC10,		0x67 },
	{ OV7670_AWBC11, 		0x49 },				{ OV7670_AWBC12,		0x0e },
	{ OV7670_AWBCTR3, 		0x0a },				{ OV7670_AWBCTR2,		0x55 },
	{ OV7670_AWBCTR1, 		0x11 },				{ OV7670_AWBCTR0,		0x9f }, /* "9e for advance AWB" */
	{ OV7670_GGAIN, 		0x40 },				{ OV7670_BLUE,			0x40 },
	{ OV7670_RED, 			0x60 },
	{ OV7670_COM8, 			COM8_FASTAEC|COM8_AECSTEP|COM8_BFILT|COM8_AGC|COM8_AEC|COM8_AWB },

	/* Matrix coefficients */
	{ OV7670_MTX1, 			0x80 },
	{ OV7670_MTX2,			0x80 },
	{ OV7670_MTX3, 			0x00 },
	{ OV7670_MTX4, 			0x22 },
	{ OV7670_MTX5, 			0x5e },
	{ OV7670_MTX6, 			0x80 },
	{ OV7670_MTXS, 			0x9e },

	{ OV7670_COM16, 		COM16_AWBGAIN },	{ OV7670_EDGE, 0x00 },
	{ OV7670_REG75, 		0x05 },				{ OV7670_REG76, 		0xe1 },
	{ OV7670_DNSTH, 		0x00 },				{ OV7670_REG77, 		0x01 },
	{ OV7670_COM13, 		0xc3 },				{ 0x4b, 				0x09 },
	{ OV7670_SATCTR, 		0x60 },				{ OV7670_COM16, 		0x38 },
	{ OV7670_CONTR, 		0x40 },

	{ OV7670_ARBLM, 		0x11 },				{ OV7670_COM11, 		COM11_EXP|COM11_HZAUTO },
	{ OV7670_NT_CTRL, 		0x88 },				{ 0x96, 				0x00 },
	{ 0x97, 				0x30 },				{ 0x98, 				0x20 },
	{ 0x99, 				0x30 },				{ 0x9a, 				0x84 },
	{ 0x9b, 				0x29 },				{ 0x9c, 				0x03 },
	{ OV7670_BD50ST, 		0x4c },				{ OV7670_BD60ST, 		0x3f },
	{ 0x78, 				0x04 },

	/* Extra-weird stuff.  Some sort of multiplexor register */
	{ 0x79, 0x01 },		{ 0xc8, 0xf0 },		{ 0x79, 0x0f },		{ 0xc8, 0x00 },
	{ 0x79, 0x10 },		{ 0xc8, 0x7e },		{ 0x79, 0x0a },		{ 0xc8, 0x80 },
	{ 0x79, 0x0b },		{ 0xc8, 0x01 },		{ 0x79, 0x0c },		{ 0xc8, 0x0f },
	{ 0x79, 0x0d },		{ 0xc8, 0x20 },		{ 0x79, 0x09 },		{ 0xc8, 0x80 },
	{ 0x79, 0x02 },		{ 0xc8, 0xc0 },		{ 0x79, 0x03 },		{ 0xc8, 0x40 },
	{ 0x79, 0x05 },		{ 0xc8, 0x30 },		{ 0x79, 0x26 },

	{ 0xff, 0xff },	/* END MARKER */
};



/*************************************************************************************
 * Here we'll try to encapsulate the changes for just the output
 * video format. RGB656 and YUV422 come from OV; RGB444 is homebrewed.
 * IMPORTANT RULE: the first entry must be for COM7, see ov7670_s_fmt for why.
*************************************************************************************/
static struct regval_list ov7670_fmt_yuv422[] = {
	{ OV7670_COM7, 		0x00 },  		/* Selects YUV mode */
	{ OV7670_RGB444, 	0x00 },			/* No RGB444 please */
	{ OV7670_COM1, 		0x00 },			/* CCIR601 */
	{ OV7670_COM15, 	COM15_R00FF },
	{ OV7670_COM9, 		0x48 }, 		/* 32x gain ceiling; 0x8 is reserved bit */
	{ OV7670_MTX1, 		0x80 },			/* "matrix coefficient 1" */
	{ OV7670_MTX2, 		0x80 },			/* "matrix coefficient 2" */
	{ OV7670_MTX3, 		0x00 },			/* vb */
	{ OV7670_MTX4, 		0x22 },			/* "matrix coefficient 4" */
	{ OV7670_MTX5, 		0x5e },			/* "matrix coefficient 5" */
	{ OV7670_MTX6, 		0x80 },			/* "matrix coefficient 6" */
	{ OV7670_COM13, 	COM13_GAMMA|COM13_UVSAT },
	{ 0xff, 0xff },
};

static struct regval_list ov7670_fmt_rgb565[] = {
	{ OV7670_COM7, 		COM7_RGB },		/* Selects RGB mode */
	{ OV7670_RGB444, 	0x00 },			/* No RGB444 please */
	{ OV7670_COM1, 		0x00 },			/* CCIR601 */
	{ OV7670_COM15, 	COM15_RGB565 },
	{ OV7670_COM9, 		0x38 },			/* 16x gain ceiling; 0x8 is reserved bit */
	{ OV7670_MTX1, 		0xb3 },			/* "matrix coefficient 1" */
	{ OV7670_MTX2, 		0xb3 },			/* "matrix coefficient 2" */
	{ OV7670_MTX3, 		0x00 },			/* vb */
	{ OV7670_MTX4, 		0x3d },			/* "matrix coefficient 4" */
	{ OV7670_MTX5, 		0xa7 },			/* "matrix coefficient 5" */
	{ OV7670_MTX6, 		0xe4 },			/* "matrix coefficient 6" */
	{ OV7670_COM13, 	COM13_GAMMA|COM13_UVSAT },
	{ 0xff, 0xff },
};

static struct regval_list ov7670_fmt_rgb444[] = {
	{ OV7670_COM7, 		COM7_RGB },		/* Selects RGB mode */
	{ OV7670_RGB444, 	R444_ENABLE },	/* Enable xxxxrrrr ggggbbbb */
	{ OV7670_COM1, 		0x00 },			/* CCIR601 */
	{ OV7670_COM15,		COM15_R01FE|COM15_RGB565 }, /* Data range needed? */
	{ OV7670_COM9, 		0x38 },			/* 16x gain ceiling; 0x8 is reserved bit */
	{ OV7670_MTX1, 		0xb3 },			/* "matrix coefficient 1" */
	{ OV7670_MTX2, 		0xb3 },			/* "matrix coefficient 2" */
	{ OV7670_MTX3, 		0x00 },			/* vb */
	{ OV7670_MTX4, 		0x3d },			/* "matrix coefficient 4" */
	{ OV7670_MTX5, 		0xa7 },			/* "matrix coefficient 5" */
	{ OV7670_MTX6, 		0xe4 },			/* "matrix coefficient 6" */
	{ OV7670_COM13, 	COM13_GAMMA|COM13_UVSAT|0x2 },  /* Magic rsvd bit */
	{ 0xff, 0xff },
};

static struct regval_list ov7670_fmt_raw[] = {
	{ OV7670_COM7, 		COM7_BAYER },
	{ OV7670_COM13, 	0x08 }, 		/* No gamma, magic rsvd bit */
	{ OV7670_COM16, 	0x3d }, 		/* Edge enhancement, denoise */
	{ OV7670_REG76, 	0xe1 }, 		/* Pix correction, magic rsvd */
	{ 0xff, 0xff },
};



/*************************************************************************************
 * QCIF mode is done (by OV) in a very strange way - it actually looks like
 * VGA with weird scaling options - they do *not* use the canned QCIF mode
 * which is allegedly provided by the sensor.  So here's the weird register
 * settings.
*************************************************************************************/
static struct regval_list ov7670_qcif_regs[] = {
	{ OV7670_COM3,			COM3_SCALEEN|COM3_DCWEN },
	{ OV7670_COM3,			COM3_DCWEN },
	{ OV7670_COM14,			COM14_DCWEN | 0x01},
	{ OV7670_SCL_PCLK_DIV,	0xf1 },
	{ OV7670_SCL_PCLK_DLY,	0x52 },
	{ OV7670_GAM1,			0x1c },
	{ OV7670_GAM2,			0x28 },
	{ OV7670_GAM3,			0x3c },
	{ OV7670_GAM5,			0x69 },
	{ OV7670_COM9,			0x38 },
	{ OV7670_DSPC3,			0x0b },
	{ OV7670_REG74,			0x19 },
	{ 0x9a,					0x80 },
	{ OV7670_AWBC1,			0x14 },
	{ OV7670_COM13,			0xc0 },
	{ 0xff, 0xff },
};



/*************************************************************************************
 * Store information about the video data format.  The color matrix
 * is deeply tied into the format, so keep the relevant values here.
 * The magic matrix numbers come from OmniVision.
*************************************************************************************/
static struct ov7670_format_struct ov7670_formats[] = {
	{
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.regs		= ov7670_fmt_yuv422,
		.cmatrix	= { 128, -128, 0, -34, -94, 128 },
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_RGB444_2X8_PADHI_LE,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.regs		= ov7670_fmt_rgb444,
		.cmatrix	= { 179, -179, 0, -61, -176, 228 },
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_RGB565_2X8_LE,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.regs		= ov7670_fmt_rgb565,
		.cmatrix	= { 179, -179, 0, -61, -176, 228 },
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SBGGR8_1X8,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.regs		= ov7670_fmt_raw,
		.cmatrix	= { 0, 0, 0, 0, 0, 0 },
	},
};
#define N_OV7670_FMTS ARRAY_SIZE(ov7670_formats)




/*************************************************************************************
 *
*************************************************************************************/
static struct ov7670_win_size ov7670_win_sizes[] = {
	/* VGA */
	{
		.width		= VGA_WIDTH,
		.height		= VGA_HEIGHT,
		.com7_bit	= COM7_FMT_VGA,
		.hstart		= 158,	/* These values from */
		.hstop		=  14,	/* Omnivision */
		.vstart		=  10,
		.vstop		= 490,
		.regs		= NULL,
	},
	/* CIF */
	{
		.width		= CIF_WIDTH,
		.height		= CIF_HEIGHT,
		.com7_bit	= COM7_FMT_CIF,
		.hstart		= 170,	/* Empirically determined */
		.hstop		=  90,
		.vstart		=  14,
		.vstop		= 494,
		.regs		= NULL,
	},
	/* QVGA */
	{
		.width		= QVGA_WIDTH,
		.height		= QVGA_HEIGHT,
		.com7_bit	= COM7_FMT_QVGA,
		.hstart		= 168,	/* Empirically determined */
		.hstop		=  24,
		.vstart		=  12,
		.vstop		= 492,
		.regs		= NULL,
	},
	/* QCIF */
	{
		.width		= QCIF_WIDTH,
		.height		= QCIF_HEIGHT,
		.com7_bit	= COM7_FMT_VGA, /* see comment above */
		.hstart		= 456,	/* Empirically determined */
		.hstop		=  24,
		.vstart		=  14,
		.vstop		= 494,
		.regs		= ov7670_qcif_regs,
	}
};



/*************************************************************************************
 * On most platforms, we'd rather do straight i2c I/O.
*************************************************************************************/
static int ov7670_read_i2c(struct ov7670_info *info, unsigned char reg, unsigned char *value)
{
	*value = i2c_read_reg(0x42U, reg);
	return 0;
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_write_i2c(struct ov7670_info *info, unsigned char reg, unsigned char value)
{
	i2c_write_reg(0x42U, reg, value);

	if (reg == OV7670_COM7 && (value & COM7_RESET))
		HAL_Delay(5);  /* Wait for reset to run */
	return 0;
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_read(struct ov7670_info *info, unsigned char reg, unsigned char *value)
{
	//struct ov7670_info *info = to_state(sd);
	return ov7670_read_i2c(info, reg, value);
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_write(struct ov7670_info *info, unsigned char reg, unsigned char value)
{
	//struct ov7670_info *info = to_state(sd);
	return ov7670_write_i2c(info, reg, value);
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_update_bits(struct ov7670_info *info, unsigned char reg, unsigned char mask, unsigned char value)
{
	unsigned char orig;
	int ret;

	ret = ov7670_read(info, reg, &orig);
	if (ret)
		return ret;

	return ov7670_write(info, reg, (orig & ~mask) | (value & mask));
}



/*************************************************************************************
 * Write a list of register settings; ff/ff stops the process.
*************************************************************************************/
static int ov7670_write_array(struct ov7670_info *info, struct regval_list *vals)
{
	while (vals->reg_num != 0xff || vals->value != 0xff) {
		int ret = ov7670_write(info, vals->reg_num, vals->value);

		if (ret < 0)
			return ret;
		vals++;
	}
	return 0;
}



/*************************************************************************************
 * Stuff that knows about the sensor.
*************************************************************************************/
static int ov7670_reset(struct ov7670_info *info, u32 val)
{
	ov7670_write(info, OV7670_COM7, COM7_RESET);
	HAL_Delay(1);
	return 0;
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_init(struct ov7670_info *info, u32 val)
{
	return ov7670_write_array(info, ov7670_default_regs);
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_detect(struct ov7670_info *info)
{
	unsigned char v;
	int ret;

	ret = ov7670_init(info, 0);
	if (ret < 0)
		return ret;
	ret = ov7670_read(info, OV7670_MIDH, &v);
	if (ret < 0)
		return ret;
	if (v != 0x7f) /* OV manuf. id. */
		return -ENODEV;
	ret = ov7670_read(info, OV7670_MIDL, &v);
	if (ret < 0)
		return ret;
	if (v != 0xa2)
		return -ENODEV;
	/* OK, we know we have an OmniVision chip...but which one?*/
	ret = ov7670_read(info, OV7670_PID, &v);
	if (ret < 0)
		return ret;
	if (v != 0x76)  /* PID + VER = 0x76 / 0x73 */
		return -ENODEV;
	ret = ov7670_read(info, OV7670_VER, &v);
	if (ret < 0)
		return ret;
	if (v != 0x73)  /* PID + VER = 0x76 / 0x73 */
		return -ENODEV;
	return 0;
}




/*************************************************************************************
 *
*************************************************************************************/
static void ov7675_get_framerate(struct ov7670_info *info, struct v4l2_fract *tpf)
{
	//struct ov7670_info *info = to_state(sd);
	u32 clkrc = info->clkrc;
	int pll_factor;

	if (info->pll_bypass)
		pll_factor = 1;
	else
		pll_factor = PLL_FACTOR;

	clkrc++;
	if (info->fmt->mbus_code == MEDIA_BUS_FMT_SBGGR8_1X8)
		clkrc = (clkrc >> 1);

	tpf->numerator = 1;
	tpf->denominator = (5 * pll_factor * info->clock_speed) /
			(4 * clkrc);
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7675_apply_framerate(struct ov7670_info *info)
{
	//struct ov7670_info *info = to_state(sd);
	int ret;

	ret = ov7670_write(info, OV7670_CLKRC, info->clkrc);
	if (ret < 0)
		return ret;

	return ov7670_write(info, OV7670_DBLV,
			    info->pll_bypass ? DBLV_BYPASS : DBLV_X4);
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7675_set_framerate(struct ov7670_info *info, struct v4l2_fract *tpf)
{
	//struct ov7670_info *info = to_state(sd);
	u32 clkrc;
	int pll_factor;

	/* The formula is fps = 5/4*pixclk for YUV/RGB and
	 * fps = 5/2*pixclk for RAW.
	 * pixclk = clock_speed / (clkrc + 1) * PLLfactor*/
	if (tpf->numerator == 0 || tpf->denominator == 0) {
		clkrc = 0;
	} else {
		pll_factor = info->pll_bypass ? 1 : PLL_FACTOR;
		clkrc = (5 * pll_factor * info->clock_speed * tpf->numerator) /
			(4 * tpf->denominator);
		if (info->fmt->mbus_code == MEDIA_BUS_FMT_SBGGR8_1X8)
			clkrc = (clkrc << 1);
		clkrc--;
	}

	/* The datasheet claims that clkrc = 0 will divide the input clock by 1
	 * but we've checked with an oscilloscope that it divides by 2 instead.
	 * So, if clkrc = 0 just bypass the divider.*/
	if (clkrc <= 0)
		clkrc = CLKRC_EXT;
	else if (clkrc > CLKRC_SCALE)
		clkrc = CLKRC_SCALE;
	info->clkrc = clkrc;

	/* Recalculate frame rate */
	ov7675_get_framerate(info, tpf);

	/* If the device is not powered up by the host driver do
	 * not apply any changes to H/W at this time. Instead
	 * the framerate will be restored right after power-up.*/
	if (info->on)
		return ov7675_apply_framerate(info);

	return 0;
}



/*************************************************************************************
 *
*************************************************************************************/
static void ov7670_get_framerate_legacy(struct ov7670_info *info, struct v4l2_fract *tpf)
{
	//struct ov7670_info *info = to_state(sd);

	tpf->numerator = 1;
	tpf->denominator = info->clock_speed;
	if ((info->clkrc & CLKRC_EXT) == 0 && (info->clkrc & CLKRC_SCALE) > 1)
		tpf->denominator /= (info->clkrc & CLKRC_SCALE);
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_set_framerate_legacy(struct ov7670_info *info, struct v4l2_fract *tpf)
{
	//struct ov7670_info *info = to_state(sd);
	int div;

	if (tpf->numerator == 0 || tpf->denominator == 0)
		div = 1;  /* Reset to full rate */
	else
		div = (tpf->numerator * info->clock_speed) / tpf->denominator;
	if (div == 0)
		div = 1;
	else if (div > CLKRC_SCALE)
		div = CLKRC_SCALE;
	info->clkrc = (info->clkrc & 0x80) | div;
	tpf->numerator = 1;
	tpf->denominator = info->clock_speed / div;

	/* If the device is not powered up by the host driver do
	 * not apply any changes to H/W at this time. Instead
	 * the framerate will be restored right after power-up.*/
	if (info->on)
		return ov7670_write(info, OV7670_CLKRC, info->clkrc);

	return 0;
}



/*************************************************************************************
 * Store a set of start/stop values into the camera.
*************************************************************************************/
static int ov7670_set_hw(struct ov7670_info *info, int hstart, int hstop, int vstart, int vstop)
{
	int ret;
	unsigned char v;
	/* Horizontal: 11 bits, top 8 live in hstart and hstop.  Bottom 3 of
	 * hstart are in href[2:0], bottom 3 of hstop in href[5:3].  There is
	 * a mystery "edge offset" value in the top two bits of href.*/
	ret = ov7670_write(info, OV7670_HSTART, (hstart >> 3) & 0xff);
	if (ret)
		return ret;
	ret = ov7670_write(info, OV7670_HSTOP, (hstop >> 3) & 0xff);
	if (ret)
		return ret;
	ret = ov7670_read(info, OV7670_HREF, &v);
	if (ret)
		return ret;
	v = (v & 0xc0) | ((hstop & 0x7) << 3) | (hstart & 0x7);
	HAL_Delay(10);
	ret = ov7670_write(info, OV7670_HREF, v);
	if (ret)
		return ret;
	/* Vertical: similar arrangement, but only 10 bits. */
	ret = ov7670_write(info, OV7670_VSTRT, (vstart >> 2) & 0xff);
	if (ret)
		return ret;
	ret = ov7670_write(info, OV7670_VSTOP, (vstop >> 2) & 0xff);
	if (ret)
		return ret;
	ret = ov7670_read(info, OV7670_VREF, &v);
	if (ret)
		return ret;
	v = (v & 0xf0) | ((vstop & 0x3) << 2) | (vstart & 0x3);
	HAL_Delay(10);
	return ov7670_write(info, OV7670_VREF, v);
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_enum_mbus_code(struct ov7670_info *info, struct v4l2_subdev_mbus_code_enum *code)
{
	if (code->pad || code->index >= N_OV7670_FMTS)
		return -EINVAL;

	code->code = ov7670_formats[code->index].mbus_code;
	return 0;
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_try_fmt_internal(struct ov7670_info *info,
		struct v4l2_mbus_framefmt *fmt,
		struct ov7670_format_struct **ret_fmt,
		struct ov7670_win_size **ret_wsize)
{
	int index, i;
	struct ov7670_win_size *wsize;
	unsigned int n_win_sizes = info->devtype->n_win_sizes;
	unsigned int win_sizes_limit = n_win_sizes;

	for (index = 0; index < N_OV7670_FMTS; index++)
		if (ov7670_formats[index].mbus_code == fmt->code)
			break;
	if (index >= N_OV7670_FMTS) {
		/* default to first format */
		index = 0;
		fmt->code = ov7670_formats[0].mbus_code;
	}
	if (ret_fmt != NULL)
		*ret_fmt = ov7670_formats + index;
	/*
	 * Fields: the OV devices claim to be progressive.
	 */
	fmt->field = V4L2_FIELD_NONE;

	/* Don't consider values that don't match min_height and min_width constraints.*/
	if (info->min_width || info->min_height)
		for (i = 0; i < n_win_sizes; i++) {
			wsize = info->devtype->win_sizes + i;

			if (wsize->width < info->min_width ||
				wsize->height < info->min_height) {
				win_sizes_limit = i;
				break;
			}
		}
	/* Round requested image size down to the nearest we support, but not below the smallest.*/
	for (wsize = info->devtype->win_sizes;
	     wsize < info->devtype->win_sizes + win_sizes_limit; wsize++)
		if (fmt->width >= wsize->width && fmt->height >= wsize->height)
			break;
	if (wsize >= info->devtype->win_sizes + win_sizes_limit)
		wsize--;   /* Take the smallest one */
	if (ret_wsize != NULL)
		*ret_wsize = wsize;
	/* Note the size we'll actually handle.*/
	fmt->width = wsize->width;
	fmt->height = wsize->height;
	fmt->colorspace = ov7670_formats[index].colorspace;

	info->format = *fmt;

	return 0;
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_apply_fmt(struct ov7670_info *info)
{
	//struct ov7670_info *info = to_state(sd);
	struct ov7670_win_size *wsize = info->wsize;
	unsigned char com7, com10 = 0;
	int ret;

	/* COM7 is a pain in the ass, it doesn't like to be read then
	 * quickly written afterward.  But we have everything we need
	 * to set it absolutely here, as long as the format-specific
	 * register sets list it first.*/
	com7 = info->fmt->regs[0].value;
	com7 |= wsize->com7_bit;
	ret = ov7670_write(info, OV7670_COM7, com7);
	if (ret)
		return ret;

	/* Configure the media bus through COM10 register*/
	if (info->mbus_config & V4L2_MBUS_VSYNC_ACTIVE_LOW)
		com10 |= COM10_VS_NEG;
	if (info->mbus_config & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		com10 |= COM10_HREF_REV;
	if (info->pclk_hb_disable)
		com10 |= COM10_PCLK_HB;
	ret = ov7670_write(info, OV7670_COM10, com10);
	if (ret)
		return ret;

	/* Now write the rest of the array.  Also store start/stops*/
	ret = ov7670_write_array(info, info->fmt->regs + 1);
	if (ret)
		return ret;

	ret = ov7670_set_hw(info, wsize->hstart, wsize->hstop, wsize->vstart,
			    wsize->vstop);
	if (ret)
		return ret;

	if (wsize->regs) {
		ret = ov7670_write_array(info, wsize->regs);
		if (ret)
			return ret;
	}



	ret = ov7670_write(info, OV7670_COM10, com10);



	/* If we're running RGB565, we must rewrite clkrc after setting
	 * the other parameters or the image looks poor.  If we're *not*
	 * doing RGB565, we must not rewrite clkrc or the image looks
	 * *really* poor.
	 *
	 * (Update) Now that we retain clkrc state, we should be able
	 * to write it unconditionally, and that will make the frame
	 * rate persistent too.*/
	ret = ov7670_write(info, OV7670_CLKRC, info->clkrc);
	if (ret)
		return ret;

	return 0;
}



/*************************************************************************************
 * Set a format.
*************************************************************************************/
static int ov7670_set_fmt(struct ov7670_info *info, struct v4l2_subdev_format *format)
{
	int ret;

	if (format->pad)
		return -EINVAL;

	if (format->which == V4L2_SUBDEV_FORMAT_TRY) {
		ret = ov7670_try_fmt_internal(info, &format->format, NULL, NULL);
		if (ret)
			return ret;

		return 0;
	}

	ret = ov7670_try_fmt_internal(info, &format->format, &info->fmt, &info->wsize);
	if (ret)
		return ret;

	/* If the device is not powered up by the host driver do
	 * not apply any changes to H/W at this time. Instead
	 * the frame format will be restored right after power-up.*/
	if (info->on)
		return ov7670_apply_fmt(info);

	return 0;
}



/*************************************************************************************
 * Get format.
*************************************************************************************/
static int ov7670_get_fmt(struct ov7670_info *info,
			  struct v4l2_subdev_state *sd_state,
			  struct v4l2_subdev_format *format)
{
	//struct ov7670_info *info = to_state(sd);
#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
	struct v4l2_mbus_framefmt *mbus_fmt;
#endif

	if (format->which == V4L2_SUBDEV_FORMAT_TRY) {
#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
		mbus_fmt = v4l2_subdev_get_try_format(info, sd_state, 0);
		format->format = *mbus_fmt;
		return 0;
#else
		return -EINVAL;
#endif
	} else {
		format->format = info->format;
	}

	return 0;
}



/*************************************************************************************
 * Implement G/S_PARM.  There is a "high quality" mode we could try
 * to do someday; for now, we just do the frame rate tweak.
*************************************************************************************/
static int ov7670_g_frame_interval(struct ov7670_info *info, struct v4l2_subdev_frame_interval *ival)
{
	info->devtype->get_framerate(info, &ival->interval);
	return 0;
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_s_frame_interval(struct ov7670_info *info, struct v4l2_subdev_frame_interval *ival)
{
	struct v4l2_fract *tpf = &ival->interval;
	return info->devtype->set_framerate(info, tpf);
}



/* Frame intervals.  Since frame rates are controlled with the clock
 * divider, we can only do 30/n for integer n values.  So no continuous
 * or stepwise options.  Here we just pick a handful of logical values.*/
static int ov7670_frame_rates[] = { 30, 15, 10, 5, 1 };



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_enum_frame_interval(struct ov7670_info *info, struct v4l2_subdev_frame_interval_enum *fie)
{
	//struct ov7670_info *info = to_state(sd);
	unsigned int n_win_sizes = info->devtype->n_win_sizes;
	int i;

	if (fie->pad)
		return -EINVAL;
	if (fie->index >= ARRAY_SIZE(ov7670_frame_rates))
		return -EINVAL;

	/* Check if the width/height is valid.
	 * If a minimum width/height was requested, filter out the capture
	 * windows that fall outside that.*/
	for (i = 0; i < n_win_sizes; i++) {
		struct ov7670_win_size *win = &info->devtype->win_sizes[i];

		if (info->min_width && win->width < info->min_width)
			continue;
		if (info->min_height && win->height < info->min_height)
			continue;
		if (fie->width == win->width && fie->height == win->height)
			break;
	}
	if (i == n_win_sizes)
		return -EINVAL;
	fie->interval.numerator = 1;
	fie->interval.denominator = ov7670_frame_rates[fie->index];
	return 0;
}



/*************************************************************************************
 * Frame size enumeration
*************************************************************************************/
static int ov7670_enum_frame_size(struct ov7670_info *info,
				  struct v4l2_subdev_state *sd_state,
				  struct v4l2_subdev_frame_size_enum *fse)
{
	//struct ov7670_info *info = to_state(sd);
	int i;
	int num_valid = -1;
	__u32 index = fse->index;
	unsigned int n_win_sizes = info->devtype->n_win_sizes;

	if (fse->pad)
		return -EINVAL;

	/* If a minimum width/height was requested, filter out the capture
	 * windows that fall outside that.*/
	for (i = 0; i < n_win_sizes; i++) {
		struct ov7670_win_size *win = &info->devtype->win_sizes[i];

		if (info->min_width && win->width < info->min_width)
			continue;
		if (info->min_height && win->height < info->min_height)
			continue;
		if (index == ++num_valid) {
			fse->min_width = fse->max_width = win->width;
			fse->min_height = fse->max_height = win->height;
			return 0;
		}
	}

	return -EINVAL;
}



/*************************************************************************************
 * Code for dealing with controls.
*************************************************************************************/
static int ov7670_store_cmatrix(struct ov7670_info *info,
		int matrix[CMATRIX_LEN])
{
	int i, ret;
	unsigned char signbits = 0;

	/* Weird crap seems to exist in the upper part of
	 * the sign bits register, so let's preserve it.*/
	ret = ov7670_read(info, REG_CMATRIX_SIGN, &signbits);
	signbits &= 0xc0;

	for (i = 0; i < CMATRIX_LEN; i++) {
		unsigned char raw;

		if (matrix[i] < 0) {
			signbits |= (1 << i);
			if (matrix[i] < -255)
				raw = 0xff;
			else
				raw = (-1 * matrix[i]) & 0xff;
		} else {
			if (matrix[i] > 255)
				raw = 0xff;
			else
				raw = matrix[i] & 0xff;
		}
		ret = ov7670_write(info, REG_CMATRIX_BASE + i, raw);
		if (ret)
			return ret;
	}
	return ov7670_write(info, REG_CMATRIX_SIGN, signbits);
}


/*************************************************************************************
 * Hue also requires messing with the color matrix.  It also requires
 * trig functions, which tend not to be well supported in the kernel.
 * So here is a simple table of sine values, 0-90 degrees, in steps
 * of five degrees.  Values are multiplied by 1000.
 *
 * The following naive approximate trig functions require an argument
 * carefully limited to -180 <= theta <= 180.
*************************************************************************************/
#define SIN_STEP 5
static const int ov7670_sin_table[] = {
	   0,	 87,   173,   258,   342,   422,
	 499,	573,   642,   707,   766,   819,
	 866,	906,   939,   965,   984,   996,
	1000
};



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_sine(int theta)
{
	int chs = 1;
	int sine;

	if (theta < 0) {
		theta = -theta;
		chs = -1;
	}
	if (theta <= 90)
		sine = ov7670_sin_table[theta/SIN_STEP];
	else {
		theta -= 90;
		sine = 1000 - ov7670_sin_table[theta/SIN_STEP];
	}
	return sine*chs;
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_cosine(int theta)
{
	theta = 90 - theta;
	if (theta > 180)
		theta -= 360;
	else if (theta < -180)
		theta += 360;
	return ov7670_sine(theta);
}



#include <string.h>
/*************************************************************************************
 *
*************************************************************************************/
static void ov7670_calc_cmatrix(struct ov7670_info *info,
		int matrix[CMATRIX_LEN], int sat, int hue)
{
	int i;
	/*
	 * Apply the current saturation setting first.
	 */
	for (i = 0; i < CMATRIX_LEN; i++)
		matrix[i] = (info->fmt->cmatrix[i] * sat) >> 7;
	/*
	 * Then, if need be, rotate the hue value.
	 */
	if (hue != 0) {
		int sinth, costh, tmpmatrix[CMATRIX_LEN];

		memcpy(tmpmatrix, matrix, CMATRIX_LEN*sizeof(int));
		sinth = ov7670_sine(hue);
		costh = ov7670_cosine(hue);

		matrix[0] = (matrix[3]*sinth + matrix[0]*costh)/1000;
		matrix[1] = (matrix[4]*sinth + matrix[1]*costh)/1000;
		matrix[2] = (matrix[5]*sinth + matrix[2]*costh)/1000;
		matrix[3] = (matrix[3]*costh - matrix[0]*sinth)/1000;
		matrix[4] = (matrix[4]*costh - matrix[1]*sinth)/1000;
		matrix[5] = (matrix[5]*costh - matrix[2]*sinth)/1000;
	}
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_s_sat_hue(struct ov7670_info *info, int sat, int hue)
{
	//struct ov7670_info *info = to_state(sd);
	int matrix[CMATRIX_LEN];

	ov7670_calc_cmatrix(info, matrix, sat, hue);
	return ov7670_store_cmatrix(info, matrix);
}



/*************************************************************************************
 * Some weird registers seem to store values in a sign/magnitude format!
*************************************************************************************/
static unsigned char ov7670_abs_to_sm(unsigned char v)
{
	if (v > 127)
		return v & 0x7f;
	return (128 - v) | 0x80;
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_s_brightness(struct ov7670_info *info, int value)
{
	unsigned char com8 = 0, v;

	ov7670_read(info, OV7670_COM8, &com8);
	com8 &= ~COM8_AEC;
	ov7670_write(info, OV7670_COM8, com8);
	v = ov7670_abs_to_sm(value);
	return ov7670_write(info, OV7670_BRIGHT, v);
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_s_contrast(struct ov7670_info *info, int value)
{
	return ov7670_write(info, OV7670_CONTR, (unsigned char) value);
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_s_hflip(struct ov7670_info *info, int value)
{
	unsigned char v = 0;
	int ret;

	ret = ov7670_read(info, OV7670_MVFP, &v);
	if (ret)
		return ret;
	if (value)
		v |= MVFP_MIRROR;
	else
		v &= ~MVFP_MIRROR;
	HAL_Delay(10);  /* FIXME */
	return ov7670_write(info, OV7670_MVFP, v);
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_s_vflip(struct ov7670_info *info, int value)
{
	unsigned char v = 0;
	int ret;

	ret = ov7670_read(info, OV7670_MVFP, &v);
	if (ret)
		return ret;
	if (value)
		v |= MVFP_FLIP;
	else
		v &= ~MVFP_FLIP;
	HAL_Delay(10);  /* FIXME */
	return ov7670_write(info, OV7670_MVFP, v);
}



/*************************************************************************************
 * GAIN is split between REG_GAIN and REG_VREF[7:6].  If one believes
 * the data sheet, the VREF parts should be the most significant, but
 * experience shows otherwise.  There seems to be little value in
 * messing with the VREF bits, so we leave them alone.
*************************************************************************************/
static int ov7670_g_gain(struct ov7670_info *info, __s32 *value)
{
	int ret;
	unsigned char gain;

	ret = ov7670_read(info, OV7670_GAIN, &gain);
	if (ret)
		return ret;
	*value = gain;
	return 0;
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_s_gain(struct ov7670_info *info, int value)
{
	int ret;
	unsigned char com8;

	ret = ov7670_write(info, OV7670_GAIN, value & 0xff);
	if (ret)
		return ret;
	/* Have to turn off AGC as well */
	ret = ov7670_read(info, OV7670_COM8, &com8);
	if (ret)
		return ret;
	return ov7670_write(info, OV7670_COM8, com8 & ~COM8_AGC);
}



/*************************************************************************************
 * Tweak autogain.
*************************************************************************************/
static int ov7670_s_autogain(struct ov7670_info *info, int value)
{
	int ret;
	unsigned char com8;

	ret = ov7670_read(info, OV7670_COM8, &com8);
	if (ret == 0) {
		if (value)
			com8 |= COM8_AGC;
		else
			com8 &= ~COM8_AGC;
		ret = ov7670_write(info, OV7670_COM8, com8);
	}
	return ret;
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_s_exp(struct ov7670_info *info, int value)
{
	int ret;
	unsigned char com1, com8, aech, aechh;

	ret = ov7670_read(info, OV7670_COM1, &com1) +
		ov7670_read(info, OV7670_COM8, &com8) +
		ov7670_read(info, OV7670_AECHH, &aechh);
	if (ret)
		return ret;

	com1 = (com1 & 0xfc) | (value & 0x03);
	aech = (value >> 2) & 0xff;
	aechh = (aechh & 0xc0) | ((value >> 10) & 0x3f);
	ret = ov7670_write(info, OV7670_COM1, com1) +
		ov7670_write(info, OV7670_AECH, aech) +
		ov7670_write(info, OV7670_AECHH, aechh);
	/* Have to turn off AEC as well */
	if (ret == 0)
		ret = ov7670_write(info, OV7670_COM8, com8 & ~COM8_AEC);
	return ret;
}



/*************************************************************************************
 * Tweak autoexposure.
*************************************************************************************/
static int ov7670_s_autoexp(struct ov7670_info *info, enum v4l2_exposure_auto_type value)
{
	int ret;
	unsigned char com8;

	ret = ov7670_read(info, OV7670_COM8, &com8);
	if (ret == 0) {
		if (value == V4L2_EXPOSURE_AUTO)
			com8 |= COM8_AEC;
		else
			com8 &= ~COM8_AEC;
		ret = ov7670_write(info, OV7670_COM8, com8);
	}
	return ret;
}



/*************************************************************************************
 *
*************************************************************************************/
static const char * const ov7670_test_pattern_menu[] = {
	"No test output",
	"Shifting \"1\"",
	"8-bar color bar",
	"Fade to gray color bar",
};



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_s_test_pattern(struct ov7670_info *info, int value)
{
	int ret;

	ret = ov7670_update_bits(info, OV7670_SCL_XSC, TEST_PATTTERN_0,
				value & BIT(0) ? TEST_PATTTERN_0 : 0);
	if (ret)
		return ret;

	return ov7670_update_bits(info, OV7670_SCL_YSC, TEST_PATTTERN_1,
				value & BIT(1) ? TEST_PATTTERN_1 : 0);
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_g_volatile_ctrl(struct ov7670_info *info, struct v4l2_ctrl *ctrl)
{
	//struct v4l2_subdev *sd = to_sd(ctrl);
	//struct ov7670_info *info = to_state(sd);

	switch (ctrl->id) {
	case V4L2_CID_AUTOGAIN:
		return ov7670_g_gain(info, &info->gain->val);
	}
	return -EINVAL;
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_s_ctrl(struct ov7670_info *info, struct v4l2_ctrl *ctrl)
{
	//struct v4l2_subdev *sd = to_sd(ctrl);
	//struct ov7670_info *info = to_state(sd);

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		return ov7670_s_brightness(info, ctrl->val);
	case V4L2_CID_CONTRAST:
		return ov7670_s_contrast(info, ctrl->val);
	case V4L2_CID_SATURATION:
		return ov7670_s_sat_hue(info,
				info->saturation->val, info->hue->val);
	case V4L2_CID_VFLIP:
		return ov7670_s_vflip(info, ctrl->val);
	case V4L2_CID_HFLIP:
		return ov7670_s_hflip(info, ctrl->val);
	case V4L2_CID_AUTOGAIN:
		/* Only set manual gain if auto gain is not explicitly
		   turned on. */
		if (!ctrl->val) {
			/* ov7670_s_gain turns off auto gain */
			return ov7670_s_gain(info, info->gain->val);
		}
		return ov7670_s_autogain(info, ctrl->val);
	case V4L2_CID_EXPOSURE_AUTO:
		/* Only set manual exposure if auto exposure is not explicitly
		   turned on. */
		if (ctrl->val == V4L2_EXPOSURE_MANUAL) {
			/* ov7670_s_exp turns off auto exposure */
			return ov7670_s_exp(info, info->exposure->val);
		}
		return ov7670_s_autoexp(info, ctrl->val);
	case V4L2_CID_TEST_PATTERN:
		return ov7670_s_test_pattern(info, ctrl->val);
	}
	return -EINVAL;
}



/*************************************************************************************
 *
*************************************************************************************/
static void ov7670_power_on(struct ov7670_info *info)
{
	if (info->on)
		return;

	OV7670_RST_LOW;
	HAL_Delay(300);
	OV7670_RST_HIGH;
	HAL_Delay(300);

	if (info->pwdn_gpio || info->resetb_gpio || info->clk)
		HAL_Delay(5);

	info->on = true;
}



/*************************************************************************************
 *
*************************************************************************************/
static void ov7670_power_off(struct ov7670_info *info)
{
	if (!info->on)
		return;

	OV7670_RST_LOW;

	if (info->pwdn_gpio)
		//gpiod_set_value(info->pwdn_gpio, 1);

	info->on = false;
}



/*************************************************************************************
 *
*************************************************************************************/
static int ov7670_s_power(struct ov7670_info *info, int on)
{
	//struct ov7670_info *info = to_state(sd);

	if (info->on == on)
		return 0;

	if (on) {
		ov7670_power_on(info);
		ov7670_init(info, 0);
		ov7670_apply_fmt(info);
		ov7675_apply_framerate(info);
		//v4l2_ctrl_handler_setup(&info->hdl);
	} else {
		ov7670_power_off(info);
	}

	return 0;
}



/*************************************************************************************
 *
*************************************************************************************/
static const struct ov7670_devtype ov7670_devdata[] = {
	[MODEL_OV7670] = {
		.win_sizes = ov7670_win_sizes,
		.n_win_sizes = ARRAY_SIZE(ov7670_win_sizes),
		.set_framerate = ov7670_set_framerate_legacy,
		.get_framerate = ov7670_get_framerate_legacy,
	},
};



//----------------------------------------------------
struct v4l2_fract g_framerate = {
		.numerator = 1,
		.denominator = 30
};

//----------------------------------------------------
static const struct v4l2_mbus_framefmt g_framefmt = {
		.width = QVGA_WIDTH,
		.height = QVGA_HEIGHT,
		.code = MEDIA_BUS_FMT_RGB565_2X8_LE,
		.field = V4L2_FIELD_NONE,
		.colorspace = V4L2_COLORSPACE_SRGB
};

//----------------------------------------------------
struct v4l2_subdev_format g_format = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.pad = 0,
		.format = g_framefmt
};

struct ov7670_format_struct g_fmt_struct = {0};
struct ov7670_win_size g_wsize_struct = {0};
//----------------------------------------------------
struct ov7670_info g_cam_info = {
		.on = false,
		.clock_speed = 20,
		.pll_bypass = true,
		.pclk_hb_disable = true,

		.min_height = QCIF_HEIGHT,
		.min_width = QCIF_WIDTH,

		.fmt = &g_fmt_struct,
		.wsize = &g_wsize_struct,

		.devtype = ov7670_devdata,

};



/*************************************************************************************
 *
*************************************************************************************/
void ov7670_initialization()
{
	ov7670_set_framerate_legacy(&g_cam_info, &g_framerate);
	ov7670_set_fmt(&g_cam_info, &g_format);
	ov7670_s_power(&g_cam_info, 1);
	ov7670_s_sat_hue(&g_cam_info, 0, 0);

	//ov7670_s_test_pattern(&g_cam_info, 3);
}


