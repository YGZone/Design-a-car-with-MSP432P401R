
//器件初始化

#include "All_Init.h"



//所有的器件初始化
void System_Init(void)
{
	//重新配置时钟
	Clock_ReConfig();
	
	//板载外设函数
	LED_Init();
	RGBLED_Init();
	oled_init();
	Clock_Show();
	Key_Init();	
	Servo_Timer_Init();
	Encoder_Init();
	Motor_Timer_Init();
	pid_param_init();
	ANO_DT_Init();
//	mpu6050_init();
	
	Sys_Timer_Init();
	Interrupt_enableMaster();
	//用户函数
	
}















