/*
 * mpu6050������ ʹ��ģ��IICͨ�� 
 */

#include "mpu6050.h"

int16 mpu_gyro_x,mpu_gyro_y,mpu_gyro_z;
int16 mpu_acc_x,mpu_acc_y,mpu_acc_z;

//-------------------------------------------------------------------------------------------------------------------
// @brief		MPU6050�Լ캯��
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				���øú���ǰ�����ȵ���ģ��IIC�ĳ�ʼ��
//-------------------------------------------------------------------------------------------------------------------
void mpu6050_self1_check(void)
{
	simiic_write_reg(MPU6050_DEV_ADDR, PWR_MGMT_1, 0x00);	//�������״̬
	simiic_write_reg(MPU6050_DEV_ADDR, SMPLRT_DIV, 0x07);   //125HZ������
	while(0x07 != simiic_read_reg(MPU6050_DEV_ADDR, SMPLRT_DIV,SIMIIC))
	{
		//��������ԭ�������¼���
		//1 MPU6050���ˣ�������µ������ĸ��ʼ���
		//2 ���ߴ������û�нӺ�
		//3 ��������Ҫ����������裬������3.3V
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		��ʼ��MPU6050
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				���øú���ǰ�����ȵ���ģ��IIC�ĳ�ʼ��
//-------------------------------------------------------------------------------------------------------------------
void mpu6050_init(void)
{
	simiic_init();
	delay_ms(100);													// �ϵ���ʱ

	mpu6050_self1_check();
	simiic_write_reg(MPU6050_DEV_ADDR, PWR_MGMT_1, 0x00);					// �������״̬
	simiic_write_reg(MPU6050_DEV_ADDR, SMPLRT_DIV, 0x07);					// 125HZ������
	simiic_write_reg(MPU6050_DEV_ADDR, MPU6050_CONFIG, 0x04);				// 
	simiic_write_reg(MPU6050_DEV_ADDR, GYRO_CONFIG, 0x18);					// 2000
	simiic_write_reg(MPU6050_DEV_ADDR, ACCEL_CONFIG, 0x10);					// 8g
	simiic_write_reg(MPU6050_DEV_ADDR, User_Control, 0x00);
	simiic_write_reg(MPU6050_DEV_ADDR, INT_PIN_CFG, 0x02);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		��ȡMPU6050���ٶȼ�����
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
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
// @brief		��ȡMPU6050����������
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
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

