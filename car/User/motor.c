#include "motor.h"

//speed
int16 pwm_l = 0,pwm_r = 0;
int16 speed_l = 0,speed_r = 0;

/* 使用定时器0作为电机的PWM输出	定时器 */


/* Timer_A PWM Configuration Parameter */
Timer_A_PWMConfig motorConfig1 =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
		TIMER_A_CLOCKSOURCE_DIVIDER_4,//12M / 24 = 500K :: 1000 = 0.002s 10000 = 0.02s 0.0015s = 750
        10000,//all duty = 20ms
        TIMER_A_CAPTURECOMPARE_REGISTER_2,
        TIMER_A_OUTPUTMODE_RESET_SET,
        0//now duty
};

Timer_A_PWMConfig motorConfig2 =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
		TIMER_A_CLOCKSOURCE_DIVIDER_4,//12M / 24 = 500K :: 1000 = 0.002s 10000 = 0.02s 0.0015s = 750
        10000,//all duty = 20ms
        TIMER_A_CAPTURECOMPARE_REGISTER_3,
        TIMER_A_OUTPUTMODE_RESET_SET,
        0//now duty
};


/* TA0 init */
void Motor_Timer_Init(void)
{
	//配置 TA0 channel_2 3 速度控制
	GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5,
            GPIO_PRIMARY_MODULE_FUNCTION);
	GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN6,
            GPIO_PRIMARY_MODULE_FUNCTION);
	Timer_A_generatePWM(TIMER_A0_BASE, &motorConfig1);
	Timer_A_generatePWM(TIMER_A0_BASE, &motorConfig2);
	//配置方向
	GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN7);
	GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN0);
}


/* 电机速度测试 */
void MotorPWM_Test(void)
{
	int16 angle0 = 0;
	while(1)
	{
		if(Key_Scan() == KEY_LEFT_PRESS)
		{
			angle0 += 100;
			if(angle0 >= 10000) angle0 = 10000;
			delay_ms(20);
			SpeedSet(angle0,angle0);
		}
		if(Key_Scan() == KEY_RIGHT_PRESS)
		{
			angle0 -= 100;
			if(angle0 <= -10000) angle0 = -10000;
			delay_ms(20);
			SpeedSet(angle0,angle0);
		}	
		oled_p6x8str(0,0,"motorpwm:");
		oled_int16(64,0,(int16)angle0);
		oled_int16(0,3,encoder0_val);
		oled_int16(0,4,encoder1_val);
		delay_ms(10);
	}
}

/* 设置电机速度 */
/* LM , RM 范围 ： +—10000 */
uint8 SpeedSet(int16 LM,int16 RM)
{
	if(!(LM >= -10000 && LM <= 10000 && RM >= -10000 && RM <= 10000))
		return 0;
	//设置速度
	Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2,(RM >= 0 ? RM:-RM));
	Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,(LM >= 0 ? LM:-LM));
	//设置方向
	LM>=0 ?  GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN7) : GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN7);
	RM>=0 ?  GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN0) : GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN0);
	
	return 1;
}









