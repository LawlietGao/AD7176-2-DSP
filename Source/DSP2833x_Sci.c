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

/*在本工程中的修改之处*/
//void InitSci(void)中添加了两个SCIb的初始化函数调用
//后面添加了void InitScib()函数体具体操作
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
	/*1bit停止位、无校验位、内部不互联、空闲线模式、8bits字长*/
    ScibRegs.SCICCR.all=0x07;
	//bit7     STOP BITS          (R/W-0)0:1bit停止位
	//bit6     EVEN/ODD PARITY    (R/W-0)
	//bit5     PARITY ENABLE      (R/W-0)0：无校验位
	//bit4     LOOP BACK ENA      (R/W-0)0：内部不使能
	//bit3     ADDR/IDLE MODE     (R/W-0)0：空闲线模式
	//bit2-0   SCI CHAR2-0        (R/W-0)111：8bits字长

   /*禁止接收错误中断、使能SCI、不设置TXWAKE、收发使能*/
	ScibRegs.SCICTL1.all=0x23;
	//bit7     Reserved           (R-0) 
	//bit6     RX ERR INTENA      (R/W-0)0：禁止接收错误中断
	//bit5     SW RESET           (R/W-0)1：使能SCI。写零将初始化SCI的状态机和操作标志位，但是不
	//                                   影响配置，一旦此位清零，SCI的标志位将冻结直至此位重新置位
	//bit4     Reserved           (R-0) 
	//bit3     TXWAKE             (R/S-0)0：不设置发送唤醒位 
	//bit2     SLEEP              (R/W-0)0：禁止睡眠模式
    //bit1     TXENA              (R/W-0)1：发送使能
	//bit0     RXENA              (R/W-0)1：接收使能

    /*低速时钟37.5MHZ，波特率为19200，所以BRR=0XF3*/
    ScibRegs.SCIHBAUD=0x00;
	//bit15-8  SCIHBAUD
	//bit7-0   Reserved
    ScibRegs.SCILBAUD=0xF3;    
    //bit15-8  Reserved
	//bit7-0   SCILBAUD
    
	/*禁止收发的相关中断*/
	ScibRegs.SCICTL2.all=0xc2;
    //bit7     TXRDY             (R-1)  若为1：发送缓冲寄存器准备好标志位
	//bit6     TX EMPTY          (R-1)  若为1：发送器空标志位
	//bit5-2   Reserved          (R-0)
	//bit1     RX/BK INTENA      (R/W-0)0：禁止接收器的相关中断
	//bit0     TX INT ENA        (R/W-0)0：禁止发送器的相关中断

	/***************************/
    ScibRegs.SCIFFTX.all=0xE040;
    //bit15    SCIRST            (R/W-1)1：不复位
    //bit14    SCIFFENA          (R/W-0)1：FIFO增强功能使能
    //bit13    TXFIFO Reset      (R/W-1)1：重新使能TXFIFO;0：将FIFO指针复位到0
	//bit12-8  TXFFST4-0         (R-0)     FIFO未发送数据的数量
	//bit7     TXFFINT Flag      (R-0)     TXFIFO中断标志位
	//bit6     TXFFINT CLR       (W-0)  1:写1清除TXFFINT Flag
	//bit5     TXFFIENA          (R/W-0)0:禁止基于TXFFIVL的中断
	//bit4-0   TXFFIL4-0         (R/W-0)00000:当TXFFST4-0小于等于此值时产生中断
    ScibRegs.SCIFFRX.all=0x605f;
    //bit15    RXFFOVF           (R-0)     FIFO溢出状态位，若为1：已接收16个数，且已失去一个
    //bit14    RXFFOVF CLR       (W-0)  1：写1清除RXFFOVF标志位
    //bit13    RXFIFO Reset      (R/W-1)1：重新使能RXFIFO;0：将FIFO指针复位到0
	//bit12-8  RXFFST4-0         (R-0)     RXFIFO已接收数据的数量
	//bit7     RXFFINT Flag      (R-0)     TXFIFO中断标志位
	//bit6     RXFFINT CLR       (W-0)  1：写1清除RXFFINT Flag
	//bit5     RXFFIENA          (R/W-0)0：禁止基于RXFFIVL的中断
	//bit4-0   RXFFIL4-0         (R/W-1)11111：当RXFFST4-0大于等此值时产生中断
    ScibRegs.SCIFFCT.all=0x4008;
	//bit15     ABD              (R-0)     ABD完成标志位
    //bit14     ABD CLR          (W-0)  1：写1清除ABD标志位
    //bit13     CDC              (R/W-0)0：禁止ABD功能
	//bit12-8   Reserved          
	//bit7-0    FFTXDLY7-0       (R/W-0)定义了自发送FIFO缓冲器到发送移位寄存器
	                              //的延迟时间，以波特时钟为基准,本例设为8
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
