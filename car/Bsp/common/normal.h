#ifndef _NORMAL_H_
#define _NORMAL_H_

#include "headfile.h"


#ifndef NULL
#define NULL ((void *)0)
#endif


#define DELAY_CLK SystemCoreClock

#define USEC_TO_COUNT(us, clockFreqInHz)		(uint64_t)(((uint64_t)(us) * (clockFreqInHz)) / 1000000U)

//------------------------------------以下宏定义用于延时------------------------------------
void systick_delay(uint32 time);
void systick_delay_ms(uint32 ms);														// 毫秒级延时函数 由于滴答定时器最大只有24位，因此用函数实现，这样延时时间范围较宽
#define systick_delay_us(time)		systick_delay(USEC_TO_COUNT(time, DELAY_CLK))		// 设置延时时间 单位us 范围0 - 16777215(0xffffff)/(DELAY_CLK*1000)ms	主频48M systick最大延时时间大约为16ms
#define delay_ms(x)  				systick_delay_ms(x)
#define delay_us(x)  				systick_delay_us(x)


//------------------------------------配置时钟的函数------------------------------------
typedef struct 
{
	uint32	 	aclk;
	uint32 		mclk;
	uint32		hsmclk;
	uint32		smclk;
	uint32 		bclk;
}SysClockStructure;
extern SysClockStructure SysClock;

//func
void Clock_ReConfig(void);
void Clock_Show(void);
int range_protect(int x, int x_min, int x_max);


#endif


