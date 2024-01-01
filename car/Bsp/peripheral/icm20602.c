
//陀螺仪 icm20602陀螺仪

#include "icm20602.h"


int16 icm_gyro_x,icm_gyro_y,icm_gyro_z;
int16 icm_acc_x,icm_acc_y,icm_acc_z;

//-------------------------------------------------------------------------------------------------------------------
// 以下函数是使用硬件SPI通信 相比较IIC 速度比IIC快非常多
//-------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------
// @brief		SPI发送接收函数
// @param		spi_n			选择SPI模块 (SPI_1-SPI_2)
// @param		modata			发送的数据缓冲区地址
// @param		midata			发送数据时接收到的数据的存储地址(不需要接收则传 NULL)
// @param		len				发送的字节数
// @param		continuous		本次通信是CS是否持续保持有效状态 1:持续保持 0:每传输完一个字节关闭CS(一般设置为1 即可)
// @return		void				
// @since		v2.0
// Sample usage:				spi_mosi(SPI_1,buf,buf,1);										//发送buff的内容，并接收到buf里，长度为1字节 通信期间CS持续拉低
//-------------------------------------------------------------------------------------------------------------------
void spi_mosi (uint8 *modata, uint8 *midata, uint32 len)
{
	//发送为空
	while(SPI_isBusy(ICM20602_EUSI));
	while(len--)
	{
		SPI_transmitData(ICM20602_EUSI, *modata++);
		while(SPI_isBusy(ICM20602_EUSI));
		if(midata != NULL)																		// 接收有效
		{
			*midata++ = SPI_receiveData(ICM20602_EUSI);												// 读取数据
		}
	}
}



//-------------------------------------------------------------------------------------------------------------------
// @brief		ICM20602 SPI写寄存器
// @param		cmd				寄存器地址
// @param		val				需要写入的数据
// @return		void
// @since		v1.0
// Sample usage:
// @note		内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void icm_spi_w_reg_byte(uint8 cmd, uint8 val)
{
	uint8 dat[2];
	ICM20602_CS(0);
	dat[0] = cmd | ICM20602_SPI_W;
	dat[1] = val;
	
	spi_mosi(dat, dat, 2);
	ICM20602_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		ICM20602 SPI读寄存器
// @param		cmd				寄存器地址
// @param		*val			接收数据的地址
// @return		void
// @since		v1.0
// Sample usage:
// @note		内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void icm_spi_r_reg_byte(uint8 cmd, uint8 *val)
{
	uint8 dat[2];
	ICM20602_CS(0);
	dat[0] = cmd | ICM20602_SPI_R;
	dat[1] = *val;

	spi_mosi(dat, dat, 2);

	*val = dat[1];
	ICM20602_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		ICM20602 SPI多字节读寄存器
// @param		cmd				寄存器地址
// @param		*val			接收数据的地址
// @param		num				读取数量
// @return		void
// @since		v1.0
// Sample usage:
// @note		内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void icm_spi_r_reg_bytes(uint8 * val, uint8 num)
{
	ICM20602_CS(0);
	spi_mosi(val, val, num);
	ICM20602_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		ICM20602自检函数
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:
// @note		内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void icm20602_self3_check(void)
{
	uint8 dat = 0;

	while(0x12 != dat)																// 判断 ID 是否正确
	{
		icm_spi_r_reg_byte(ICM20602_WHO_AM_I, &dat);								// 读取ICM20602 ID
		systick_delay_ms(10);
		//卡在这里原因有以下几点
		//1 ICM20602坏了，如果是新的这样的概率极低
		//2 接线错误或者没有接好
		//3 可能你需要外接上拉电阻，上拉到3.3V
	}
}


//![Simple SPI Config]
/* SPI Master Configuration Parameter */
const eUSCI_SPI_MasterConfig spiMasterConfig =
{
        EUSCI_B_SPI_CLOCKSOURCE_SMCLK,             // SMCLK Clock Source
        12000000,                                  // SMCLK = DCO = 12MHZ
        500000,                                    // SPICLK = 500khz
        EUSCI_B_SPI_MSB_FIRST,                     // MSB First
        EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    // Phase
        EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH, // High polarity
        EUSCI_B_SPI_3PIN                           // 3Wire SPI Mode
};
//-------------------------------------------------------------------------------------------------------------------
// @brief		初始化ICM20602
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void icm20602_init_spi(void)
{
	uint8 val = 0x0;

	systick_delay_ms(10);  //上电延时

	//CS片选初始化
	GPIO_setAsOutputPin(ICM20602_CS_PORT,ICM20602_CS_PIN);
	//gpio
	 GPIO_setAsPeripheralModuleFunctionInputPin(ICM20602_GPIO_PORT,
		ICM20602_SCK_PIN | ICM20602_MOSI_PIN | ICM20602_MISO_PIN, GPIO_PRIMARY_MODULE_FUNCTION);
	//SPI初始化
	SPI_initMaster(ICM20602_EUSI, &spiMasterConfig);
	/* Enable SPI module */
    SPI_enableModule(ICM20602_EUSI);
	
	icm20602_self3_check();//检测

	icm_spi_w_reg_byte(ICM20602_PWR_MGMT_1,0x80);//复位设备
	systick_delay_ms(2);
	do																				// 等待复位成功
	{
		icm_spi_r_reg_byte(ICM20602_PWR_MGMT_1,&val);
	}while(0x41 != val);

	icm_spi_w_reg_byte(ICM20602_PWR_MGMT_1,		0x01);								// 时钟设置
	icm_spi_w_reg_byte(ICM20602_PWR_MGMT_2,		0x00);								// 开启陀螺仪和加速度计
	icm_spi_w_reg_byte(ICM20602_CONFIG,			0x01);								// 176HZ 1KHZ
	icm_spi_w_reg_byte(ICM20602_SMPLRT_DIV,		0x07);								// 采样速率 SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
	icm_spi_w_reg_byte(ICM20602_GYRO_CONFIG,	0x18);								// ±2000 dps
	icm_spi_w_reg_byte(ICM20602_ACCEL_CONFIG,	0x10);								// ±8g
	icm_spi_w_reg_byte(ICM20602_ACCEL_CONFIG_2,	0x03);								// Average 4 samples   44.8HZ   //0x23 Average 16 samples
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		获取ICM20602加速度计数据
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_accdata_spi(void)
{
	struct
	{
		uint8 reg;
		uint8 dat[6];
	}buf;

	buf.reg = ICM20602_ACCEL_XOUT_H | ICM20602_SPI_R;

	icm_spi_r_reg_bytes(&buf.reg, 7);
	icm_acc_x = (int16)(((uint16)buf.dat[0]<<8 | buf.dat[1]));
	icm_acc_y = (int16)(((uint16)buf.dat[2]<<8 | buf.dat[3]));
	icm_acc_z = (int16)(((uint16)buf.dat[4]<<8 | buf.dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		获取ICM20602陀螺仪数据
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_gyro_spi(void)
{
	struct
	{
		uint8 reg;
		uint8 dat[6];
	}buf;

	buf.reg = ICM20602_GYRO_XOUT_H | ICM20602_SPI_R;

	icm_spi_r_reg_bytes(&buf.reg, 7);
	icm_gyro_x = (int16)(((uint16)buf.dat[0]<<8 | buf.dat[1]));
	icm_gyro_y = (int16)(((uint16)buf.dat[2]<<8 | buf.dat[3]));
	icm_gyro_z = (int16)(((uint16)buf.dat[4]<<8 | buf.dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
// 以上函数是使用硬件SPI通信 相比较IIC 速度比IIC快非常多
//-------------------------------------------------------------------------------------------------------------------

void ICM20602_Test(void)
{
	get_icm20602_accdata_spi();
	get_icm20602_gyro_spi();
	oled_printf_int32(64,1,icm_gyro_x,5);
	oled_printf_int32(64,2,icm_gyro_y,5);
	oled_printf_int32(64,3,icm_gyro_z,5);
	oled_printf_int32(64,5,icm_acc_x,5);
	oled_printf_int32(64,6,icm_acc_y,5);
	oled_printf_int32(64,7,icm_acc_z,5);
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
