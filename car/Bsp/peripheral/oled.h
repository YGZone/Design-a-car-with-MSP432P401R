#ifndef _OLED_H_
#define _OLED_H_


#include "headfile.h"

//----宏定义OLED引脚----	 
#define OLED_SCL_PORT			GPIO_PORT_P3
#define OLED_SDA_PORT			GPIO_PORT_P5
#define OLED_RST_PORT			GPIO_PORT_P5
#define OLED_DC_PORT			GPIO_PORT_P3
#define OLED_CS_PORT			GPIO_PORT_P3
#define OLED_SCL_PIN			GPIO_PIN6
#define OLED_SDA_PIN			GPIO_PIN2
#define OLED_RST_PIN			GPIO_PIN0
#define OLED_DC_PIN				GPIO_PIN7
#define OLED_CS_PIN				GPIO_PIN5

//定义显示方向
//0 横屏模式
//1 横屏模式  旋转180
#define OLED_DISPLAY_DIR		0

#if (0==OLED_DISPLAY_DIR || 1==OLED_DISPLAY_DIR)
#define X_WIDTH					128
#define Y_WIDTH					64

#else
#error "OLED_DISPLAY_DIR 定义错误"
#endif
                            
#define	Brightness				0x7f										// 设置OLED亮度 越大越亮 范围0-0XFF
#define XLevelL					0x00
#define XLevelH					0x10
#define XLevel					((XLevelH&0x0F)*16+XLevelL)
#define Max_Column				128
#define Max_Row					64

void	oled_init				(void);     
void	oled_fill				(uint8 dat);
void	oled_set_pos			(uint8 x, uint8 y);
void	oled_putpixel			(uint8 x,uint8 y,uint8 data1);
void	oled_clrpixel			(uint8 x,uint8 y);
void	oled_p6x8str			(uint8 x,uint8 y,const int8 ch[]);
void	oled_p8x16str			(uint8 x,uint8 y,const int8 ch[]);
void	oled_uint16				(uint8 x, uint8 y, uint16 num);
void	oled_int16				(uint8 x, uint8 y, int16 num);
void	oled_printf_int32		(uint16 x,uint16 y,int32 dat,uint8 num);
void	oled_printf_float		(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum);
void	oled_dis_bmp			(uint16 high, uint16 width, uint8 *p,uint8 value);
void	oled_print_chinese		(uint8 x, uint8 y, uint8 size, const uint8 *p, uint8 len);

//格式化
uint32 zf_sprintf(int8 *buff, const int8 *format, ...);




#endif

