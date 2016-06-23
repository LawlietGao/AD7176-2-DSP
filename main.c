/*
 * main.c
 */
#include "DSP28x_Project.h"
#include "AD7176.h"
//////////////////////////////////////////////////////
Uint16 rdata[3];     // Receive data buffer
Uint16 revData[24] = {0};
int revSeq=0;
Uint16 temp[2]={0};

#define	  LED1	GpioDataRegs.GPADAT.bit.GPIO8
#define	  LED2	GpioDataRegs.GPADAT.bit.GPIO9
#define	  LED3	GpioDataRegs.GPADAT.bit.GPIO10
#define	  LED4	GpioDataRegs.GPADAT.bit.GPIO11
//////////////////////////////////////////////////////

Uint16 sample = 0;
Uint8 DataStatusByte = 0x00;
Uint8 CrcByte = 0x00;
Uint8 WordLen24Byte = 0x01;
Uint8 CrcCheckBytes = 0x00;
Uint8 OperationMode = 0x00;
Uint8 ContReadIndicator = 0x00;
Uint8 CommByte = 0x01;
Uint8 CRCCalculationMode = 0x00;

Uint8 Ch0En = 0x00, Ch1En = 0x00, Ch2En = 0x00, Ch3En = 0x00;
Uint8 ByteCount = 2;
void RegisterWrite(void);
void ContConv(void);
void ContRead(void);
void SingleCont(void);
void GPIO_XINT_init(void);
interrupt void spi_TxFifo_Isr(void);
interrupt void spi_RxFifo_Isr(void);
void spi_fifo_init();

Uint64 ADC_DATA = 0x0000;
int main(void)
{
	// Step 1. Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	// This example function is found in the F2806x_SysCtrl.c file.
	InitSysCtrl();

	// Step 2. Initalize GPIO:
	// This example function is found in the F2806x_Gpio.c file and
	// illustrates how to set the GPIO to it's default state.
	// InitGpio();  // Skipped for this example
	// Setup only the GP I/O only for SPI-A functionality

	// Step 3. Initialize PIE vector table:
	// Disable and clear all CPU interrupts
	DINT;
	IER = 0x0000;
	IFR = 0x0000;

	// Initialize PIE control registers to their default state:
	// This function is found in the F2806x_PieCtrl.c file.
	InitPieCtrl();

	// Initialize the PIE vector table with pointers to the shell Interrupt
	// Service Routines (ISR).
	// This will populate the entire table, even if the interrupt
	// is not used in this example.  This is useful for debug purposes.
	// The shell ISR routines are found in F2806x_DefaultIsr.c.
	// This function is found in F2806x_PieVect.c.
	InitPieVectTable();
	InitSpiaGpio();
	GPIO_XINT_init();
	// Interrupts that are used in this example are re-mapped to
	// ISR functions found within this file.
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.SPIRXINTA = &spi_RxFifo_Isr;
//	PieVectTable.XINT1 = &cs_falling_edge_isr;
	//PieVectTable.SPITXINTA = &spi_TxFifo_Isr;
	EDIS;   // This is needed to disable write to EALLOW protected registers

	// Step 4. Initialize all the Device Peripherals:
	// This function is found in F2806x_InitPeripherals.c
	// InitPeripherals(); // Not required for this example
	spi_fifo_init();   // Initialize the SPI only

	// Step 5. User specific code, enable interrupts:

	// Enable interrupts required for this example
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
	PieCtrlRegs.PIEIER6.bit.INTx1=1;     // Enable PIE Group 6, INT 1
	//PieCtrlRegs.PIEIER6.bit.INTx2=1;     // Enable PIE Group 6, INT 2
	PieCtrlRegs.PIEIER1.bit.INTx4 = 1;		//Enable PIE Group 1, INT 4
	IER=0x20;                            // Enable CPU INT6
//	IER|=M_INT1;
	EINT;                                // Enable Global Interrupts

//	PieCtrlRegs.PIEACK.all &= 0xfff0;

    LED1=1;
    DELAY_US(10);
    LED2=1;
    DELAY_US(10);
    LED3=1;
    DELAY_US(10);
    LED4=1;
    DELAY_US(10);

//    SoftwareReset();
    SingleCont();
//    ContRead();
//    ContConv();
	// Step 6. IDLE loop. Just sit and loop forever (optional):
//	while(1)
//	{
//	}
}

// Some Useful local functions
void delay_loop()
{
    long      i;
    for (i = 0; i < 1000000; i++) {}
}

void error(void)
{
    asm("     ESTOP0");  //Test failed!! Stop!
    for (;;);
}

void spi_fifo_init()
{
// Initialize SPI FIFO registers
    SpiaRegs.SPICCR.bit.SPISWRESET=0; // Reset SPI

    SpiaRegs.SPICCR.all=0x0047;
    //�������½��ط��������ؽ��������ݳ���Ϊ8
    SpiaRegs.SPICTL.all=0x0017;
    //ʹ�ܽ�������жϣ�����ʱ��ʱ�ӿ��Ʒ�����SPI����Ϊ��������ģʽ��ʹ�ܷ����жϣ�ʹ�ܽ����ж�
    SpiaRegs.SPISTS.all=0x0000;
    //��ʼ��SPISTS�Ĵ���
    SpiaRegs.SPIBRR=0x0042;
    //������
    SpiaRegs.SPIFFTX.all=0xC021;
    //SPI FIFO�����¿�ʼ�����뷢�ͣ�ʹ��SPI FIFO���ܣ�д0����������FIFOָ�븴λ��0���������ڸ�λ״̬��
    //��������FIFOΪ�գ�û�з���TXFIFO�жϣ�д0�޷�Ӧ����ֹTXFIFO��TXFFIVLƥ���жϣ�����TXFIFO���ж����
    SpiaRegs.SPIFFRX.all=0x0021;
    //û�з���RXFIFO�жϣ�д0�޷�Ӧ��ʹ��RXFIFO��RXFFIVLƥ���жϣ�
    //����RXFIFO���ж����
    SpiaRegs.SPIFFCT.all=0x00;
    //���÷��ͻ�����װ�����ݵ�ʱ����
    SpiaRegs.SPIPRI.all=0x0010;
    //free-runģʽ
    SpiaRegs.SPICCR.bit.SPISWRESET=1;  // Enable SPI

    SpiaRegs.SPIFFTX.bit.TXFIFO=1;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET=1;
}

void RegisterRead (void)	//��ȡ�Ĵ�������
{
	ReadStatus();
	ReadRegisterADCMode();
	ReadRegisterIFMode();
	ReadRegisterRegChk();
	ReadRegisterData();
	ReadGPIOConfigREG();
	ReadRegisterID();
	ReadRegisterCHMAP0();
	ReadRegisterCHMAP1();
	ReadRegisterCHMAP2();
	ReadRegisterCHMAP3();
	ReadSetupConREG0();
	ReadSetupConREG1();
	ReadSetupConREG2();
	ReadSetupConREG3();
	ReadRegisterFilterCon0();
	ReadRegisterFilterCon1();
	ReadRegisterFilterCon2();
	ReadRegisterFilterCon3();
	ReadRegisterOffset0();
	ReadRegisterOffset1();
	ReadRegisterOffset2();
	ReadRegisterOffset3();
	ReadRegisterGain0();
	ReadRegisterGain1();
	ReadRegisterGain2();
	ReadRegisterGain3();
}

void RegisterWrite (void) //Ĭ������
{
	ADCModeConfig (REF_EN, SING_CYC_DIS, DELAY_0us, MODE_CONT_CONV, CLOCKSEL_INTOS);
	INTModeConfig (ALT_SYNC_DIS, IOSTRENGTH_DIS, DOUT_RESET_DIS, CONTREAD_DIS, DATA_STAT_DIS, REG_CHECK_DIS, CRC_EN_DIS, WL24);
	GPIOConfig (MUX_IO_DIS, SYNC_EN, ERR_DIS, ERR_DAT_DIS, IP_EN1_DIS, IP_EN0_DIS, OP_EN1_DIS, OP_EN0_DIS, GP_DATA1_DIS, GP_DATA0_DIS);
	ChannelConfig (REG_CHMAP0, CH_EN0, SETUP_SEL0, AINPOS0_AIN0, AINNEG0_AIN1);
	ChannelConfig (REG_CHMAP1, CH_EN0_DIS, SETUP_SEL0, AINPOS0_AIN0, AINNEG0_AIN1);
	ChannelConfig (REG_CHMAP2, CH_EN0_DIS, SETUP_SEL0, AINPOS0_AIN0, AINNEG0_AIN1);
	ChannelConfig (REG_CHMAP3, CH_EN0_DIS, SETUP_SEL0, AINPOS0_AIN0, AINNEG0_AIN1);
	SetUpConfig (REG_SETUPCON0, BI_UNIPOLAR0_EN, REF_SEL0_INT);
	SetUpConfig (REG_SETUPCON1, BI_UNIPOLAR0_EN, REF_SEL0_INT);
	SetUpConfig (REG_SETUPCON2, BI_UNIPOLAR0_EN, REF_SEL0_INT);
	SetUpConfig (REG_SETUPCON3, BI_UNIPOLAR0_EN, REF_SEL0_INT);
	FilterConfig (REG_FILTCON0, SINC3MAP0_DIS, ENHFILT0_DIS, ENFILT0_NO, ORDER0_SINC5_SINC1, ODR0_250000SPS);
	FilterConfig (REG_FILTCON1, SINC3MAP0_DIS, ENHFILT0_DIS, ENFILT0_NO, ORDER0_SINC5_SINC1, ODR0_250000SPS);
	FilterConfig (REG_FILTCON2, SINC3MAP0_DIS, ENHFILT0_DIS, ENFILT0_NO, ORDER0_SINC5_SINC1, ODR0_250000SPS);
	FilterConfig (REG_FILTCON3, SINC3MAP0_DIS, ENHFILT0_DIS, ENFILT0_NO, ORDER0_SINC5_SINC1, ODR0_250000SPS);
	OffsetConfig (REG_OFFSET0, 0x800000);
	OffsetConfig (REG_OFFSET1, 0x800000);
	OffsetConfig (REG_OFFSET2, 0x800000);
	OffsetConfig (REG_OFFSET3, 0x800000);
	GainConfig (REG_GAIN0, 0x5554A0);
	GainConfig (REG_GAIN1, 0x5554A0);
	GainConfig (REG_GAIN2, 0x5554A0);
	GainConfig (REG_GAIN3, 0x5554A0);
}

void ContConv(void)		//����ת��ģʽ����
{
	ADCModeConfig (REF_EN, SING_CYC_DIS, DELAY_0us, MODE_CONT_CONV, CLOCKSEL_INTOS);
	INTModeConfig (ALT_SYNC_DIS, IOSTRENGTH_DIS, DOUT_RESET_DIS, CONTREAD_DIS, DATA_STAT_EN, REG_CHECK_DIS, CRC_EN_DIS, WL24);

	FilterConfig (REG_FILTCON0, SINC3MAP0_DIS, ENHFILT0_DIS, ENFILT0_NO, ORDER0_SINC5_SINC1, ODR0_5SPS);

	SetUpConfig (REG_SETUPCON0, BI_UNIPOLAR0_DIS, REF_SEL0_EXT);

	ChannelConfig (REG_CHMAP0, CH_EN0, SETUP_SEL0, AINPOS0_AIN1, AINNEG0_REF_N);
	ChannelConfig (REG_CHMAP1, CH_EN0_DIS, SETUP_SEL0, AINPOS0_AIN1, AINNEG0_AIN0);
	ChannelConfig (REG_CHMAP2, CH_EN0_DIS, SETUP_SEL0, AINPOS0_AIN2, AINNEG0_AIN3);
	ChannelConfig (REG_CHMAP3, CH_EN0_DIS, SETUP_SEL0, AINPOS0_AIN3, AINNEG0_AIN2);


	ByteCount = ByteCount + WordLen24Byte + DataStatusByte + CrcByte;
	ContConvMode();
}

void ContRead(void)		//������ģʽ����
{
	Uint8 Bytes = 0;
	Uint8 NoOfBytes = 4;
	ADCModeConfig (REF_EN, SING_CYC_DIS, DELAY_0us, MODE_CONT_CONV, CLOCKSEL_INTOS);


	FilterConfig (REG_FILTCON0, SINC3MAP0_DIS, ENHFILT0_DIS, ENFILT0_NO, ORDER0_SINC5_SINC1, ODR0_5SPS);
//	FilterConfig (REG_FILTCON1, SINC3MAP0_DIS, ENHFILT0_DIS, ENFILT0_NO, ORDER0_SINC5_SINC1, ODR0_5SPS);
//	FilterConfig (REG_FILTCON2, SINC3MAP0_DIS, ENHFILT0_DIS, ENFILT0_NO, ORDER0_SINC5_SINC1, ODR0_5SPS);
//	FilterConfig (REG_FILTCON3, SINC3MAP0_DIS, ENHFILT0_DIS, ENFILT0_NO, ORDER0_SINC5_SINC1, ODR0_5SPS);

	SetUpConfig (REG_SETUPCON0, BI_UNIPOLAR0_DIS, REF_SEL0_EXT);
//	SetUpConfig (REG_SETUPCON1, BI_UNIPOLAR0_DIS, REF_SEL0_EXT);


	ChannelConfig (REG_CHMAP0, CH_EN0, SETUP_SEL0, AINPOS0_AIN1, AINNEG0_REF_N);
	ChannelConfig (REG_CHMAP1, CH_EN0_DIS, SETUP_SEL0, AINPOS0_AIN1, AINNEG0_AIN0);
	ChannelConfig (REG_CHMAP2, CH_EN0_DIS, SETUP_SEL0, AINPOS0_AIN2, AINNEG0_AIN3);
	ChannelConfig (REG_CHMAP3, CH_EN0_DIS, SETUP_SEL0, AINPOS0_AIN3, AINNEG0_AIN2);


	ByteCount = ByteCount + WordLen24Byte + DataStatusByte + CrcByte;
	INTModeConfig (ALT_SYNC_DIS, IOSTRENGTH_DIS, DOUT_RESET_DIS, CONTREAD_EN, DATA_STAT_EN, REG_CHECK_DIS, CRC_EN_DIS, WL24);

//	ContReadMode();
	while(1)
	{
		DELAY_US(20000);
		revSeq=0;
		for(Bytes=0;Bytes<NoOfBytes;Bytes++)
		{
			SpiaRegs.SPITXBUF=((unsigned char)(0x00)<<8);
		}
//		DELAY_US(20);
	}
}

void SingleCont(void)		//����ת��ģʽ����
{

	ADCModeConfig (REF_EN, SING_CYC_DIS, DELAY_0us, MODE_SING_CONV, CLOCKSEL_INTOS);
	INTModeConfig (ALT_SYNC_DIS, IOSTRENGTH_DIS, DOUT_RESET_DIS, CONTREAD_DIS, DATA_STAT_EN, REG_CHECK_DIS, CRC_EN_DIS, WL24);
//	FilterConfig (REG_FILTCON0, SINC3MAP0_DIS, ENHFILT0_DIS, ENFILT0_NO, ORDER0_SINC5_SINC1, ODR0_5SPS);
	SetUpConfig (REG_SETUPCON0, BI_UNIPOLAR0_DIS, REF_SEL0_EXT);

	ChannelConfig (REG_CHMAP0, CH_EN0, SETUP_SEL0, AINPOS0_AIN1, AINNEG0_REF_N);
	ChannelConfig (REG_CHMAP1, CH_EN0_DIS, SETUP_SEL0, AINPOS0_AIN1, AINNEG0_AIN0);
	ChannelConfig (REG_CHMAP2, CH_EN0_DIS, SETUP_SEL0, AINPOS0_AIN2, AINNEG0_AIN3);
	ChannelConfig (REG_CHMAP3, CH_EN0_DIS, SETUP_SEL0, AINPOS0_AIN3, AINNEG0_AIN2);

	ByteCount = ByteCount + WordLen24Byte + DataStatusByte + CrcByte;

	while (1)
	{
		SingleConvMode();
	}
}

void GPIO_XINT_init(void)
{
	EALLOW;
	//LED�Ƴ�ʼ��
	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0; // GPIO8 = GPIO8
	GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0; // GPIO9 = GPIO9
	GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0; // GPIO10 = GPIO10
	GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0; // GPIO11 = GPIO11
	GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;

	//GPIO14�½����ж�
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;			//����GPIO����
	GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;				//����GPIO����Ϊ����
	GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 0;			//��ʱ��SYSCLKOUTͬ��
	GpioCtrlRegs.GPAPUD.bit.GPIO14 = 1;
	GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 14;		//�ⲿ�ж�XINT3
	XIntruptRegs.XINT1CR.bit.POLARITY = 0;			//�½��ش���
	XIntruptRegs.XINT1CR.bit.ENABLE = 1;			//ʹ���ж�
	EDIS;
}

interrupt void spi_RxFifo_Isr(void)		//���������ж�
{
    Uint16 i=0;
//    for(i=0; i<3; i++)
//    {
        rdata[i]=SpiaRegs.SPIRXBUF;     // Read data
        revData[revSeq]=rdata[i];
        revSeq++;
//    }

    if(revSeq>24)
    {
        revSeq=0;
    }
    SpiaRegs.SPIFFRX.bit.RXFFOVFCLR=1;  // Clear Overflow flag
    SpiaRegs.SPIFFRX.bit.RXFFINTCLR=1;  // Clear Interrupt flag
    PieCtrlRegs.PIEACK.all|=0x20;       // Issue PIE ack
}
