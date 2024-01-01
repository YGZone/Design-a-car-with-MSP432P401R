#ifndef _NORMAL_H_
#define _NORMAL_H_

#include "headfile.h"


#ifndef NULL
#define NULL ((void *)0)
#endif


#define DELAY_CLK SystemCoreClock

#define USEC_TO_COUNT(us, clockFreqInHz)		(uint64_t)(((uint64_t)(us) * (clockFreqInHz)) / 1000000U)

//------------------------------------���º궨��������ʱ------------------------------------
void systick_delay(uint32 time);
void systick_delay_ms(uint32 ms);														// ���뼶��ʱ���� ���ڵδ�ʱ�����ֻ��24λ������ú���ʵ�֣�������ʱʱ�䷶Χ�Ͽ�
#define systick_delay_us(time)		systick_delay(USEC_TO_COUNT(time, DELAY_CLK))		// ������ʱʱ�� ��λus ��Χ0 - 16777215(0xffffff)/(DELAY_CLK*1000)ms	��Ƶ48M systick�����ʱʱ���ԼΪ16ms
#define delay_ms(x)  				systick_delay_ms(x)
#define delay_us(x)  				systick_delay_us(x)


//------------------------------------����ʱ�ӵĺ���------------------------------------
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


