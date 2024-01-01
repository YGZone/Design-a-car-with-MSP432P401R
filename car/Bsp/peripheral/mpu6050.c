/*
 * mpu6050驱动库 使用模拟IIC通信 
 */

#include "mpu6050.h"

int16 mpu_gyro_x,mpu_gyro_y,mpu_gyro_z;
int16 mpu_acc_x,mpu_acc_y,mpu_acc_z;

//-------------------------------------------------------------------------------------------------------------------
// @brief		MPU6050自检函数
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void mpu6050_self1_check(void)
{
	simiic_write_reg(MPU6050_DEV_ADDR, PWR_MGMT_1, 0x00);	//解除休眠状态
	simiic_write_reg(MPU6050_DEV_ADDR, SMPLRT_DIV, 0x07);   //125HZ采样率
	while(0x07 != simiic_read_reg(MPU6050_DEV_ADDR, SMPLRT_DIV,SIMIIC))
	{
		//卡在这里原因有以下几点
		//1 MPU6050坏了，如果是新的这样的概率极低
		//2 接线错误或者没有接好
		//3 可能你需要外接上拉电阻，上拉到3.3V
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		初始化MPU6050
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void mpu6050_init(void)
{
	simiic_init();
	delay_ms(100);													// 上电延时

	mpu6050_self1_check();
	simiic_write_reg(MPU6050_DEV_ADDR, PWR_MGMT_1, 0x00);					// 解除休眠状态
	simiic_write_reg(MPU6050_DEV_ADDR, SMPLRT_DIV, 0x07);					// 125HZ采样率
	simiic_write_reg(MPU6050_DEV_ADDR, MPU6050_CONFIG, 0x04);				// 
	simiic_write_reg(MPU6050_DEV_ADDR, GYRO_CONFIG, 0x18);					// 2000
	simiic_write_reg(MPU6050_DEV_ADDR, ACCEL_CONFIG, 0x10);					// 8g
	simiic_write_reg(MPU6050_DEV_ADDR, User_Control, 0x00);
	simiic_write_reg(MPU6050_DEV_ADDR, INT_PIN_CFG, 0x02);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		获取MPU6050加速度计数据
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_accdata(void)
{
	uint8 dat[6];

	simiic_read_regs(MPU6050_DEV_ADDR, ACCEL_XOUT_H, dat, 6, SIMIIC);  
	mpu_acc_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
	mpu_acc_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
	mpu_acc_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		获取MPU6050陀螺仪数据
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_gyro(void)
{
	uint8 dat[6];

	simiic_read_regs(MPU6050_DEV_ADDR, GYRO_XOUT_H, dat, 6, SIMIIC);  
	mpu_gyro_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
	mpu_gyro_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
	mpu_gyro_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}


//show
void oled_show_mpu6050(void)
{
	get_accdata();
	get_gyro();
	oled_printf_int32(64,1,mpu_gyro_x,5);
	oled_printf_int32(64,2,mpu_gyro_y,5);
	oled_printf_int32(64,3,mpu_gyro_z,5);
	oled_printf_int32(64,5,mpu_acc_x,5);
	oled_printf_int32(64,6,mpu_acc_y,5);
	oled_printf_int32(64,7,mpu_acc_z,5);
	oled_p6x8str(0,0,"gyro:");
	oled_p6x8str(0,1,"x:");
	oled_p6x8str(0,2,"y:");
	oled_p6x8str(0,3,"z:");
	oled_p6x8str(0,4,"acc:");
	oled_p6x8str(0,5,"x:");
	oled_p6x8str(0,6,"y:");
	oled_p6x8str(0,7,"z:");
	delay_ms(50);
}

