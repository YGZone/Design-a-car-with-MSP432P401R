#include "system.h"



/* 初始化系统定时器Timer32 */
void Sys_Timer_Init(void)
{	
	//配置timer32
	Timer32_initModule(TIMER32_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,
		TIMER32_PERIODIC_MODE);
	//开启中断
	Interrupt_enableInterrupt(INT_T32_INT1);
	//开启定时器
	Timer32_setCount(TIMER32_BASE,480000);//10ms中断
    Timer32_enableInterrupt(TIMER32_BASE);
    Timer32_startTimer(TIMER32_BASE, true);
}


/* 速度控制 */
void Speed_Control(void)
{
	/* 读取速度 */
	Read_Encoder();
	/* 右轮速度控制 */
	pwm_r = SimpleIncremental_PID(&SpeedPIDRight,speed_r,encoder1_val);
	/* 左轮速度控制 */
	pwm_l = SimpleIncremental_PID(&SpeedPIDLeft,speed_l,encoder0_val);
	/* 速度写入 */
	SpeedSet(pwm_l,pwm_r);
}


void Car_Control(void)
{
	if(PS2.l_up == 1)
	{
		speed_r = 30;
		speed_l = 30;
	}
	else if(PS2.l_down == 1)
	{
		speed_r = -30;
		speed_l = -30;
	}
	else
	{
		speed_r = 0;
		speed_l = 0;
	}
	if(PS2.l_left == 1)
		TurnAngleSet(-150);
	else if(PS2.l_right == 1)
		TurnAngleSet(150);
	else
		TurnAngleSet(0);
}

