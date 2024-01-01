
//������ icm20602������

#include "icm20602.h"


int16 icm_gyro_x,icm_gyro_y,icm_gyro_z;
int16 icm_acc_x,icm_acc_y,icm_acc_z;

//-------------------------------------------------------------------------------------------------------------------
// ���º�����ʹ��Ӳ��SPIͨ�� ��Ƚ�IIC �ٶȱ�IIC��ǳ���
//-------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------
// @brief		SPI���ͽ��պ���
// @param		spi_n			ѡ��SPIģ�� (SPI_1-SPI_2)
// @param		modata			���͵����ݻ�������ַ
// @param		midata			��������ʱ���յ������ݵĴ洢��ַ(����Ҫ������ NULL)
// @param		len				���͵��ֽ���
// @param		continuous		����ͨ����CS�Ƿ����������Ч״̬ 1:�������� 0:ÿ������һ���ֽڹر�CS(һ������Ϊ1 ����)
// @return		void				
// @since		v2.0
// Sample usage:				spi_mosi(SPI_1,buf,buf,1);										//����buff�����ݣ������յ�buf�����Ϊ1�ֽ� ͨ���ڼ�CS��������
//-------------------------------------------------------------------------------------------------------------------
void spi_mosi (uint8 *modata, uint8 *midata, uint32 len)
{
	//����Ϊ��
	while(SPI_isBusy(ICM20602_EUSI));
	while(len--)
	{
		SPI_transmitData(ICM20602_EUSI, *modata++);
		while(SPI_isBusy(ICM20602_EUSI));
		if(midata != NULL)																		// ������Ч
		{
			*midata++ = SPI_receiveData(ICM20602_EUSI);												// ��ȡ����
		}
	}
}



//-------------------------------------------------------------------------------------------------------------------
// @brief		ICM20602 SPIд�Ĵ���
// @param		cmd				�Ĵ�����ַ
// @param		val				��Ҫд�������
// @return		void
// @since		v1.0
// Sample usage:
// @note		�ڲ����� �û��������
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
// @brief		ICM20602 SPI���Ĵ���
// @param		cmd				�Ĵ�����ַ
// @param		*val			�������ݵĵ�ַ
// @return		void
// @since		v1.0
// Sample usage:
// @note		�ڲ����� �û��������
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
// @brief		ICM20602 SPI���ֽڶ��Ĵ���
// @param		cmd				�Ĵ�����ַ
// @param		*val			�������ݵĵ�ַ
// @param		num				��ȡ����
// @return		void
// @since		v1.0
// Sample usage:
// @note		�ڲ����� �û��������
//-------------------------------------------------------------------------------------------------------------------
static void icm_spi_r_reg_bytes(uint8 * val, uint8 num)
{
	ICM20602_CS(0);
	spi_mosi(val, val, num);
	ICM20602_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		ICM20602�Լ캯��
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:
// @note		�ڲ����� �û��������
//-------------------------------------------------------------------------------------------------------------------
static void icm20602_self3_check(void)
{
	uint8 dat = 0;

	while(0x12 != dat)																// �ж� ID �Ƿ���ȷ
	{
		icm_spi_r_reg_byte(ICM20602_WHO_AM_I, &dat);								// ��ȡICM20602 ID
		systick_delay_ms(10);
		//��������ԭ�������¼���
		//1 ICM20602���ˣ�������µ������ĸ��ʼ���
		//2 ���ߴ������û�нӺ�
		//3 ��������Ҫ����������裬������3.3V
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
// @brief		��ʼ��ICM20602
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void icm20602_init_spi(void)
{
	uint8 val = 0x0;

	systick_delay_ms(10);  //�ϵ���ʱ

	//CSƬѡ��ʼ��
	GPIO_setAsOutputPin(ICM20602_CS_PORT,ICM20602_CS_PIN);
	//gpio
	 GPIO_setAsPeripheralModuleFunctionInputPin(ICM20602_GPIO_PORT,
		ICM20602_SCK_PIN | ICM20602_MOSI_PIN | ICM20602_MISO_PIN, GPIO_PRIMARY_MODULE_FUNCTION);
	//SPI��ʼ��
	SPI_initMaster(ICM20602_EUSI, &spiMasterConfig);
	/* Enable SPI module */
    SPI_enableModule(ICM20602_EUSI);
	
	icm20602_self3_check();//���

	icm_spi_w_reg_byte(ICM20602_PWR_MGMT_1,0x80);//��λ�豸
	systick_delay_ms(2);
	do																				// �ȴ���λ�ɹ�
	{
		icm_spi_r_reg_byte(ICM20602_PWR_MGMT_1,&val);
	}while(0x41 != val);

	icm_spi_w_reg_byte(ICM20602_PWR_MGMT_1,		0x01);								// ʱ������
	icm_spi_w_reg_byte(ICM20602_PWR_MGMT_2,		0x00);								// ���������Ǻͼ��ٶȼ�
	icm_spi_w_reg_byte(ICM20602_CONFIG,			0x01);								// 176HZ 1KHZ
	icm_spi_w_reg_byte(ICM20602_SMPLRT_DIV,		0x07);								// �������� SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
	icm_spi_w_reg_byte(ICM20602_GYRO_CONFIG,	0x18);								// ��2000 dps
	icm_spi_w_reg_byte(ICM20602_ACCEL_CONFIG,	0x10);								// ��8g
	icm_spi_w_reg_byte(ICM20602_ACCEL_CONFIG_2,	0x03);								// Average 4 samples   44.8HZ   //0x23 Average 16 samples
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		��ȡICM20602���ٶȼ�����
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
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
// @brief		��ȡICM20602����������
// @param		NULL
// @return		void
// @since		v1.0
// Sample usage:				ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
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
// ���Ϻ�����ʹ��Ӳ��SPIͨ�� ��Ƚ�IIC �ٶȱ�IIC��ǳ���
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
