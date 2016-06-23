/*
 * AD7176.c
 *
 *  Created on: 2016��6��7��
 *      Author: LawlietGao
 */

#include "AD7176.h"

extern Uint8 WordLen24Byte;			//24λ���ݳ���
extern Uint8 OperationMode;			//����ģʽ
extern Uint8 CommByte;
extern Uint8 ContReadIndicator;		//������
extern Uint8 CrcByte;				//CRCУ��λ
extern Uint8 DataStatusByte;		//����״̬λ
extern Uint8 Ch0En, Ch1En, Ch2En, Ch3En;		//ͨ��0��ͨ��1��ͨ��2��ͨ��3
extern Uint64 ADC_DATA;				//ADC����
extern Uint8 CRCCalculationMode;	//CRCУ���㷨
extern Uint16 sample;				//����
extern Uint8 CrcCheckBytes;
extern Uint16 temp[2];
extern int revSeq;

//Reset AD7176-2
void SoftwareReset()
{
	Uint8 NoOfBytes = 0x8;
	Uint8 Bytes = 0x00;

	for(Bytes=0;Bytes<NoOfBytes;Bytes++)
	{
		SpiaRegs.SPITXBUF=((unsigned char)(0xff)<<8);
	}
}

void ReadData(Uint8 CommData, Uint8 NoOfBytes)
{
	Uint8 Bytes = 0x00;
	SpiaRegs.SPITXBUF = ((unsigned char)(CommData)<<8);
//	while(SpiaRegs.SPIFFTX.bit.TXFFST!=0);

	for(Bytes=0;Bytes<NoOfBytes;Bytes++)
	{
		SpiaRegs.SPITXBUF = ((unsigned char)(0x00)<<8);
//		while(SpiaRegs.SPIFFTX.bit.TXFFST!=0);
 	}
	//return ReturnData;		//ʵ����Ӧ��û���õ� ���ص�������DSP���жϽ��д����
}

void ReadStatus()
{
	Uint8 CommData = 0x40;		//��ȡAD7176-2״̬�Ĵ���
	ReadData(CommData,1);
}

void ReadRegisterADCMode()		//��ȡAD7176-2 ADCģʽ�Ĵ���
{
	Uint8 CommData = 0x41;
	ReadData(CommData,2);
}

void ReadRegisterIFMode()		//��ȡAD7176-2 �ӿ�ģʽ�Ĵ���
{
	Uint8 CommData = 0x42;
	ReadData(CommData,2);
}

void ReadRegisterRegChk()		//��ȡAD7176-2 REGCHECK�Ĵ���
{
	Uint8 CommData = 0x43;
	ReadData(CommData,3);
}

void ReadRegisterData()			//��ȡAD7176-2���ݼĴ���
{
	Uint8 CommData = 0x44;
	Uint8 ByteCount = 2;
	ByteCount = ByteCount + WordLen24Byte;
	ReadData(CommData,ByteCount);
}

void ReadGPIOConfigREG()		//��ȡGPIO���üĴ���
{
	Uint8 CommData = 0x46;
	ReadData(CommData,2);
}

void ReadRegisterID()			//��ȡAD7176-2��ID��
{
	Uint8 CommData = 0x47;
	ReadData(CommData,2);
}

void ReadRegisterCHMAP0()		//��ȡͨ��0�Ĵ���
{
	Uint8 CommData = 0x50;
	ReadData(CommData,2);
}

void ReadRegisterCHMAP1()		//��ȡͨ��1�Ĵ���
{
	Uint8 CommData = 0x51;
	ReadData(CommData,2);
}

void ReadRegisterCHMAP2()		//��ȡͨ��2�Ĵ���
{
	Uint8 CommData = 0x52;
	ReadData(CommData,2);
}

void ReadRegisterCHMAP3()		//��ȡͨ��3�Ĵ���
{
	Uint8 CommData = 0x53;
	ReadData(CommData,2);
}

void ReadSetupConREG0()			//��ȡͨ��0���üĴ���
{
	Uint8 CommData = 0x60;
	ReadData(CommData,2);
}

void ReadSetupConREG1()			//��ȡͨ��1���üĴ���
{
	Uint8 CommData = 0x61;
	ReadData(CommData,2);
}

void ReadSetupConREG2()			//��ȡͨ��2���üĴ���
{
	Uint8 CommData = 0x62;
	ReadData(CommData,2);
}

void ReadSetupConREG3()			//��ȡͨ��3���üĴ���
{
	Uint8 CommData = 0x63;
	ReadData(CommData,2);
}

void ReadRegisterFilterCon0()	//��ȡ�˲���0���üĴ���
{
	Uint8 CommData = 0x68;
	ReadData(CommData,2);
}

void ReadRegisterFilterCon1()	//��ȡ�˲���1���üĴ���
{
	Uint8 CommData = 0x69;
	ReadData(CommData,2);
}

void ReadRegisterFilterCon2()	//��ȡ�˲���2���üĴ���
{
	Uint8 CommData = 0x6A;
	ReadData(CommData,2);
}

void ReadRegisterFilterCon3()	//��ȡ�˲���3���üĴ���
{
	Uint8 CommData = 0x6B;
	ReadData(CommData,2);
}

void ReadRegisterOffset0()		//��ȡʧ��0�Ĵ���
{
	Uint8 CommData = 0x70;
	ReadData(CommData,3);
}

void ReadRegisterOffset1()		//��ȡʧ��1�Ĵ���
{
	Uint8 CommData = 0x71;
	ReadData(CommData,3);
}

void ReadRegisterOffset2()		//��ȡʧ��2�Ĵ���
{
	Uint8 CommData = 0x72;
	ReadData(CommData,3);
}

void ReadRegisterOffset3()		//��ȡʧ��3�Ĵ���
{
	Uint8 CommData = 0x73;
	ReadData(CommData,3);
}

void ReadRegisterGain0()		//��ȡ����0�Ĵ���
{
	Uint8 CommData = 0x78;
	ReadData(CommData,3);
}

void ReadRegisterGain1()		//��ȡ����1�Ĵ���
{
	Uint8 CommData = 0x79;
	ReadData(CommData,3);
}

void ReadRegisterGain2()		//��ȡ����2�Ĵ���
{
	Uint8 CommData = 0x7A;
	ReadData(CommData,3);
}

void ReadRegisterGain3()		//��ȡ����3�Ĵ���
{
	Uint8 CommData = 0x7B;
	ReadData(CommData,3);
}

//Register Data Write
void WriteRegisterData(Uint8 CommData, Uint32 WriteData, Uint8 NoOfBytes)		//д�Ĵ���
{
	Uint8 Bytes = 0x00;

	SpiaRegs.SPITXBUF = ((unsigned char)(CommData)<<8);
	while(SpiaRegs.SPIFFTX.bit.TXFFST!=0);

	for(Bytes=0;Bytes<NoOfBytes;Bytes++)
	{
		temp[Bytes]=(WriteData<<8*Bytes) & 0xff00;
		SpiaRegs.SPITXBUF = ((unsigned char)((WriteData<<8*Bytes) & 0xff00));
		while(SpiaRegs.SPIFFTX.bit.TXFFST!=0);
	}
}

void ADCModeConfig(Uint16 RefEn, Uint16 SingCycEN, Uint16 Delay, Uint16 OpMode, Uint16 ClockSel)	//ADCģʽ�Ĵ�������
{
	Uint16 WriteDataValue = 0x0000;
	WriteDataValue = RefEn + SingCycEN + Delay + OpMode + ClockSel;
	OperationMode = OpMode;
	WriteRegisterData(REG_ADCMODE,WriteDataValue,2);
}

void INTModeConfig(Uint16 AltSyscEn, Uint16 IostrengthEn, Uint16 DoutReset, Uint16 ContReadEn, Uint16 DataStat, Uint16 RegCheckEn, Uint16 CrcEn, Uint16 WordLen)			//�ӿ�ģʽ�Ĵ�������
{
	Uint16 WriteDataValue = 0x0000;
	WriteDataValue = AltSyscEn + IostrengthEn + DoutReset + ContReadEn + DataStat + RegCheckEn + CrcEn + WordLen;
	if(ContReadEn == CONTREAD_EN)
	{
		CommByte = 0x00;							//Decrease the number of Bytes in Interrupt read routine
		ContReadIndicator = 0x01;					//Selects Operation mode to Continuous Read Mode
	}
	if(DataStat == DATA_STAT_EN)
	{
		DataStatusByte = 0x01;						//����״̬λ
	}
	if((CrcEn == CRC_EN_XOR)|(CrcEn == CRC_EN))
	{
		CrcByte = 0x01;								//����CRCλ
	}
	if(WordLen == WL16)
	{
		WordLen24Byte = 0x00;						//��ʾ���ݳ���Ϊ16������24
	}
	WriteRegisterData(REG_IFMODE,WriteDataValue,2);
}

void GPIOConfig(Uint16 MuxIO, Uint16 SyncEn, Uint16 Err_En, Uint16 ErrDat, Uint16 IpEn1, Uint16 IpEn0,
		Uint16 OpEn1, Uint16 OpEn0, Uint16 GpData1, Uint16 GpData0)			//GPIO����
{
	Uint16 WriteDataValue = 0x0000;
	WriteDataValue = MuxIO + SyncEn + Err_En + ErrDat + IpEn1 + IpEn0 + OpEn1 + OpEn0 + GpData1 + GpData0;
	WriteRegisterData(REG_GPIOCON,WriteDataValue,2);
}

void ChannelConfig(Uint8 RegChanSel, Uint16 ChanEn, Uint16 SetupSelNumber, Uint16 AinPos, Uint16 AinNeg)	//ͨ������
{
	Uint16 WriteDataValue = 0x0000;
	WriteDataValue = ChanEn + SetupSelNumber + AinPos + AinNeg;
	WriteRegisterData(RegChanSel,WriteDataValue,2);

	//��¼��һ��ͨ����ʹ��
	if(RegChanSel == 0x10)
	{
		if(ChanEn == 0x8000)
			Ch0En = 0x01;
		else
			Ch0En = 0x00;
	}

	if(RegChanSel == 0x11)
	{
		if(ChanEn == 0x8000)
			Ch1En = 0x01;
		else
			Ch1En = 0x00;
	}

	if(RegChanSel == 0x12)
	{
		if(ChanEn == 0x8000)
			Ch2En = 0x01;
		else
			Ch2En = 0x00;
	}

	if(RegChanSel == 0x13)
	{
		if(ChanEn == 0x8000)
			Ch3En = 0x01;
		else
			Ch3En = 0x00;
	}
}

void SetUpConfig(Uint8 RegSetupConfigNumber, Uint16 BiUniPolar, Uint16 RefSel)		//�������üĴ���
{
	Uint16 WriteDataValue = 0x0000;
	WriteDataValue = BiUniPolar + RefSel;
	WriteRegisterData(RegSetupConfigNumber,WriteDataValue,2);
}

void FilterConfig(Uint8 RefFilConfigNumber, Uint16 Sinc3Map, Uint16 EnFiltEn, Uint16 EnFilSel,
		Uint16 Order, Uint16 outputdatarate)		//����������
{
	Uint16 WriteDataValue = 0x00;
	WriteDataValue = Sinc3Map + EnFiltEn + EnFilSel + Order + outputdatarate;
	WriteRegisterData(RefFilConfigNumber,WriteDataValue,2);
}

void OffsetConfig(Uint8 RegOffsetSel, Uint32 OffsetVal)		//ʧ������
{
	WriteRegisterData(RegOffsetSel,OffsetVal,3);
}

void GainConfig(Uint8 RegGainSel, Uint32 GainVal)		//��������
{
	WriteRegisterData(RegGainSel,GainVal,3);
}

Uint8 CrcPolynomial(Uint64 Data, Uint8 Command, Uint8 NoOfBytes)		//CRC����ʽУ��
{
	Uint8 checksum = 0x00;

	Uint64 remainder;
	Uint64 polynomial = 0x107;
	Uint64 polynomialShift;
	Uint64 AD7176Data;
	Uint64 dummyData = 0x8000000000000000;

	Uint8 bit = 63;

	AD7176Data = Command;
	AD7176Data <<= 8*NoOfBytes;
	AD7176Data |= Data;

	remainder = (AD7176Data & 0xffffffffffffff00);
	while(remainder>0xff)
	{
		while((remainder & dummyData) == 0)
		{
			bit = bit-1;
			dummyData = dummyData>>1;
		}
		polynomialShift = polynomial << (bit-8);
		remainder ^= polynomialShift;
	}
	checksum = remainder;

	return checksum;
}

Uint8 CrcXor(Uint64 Data, Uint8 Command, Uint8 NoOfBytes)			//CRC���У��
{
	Uint8 XorResult = 0x00;
	Uint8 Bytes = 0x00;
	Uint8 SampleData = 0x00;
	XorResult = Command;
	for(Bytes = NoOfBytes; Bytes > 1; Bytes--)
	{
		SampleData = (Uint8)(Data>>(8*(Bytes-1)));
		XorResult = XorResult^SampleData;
	}
	return XorResult;
}

//void ReadValues(void)			//��ȡ����
//{
//	Uint8 ByteCount = 2;
//	Uint32 DATA = 0x00;
//	Uint8 Stat = 0xff;
//	Uint8 CRC = 0x44;
//	Uint8 CalcCRC = 0x00;
//
//	ByteCount = ByteCount + WordLen24Byte + DataStatusByte + CrcByte;
//
//	DATA = (Uint32)(ADC_DATA>>8*(DataStatusByte + CrcByte));
//	if(DataStatusByte == 0x01)
//		Stat = (Uint8)(ADC_DATA>>8*(CrcByte));
//	if(CrcByte == 0x01)
//		CRC = (Uint8)(ADC_DATA);
//	if(CRCCalculationMode == CRC_EN_XOR)
//		CalcCRC = CrcXor(ADC_DATA,0x44,ByteCount);
//	else if(CRCCalculationMode == CRC_EN)
//		CalcCRC = CrcPolynomial(ADC_DATA,0x44,ByteCount);
//	else if(CRCCalculationMode == CRC_EN_DIS)
//		CalcCRC = 0x00;
//
//	//��ʾ���
//}

interrupt void cs_falling_edge_isr(void)
{
	PieCtrlRegs.PIEACK.all &= 0xfff0;

	Uint8 Bytes;
	Uint8 NoOfBytes = 0x02;

	ADC_DATA = 0x0000;
	NoOfBytes = NoOfBytes + WordLen24Byte + DataStatusByte + CrcByte;
	CrcCheckBytes = NoOfBytes;
	if((OperationMode == MODE_CONT_CONV) && (ContReadIndicator == 0x00))
	{
		if(ContReadIndicator == 0x00)
		{
			SpiaRegs.SPITXBUF=((unsigned char)(0x44)<<8);
			//�ȴ��������
			while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
		}
		for(Bytes=0;Bytes<NoOfBytes;Bytes++)
		{
			SpiaRegs.SPITXBUF=((unsigned char)(0x00)<<8);
			//�ȴ��������
			while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
			ADC_DATA = ADC_DATA << 8;
			ADC_DATA = ADC_DATA | SpiaRegs.SPIRXBUF;
		}
		sample++;
	}

	if((OperationMode == MODE_CONT_CONV) && (ContReadIndicator == 0x01))
	{
		for(Bytes=0;Bytes<NoOfBytes;Bytes++)
		{
			SpiaRegs.SPITXBUF=((unsigned char)(0x00)<<8);
			//�ȴ��������
			while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
			ADC_DATA = ADC_DATA << 8;
			ADC_DATA = ADC_DATA | SpiaRegs.SPIRXBUF;
		}
		sample++;
	}

	if(OperationMode == MODE_SING_CONV)
	{
		SpiaRegs.SPITXBUF=((unsigned char)(0x44)<<8);
		//�ȴ��������
		while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
		DELAY_US(10000);
		for(Bytes=0;Bytes<NoOfBytes;Bytes++)
		{
			SpiaRegs.SPITXBUF=((unsigned char)(0x00)<<8);
			//�ȴ��������
			while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
			ADC_DATA = ADC_DATA << 8;
			ADC_DATA = ADC_DATA | SpiaRegs.SPIRXBUF;
		}
		sample++;
	}

	GpioDataRegs.GPATOGGLE.bit.GPIO8=1;
	GpioDataRegs.GPATOGGLE.bit.GPIO9=1;
	GpioDataRegs.GPATOGGLE.bit.GPIO10=1;
	GpioDataRegs.GPATOGGLE.bit.GPIO11=1;

	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;
}

void ContConvMode(void)			//����ת��ģʽ
{
	//ʹ���ж�
//	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;

	while(1)
	{
		revSeq=0;
		DELAY_US(200);
		ReadData(0x44,4);
		DELAY_US(200000);
	}
}

void ContReadMode(void)				//������ȡģʽ
{
	Uint8 Bytes;
	Uint8 NoOfBytes = 4;
	SpiaRegs.SPITXBUF=((unsigned char)(0x02)<<8);
	//�ȴ��������
//	while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
	SpiaRegs.SPITXBUF=((unsigned char)(0x00)<<8);
	//�ȴ��������
//	while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
	SpiaRegs.SPITXBUF=((unsigned char)(0xC0)<<8);
	//�ȴ��������
//	while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);

	//ʹ���ж�
//	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;

	while(1)
	{
		DELAY_US(20);
		revSeq=0;
		for(Bytes=0;Bytes<NoOfBytes;Bytes++)
		{
			SpiaRegs.SPITXBUF=((unsigned char)(0x00)<<8);
			//�ȴ��������
//			while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
		}
	}
}

void SingleConvMode(void)		//����ת��ģʽ
{

//	PieCtrlRegs.PIEACK.all &= 0xfff0;
	SpiaRegs.SPITXBUF=((unsigned char)(0x01)<<8);
	//�ȴ��������
//	while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
	SpiaRegs.SPITXBUF=((unsigned char)(0x00)<<8);
//	while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
	SpiaRegs.SPITXBUF=((unsigned char)(0x10)<<8);
	//�ȴ��������
//	while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);

	revSeq=0;
	//ʹ���ж�
//	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;
	DELAY_US(20000);
	ReadData(0x44,4);
//	ReadStatus();

}




