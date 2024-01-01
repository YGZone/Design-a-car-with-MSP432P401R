
//LED 

#include "led.h"

//!��ɫLED��Ϊ����ָʾ ������������Ϊ��ɫ��led pwm����ɫ�� ���Ƽ�ʹ�ò�ɫ��led


//led pin init
void LED_Init(void)
{
	GPIO_setAsOutputPin(LED_PORT,LED_PIN);
	LED_OFF;
}

//rgbled init
void RGBLED_Init(void)
{
	GPIO_setAsOutputPin(RGB_LED_PORT,RGBLED_R_PIN);
	GPIO_setAsOutputPin(RGB_LED_PORT,RGBLED_G_PIN);
	GPIO_setAsOutputPin(RGB_LED_PORT,RGBLED_B_PIN);
	RGBLED_R_OFF;
	RGBLED_G_OFF;
	RGBLED_B_OFF;
}


//rgbled show special color
void RGBLED(unsigned short color)
{
	switch (color)
	{
		case(RGBLED_RED):
		{
			RGBLED_R_ON;
			RGBLED_G_OFF;
			RGBLED_B_OFF;
			break;
		}
		case(RGBLED_GREEN):
		{
			RGBLED_R_OFF;
			RGBLED_G_ON;
			RGBLED_B_OFF;
			break;
		}
		case(RGBLED_BLUE):
		{
			RGBLED_R_OFF;
			RGBLED_G_OFF;
			RGBLED_B_ON;
			break;
		}
		case(RGBLED_OFF):
		{
			RGBLED_R_OFF;
			RGBLED_G_OFF;
			RGBLED_B_OFF;
			break;
		}
	}
}



/* ��ɫLED���Գ��� */
void rgbled_test(void)
{
	short i = 1;
	while(1)
	{
		i ++;
		if(i == 5) i = 1;
		RGBLED(i);
		delay_ms(300);
	}
}



