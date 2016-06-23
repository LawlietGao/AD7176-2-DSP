// TI File $Revision: /main/2 $
// Checkin $Date: March 1, 2007   16:06:07 $
//###########################################################################
//
// FILE:	DSP2833x_Sci.c
//
// TITLE:	DSP2833x SCI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

/*�ڱ������е��޸�֮��*/
//void InitSci(void)�����������SCIb�ĳ�ʼ����������
//���������void InitScib()������������
/*********************/

//---------------------------------------------------------------------------
// InitSci: 
//---------------------------------------------------------------------------
// This function initializes the SCI(s) to a known state.
//
void InitSci(void)
{
	// Initialize SCI-A:

	//tbd...
 	

	// Initialize SCI-B:
     InitScibGpio();
	 InitScib();
	//tbd...
  
      // Initialize SCI-C:

      //tbd...
}	

//---------------------------------------------------------------------------
// Example: InitSciGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as SCI pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 
// Caution: 
// Only one GPIO pin should be enabled for SCITXDA/B operation.
// Only one GPIO pin shoudl be enabled for SCIRXDA/B operation. 
// Comment out other unwanted lines.

void InitSciGpio()
{
   InitSciaGpio();
#if DSP28_SCIB   
   InitScibGpio();
#endif // if DSP28_SCIB  
#if DSP28_SCIC
   InitScicGpio();
#endif // if DSP28_SCIC
}

void InitSciaGpio()
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.  
// This will enable the pullups for the specified pins.

	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;	   // Enable pull-up for GPIO29 (SCITXDA)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.  
// This will select asynch (no qualification) for the selected pins.

	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)

/* Configure SCI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.

	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 for SCIRXDA operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 for SCITXDA operation
	
    EDIS;
}

#if DSP28_SCIB 
void InitScibGpio()
{
   EALLOW;
	
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.  
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;     // Enable pull-up for GPIO9  (SCITXDB)
//  GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up for GPIO14 (SCITXDB)
	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;	   // Enable pull-up for GPIO18 (SCITXDB)
//  GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;    // Enable pull-up for GPIO22 (SCITXDB)

	
//  GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up for GPIO11 (SCIRXDB)
//  GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;    // Enable pull-up for GPIO15 (SCIRXDB)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;	   // Enable pull-up for GPIO19 (SCIRXDB)
//  GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;    // Enable pull-up for GPIO23 (SCIRXDB)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;  // Asynch input GPIO11 (SCIRXDB)
//  GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (SCIRXDB)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;  // Asynch input GPIO19 (SCIRXDB)
//  GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;  // Asynch input GPIO23 (SCIRXDB)

/* Configure SCI-B pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 2;    // Configure GPIO9 for SCITXDB operation
//  GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 2;   // Configure GPIO14 for SCITXDB operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;   // Configure GPIO18 for SCITXDB operation
//  GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3;   // Configure GPIO22 for SCITXDB operation
	
//  GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 2;   // Configure GPIO11 for SCIRXDB operation
//  GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2;   // Configure GPIO15 for SCIRXDB operation
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;   // Configure GPIO19 for SCIRXDB operation
//  GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3;   // Configure GPIO23 for SCIRXDB operation
	
    EDIS;
}
void InitScib()
{
	/*1bitֹͣλ����У��λ���ڲ���������������ģʽ��8bits�ֳ�*/
    ScibRegs.SCICCR.all=0x07;
	//bit7     STOP BITS          (R/W-0)0:1bitֹͣλ
	//bit6     EVEN/ODD PARITY    (R/W-0)
	//bit5     PARITY ENABLE      (R/W-0)0����У��λ
	//bit4     LOOP BACK ENA      (R/W-0)0���ڲ���ʹ��
	//bit3     ADDR/IDLE MODE     (R/W-0)0��������ģʽ
	//bit2-0   SCI CHAR2-0        (R/W-0)111��8bits�ֳ�

   /*��ֹ���մ����жϡ�ʹ��SCI��������TXWAKE���շ�ʹ��*/
	ScibRegs.SCICTL1.all=0x23;
	//bit7     Reserved           (R-0) 
	//bit6     RX ERR INTENA      (R/W-0)0����ֹ���մ����ж�
	//bit5     SW RESET           (R/W-0)1��ʹ��SCI��д�㽫��ʼ��SCI��״̬���Ͳ�����־λ�����ǲ�
	//                                   Ӱ�����ã�һ����λ���㣬SCI�ı�־λ������ֱ����λ������λ
	//bit4     Reserved           (R-0) 
	//bit3     TXWAKE             (R/S-0)0�������÷��ͻ���λ 
	//bit2     SLEEP              (R/W-0)0����ֹ˯��ģʽ
    //bit1     TXENA              (R/W-0)1������ʹ��
	//bit0     RXENA              (R/W-0)1������ʹ��

    /*����ʱ��37.5MHZ��������Ϊ19200������BRR=0XF3*/
    ScibRegs.SCIHBAUD=0x00;
	//bit15-8  SCIHBAUD
	//bit7-0   Reserved
    ScibRegs.SCILBAUD=0xF3;    
    //bit15-8  Reserved
	//bit7-0   SCILBAUD
    
	/*��ֹ�շ�������ж�*/
	ScibRegs.SCICTL2.all=0xc2;
    //bit7     TXRDY             (R-1)  ��Ϊ1�����ͻ���Ĵ���׼���ñ�־λ
	//bit6     TX EMPTY          (R-1)  ��Ϊ1���������ձ�־λ
	//bit5-2   Reserved          (R-0)
	//bit1     RX/BK INTENA      (R/W-0)0����ֹ������������ж�
	//bit0     TX INT ENA        (R/W-0)0����ֹ������������ж�

	/***************************/
    ScibRegs.SCIFFTX.all=0xE040;
    //bit15    SCIRST            (R/W-1)1������λ
    //bit14    SCIFFENA          (R/W-0)1��FIFO��ǿ����ʹ��
    //bit13    TXFIFO Reset      (R/W-1)1������ʹ��TXFIFO;0����FIFOָ�븴λ��0
	//bit12-8  TXFFST4-0         (R-0)     FIFOδ�������ݵ�����
	//bit7     TXFFINT Flag      (R-0)     TXFIFO�жϱ�־λ
	//bit6     TXFFINT CLR       (W-0)  1:д1���TXFFINT Flag
	//bit5     TXFFIENA          (R/W-0)0:��ֹ����TXFFIVL���ж�
	//bit4-0   TXFFIL4-0         (R/W-0)00000:��TXFFST4-0С�ڵ��ڴ�ֵʱ�����ж�
    ScibRegs.SCIFFRX.all=0x605f;
    //bit15    RXFFOVF           (R-0)     FIFO���״̬λ����Ϊ1���ѽ���16����������ʧȥһ��
    //bit14    RXFFOVF CLR       (W-0)  1��д1���RXFFOVF��־λ
    //bit13    RXFIFO Reset      (R/W-1)1������ʹ��RXFIFO;0����FIFOָ�븴λ��0
	//bit12-8  RXFFST4-0         (R-0)     RXFIFO�ѽ������ݵ�����
	//bit7     RXFFINT Flag      (R-0)     TXFIFO�жϱ�־λ
	//bit6     RXFFINT CLR       (W-0)  1��д1���RXFFINT Flag
	//bit5     RXFFIENA          (R/W-0)0����ֹ����RXFFIVL���ж�
	//bit4-0   RXFFIL4-0         (R/W-1)11111����RXFFST4-0���ڵȴ�ֵʱ�����ж�
    ScibRegs.SCIFFCT.all=0x4008;
	//bit15     ABD              (R-0)     ABD��ɱ�־λ
    //bit14     ABD CLR          (W-0)  1��д1���ABD��־λ
    //bit13     CDC              (R/W-0)0����ֹABD����
	//bit12-8   Reserved          
	//bit7-0    FFTXDLY7-0       (R/W-0)�������Է���FIFO��������������λ�Ĵ���
	                              //���ӳ�ʱ�䣬�Բ���ʱ��Ϊ��׼,������Ϊ8
}

#endif // if DSP28_SCIB 

#if DSP28_SCIC
void InitScicGpio()
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.  
// This will enable the pullups for the specified pins.

	GpioCtrlRegs.GPBPUD.bit.GPIO62 = 0;    // Enable pull-up for GPIO62 (SCIRXDC)
	GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0;	   // Enable pull-up for GPIO63 (SCITXDC)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.  
// This will select asynch (no qualification) for the selected pins.

	GpioCtrlRegs.GPBQSEL2.bit.GPIO62 = 3;  // Asynch input GPIO62 (SCIRXDC)

/* Configure SCI-C pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.

	GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 1;   // Configure GPIO62 for SCIRXDC operation
	GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 1;   // Configure GPIO63 for SCITXDC operation
	
    EDIS;
}
#endif // if DSP28_SCIC 

	
//===========================================================================
// End of file.
//===========================================================================
