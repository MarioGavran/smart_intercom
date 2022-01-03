/*
 * OV7670.h
 *
 *  Created on: Dec 21, 2021
 *      Author: enio
 */
#include <stdint.h>
#include <stdbool.h>
#include "../../Core/Inc/ov7670.h"

#ifndef INC_OV7670_H_
#define INC_OV7670_H_


typedef int8_t 		__s8;
typedef uint8_t 	__u8;
typedef int16_t 	__s16;
typedef uint16_t 	__u16;
typedef int32_t		__s32;
typedef uint32_t 	__u32;

typedef int8_t 		s8;
typedef uint8_t 	u8;
typedef int16_t 	s16;
typedef uint16_t 	u16;
typedef int32_t		s32;
typedef uint32_t 	u32;

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#define MEDIA_BUS_FMT_YUYV8_2X8				0x2008
#define MEDIA_BUS_FMT_RGB444_2X8_PADHI_LE	0x1002
#define MEDIA_BUS_FMT_RGB565_2X8_LE			0x1008
#define MEDIA_BUS_FMT_SBGGR8_1X8			0x3001

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#define CIF_WIDTH		352
#define CIF_HEIGHT		288

#define QCIF_WIDTH		176
#define QCIF_HEIGHT		144

#define QVGA_WIDTH		320
#define QVGA_HEIGHT		240

#define VGA_WIDTH		640
#define VGA_HEIGHT		480


#define PLL_FACTOR	4

#define   CMATRIX_LEN 6

#define EINVAL 		22
#define	ENODEV		19	/* No such device */


/*********************************************************************************************
 *
*********************************************************************************************/
struct regval_list {
	unsigned char reg_num;
	unsigned char value;
};



/*********************************************************************************************
 * see also http://vektor.theorem.ca/graphics/ycbcr/
*********************************************************************************************/
enum v4l2_colorspace {
	/* Default colorspace, i.e. let the driver figure it out.
	 * Can only be used with video capture.*/
	V4L2_COLORSPACE_DEFAULT       = 0,
	/* SMPTE 170M: used for broadcast NTSC/PAL SDTV */
	V4L2_COLORSPACE_SMPTE170M     = 1,
	/* Obsolete pre-1998 SMPTE 240M HDTV standard, superseded by Rec 709 */
	V4L2_COLORSPACE_SMPTE240M     = 2,
	/* Rec.709: used for HDTV */
	V4L2_COLORSPACE_REC709        = 3,
	/* Deprecated, do not use. No driver will ever return this. This was
	 * based on a misunderstanding of the bt878 datasheet.*/
	V4L2_COLORSPACE_BT878         = 4,
	/* NTSC 1953 colorspace. This only makes sense when dealing with
	 * really, really old NTSC recordings. Superseded by SMPTE 170M.*/
	V4L2_COLORSPACE_470_SYSTEM_M  = 5,
	/* EBU Tech 3213 PAL/SECAM colorspace.*/
	V4L2_COLORSPACE_470_SYSTEM_BG = 6,
	/* Effectively shorthand for V4L2_COLORSPACE_SRGB, V4L2_YCBCR_ENC_601
	 * and V4L2_QUANTIZATION_FULL_RANGE. To be used for (Motion-)JPEG.*/
	V4L2_COLORSPACE_JPEG          = 7,
	/* For RGB colorspaces such as produces by most webcams. */
	V4L2_COLORSPACE_SRGB          = 8,
	/* opRGB colorspace */
	V4L2_COLORSPACE_OPRGB         = 9,
	/* BT.2020 colorspace, used for UHDTV. */
	V4L2_COLORSPACE_BT2020        = 10,
	/* Raw colorspace: for RAW unprocessed images */
	V4L2_COLORSPACE_RAW           = 11,
	/* DCI-P3 colorspace, used by cinema projectors */
	V4L2_COLORSPACE_DCI_P3        = 12,
};



/*********************************************************************************************
 *
*********************************************************************************************/
enum v4l2_field {
	V4L2_FIELD_ANY           = 0, /* driver can choose from none,
					 top, bottom, interlaced
					 depending on whatever it thinks
					 is approximate ... */
	V4L2_FIELD_NONE          = 1, /* this device has no fields ... */
	V4L2_FIELD_TOP           = 2, /* top field only */
	V4L2_FIELD_BOTTOM        = 3, /* bottom field only */
	V4L2_FIELD_INTERLACED    = 4, /* both fields interlaced */
	V4L2_FIELD_SEQ_TB        = 5, /* both fields sequential into one
					 buffer, top-bottom order */
	V4L2_FIELD_SEQ_BT        = 6, /* same as above + bottom-top order */
	V4L2_FIELD_ALTERNATE     = 7, /* both fields alternating into
					 separate buffers */
	V4L2_FIELD_INTERLACED_TB = 8, /* both fields interlaced, top field
					 first and the top field is
					 transmitted first */
	V4L2_FIELD_INTERLACED_BT = 9, /* both fields interlaced, top field
					 first and the bottom field is
					 transmitted first */
};



/*********************************************************************************************
 * enum v4l2_subdev_format_whence - Media bus format type
 * @V4L2_SUBDEV_FORMAT_TRY: try format, for negotiation only
 * @V4L2_SUBDEV_FORMAT_ACTIVE: active format, applied to the device
*********************************************************************************************/
enum v4l2_subdev_format_whence {
	V4L2_SUBDEV_FORMAT_TRY = 0,
	V4L2_SUBDEV_FORMAT_ACTIVE = 1,
};



/*********************************************************************************************
 * struct v4l2_mbus_framefmt - frame format on the media bus
 * @width:	image width
 * @height:	image height
 * @code:	data format code (from enum v4l2_mbus_pixelcode)
 * @field:	used interlacing type (from enum v4l2_field)
 * @colorspace:	colorspace of the data (from enum v4l2_colorspace)
 * @ycbcr_enc:	YCbCr encoding of the data (from enum v4l2_ycbcr_encoding)
 * @hsv_enc:	HSV encoding of the data (from enum v4l2_hsv_encoding)
 * @quantization: quantization of the data (from enum v4l2_quantization)
 * @xfer_func:  transfer function of the data (from enum v4l2_xfer_func)
 * @flags:	flags (V4L2_MBUS_FRAMEFMT_*)
 * @reserved:  reserved bytes that can be later used
*********************************************************************************************/
struct v4l2_mbus_framefmt {
	__u32			width;
	__u32			height;
	__u32			code;
	__u32			field;
	__u32			colorspace;
	union {
		/* enum v4l2_ycbcr_encoding */
		__u16			ycbcr_enc;
		/* enum v4l2_hsv_encoding */
		__u16			hsv_enc;
	};
	__u16			quantization;
	__u16			xfer_func;
	__u16			flags;
	__u16			reserved[10];
};



/*********************************************************************************************
 *
*********************************************************************************************/
struct ov7670_win_size {
	int	width;
	int	height;
	unsigned char com7_bit;
	int	hstart;					/* Start/stop values for the camera.  Note */
	int	hstop;					/* that they do not always make complete */
	int	vstart;					/* sense to humans, but evidently the sensor */
	int	vstop;					/* will do the right thing... */
	struct regval_list *regs; 	/* Regs to tweak */
};






/*********************************************************************************************
 *
*********************************************************************************************/
struct v4l2_fract {
	__u32   numerator;
	__u32   denominator;
};



/*********************************************************************************************
 *
*********************************************************************************************/
struct v4l2_rect {
	__s32   left;
	__s32   top;
	__u32   width;
	__u32   height;
};



/*********************************************************************************************
 * struct v4l2_subdev_frame_interval - Pad-level frame rate
 * @pad: pad number, as reported by the media API
 * @interval: frame interval in seconds
 * @reserved: drivers and applications must zero this array
*********************************************************************************************/
struct v4l2_subdev_frame_interval {
	__u32 pad;
	struct v4l2_fract interval;
	__u32 reserved[9];
};



/*********************************************************************************************
 * struct v4l2_subdev_frame_interval_enum - Frame interval enumeration
 * @pad: pad number, as reported by the media API
 * @index: frame interval index during enumeration
 * @code: format code (MEDIA_BUS_FMT_ definitions)
 * @width: frame width in pixels
 * @height: frame height in pixels
 * @interval: frame interval in seconds
 * @which: format type (from enum v4l2_subdev_format_whence)
 * @reserved: drivers and applications must zero this array
*********************************************************************************************/
struct v4l2_subdev_frame_interval_enum {
	__u32 index;
	__u32 pad;
	__u32 code;
	__u32 width;
	__u32 height;
	struct v4l2_fract interval;
	__u32 which;
	__u32 reserved[8];
};



/*********************************************************************************************
 * struct v4l2_subdev_pad_config - Used for storing subdev pad information.
 *
 * @try_fmt: &struct v4l2_mbus_framefmt
 * @try_crop: &struct v4l2_rect to be used for crop
 * @try_compose: &struct v4l2_rect to be used for compose
 *
 * This structure only needs to be passed to the pad op if the 'which' field
 * of the main argument is set to %V4L2_SUBDEV_FORMAT_TRY. For
 * %V4L2_SUBDEV_FORMAT_ACTIVE it is safe to pass %NULL.
*********************************************************************************************/
struct v4l2_subdev_pad_config {
	struct v4l2_mbus_framefmt try_fmt;
	struct v4l2_rect try_crop;
	struct v4l2_rect try_compose;
};



/*********************************************************************************************
 * struct v4l2_subdev_state - Used for storing subdev state information.
 *
 * @pads: &struct v4l2_subdev_pad_config array
 *
 * This structure only needs to be passed to the pad op if the 'which' field
 * of the main argument is set to %V4L2_SUBDEV_FORMAT_TRY. For
 * %V4L2_SUBDEV_FORMAT_ACTIVE it is safe to pass %NULL.
*********************************************************************************************/
struct v4l2_subdev_state {
	struct v4l2_subdev_pad_config *pads;
};



/*********************************************************************************************
 * struct v4l2_subdev_format - Pad-level media bus format
 * @which: format type (from enum v4l2_subdev_format_whence)
 * @pad: pad number, as reported by the media API
 * @format: media bus format (format code and frame size)
 * @reserved: drivers and applications must zero this array
*********************************************************************************************/
struct v4l2_subdev_format {
	__u32 which;
	__u32 pad;
	struct v4l2_mbus_framefmt format;
	__u32 reserved[8];
};



/*********************************************************************************************
 * struct v4l2_subdev_frame_size_enum - Media bus format enumeration
 * @index: format index during enumeration
 * @pad: pad number, as reported by the media API
 * @code: format code (MEDIA_BUS_FMT_ definitions)
 * @min_width: minimum frame width, in pixels
 * @max_width: maximum frame width, in pixels
 * @min_height: minimum frame height, in pixels
 * @max_height: maximum frame height, in pixels
 * @which: format type (from enum v4l2_subdev_format_whence)
 * @reserved: drivers and applications must zero this array
*********************************************************************************************/
struct v4l2_subdev_frame_size_enum {
	__u32 index;
	__u32 pad;
	__u32 code;
	__u32 min_width;
	__u32 max_width;
	__u32 min_height;
	__u32 max_height;
	__u32 which;
	__u32 reserved[8];
};



/*********************************************************************************************
 * struct v4l2_subdev_mbus_code_enum - Media bus format enumeration
 * @pad: pad number, as reported by the media API
 * @index: format index during enumeration
 * @code: format code (MEDIA_BUS_FMT_ definitions)
 * @which: format type (from enum v4l2_subdev_format_whence)
 * @flags: flags set by the driver, (V4L2_SUBDEV_MBUS_CODE_*)
 * @reserved: drivers and applications must zero this array
*********************************************************************************************/
struct v4l2_subdev_mbus_code_enum {
	__u32 pad;
	__u32 index;
	__u32 code;
	__u32 which;
	__u32 flags;
	__u32 reserved[7];
};



/*********************************************************************************************
 *
*********************************************************************************************/
struct ov7670_devtype {
	struct ov7670_win_size *win_sizes;
	unsigned int n_win_sizes;
	int (*set_framerate)(struct ov7670_info *, struct v4l2_fract *);
	void (*get_framerate)(struct ov7670_info *, struct v4l2_fract *);
};



/*********************************************************************************************
 * Store information about the video data format.  The color matrix
 * is deeply tied into the format, so keep the relevant values here.
 * The magic matrix numbers come from OmniVision.
 *********************************************************************************************/
struct ov7670_format_struct {
	u32 mbus_code;
	enum v4l2_colorspace colorspace;
	struct regval_list *regs;
	int cmatrix[CMATRIX_LEN];
};
#define N_OV7670_FMTS ARRAY_SIZE(ov7670_formats)



/*********************************************************************************************
 * Information we maintain about a known sensor.
 *********************************************************************************************/
struct ov7670_format_struct;  /* coming later */
struct ov7670_info {
	//struct v4l2_subdev sd;
#if defined(CONFIG_MEDIA_CONTROLLER)
	struct media_pad pad;
#endif
	//struct v4l2_ctrl_handler hdl;
	struct {
		/* gain cluster */
		struct v4l2_ctrl *auto_gain;
		struct v4l2_ctrl *gain;
	};
	struct {
		/* exposure cluster */
		struct v4l2_ctrl *auto_exposure;
		struct v4l2_ctrl *exposure;
	};
	struct {
		/* saturation/hue cluster */
		struct v4l2_ctrl *saturation;
		struct v4l2_ctrl *hue;
	};
	struct v4l2_mbus_framefmt format;
	struct ov7670_format_struct *fmt;  /* Current format */
	struct ov7670_win_size *wsize;
	struct clk *clk;
	int on;
	struct gpio_desc *resetb_gpio;
	struct gpio_desc *pwdn_gpio;
	unsigned int mbus_config;	/* Media bus configuration flags */
	int min_width;			/* Filter out smaller sizes */
	int min_height;			/* Filter out smaller sizes */
	int clock_speed;		/* External clock speed (MHz) */
	u8 clkrc;				/* Clock divider value */
	//bool use_smbus;			/* Use smbus I/O instead of I2C */
	bool pll_bypass;
	bool pclk_hb_disable;
	const struct ov7670_devtype *devtype; /* Device specifics */
};


enum  v4l2_exposure_auto_type {
	V4L2_EXPOSURE_AUTO = 0,
	V4L2_EXPOSURE_MANUAL = 1,
	V4L2_EXPOSURE_SHUTTER_PRIORITY = 2,
	V4L2_EXPOSURE_APERTURE_PRIORITY = 3
};

#define V4L2_CTRL_CLASS_USER		0x00980000	/* Old-style 'user' controls */
#define V4L2_CID_BASE			(V4L2_CTRL_CLASS_USER | 0x900)
#define V4L2_CID_USER_BASE		V4L2_CID_BASE
#define V4L2_CID_USER_CLASS		(V4L2_CTRL_CLASS_USER | 1)
#define V4L2_CID_BRIGHTNESS		(V4L2_CID_BASE+0)
#define V4L2_CID_CONTRAST		(V4L2_CID_BASE+1)
#define V4L2_CID_SATURATION		(V4L2_CID_BASE+2)
#define V4L2_CID_HUE			(V4L2_CID_BASE+3)
#define V4L2_CID_AUDIO_VOLUME		(V4L2_CID_BASE+5)
#define V4L2_CID_AUDIO_BALANCE		(V4L2_CID_BASE+6)
#define V4L2_CID_AUDIO_BASS		(V4L2_CID_BASE+7)
#define V4L2_CID_AUDIO_TREBLE		(V4L2_CID_BASE+8)
#define V4L2_CID_AUDIO_MUTE		(V4L2_CID_BASE+9)
#define V4L2_CID_AUDIO_LOUDNESS		(V4L2_CID_BASE+10)
#define V4L2_CID_BLACK_LEVEL		(V4L2_CID_BASE+11) /* Deprecated */
#define V4L2_CID_AUTO_WHITE_BALANCE	(V4L2_CID_BASE+12)
#define V4L2_CID_DO_WHITE_BALANCE	(V4L2_CID_BASE+13)
#define V4L2_CID_RED_BALANCE		(V4L2_CID_BASE+14)
#define V4L2_CID_BLUE_BALANCE		(V4L2_CID_BASE+15)
#define V4L2_CID_GAMMA			(V4L2_CID_BASE+16)
#define V4L2_CID_WHITENESS		(V4L2_CID_GAMMA) /* Deprecated */
#define V4L2_CID_EXPOSURE		(V4L2_CID_BASE+17)
#define V4L2_CID_AUTOGAIN		(V4L2_CID_BASE+18)
#define V4L2_CID_GAIN			(V4L2_CID_BASE+19)
#define V4L2_CID_HFLIP			(V4L2_CID_BASE+20)
#define V4L2_CID_VFLIP			(V4L2_CID_BASE+21)

#define V4L2_CTRL_CLASS_CAMERA		0x009a0000	/* Camera class controls */
#define V4L2_CID_CAMERA_CLASS_BASE	(V4L2_CTRL_CLASS_CAMERA | 0x900)
#define V4L2_CID_CAMERA_CLASS		(V4L2_CTRL_CLASS_CAMERA | 1)

#define V4L2_CTRL_CLASS_IMAGE_PROC	0x009f0000	/* Image processing controls */
#define V4L2_CID_IMAGE_PROC_CLASS_BASE		(V4L2_CTRL_CLASS_IMAGE_PROC | 0x900)
#define V4L2_CID_EXPOSURE_AUTO			(V4L2_CID_CAMERA_CLASS_BASE+1)
#define V4L2_CID_TEST_PATTERN			(V4L2_CID_IMAGE_PROC_CLASS_BASE + 3)


#define REG_SCALING_XSC	0x70	/* Test pattern and horizontal scale factor */
#define   TEST_PATTTERN_0 0x80
#define REG_SCALING_YSC	0x71	/* Test pattern and vertical scale factor */
#define   TEST_PATTTERN_1 0x80



#define	REG_CMATRIX_BASE 0x4f
#define   CMATRIX_LEN 6
#define REG_CMATRIX_SIGN 0x58




#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define BIT(n)		(1 << (n))




#define V4L2_MBUS_HSYNC_ACTIVE_HIGH		BIT(2)
#define V4L2_MBUS_HSYNC_ACTIVE_LOW		BIT(3)
#define V4L2_MBUS_VSYNC_ACTIVE_HIGH		BIT(4)
#define V4L2_MBUS_VSYNC_ACTIVE_LOW		BIT(5)
#define V4L2_MBUS_PCLK_SAMPLE_RISING		BIT(6)
#define V4L2_MBUS_PCLK_SAMPLE_FALLING		BIT(7)
#define V4L2_MBUS_DATA_ACTIVE_HIGH		BIT(8)
#define V4L2_MBUS_DATA_ACTIVE_LOW		BIT(9)

/**
 * struct v4l2_ctrl - The control structure.
 *
 * @node:	The list node.
 * @ev_subs:	The list of control event subscriptions.
 * @handler:	The handler that owns the control.
 * @cluster:	Point to start of cluster array.
 * @ncontrols:	Number of controls in cluster array.
 * @done:	Internal flag: set for each processed control.
 * @is_new:	Set when the user specified a new value for this control. It
 *		is also set when called from v4l2_ctrl_handler_setup(). Drivers
 *		should never set this flag.
 * @has_changed: Set when the current value differs from the new value. Drivers
 *		should never use this flag.
 * @is_private: If set, then this control is private to its handler and it
 *		will not be added to any other handlers. Drivers can set
 *		this flag.
 * @is_auto:   If set, then this control selects whether the other cluster
 *		members are in 'automatic' mode or 'manual' mode. This is
 *		used for autogain/gain type clusters. Drivers should never
 *		set this flag directly.
 * @is_int:    If set, then this control has a simple integer value (i.e. it
 *		uses ctrl->val).
 * @is_string: If set, then this control has type %V4L2_CTRL_TYPE_STRING.
 * @is_ptr:	If set, then this control is an array and/or has type >=
 *		%V4L2_CTRL_COMPOUND_TYPES
 *		and/or has type %V4L2_CTRL_TYPE_STRING. In other words, &struct
 *		v4l2_ext_control uses field p to point to the data.
 * @is_array: If set, then this control contains an N-dimensional array.
 * @has_volatiles: If set, then one or more members of the cluster are volatile.
 *		Drivers should never touch this flag.
 * @call_notify: If set, then call the handler's notify function whenever the
 *		control's value changes.
 * @manual_mode_value: If the is_auto flag is set, then this is the value
 *		of the auto control that determines if that control is in
 *		manual mode. So if the value of the auto control equals this
 *		value, then the whole cluster is in manual mode. Drivers should
 *		never set this flag directly.
 * @ops:	The control ops.
 * @type_ops:	The control type ops.
 * @id:	The control ID.
 * @name:	The control name.
 * @type:	The control type.
 * @minimum:	The control's minimum value.
 * @maximum:	The control's maximum value.
 * @default_value: The control's default value.
 * @step:	The control's step value for non-menu controls.
 * @elems:	The number of elements in the N-dimensional array.
 * @elem_size:	The size in bytes of the control.
 * @dims:	The size of each dimension.
 * @nr_of_dims:The number of dimensions in @dims.
 * @menu_skip_mask: The control's skip mask for menu controls. This makes it
 *		easy to skip menu items that are not valid. If bit X is set,
 *		then menu item X is skipped. Of course, this only works for
 *		menus with <= 32 menu items. There are no menus that come
 *		close to that number, so this is OK. Should we ever need more,
 *		then this will have to be extended to a u64 or a bit array.
 * @qmenu:	A const char * array for all menu items. Array entries that are
 *		empty strings ("") correspond to non-existing menu items (this
 *		is in addition to the menu_skip_mask above). The last entry
 *		must be NULL.
 *		Used only if the @type is %V4L2_CTRL_TYPE_MENU.
 * @qmenu_int:	A 64-bit integer array for with integer menu items.
 *		The size of array must be equal to the menu size, e. g.:
 *		:math:`ceil(\frac{maximum - minimum}{step}) + 1`.
 *		Used only if the @type is %V4L2_CTRL_TYPE_INTEGER_MENU.
 * @flags:	The control's flags.
 * @cur:	Structure to store the current value.
 * @cur.val:	The control's current value, if the @type is represented via
 *		a u32 integer (see &enum v4l2_ctrl_type).
 * @val:	The control's new s32 value.
 * @priv:	The control's private pointer. For use by the driver. It is
 *		untouched by the control framework. Note that this pointer is
 *		not freed when the control is deleted. Should this be needed
 *		then a new internal bitfield can be added to tell the framework
 *		to free this pointer.
 * @p_def:	The control's default value represented via a union which
 *		provides a standard way of accessing control types
 *		through a pointer (for compound controls only).
 * @p_cur:	The control's current value represented via a union which
 *		provides a standard way of accessing control types
 *		through a pointer.
 * @p_new:	The control's new value represented via a union which provides
 *		a standard way of accessing control types
 *		through a pointer.
 */
struct v4l2_ctrl {
	/* Administrative fields */
	//struct list_head node;
	//struct list_head ev_subs;
	struct v4l2_ctrl_handler *handler;
	struct v4l2_ctrl **cluster;
	unsigned int ncontrols;

	unsigned int done:1;

	unsigned int is_new:1;
	unsigned int has_changed:1;
	unsigned int is_private:1;
	unsigned int is_auto:1;
	unsigned int is_int:1;
	unsigned int is_string:1;
	unsigned int is_ptr:1;
	unsigned int is_array:1;
	unsigned int has_volatiles:1;
	unsigned int call_notify:1;
	unsigned int manual_mode_value:8;

	const struct v4l2_ctrl_ops *ops;
	const struct v4l2_ctrl_type_ops *type_ops;
	u32 id;
	const char *name;
	//enum v4l2_ctrl_type type;
	//s64 minimum, maximum, default_value;
	u32 elems;
	u32 elem_size;
	//u32 dims[V4L2_CTRL_MAX_DIMS];
	u32 nr_of_dims;
	//union {
	//	u64 step;
	//	u64 menu_skip_mask;
	//};
	//union {
	//	const char * const *qmenu;
	//	const s64 *qmenu_int;
	//};
	unsigned long flags;
	void *priv;
	s32 val;
	struct {
		s32 val;
	} cur;

	//union v4l2_ctrl_ptr p_def;
	//union v4l2_ctrl_ptr p_new;
	//union v4l2_ctrl_ptr p_cur;
};






void ov7670_initialization();


#endif /* INC_OV7670_H_ */
