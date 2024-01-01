
//���õĺ�����

#include "normal.h"


//��ʱ���� systickʵ�� ʱ�ӿ̶�ΪϵͳƵ��
void systick_delay(uint32 t) 
{
	SysTick-> CTRL = 0x00;
	SysTick->LOAD = t - 1;
	SysTick->VAL = 0x00;
	SysTick->CTRL	=	SysTick_CTRL_CLKSOURCE_Msk |					//ʱ��Դѡ�� (core clk)
						SysTick_CTRL_ENABLE_Msk;						//ʹ�� systick
	while( !(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
}


//��ʱms
void systick_delay_ms (uint32 time)
{
	while(time--) systick_delay(SystemCoreClock / 1000);
}


SysClockStructure SysClock;
//ʱ������ 
/* 
	MCLK 	= 48MHz
	ACLK 	= 32.768KHz
	HSMCLK 	= 24MHz 
	SMCLK	= 12MHz 
	BCLK	= 32.768KHz
*/

void Clock_ReConfig(void)
{
	//���þ���pin
	GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
            GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
	//����ʱ��Ƶ��
	CS_setExternalClockSourceFrequency(32000,48000000);
	//�����ں˵�ѹ bank�ӳ�
	PCM_setCoreVoltageLevel(PCM_VCORE1);
    FlashCtl_setWaitState(FLASH_BANK0, 1);
    FlashCtl_setWaitState(FLASH_BANK1, 1);
    CS_startHFXT(false);
	//���Ӹ�����ʱ��
	CS_initClockSignal(CS_MCLK	, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
	CS_initClockSignal(CS_ACLK	, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_HSMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_2);
    CS_initClockSignal(CS_SMCLK	, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_4);
    CS_initClockSignal(CS_BCLK	, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
	
	SysClock.aclk 	= CS_getACLK();
    SysClock.mclk  	= CS_getMCLK();
    SysClock.smclk  = CS_getSMCLK();
    SysClock.hsmclk = CS_getHSMCLK();
    SysClock.bclk 	= CS_getBCLK();
	//��fpu
    FPU_enableModule();
    FPU_enableLazyStacking();
}



/* ��ʾ��������ʱ�� */
void Clock_Show(void)
{
	oled_p8x16str(20,0,"CLOCK CFG:");
	oled_p6x8str(0,3,"ACLK: ");
	oled_p6x8str(0,4,"MCLK: ");
	oled_p6x8str(0,5,"SMCLK: ");
	oled_p6x8str(0,6,"HSMCLK:");
	oled_printf_int32(50,3,SysClock.aclk,8);
	oled_printf_int32(50,4,SysClock.mclk,8);
	oled_printf_int32(50,5,SysClock.smclk,8);
	oled_printf_int32(50,6,SysClock.hsmclk,8);
	oled_p6x8str(115,3,"Hz");
	oled_p6x8str(115,4,"Hz");
	oled_p6x8str(115,5,"Hz");
	oled_p6x8str(115,6,"Hz");
	delay_ms(800);
	oled_fill(0x00);
}

//�����޷�����
int range_protect(int x, int x_min, int x_max)
{
	if(x >= x_max) return x_max;
	else if(x <= x_min) return x_min;
	//none
	return x;
}


