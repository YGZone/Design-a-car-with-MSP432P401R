#ifndef _LED_H_
#define _LED_H_


#include "headfile.h"

#define LED_PORT    GPIO_PORT_P1
#define LED_PIN		GPIO_PIN0
#define LED_ON		GPIO_setOutputHighOnPin(LED_PORT,LED_PIN)
#define LED_OFF  	GPIO_setOutputLowOnPin(LED_PORT,LED_PIN)
#define LED_TOGGLE  GPIO_toggleOutputOnPin(LED_PORT,LED_PIN)

#define RGB_LED_PORT    GPIO_PORT_P2
#define RGBLED_R_PIN	GPIO_PIN0
#define RGBLED_G_PIN	GPIO_PIN1
#define RGBLED_B_PIN	GPIO_PIN2
#define RGBLED_R_ON		GPIO_setOutputHighOnPin(RGB_LED_PORT,RGBLED_R_PIN)
#define RGBLED_R_OFF  	GPIO_setOutputLowOnPin(RGB_LED_PORT,RGBLED_R_PIN)
#define RGBLED_G_ON		GPIO_setOutputHighOnPin(RGB_LED_PORT,RGBLED_G_PIN)
#define RGBLED_G_OFF  	GPIO_setOutputLowOnPin(RGB_LED_PORT,RGBLED_G_PIN)
#define RGBLED_B_ON		GPIO_setOutputHighOnPin(RGB_LED_PORT,RGBLED_B_PIN)
#define RGBLED_B_OFF  	GPIO_setOutputLowOnPin(RGB_LED_PORT,RGBLED_B_PIN)

#define RGBLED_RED			1
#define RGBLED_GREEN        2
#define RGBLED_BLUE			3
#define RGBLED_OFF			4


//function
void LED_Init(void);
void RGBLED_Init(void);
void RGBLED(unsigned short color);
void rgbled_test(void);


#endif

