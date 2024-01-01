
//oled12864
//zf库 

#include "oled.h"
#include "font.h"
#include <stdarg.h>
#include <string.h>

#define OLED_SCL(x)	((x == 0)? (GPIO_setOutputLowOnPin(OLED_SCL_PORT,OLED_SCL_PIN))	:(GPIO_setOutputHighOnPin(OLED_SCL_PORT,OLED_SCL_PIN)))
#define OLED_SDA(x)	((x == 0)? (GPIO_setOutputLowOnPin(OLED_SDA_PORT,OLED_SDA_PIN))	:(GPIO_setOutputHighOnPin(OLED_SDA_PORT,OLED_SDA_PIN)))
#define OLED_RST(x)	((x == 0)? (GPIO_setOutputLowOnPin(OLED_RST_PORT,OLED_RST_PIN))	:(GPIO_setOutputHighOnPin(OLED_RST_PORT,OLED_RST_PIN)))
#define OLED_DC(x)	((x == 0)? (GPIO_setOutputLowOnPin(OLED_DC_PORT,OLED_DC_PIN))	:(GPIO_setOutputHighOnPin(OLED_DC_PORT,OLED_DC_PIN)))
#define OLED_CS(x)	((x == 0)? (GPIO_setOutputLowOnPin(OLED_CS_PORT,OLED_CS_PIN))	:(GPIO_setOutputHighOnPin(OLED_CS_PORT,OLED_CS_PIN)))

//-------------------------------------------------------------------------------------------------------------------
// @brief		写8位数据
// @param		data			数据
// @return		void
// @since		v1.0
// Sample usage:
// @note		内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void oled_wrdat(uint8 data)
{
	uint8 i=8;

	OLED_CS(0);																// 使能信号端，拉低时正常使用
	OLED_DC(1);
	OLED_SCL(0);
	while(i--)
	{
		if(data&0x80){OLED_SDA(1);}
		else{OLED_SDA(0);}
		OLED_SCL(1);

		OLED_SCL(0);
		data<<=1;
	}
	OLED_CS(1);																// 使能信号端，拉低时正常使用
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		写命令
// @param		cmd				命令
// @return		void
// @since		v1.0
// Sample usage:
// @note		内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void oled_wrcmd(uint8 cmd)
{
	uint8 i=8;

	OLED_CS(0);																// 使能信号端，拉低时正常使用
	OLED_DC(0);
	OLED_SCL(0);;

	while(i--)
	{
		if(cmd&0x80){OLED_SDA(1);}
		else{OLED_SDA(0);}
		OLED_SCL(1);

		OLED_SCL(0);
		cmd<<=1;
	}
	OLED_CS(1);																// 使能信号端，拉低时正常使用
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		转换16进制ascii码
// @param		hex				ascii码
// @param		Print			存放地址
// @return		void
// @since		v1.0
// Sample usage:
// @note		内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void oled_hexascii(uint16 hex,int8 * Print)
{
	uint8 hexcheck ;
	uint8 TEMP ;
	TEMP = 6 ;
	Print[TEMP ]='\0';
	while(TEMP)
	{
		TEMP -- ;
		hexcheck  =  hex%10 ;
		hex   /=10 ;
		Print[TEMP ]  = hexcheck + 0x30 ;
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED初始化函数
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void oled_init(void)
{
	GPIO_setAsOutputPin(OLED_SCL_PORT,OLED_SCL_PIN);
	GPIO_setAsOutputPin(OLED_SDA_PORT,OLED_SDA_PIN);
	GPIO_setAsOutputPin(OLED_RST_PORT,OLED_RST_PIN);
	GPIO_setAsOutputPin(OLED_DC_PORT,OLED_DC_PIN);
	GPIO_setAsOutputPin(OLED_CS_PORT,OLED_CS_PIN);
	
	OLED_SCL(1);
	OLED_RST(0);
	systick_delay_ms(50);
	OLED_RST(1);

	oled_wrcmd(0xae);														// --turn off oled panel
	oled_wrcmd(0x00);														// ---set low column address
	oled_wrcmd(0x10);														// ---set high column address
	oled_wrcmd(0x40);														// --set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	oled_wrcmd(0x81);														// --set contrast control register
	oled_wrcmd(Brightness);													//  Set SEG Output Current Brightness

#if (0 == OLED_DISPLAY_DIR)
	oled_wrcmd(0xa1);														// --Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	oled_wrcmd(0xc8);														// Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
#else
	oled_wrcmd(0xa0);														// --Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	oled_wrcmd(0xc0);														// Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
#endif
    
	oled_wrcmd(0xa6);														// --set normal display
	oled_wrcmd(0xa8);														// --set multiplex ratio(1 to 64)
	oled_wrcmd(0x3f);														// --1/64 duty
	oled_wrcmd(0xd3);														// -set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	oled_wrcmd(0x00);														// -not offset
	oled_wrcmd(0xd5);														// --set display clock divide ratio/oscillator frequency
	oled_wrcmd(0x80);														// --set divide ratio, Set Clock as 100 Frames/Sec
	oled_wrcmd(0xd9);														// --set pre-charge period
	oled_wrcmd(0xf1);														// Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	oled_wrcmd(0xda);														// --set com pins hardware configuration
	oled_wrcmd(0x12);
	oled_wrcmd(0xdb);														// --set vcomh
	oled_wrcmd(0x40);														// Set VCOM Deselect Level
	oled_wrcmd(0x20);														// -Set Page Addressing Mode (0x00/0x01/0x02)
	oled_wrcmd(0x02);														// 
	oled_wrcmd(0x8d);														// --set Charge Pump enable/disable
	oled_wrcmd(0x14);														// --set(0x10) disable
	oled_wrcmd(0xa4);														//  Disable Entire Display On (0xa4/0xa5)
	oled_wrcmd(0xa6);														//  Disable Inverse Display On (0xa6/a7)
	oled_wrcmd(0xaf);														// --turn on oled panel
	oled_fill(0x00);														// 初始清屏
	oled_set_pos(0,0);
	oled_p8x16str(0,0,"Hello Ti!");
	for(uint8 i = 0;i < 128;i ++)
	{
		oled_putpixel(i,5,0xff);
		delay_ms(2);
	}
	delay_ms(300);
	oled_fill(0x00);
	oled_set_pos(0,0);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED显示坐标设置
// @param		x				x轴坐标设置0-127
// @param		y				y轴坐标设置0-7
// @return		void
// @since		v1.0
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void oled_set_pos(uint8 x, uint8 y)
{
	oled_wrcmd(0xb0+y);
	oled_wrcmd(((x&0xf0)>>4)|0x10);
	oled_wrcmd((x&0x0f)|0x00);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED清屏函数
// @param		bmp_data		填充颜色选着(0x00 or 0xff)
// @return		void
// @since		v1.0
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void oled_fill(uint8 bmp_data)
{
	uint8 y,x;

	for(y=0;y<8;y++)
	{
		oled_wrcmd(0xb0+y);
		oled_wrcmd(0x01);
		oled_wrcmd(0x10);
		for(x=0;x<X_WIDTH;x++)	oled_wrdat(bmp_data); 
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED控制一个坐标下8个像素的点亮与熄灭
// @param		x				x轴坐标设置0-127
// @param		y				y轴坐标设置0-7
// @return		void
// @since		v1.0
// Sample usage:				oled_putpixel(0,0,0xff);//将0,0坐标 8个点全部点亮
// Sample usage:				oled_putpixel(0,0,0x01);//将0,0坐标 最低位点亮其余7个熄灭
// @note		同理可以任意控制一个坐标下8个像素的点亮与熄灭
//-------------------------------------------------------------------------------------------------------------------
void oled_putpixel(uint8 x,uint8 y,uint8 data1)
{
	oled_set_pos(x,y);
	oled_wrcmd(0xb0+y);
	oled_wrcmd(((x&0xf0)>>4)|0x10);
	oled_wrcmd((x&0x0f)|0x00);
	oled_wrdat(data1);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED关闭一个坐标所有亮点
// @param		x				x轴坐标设置0-127
// @param		y				y轴坐标设置0-7
// @return		void
// @since		v1.0
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void oled_clrpixel(uint8 x,uint8 y)
{
	oled_set_pos(x,y);
	oled_wrcmd(0xb0+y);
	oled_wrcmd(((x&0xf0)>>4)|0x10);
	oled_wrcmd((x&0x0f)|0x00);
	oled_wrdat(0x00);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED显示字符串(6*8字体)
// @param		x				x轴坐标设置0-127
// @param		y				y轴坐标设置0-7
// @param		ch[]			字符串
// @return		void
// @since		v1.0
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void oled_p6x8str(uint8 x,uint8 y,const int8 ch[])
{
	uint8 c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>126)
		{
			x=0;
			y++;
		}
		oled_set_pos(x,y);
		for(i=0;i<6;i++)
			oled_wrdat(oled_6x8[c][i]);
		x+=6;
		j++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED显示字符串(8*16字体)
// @param		x				x轴坐标设置0-127
// @param		y				y轴坐标设置0-7
// @param		ch[]			字符串
// @return		void
// @since		v1.0
// Sample usage:				务必注意，本函数字符列高位16，因此y应该是每次递增2
//-------------------------------------------------------------------------------------------------------------------
void oled_p8x16str(uint8 x,uint8 y,const int8 ch[])
{
	uint8 c=0,i=0,j=0;

	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120)
		{
			x=0;
			y++;
		}
		oled_set_pos(x,y);
		for(i=0;i<8;i++)
			oled_wrdat(oled_8x16[c*16+i]);

		oled_set_pos(x,y+1);
		for(i=0;i<8;i++)
			oled_wrdat(oled_8x16[c*16+i+8]);
		x+=8;
		j++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED显示无符号数(6*8字体)
// @param		x				x轴坐标设置0-127
// @param		y				y轴坐标设置0-7
// @param		num				无符号数
// @return		void
// @since		v1.0
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void oled_uint16(uint8 x, uint8 y, uint16 num)
{
	int8 ch[7];

	oled_hexascii(num,ch);
	oled_p6x8str(x, y, &ch[1]);												// 显示数字  6*8字体
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED显示有符号数(6*8字体)
// @param		x				x轴坐标设置0-127
// @param		y				y轴坐标设置0-7
// @param		num				有符号数
// @return		void
// @since		v1.0
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void oled_int16(uint8 x, uint8 y, int16 num)
{
	int8 ch[7];
	if(num<0)
	{
		num = -num;
		oled_p6x8str(x, y, "-");
	}
	else
		oled_p6x8str(x, y, " ");
	x+=6;       

	oled_hexascii(num,ch);
	oled_p6x8str(x, y, &ch[1]);												// 显示数字  6*8字体
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED显示32位有符号(去除整数部分无效的0)
// @param		x				x轴坐标设置0-127
// @param		y				y轴坐标设置0-7
// @param		dat				需要显示的变量，数据类型uint32
// @param		num				需要显示的位数 最高10位  不包含正负号
// @return		void
// @since		v1.0
// Sample usage:				oled_printf_int32(0,0,x,5);//x可以为int32 uint16 int16 uint8 int8类型
// Sample usage:				负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void oled_printf_int32(uint16 x,uint16 y,int32 dat,uint8 num)
{
	int8    buff[34];
	uint8   length;

	if(10<num)      num = 10;

	num++;
	if(0>dat)
		length = zf_sprintf( &buff[0],"%d",dat);							// 负数
	else
	{
		buff[0] = ' ';
		length = zf_sprintf( &buff[1],"%d",dat);
		length++;
	}
	while(length < num)
	{
		buff[length] = ' ';
		length++;
	}
	buff[num] = '\0';

	oled_p6x8str(x, y, buff);												// 显示数字
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED显示浮点数(去除整数部分无效的0)
// @param		x				x轴坐标设置0-127
// @param		y				y轴坐标设置0-7
// @param		dat				需要显示的变量，数据类型float或double
// @param		num				整数位显示长度   最高10位  
// @param		pointnum		小数位显示长度   最高6位
// @return		void
// @since		v1.0
// Sample usage:		oled_printf_float(0,0,x,2,3);//显示浮点数   整数显示2位   小数显示三位
// @note				特别注意当发现小数部分显示的值与你写入的值不一样的时候，
// 						可能是由于浮点数精度丢失问题导致的，这并不是显示函数的问题，
// 						有关问题的详情，请自行百度学习   浮点数精度丢失问题。
// 						负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void oled_printf_float(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum)
{
	static uint8	length;
	static int8		buff[34];
	static int8		end,point;
	static int start; 
	if(6<pointnum)
		pointnum = 6;
	if(10<num)
		num = 10;

	if(0>dat)
		length = zf_sprintf( &buff[0],"%f",dat);							// 负数
	else
	{
		length = zf_sprintf( &buff[1],"%f",dat);
		length++;
	}
	point = length - 7;														// 计算小数点位置
	start = point - num - 1;												// 计算起始位
	end = point + pointnum + 1;												// 计算结束位
	while(start < 0)															// 整数位不够  末尾应该填充空格
	{
		buff[end] = ' ';
		end++;
		start++;
	}

	if(0>dat)
		buff[start] = '-';
	else
		buff[start] = ' ';
	buff[end] = '\0';

	oled_p6x8str(x, y, buff);												// 显示数字
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED显示图像
// @param		high			图像高度
// @param		width			图像宽度
// @param		*p				图像地 址（数组）
// @param		value			二值化阀值
// @return		void
// @since		v1.0
// Sample usage:
// @Note		使用Image2lcd V3.2软件取模   C语言数组   水平扫描   
// 				宽度高度自行设置   颜色反转  256色
//-------------------------------------------------------------------------------------------------------------------
void oled_dis_bmp(uint16 high, uint16 width, uint8 *p,uint8 value)
{
	int16 i,j;
	int16 temp,temp1;
	uint8 dat;


	temp1 = high%8;
	if(temp1 == 0)
		temp = high/8;
	else
		temp = high/8+1;

	for(i=0; i<temp; i++)
	{
		oled_set_pos(0,i);
		for(j=0; j<width; j++)
		{
			dat = 0;
			if( i<(temp-1) || !temp1 || temp1>=1)dat |= (*(p+i*8*width+j+width*0) > value? 1: 0)<<0;
			if( i<(temp-1) || !temp1 || temp1>=2)dat |= (*(p+i*8*width+j+width*1) > value? 1: 0)<<1;
			if( i<(temp-1) || !temp1 || temp1>=3)dat |= (*(p+i*8*width+j+width*2) > value? 1: 0)<<2;
			if( i<(temp-1) || !temp1 || temp1>=4)dat |= (*(p+i*8*width+j+width*3) > value? 1: 0)<<3;
			if( i<(temp-1) || !temp1 || temp1>=5)dat |= (*(p+i*8*width+j+width*4) > value? 1: 0)<<4;
			if( i<(temp-1) || !temp1 || temp1>=6)dat |= (*(p+i*8*width+j+width*5) > value? 1: 0)<<5;
			if( i<(temp-1) || !temp1 || temp1>=7)dat |= (*(p+i*8*width+j+width*6) > value? 1: 0)<<6;
			if( i<(temp-1) || !temp1 || temp1>=8)dat |= (*(p+i*8*width+j+width*7) > value? 1: 0)<<7;

			oled_wrdat(dat);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		汉字显示
// @param		x				横坐标 0-127
// @param		y				纵坐标 0-7
// @param		size			取模的时候设置的汉字字体大小，也就是一个汉字占用的点阵长宽为多少个点，取模的时候需要长宽是一样的。
// @param		*p				需要显示的汉字数组
// @param		len				需要显示多少位
// @return		void
// @since		v1.0
// Sample usage:
// @Note		使用PCtoLCD2002软件取模		阴码、逐行式、顺向		16*16
//-------------------------------------------------------------------------------------------------------------------
void oled_print_chinese(uint8 x, uint8 y, uint8 size, const uint8 *p, uint8 len)
{
	int16 i,j,k;

	for(i=0; i<len; i++)
	{
		for(j=0; j<(size/8); j++)
		{
			oled_set_pos(x+i*size,y+j);
			for(k=0; k<16; k++)
			{
				oled_wrdat(*p);
				p++;
			}
		}
	}
}



//格式化
uint8 number_conversion_ascii(uint32 dat, int8 *p, uint8 neg_type, uint8 radix)
{
	int32   neg_dat;
	uint32  pos_dat;
	uint8   temp_data = 0;
	uint8   valid_num = 0;

	if(neg_type)
	{
		neg_dat = (int32)dat;
		if(neg_dat<0)   neg_dat = -neg_dat;
		while(1)
		{
			*p = neg_dat%radix + '0';
			neg_dat = neg_dat/radix;
			valid_num++;

			if(!neg_dat) break;
			p++;
		}
	}
	else
	{
		pos_dat = dat;
		while(1)
		{
			temp_data = pos_dat%radix;
			if(10 <= temp_data)	temp_data += 'A'-10;
			else				temp_data += '0';

			*p = temp_data;

			pos_dat = pos_dat/radix;
			valid_num++;

			if(!pos_dat) break;
			p++;
		}
	}
	return valid_num;
}

void printf_reverse_order(int8 *d_buff, uint32 len)
{
	uint32 i;
	int8  temp_data;
	for(i=0;i<len/2;i++)
	{
		temp_data = d_buff[len-1-i];
		d_buff[len-1-i] = d_buff[i];
		d_buff[i] = temp_data; 
	}
}

uint32 zf_sprintf(int8 *buff, const int8 *format, ...)
{
	uint32 buff_len=0;
	va_list arg;
	va_start(arg, format);

	while (*format)
	{
		int8 ret = *format;
		if (ret == '%')
		{
			switch (*++format)
			{
				case 'a':// 十六进制p计数法输出浮点数 暂未实现
					{
					}
					break;

				case 'c':// 一个字符
					{
						int8 ch = (int8)va_arg(arg, uint32);
						*buff = ch;
						buff++;
						buff_len++;
					}
					break;

				case 'd':
				case 'i':// 有符号十进制整数
					{
						int8 vstr[33];
						int32 ival = (int32)va_arg(arg, int32);
						uint8 vlen = number_conversion_ascii((uint32)ival, vstr, 1, 10);

						if(ival<0)  
						{
							vstr[vlen] = '-';
							vlen++;
						}
						printf_reverse_order(vstr,vlen);
						memcpy(buff,vstr,vlen);
						buff += vlen;
						buff_len += vlen;
					}
					break;

				case 'f':// 浮点数，输出小数点后六位  不能指定输出精度
				case 'F':// 浮点数，输出小数点后六位  不能指定输出精度
				{
					int8 vstr[33];
					double ival = (double)va_arg(arg, double);
					uint8 vlen = number_conversion_ascii((uint32)(int32)ival, vstr, 1, 10);

					if(ival<0)  
					{
						vstr[vlen] = '-';
						vlen++;
					}
					printf_reverse_order(vstr,vlen);
					memcpy(buff,vstr,vlen);
					buff += vlen;
					buff_len += vlen;

					ival = ((double)ival - (int32)ival)*1000000;
					if(ival)
					{
						vlen = number_conversion_ascii((uint32)(int32)ival, vstr, 1, 10);
					}
					else
					{
						vstr[0] = vstr[1] = vstr[2] = vstr[3] = vstr[4] = vstr[5] = '0';
						vlen = 6;
					}

					while(6>vlen)
					{
						vstr[vlen] = '0';
						vlen++;
					}

					vstr[vlen] = '.';
					vlen++;

					printf_reverse_order(vstr,vlen);
					memcpy(buff,vstr,vlen);
					buff_len += vlen;
				}
				break;

				case 'u':// 无符号十进制整数
					{
						int8 vstr[33];
						uint32 ival = (uint32)va_arg(arg, uint32);
						uint8 vlen = number_conversion_ascii(ival, vstr, 0, 10);

						printf_reverse_order(vstr,vlen);
						memcpy(buff,vstr,vlen);
						buff += vlen;
						buff_len += vlen;
					}
					break;

				case 'o':// 无符号八进制整数 
					{
						int8 vstr[33];
						uint32 ival = (uint32)va_arg(arg, uint32);
						uint8 vlen = number_conversion_ascii(ival, vstr, 0, 8);

						printf_reverse_order(vstr,vlen);
						memcpy(buff,vstr,vlen);
						buff += vlen;
						buff_len += vlen;

					}
					break;

				case 'x':// 无符号十六进制整数
				case 'X':// 无符号十六进制整数
					{
						int8 vstr[33];
						uint32 ival = (uint32)va_arg(arg, uint32);
						uint8 vlen = number_conversion_ascii(ival, vstr, 0, 16);

						printf_reverse_order(vstr,vlen);
						memcpy(buff,vstr,vlen);
						buff += vlen;
						buff_len += vlen;
					}
					break;

				case 's':// 字符串
					{
						int8 *pc = va_arg(arg, int8 *);
						while (*pc)
						{
							*buff = *pc;
							buff++;
							buff_len++;
							pc++;
						}
					}
					break;

				case 'p':// 以16进制形式输出指针
					{
						int8 vstr[33];
						uint32 ival = (uint32)va_arg(arg, uint32);
						uint8 vlen = number_conversion_ascii(ival, vstr, 0, 16);

						printf_reverse_order(vstr,8);
						memcpy(buff,vstr,8);
						buff += 8;
						buff_len += 8;
					}
					break;

				case '%':// 输出字符% 
					{
						*buff = '%';
						buff++;
						buff_len++;
					}
					break;

				default:
					break;
			}
		}
		else
		{
			*buff = (int8)(*format);
			buff++;
			buff_len++;
		}
		format++;
	}
	va_end(arg);

	return buff_len;
}






