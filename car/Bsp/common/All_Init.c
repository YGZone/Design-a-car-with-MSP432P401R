
//������ʼ��

#include "All_Init.h"



//���е�������ʼ��
void System_Init(void)
{
	//��������ʱ��
	Clock_ReConfig();
	
	//�������躯��
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
	//�û�����
	
}















