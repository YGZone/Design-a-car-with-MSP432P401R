#ifndef _HEADFILE_H_
#define _HEADFILE_H_


//数据类型声明
typedef unsigned char		uint8;													//  8 bits 
typedef unsigned short int	uint16;													// 16 bits 
typedef unsigned long int	uint32;													// 32 bits 
typedef unsigned long long	uint64;													// 64 bits 

typedef char				int8;													//  8 bits 
typedef short int			int16;													// 16 bits 
typedef long  int			int32;													// 32 bits 
typedef long  long			int64;													// 64 bits 

typedef volatile int8		vint8;													//  8 bits 
typedef volatile int16		vint16;													// 16 bits 
typedef volatile int32		vint32;													// 32 bits 
typedef volatile int64		vint64;													// 64 bits 

typedef volatile uint8		vuint8;													//  8 bits 
typedef volatile uint16		vuint16;												// 16 bits 
typedef volatile uint32		vuint32;												// 32 bits 
typedef volatile uint64		vuint64;												// 64 bits 



//头文件定义

/* DriverLib Includes */
#include <driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

/* User Lib*/
#include "normal.h"
#include "All_Init.h"
#include "led.h"
#include "key.h"
#include "isr.h"
#include "oled.h"
#include "servo.h"
#include "icm20602.h"
#include "encoder.h"
#include "ANO_DT.h"
#include "my_simiic.h"
#include "mpu6050.h"

#include "system.h"
#include "motor.h"
#include "pid.h"
#include "ps2gamepad.h"


#endif


