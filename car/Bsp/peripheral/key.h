#ifndef _KEY_H_
#define _KEY_H_


#include "headfile.h"

#define KEY_LEFT_PORT		GPIO_PORT_P1
#define KEY_LEFT_PIN 		GPIO_PIN1
#define KEY_LEFT			GPIO_getInputPinValue(KEY_LEFT_PORT,KEY_LEFT_PIN)
#define KEY_LEFT_PRESS		1

#define KEY_RIGHT_PORT 		GPIO_PORT_P1
#define KEY_RIGHT_PIN 		GPIO_PIN4
#define KEY_RIGHT			GPIO_getInputPinValue(KEY_RIGHT_PORT,KEY_RIGHT_PIN)
#define KEY_RIGHT_PRESS		2


//function
void 	Key_Init(void);
void 	Key_Int_Init(void);
uint8 	Key_Scan(void);
void 	Key_Test(void);

#endif

