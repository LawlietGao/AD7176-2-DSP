/*
 * AD7176.c
 *
 *  Created on: 2016年6月7日
 *      Author: LawlietGao
 */

#include "AD7176.h"

extern Uint8 WordLen24Byte;			//24位数据长度
extern Uint8 OperationMode;			//操作模式
extern Uint8 CommByte;
extern Uint8 ContReadIndicator;		//连续读
extern Uint8 CrcByte;				//CRC校验位
extern Uint8 DataStatusByte;		//数据状态位
extern Uint8 Ch0En, Ch1En, Ch2En, Ch3En;		//通道0，通道1，通道2，通道3
extern Uint64 ADC_DATA;				//ADC数据
extern Uint8 CRCCalculationMode;	//CRC校验算法
extern Uint16 sample;				//采样
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
	//return ReturnData;		//实际上应该没有用到 返回的数据由DSP的中断进行处理的
}

void ReadStatus()
{
	Uint8 CommData = 0x40;		//读取AD7176-2状态寄存器
	ReadData(CommData,1);
}

void ReadRegisterADCMode()		//读取AD7176-2 ADC模式寄存器
{
	Uint8 CommData = 0x41;
	ReadData(CommData,2);
}

void ReadRegisterIFMode()		//读取AD7176-2 接口模式寄存器
{
	Uint8 CommData = 0x42;
	ReadData(CommData,2);
}

void ReadRegisterRegChk()		//读取AD7176-2 REGCHECK寄存器
{
	Uint8 CommData = 0x43;
	ReadData(CommData,3);
}

void ReadRegisterData()			//读取AD7176-2数据寄存器
{
	Uint8 CommData = 0x44;
	Uint8 ByteCount = 2;
	ByteCount = ByteCount + WordLen24Byte;
	ReadData(CommData,ByteCount);
}

void ReadGPIOConfigREG()		//读取GPIO配置寄存器
{
	Uint8 CommData = 0x46;
	ReadData(CommData,2);
}

void ReadRegisterID()			//读取AD7176-2的ID号
{
	Uint8 CommData = 0x47;
	ReadData(CommData,2);
}

void ReadRegisterCHMAP0()		//读取通道0寄存器
{
	Uint8 CommData = 0x50;
	ReadData(CommData,2);
}

void ReadRegisterCHMAP1()		//读取通道1寄存器
{
	Uint8 CommData = 0x51;
	ReadData(CommData,2);
}

void ReadRegisterCHMAP2()		//读取通道2寄存器
{
	Uint8 CommData = 0x52;
	ReadData(CommData,2);
}

void ReadRegisterCHMAP3()		//读取通道3寄存器
{
	Uint8 CommData = 0x53;
	ReadData(CommData,2);
}

void ReadSetupConREG0()			//读取通道0配置寄存器
{
	Uint8 CommData = 0x60;
	ReadData(CommData,2);
}

void ReadSetupConREG1()			//读取通道1配置寄存器
{
	Uint8 CommData = 0x61;
	ReadData(CommData,2);
}

void ReadSetupConREG2()			//读取通道2配置寄存器
{
	Uint8 CommData = 0x62;
	ReadData(CommData,2);
}

void ReadSetupConREG3()			//读取通道3配置寄存器
{
	Uint8 CommData = 0x63;
	ReadData(CommData,2);
}

void ReadRegisterFilterCon0()	//读取滤波器0配置寄存器
{
	Uint8 CommData = 0x68;
	ReadData(CommData,2);
}

void ReadRegisterFilterCon1()	//读取滤波器1配置寄存器
{
	Uint8 CommData = 0x69;
	ReadData(CommData,2);
}

void ReadRegisterFilterCon2()	//读取滤波器2配置寄存器
{
	Uint8 CommData = 0x6A;
	ReadData(CommData,2);
}

void ReadRegisterFilterCon3()	//读取滤波器3配置寄存器
{
	Uint8 CommData = 0x6B;
	ReadData(CommData,2);
}

void ReadRegisterOffset0()		//读取失调0寄存器
{
	Uint8 CommData = 0x70;
	ReadData(CommData,3);
}

void ReadRegisterOffset1()		//读取失调1寄存器
{
	Uint8 CommData = 0x71;
	ReadData(CommData,3);
}

void ReadRegisterOffset2()		//读取失调2寄存器
{
	Uint8 CommData = 0x72;
	ReadData(CommData,3);
}

void ReadRegisterOffset3()		//读取失调3寄存器
{
	Uint8 CommData = 0x73;
	ReadData(CommData,3);
}

void ReadRegisterGain0()		//读取增益0寄存器
{
	Uint8 CommData = 0x78;
	ReadData(CommData,3);
}

void ReadRegisterGain1()		//读取增益1寄存器
{
	Uint8 CommData = 0x79;
	ReadData(CommData,3);
}

void ReadRegisterGain2()		//读取增益2寄存器
{
	Uint8 CommData = 0x7A;
	ReadData(CommData,3);
}

void ReadRegisterGain3()		//读取增益3寄存器
{
	Uint8 CommData = 0x7B;
	ReadData(CommData,3);
}

//Register Data Write
void WriteRegisterData(Uint8 CommData, Uint32 WriteData, Uint8 NoOfBytes)		//写寄存器
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

void ADCModeConfig(Uint16 RefEn, Uint16 SingCycEN, Uint16 Delay, Uint16 OpMode, Uint16 ClockSel)	//ADC模式寄存器配置
{
	Uint16 WriteDataValue = 0x0000;
	WriteDataValue = RefEn + SingCycEN + Delay + OpMode + ClockSel;
	OperationMode = OpMode;
	WriteRegisterData(REG_ADCMODE,WriteDataValue,2);
}

void INTModeConfig(Uint16 AltSyscEn, Uint16 IostrengthEn, Uint16 DoutReset, Uint16 ContReadEn, Uint16 DataStat, Uint16 RegCheckEn, Uint16 CrcEn, Uint16 WordLen)			//接口模式寄存器配置
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
		DataStatusByte = 0x01;						//增减状态位
	}
	if((CrcEn == CRC_EN_XOR)|(CrcEn == CRC_EN))
	{
		CrcByte = 0x01;								//增加CRC位
	}
	if(WordLen == WL16)
	{
		WordLen24Byte = 0x00;						//表示数据长度为16而不是24
	}
	WriteRegisterData(REG_IFMODE,WriteDataValue,2);
}

void GPIOConfig(Uint16 MuxIO, Uint16 SyncEn, Uint16 Err_En, Uint16 ErrDat, Uint16 IpEn1, Uint16 IpEn0,
		Uint16 OpEn1, Uint16 OpEn0, Uint16 GpData1, Uint16 GpData0)			//GPIO配置
{
	Uint16 WriteDataValue = 0x0000;
	WriteDataValue = MuxIO + SyncEn + Err_En + ErrDat + IpEn1 + IpEn0 + OpEn1 + OpEn0 + GpData1 + GpData0;
	WriteRegisterData(REG_GPIOCON,WriteDataValue,2);
}

void ChannelConfig(Uint8 RegChanSel, Uint16 ChanEn, Uint16 SetupSelNumber, Uint16 AinPos, Uint16 AinNeg)	//通道配置
{
	Uint16 WriteDataValue = 0x0000;
	WriteDataValue = ChanEn + SetupSelNumber + AinPos + AinNeg;
	WriteRegisterData(RegChanSel,WriteDataValue,2);

	//记录哪一个通道被使能
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

void SetUpConfig(Uint8 RegSetupConfigNumber, Uint16 BiUniPolar, Uint16 RefSel)		//设置配置寄存器
{
	Uint16 WriteDataValue = 0x0000;
	WriteDataValue = BiUniPolar + RefSel;
	WriteRegisterData(RegSetupConfigNumber,WriteDataValue,2);
}

void FilterConfig(Uint8 RefFilConfigNumber, Uint16 Sinc3Map, Uint16 EnFiltEn, Uint16 EnFilSel,
		Uint16 Order, Uint16 outputdatarate)		//过滤器设置
{
	Uint16 WriteDataValue = 0x00;
	WriteDataValue = Sinc3Map + EnFiltEn + EnFilSel + Order + outputdatarate;
	WriteRegisterData(RefFilConfigNumber,WriteDataValue,2);
}

void OffsetConfig(Uint8 RegOffsetSel, Uint32 OffsetVal)		//失调配置
{
	WriteRegisterData(RegOffsetSel,OffsetVal,3);
}

void GainConfig(Uint8 RegGainSel, Uint32 GainVal)		//增益配置
{
	WriteRegisterData(RegGainSel,GainVal,3);
}

Uint8 CrcPolynomial(Uint64 Data, Uint8 Command, Uint8 NoOfBytes)		//CRC多项式校验
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

Uint8 CrcXor(Uint64 Data, Uint8 Command, Uint8 NoOfBytes)			//CRC异或校验
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

//void ReadValues(void)			//读取数据
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
//	//显示结果
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
			//等待发送完成
			while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
		}
		for(Bytes=0;Bytes<NoOfBytes;Bytes++)
		{
			SpiaRegs.SPITXBUF=((unsigned char)(0x00)<<8);
			//等待发送完成
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
			//等待发送完成
			while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
			ADC_DATA = ADC_DATA << 8;
			ADC_DATA = ADC_DATA | SpiaRegs.SPIRXBUF;
		}
		sample++;
	}

	if(OperationMode == MODE_SING_CONV)
	{
		SpiaRegs.SPITXBUF=((unsigned char)(0x44)<<8);
		//等待发送完成
		while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
		DELAY_US(10000);
		for(Bytes=0;Bytes<NoOfBytes;Bytes++)
		{
			SpiaRegs.SPITXBUF=((unsigned char)(0x00)<<8);
			//等待发送完成
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

void ContConvMode(void)			//连续转换模式
{
	//使能中断
//	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;

	while(1)
	{
		revSeq=0;
		DELAY_US(200);
		ReadData(0x44,4);
		DELAY_US(200000);
	}
}

void ContReadMode(void)				//连续读取模式
{
	Uint8 Bytes;
	Uint8 NoOfBytes = 4;
	SpiaRegs.SPITXBUF=((unsigned char)(0x02)<<8);
	//等待发送完成
//	while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
	SpiaRegs.SPITXBUF=((unsigned char)(0x00)<<8);
	//等待发送完成
//	while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
	SpiaRegs.SPITXBUF=((unsigned char)(0xC0)<<8);
	//等待发送完成
//	while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);

	//使能中断
//	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;

	while(1)
	{
		DELAY_US(20);
		revSeq=0;
		for(Bytes=0;Bytes<NoOfBytes;Bytes++)
		{
			SpiaRegs.SPITXBUF=((unsigned char)(0x00)<<8);
			//等待发送完成
//			while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
		}
	}
}

void SingleConvMode(void)		//单次转换模式
{

//	PieCtrlRegs.PIEACK.all &= 0xfff0;
	SpiaRegs.SPITXBUF=((unsigned char)(0x01)<<8);
	//等待发送完成
//	while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
	SpiaRegs.SPITXBUF=((unsigned char)(0x00)<<8);
//	while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);
	SpiaRegs.SPITXBUF=((unsigned char)(0x10)<<8);
	//等待发送完成
//	while((SpiaRegs.SPIFFTX.bit.TXFFST|0x00) != 0x00);

	revSeq=0;
	//使能中断
//	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;
	DELAY_US(20000);
	ReadData(0x44,4);
//	ReadStatus();

}




