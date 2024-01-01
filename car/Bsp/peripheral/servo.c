
//使用TA0控制舵机

#include "servo.h"


/* Timer_A PWM Configuration Parameter */
Timer_A_PWMConfig ServoConfig0 =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
		TIMER_A_CLOCKSOURCE_DIVIDER_24,//12M / 24 = 500K :: 1000 = 0.002s 10000 = 0.02s 0.0015s = 750
        10000,//all duty = 20ms
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        750//now duty
};


/* TA1 init */
void Servo_Timer_Init(void)
{
	//配置 TA0 channel_1
	GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P7, GPIO_PIN7,
            GPIO_PRIMARY_MODULE_FUNCTION);
	Timer_A_generatePWM(TIMER_A1_BASE, &ServoConfig0);
	TurnAngleSet(0);//舵机归零
}


//TA1 CH1 控制角度
void Servo1_Angle(uint16 x)
{
	uint32 ta0ch1val = 0;
	//0.0015s = 750
	//0.0005s = 250
	//0.0025s = 1250	
	//0.0005s ~ 0.0025s 250 ~ 1250
	ta0ch1val = x * 1000 / 180 + 250; 
	x > 180 ? (x = 180):(x);
	Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,(uint16)ta0ch1val);
}


/* 转向控制 */
#define TURN_ADD_VAL  -30  //中点补偿数值
uint8 TurnAngleSet(int16 x)
{
	x += TURN_ADD_VAL;
	if(x < -250 || x > 250)
		return 0;
	//0.0015s = 750
	//0.0005s = 250
	//0.0025s = 1250	
	//0.0005s ~ 0.0025s 250 ~ 1250
	Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,x + 250 + 250);
	
	return 1;
}


/* 转向测试 */
void Turn_Test(void)
{
	int16 angle0 = 0;
	while(1)
	{
		if(Key_Scan() == KEY_LEFT_PRESS)
		{
			angle0 += 10;
			if(angle0 >= 250) angle0 = 250;
			delay_ms(100);
		}
		if(Key_Scan() == KEY_RIGHT_PRESS)
		{
			angle0 -= 10;
			if(angle0 <= -250) angle0 = -250;
			delay_ms(100);
		}	
		TurnAngleSet(angle0);
		oled_p6x8str(0,0,"turn:");
		oled_int16(64,0,(int16)angle0);
		delay_ms(100);
	}
}



