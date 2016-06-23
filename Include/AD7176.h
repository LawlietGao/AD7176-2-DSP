/*
 * AD7176.h
 *
 *  Created on: 2016��6��7��
 *      Author: LawlietGao
 */

#ifndef AD7176_H_
#define AD7176_H_
#include "DSP28x_Project.h"

/*Operation Mode*/
#define CONCONVMODE		0x00
#define CONREADMODE 	0x01
#define SINGCONVMODE 	0x02
#define STDBYMODE		0x03
#define CALMODE			0x04

/*Command*/
#define WRITE_EN		0x00
#define WRITE			0x00
#define READ			0x40

/*Communication Register*/
#define REG_STATUS		0x00
#define REG_ADCMODE		0x01
#define REG_IFMODE		0x02
#define REG_REGCHECK	0x03
#define REG_DATA		0x04
#define REG_GPIOCON		0x06
#define REG_ID			0x07

#define REG_CHMAP0		0x10
#define REG_CHMAP1		0x11
#define REG_CHMAP2		0x12
#define REG_CHMAP3		0x13

#define REG_SETUPCON0	0x20
#define REG_SETUPCON1	0x21
#define REG_SETUPCON2	0x22
#define REG_SETUPCON3	0x23

#define REG_FILTCON0	0x28
#define REG_FILTCON1	0x29
#define REG_FILTCON2	0x2A
#define REG_FILTCON3	0x2B

#define REG_OFFSET0		0x30
#define REG_OFFSET1		0x31
#define REG_OFFSET2		0x32
#define REG_OFFSET3		0x33

#define REG_GAIN0		0x38
#define REG_GAIN1		0x39
#define REG_GAIN2		0x3A
#define REG_GAIN3		0x3B

/*ADC Mode Register*/
#define REF_EN			0x8000		//ʹ���ڲ���׼��ѹԴ
#define	REF_DIS			0x0000

#define SING_CYC_EN		0x2000		//������ͨ����Чʱ������ʹ�ô�λ������ADC���Խ������˲��������������
#define SING_CYC_DIS	0x0000

#define DELAY_0us		0x0000
#define DELAY_4us		0x0100
#define DELAY_16us		0x0200
#define DELAY_40us		0x0300
#define DELAY_100us		0x0400
#define DELAY_200us		0x0500
#define DELAY_500us		0x0600
#define DELAY_1ms		0x0700

#define MODE_CONT_CONV		0x0000	//����ת��ģʽ
#define MODE_SING_CONV		0x0010	//����ת��ģʽ
#define MODE_STANDBY		0x0020	//����ģʽ
#define MODE_PD_DWN			0x0030	//����ģʽ
#define MODE_INT_OFFSET_CAL	0x0040	//�ڲ�ʧ��У׼
#define MODE_SYS_OFFSET_CAL	0x0060	//ϵͳʧ��У׼
#define MODE_SYS_GAIN_CAL	0x0070	//ϵͳ����У׼

#define CLOCKSEL_INTOS		0x0000	//�ڲ�����
#define CLOCKSEL_INTOSO		0x0004	//XTAL2�����ϵ��ڲ��������
#define	CLOCKSEL_EXTCLK		0x0008	//XTAL2�����ϵ��ⲿʱ������
#define CLOCKSEL_EXTOS		0x000C	//XTAL1��XTAL2�����ϵ��ⲿ����

/*Interface Mode Register*/
#define ALT_SYNC_EN		0x1000		//��λʹ��ERROR/SYNC���ŵĲ�ͬ��Ϊ���Ա�����ERROR/SYNC������ѭ��ͨ����ת��
#define ALT_SYNC_DIS	0x0000

#define IOSTRENGTH_EN	0x0800		//��λ����DOUT���ŵ�����ǿ��
#define IOSTRENGTH_DIS	0x0000

#define DOUT_RESET_EN	0x0100		//��λ��ֹDOUT/RDY�����ڶ��������һ��SCLK������֮�����������DOUT�л������RDY
#define DOUT_RESET_DIS	0x0000

#define CONTREAD_EN		0x0080		//ʹ��������ȡADC���ݼĴ���
#define CONTREAD_DIS	0x0000

#define DATA_STAT_EN	0x0040		//��ȡʱ���ݼĴ�������״̬�Ĵ�����ʹ��ͨ����״̬��Ϣ������һͬ����
#define DATA_STAT_DIS	0x0000

#define REG_CHECK_EN	0x0020		//��λʹ�ܼĴ��������Լ�飬���ô˼��ɼ����û��Ĵ���ֵ���κα仯
#define REG_CHECK_DIS	0x0000

#define CRC_EN_DIS		0x0000		//����CRC
#define CRC_EN_XOR		0x0004		//Cʹ�ܼĴ����������XORУ���
#define CRC_EN			0x0008		//CRCʹ��

#define WL16			0x0001		//16λ����
#define WL24			0x0000		//24λ����

/*GPIO Configuration Register*/
#define MUX_IO_EN		0x1000
#define MUX_IO_DIS		0x0000

#define SYNC_EN			0x0800		//��λ��ʹSYNC/ERROR��������ͬ������
#define SYNC_DIS		0x0000

#define ERR_DIS			0x0000		//��ֹ
#define ERR_IN			0x0200		//SYNC/ERROR�Ǵ�������
#define ERR_OD_EO		0x0400		//SYNC/ERROR�ǿ�©�������
#define ERR_GPIO		0x0600		//SYNC/ERROR��ͨ�����

#define ERR_DAT_EN		0x0100		//ERROR��������ͨ�����ʱ����λ�������߼���ƽ����������ʱ������ӳ�����ŵĻض�״̬��
#define ERR_DAT_DIS		0x0000

#define IP_EN1			0x0020		//��λ��GPIO1��Ϊ����
#define IP_EN1_DIS		0x0000

#define IP_EN0			0x0010		//��λ��GPIO0��Ϊ����
#define IP_EN0_DIS		0x0000

#define OP_EN1			0x0008		//��λ��GPIO1��Ϊ���
#define OP_EN1_DIS		0x0000

#define OP_EN0			0x0004		//��λ��GPIO0��Ϊ���
#define OP_EN0_DIS		0x0000

#define GP_DATA1_EN		0x0002		//��λ��GPIO1�Ļض���д������
#define GP_DATA1_DIS	0x0000

#define GP_DATA0_EN		0x0001		//��λ��GPIO0�Ļض���д������
#define GP_DATA0_DIS	0x0000

/*Channel Map Register 0*/
#define CH_EN0			0x8000
#define CH_EN0_DIS		0x0000

#define SETUP_SEL0		0x0000
#define SETUP_SEL1		0x1000
#define SETUP_SEL2		0x2000
#define SETUO_SEL3		0x3000

#define AINPOS0_AIN0	0x0000
#define AINPOS0_AIN1	0x0020
#define AINPOS0_AIN2	0x0040
#define AINPOS0_AIN3	0x0060
#define AINPOS0_AIN4	0x0080
#define AINPOS0_REF_P	0x02A0
#define AINPOS0_REF_N	0x02C0

#define AINNEG0_AIN0	0x0000
#define AINNEG0_AIN1	0x0001
#define AINNEG0_AIN2	0x0002
#define AINNEG0_AIN3	0x0003
#define AINNEG0_AIN4	0x0004
#define AINNEG0_REF_P	0x0015
#define AINNEG0_REF_N	0x0016

/*Setup Configuration Register 0*/
#define BI_UNIPOLAR0_EN		0x1000
#define BI_UNIPOLAR0_DIS	0x0000

#define REF_SEL0_EXT		0x0000
#define REF_SEL0_INT		0x0020
#define REF_SEL0_DIAG		0x0030

/*Filter Configuration Register 0*/
#define SINC3MAP0_DIS 0x0000
#define SINC3MAP0_EN  0x8000

#define ENHFILT0_DIS 0x0000
#define ENHFILT0_EN  0x0800

#define ENFILT0_NO         0x0000
#define ENFILT0_27SPS    0x0200
#define ENFILT0_25SPS       0x0300
#define ENFILT0_20SPS       0x0500
#define ENFILT0_16_67SPS    0x0600

#define ORDER0_SINC5_SINC1  0x0000
#define ORDER0_SINC3        0x0060

#define ODR0_250000SPS      0x0000
#define ODR0_125000SPS      0x0001
#define ODR0_62500SPS       0x0002
#define ODR0_50000SPS       0x0003
#define ODR0_31250PS        0x0004
#define ODR0_25000SPS       0x0005
#define ODR0_15625SPS       0x0006
#define ODR0_10000SPS       0x0007
#define ODR0_5000SPS       	0x0008
#define ODR0_2500SPS       	0x0009
#define ODR0_1000SPS       	0x000A
#define ODR0_500SPS       	0x000B
#define ODR0_397_5SPS       0x000C
#define ODR0_200SPS       	0x000D
#define ODR0_100SPS         0x000E
#define ODR0_59_94SPS       0x000F
#define ODR0_49_96SPS       0x0010
#define ODR0_20SPS         	0x0011
#define ODR0_16_667SPS      0x0012
#define ODR0_10SPS         	0x0013
#define ODR0_5SPS         	0x0014

void SoftwareReset();
void ReadData(Uint8 CommData, Uint8 NoOfBytes);
void ReadStatus();
void ReadRegisterADCMode();
void ReadRegisterIFMode();
void ReadRegisterRegChk();
void ReadRegisterData();
void ReadGPIOConfigREG();
void ReadRegisterID();
void ReadRegisterCHMAP0();
void ReadRegisterCHMAP1();
void ReadRegisterCHMAP2();
void ReadRegisterCHMAP3();
void ReadSetupConREG0();
void ReadSetupConREG1();
void ReadSetupConREG2();
void ReadSetupConREG3();
void ReadRegisterFilterCon0();
void ReadRegisterFilterCon1();
void ReadRegisterFilterCon2();
void ReadRegisterFilterCon3();
void ReadRegisterOffset0();
void ReadRegisterOffset1();
void ReadRegisterOffset2();
void ReadRegisterOffset3();
void ReadRegisterGain0();
void ReadRegisterGain1();
void ReadRegisterGain2();
void ReadRegisterGain3();
void WriteRegisterData(Uint8 CommData, Uint32 WriteData, Uint8 NoOfBytes);
void ADCModeConfig(Uint16 RefEn, Uint16 SingCycEN, Uint16 Delay, Uint16 OpMode, Uint16 ClockSel);
void INTModeConfig(Uint16 AltSyscEn, Uint16 IostrengthEn, Uint16 DoutReset, Uint16 ContReadEn, Uint16 DataStat, Uint16 RegCheckEn, Uint16 CrcEn, Uint16 WordLen);
void GPIOConfig(Uint16 MuxIO, Uint16 SyncEn, Uint16 Err_En, Uint16 ErrDat, Uint16 IpEn1, Uint16 IpEn0, Uint16 OpEn1, Uint16 OpEn0, Uint16 GpData1, Uint16 GpData0);
void ChannelConfig(Uint8 RegChanSel, Uint16 ChanEn, Uint16 SetupSelNumber, Uint16 AinPos, Uint16 AinNeg);
void SetUpConfig(Uint8 RegSetupConfigNumber, Uint16 BiUniPolar, Uint16 RefSel);
void FilterConfig(Uint8 RefFilConfigNumber, Uint16 Sinc3Map, Uint16 EnFiltEn, Uint16 EnFilSel, Uint16 Order, Uint16 outputdatarate);
void OffsetConfig(Uint8 RegOffsetSel, Uint32 OffsetVal);
void GainConfig(Uint8 RegGainSel, Uint32 GainVal);
Uint8 CrcPolynomial(Uint64 Data, Uint8 Command, Uint8 NoOfBytes);
Uint8 CrcXor(Uint64 Data, Uint8 Command, Uint8 NoOfBytes);
void ReadValues(void);
void ContConvMode(void);
void ContReadMode(void);
void SingleConvMode(void);
interrupt void cs_falling_edge_isr(void);

#endif /* AD7176_H_ */
