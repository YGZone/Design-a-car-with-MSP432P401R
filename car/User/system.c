#include "system.h"



/* ��ʼ��ϵͳ��ʱ��Timer32 */
void Sys_Timer_Init(void)
{	
	//����timer32
	Timer32_initModule(TIMER32_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,
		TIMER32_PERIODIC_MODE);
	//�����ж�
	Interrupt_enableInterrupt(INT_T32_INT1);
	//������ʱ��
	Timer32_setCount(TIMER32_BASE,480000);//10ms�ж�
    Timer32_enableInterrupt(TIMER32_BASE);
    Timer32_startTimer(TIMER32_BASE, true);
}


/* �ٶȿ��� */
void Speed_Control(void)
{
	/* ��ȡ�ٶ� */
	Read_Encoder();
	/* �����ٶȿ��� */
	pwm_r = SimpleIncremental_PID(&SpeedPIDRight,speed_r,encoder1_val);
	/* �����ٶȿ��� */
	pwm_l = SimpleIncremental_PID(&SpeedPIDLeft,speed_l,encoder0_val);
	/* �ٶ�д�� */
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

