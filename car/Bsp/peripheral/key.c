
//板载按键P1.1 P1.4

#include "key.h"


//key pin init
void Key_Init(void)
{
	GPIO_setAsInputPinWithPullUpResistor(KEY_LEFT_PORT,KEY_LEFT_PIN);
	GPIO_setAsInputPinWithPullUpResistor(KEY_RIGHT_PORT,KEY_RIGHT_PIN);
}

//key int init 
//!中断函数需要自己在isr.c中注册
void Key_Int_Init(void)
{
	//配置引脚
	GPIO_setAsInputPinWithPullUpResistor(KEY_LEFT_PORT,KEY_LEFT_PIN);
	//配置中断
	GPIO_clearInterruptFlag(KEY_LEFT_PORT, KEY_LEFT_PIN);
	GPIO_enableInterrupt(KEY_LEFT_PORT, KEY_LEFT_PIN);
	Interrupt_enableInterrupt(INT_PORT1);
	//使能sram bank 低功耗 开不开都行
	SysCtl_enableSRAMBankRetention(SYSCTL_SRAM_BANK1);
	//使能中断控制器
	Interrupt_enableMaster();
}


//simple key scan 
uint8 Key_Scan(void)
{
	if(KEY_LEFT == 0)
	{
		delay_ms(5);
		if(KEY_LEFT == 0)
			return KEY_LEFT_PRESS;
	}
	else if(KEY_RIGHT == 0)
	{
		delay_ms(5);
		if(KEY_RIGHT == 0)
			return KEY_RIGHT_PRESS;
	}
	
	//
	return 0;
}


//test
void Key_Test(void)
{
	if(Key_Scan() == KEY_LEFT_PRESS)
	{
		LED_ON;
	}
	if(Key_Scan() == KEY_RIGHT_PRESS)
	{
		LED_OFF;
	}
}

