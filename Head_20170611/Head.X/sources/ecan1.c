
#include <p33Fxxxx.h>

#include "ecan.h"

/************* START OF GLOBAL DEFINITIONS **********/
int currh;
/************** END OF GLOBAL DEFINITIONS ***********/

/******************************************************************************
*                                                                             
*    Function:			initCAN
*    Description:       Initialises the ECAN module  
*                       设置2个发送缓冲区（0、6） 5个接收缓冲区（1-5）                                                      
*                                                                                                             
******************************************************************************/

void initECAN (void)
{
	/*1. put the module in configuration mode */
	C1CTRL1bits.REQOP=4;
	while(C1CTRL1bits.OPMODE != 4);
			
	/* 2.FCAN is selected to be FCY   FCAN = FCY = 40MHz */
	C1CTRL1bits.CANCKS = 0x1;

	/*
	Bit Time = (Sync Segment + Propagation Delay + Phase Segment 1 + Phase Segment 2)=20*TQ
	Phase Segment 1 = 8TQ
	Phase Segment 2 = 6Tq
	Propagation Delay = 5Tq
	Sync Segment = 1TQ
	CiCFG1<BRP> =(FCAN /(2 茂驴陆N茂驴陆FBAUD))?1
	BIT RATE OF 1Mbps
	*/	
	C1CFG1bits.BRP = BRP_VAL;
	/* Synchronization Jump Width set to 4 TQ */
	C1CFG1bits.SJW = 0x3;
	/* Phase Segment 1 time is 8 TQ */
	C1CFG2bits.SEG1PH=0x7;
	/* Phase Segment 2 time is set to be programmable */
	C1CFG2bits.SEG2PHTS = 0x1;
	/* Phase Segment 2 time is 6 TQ */
	C1CFG2bits.SEG2PH = 0x5;
	/* Propagation Segment time is 5 TQ */
	C1CFG2bits.PRSEG = 0x4;
	/* Bus line is sampled three times at the sample point */
	C1CFG2bits.SAM = 0x1;
	
	/*3. DMA分配8个缓冲区 CAN Messages to be buffered in DMA RAM ******************************************/	
	C1FCTRLbits.DMABS=0b010;
	
	/* 4. Filter configuration */
	/* enable window to access the filter configuration registers */
	C1CTRL1bits.WIN=0b1;
    
	/*4.1 select acceptance mask屏蔽器 0（=0） filter过滤器 0（F0） buffer 1 */
	C1FMSKSEL1bits.F0MSK=0;
	/* configure accpetence mask 0 - match the id in filter 0 
	setup the mask to check every bit of the standard message, 
	the macro when called as CAN_FILTERMASK2REG_SID(0x7FF) will 
	write the register C1RXM0SID to include every bit in filter comparison 
	屏蔽器0 固定？*/ 	
	C1RXM0SID=CAN_FILTERMASK2REG_SID(0x7FF);
	/* configure accpetence filter 0 
	setup the filter to accept a standard id of 0x123, 
	the macro when called as CAN_FILTERMASK2REG_SID(0x123) will 
	write the register C1RXF0SID to accept only standard id of 0x123 	
	过滤器0*/ 	
	C1RXF0SID=CAN_FILTERMASK2REG_SID(0x2);
	/* set filter to check for standard ID and accept standard id only */
	C1RXM0SID=CAN_SETMIDE(C1RXM0SID);
	C1RXF0SID=CAN_FILTERSTD(C1RXF0SID);	
	/* acceptance filter to use buffer 1 for incoming messages 选buffer*/
	C1BUFPNT1bits.F0BP=0b0001;
	/* enable filter 0 */
	C1FEN1bits.FLTEN0=1;
	
    /* 4.2 select acceptance mask 0 filter 1 and buffer 2 */
    C1FMSKSEL1bits.F1MSK=0;
	/* configure acceptance filter 1  改F？、接受ID*/ 
	C1RXF1SID=CAN_FILTERMASK2REG_SID(0x3);		
	/* filter to check for extended ID only 改2个F？*/
	C1RXF1SID=CAN_FILTERSTD(C1RXF1SID);
	/* acceptance filter to use buffer 2 for incoming messages 改F？、=2*/
	C1BUFPNT1bits.F1BP=0b0010;
	/* enable filter 1  改FLTEN？*/
	C1FEN1bits.FLTEN1=1;
	
	 /* 4.3 select acceptance mask 0 filter 2 and buffer 3 */
    C1FMSKSEL1bits.F2MSK=0;
	/* configure acceptance filter 2 */ 
	C1RXF2SID=CAN_FILTERMASK2REG_SID(0x4);		
	/* filter to check for extended ID only */
	C1RXF2SID=CAN_FILTERSTD(C1RXF2SID);
	/* acceptance filter to use buffer 3 for incoming messages */
	C1BUFPNT1bits.F2BP=0b0011;
	/* enable filter 2 */
	C1FEN1bits.FLTEN2=1;
    
    /*4.4 select acceptance mask 0 filter 3 and buffer 4 */
    C1FMSKSEL1bits.F3MSK=0;
	/* configure acceptance filter 3 */ 
	C1RXF3SID=CAN_FILTERMASK2REG_SID(0x5);		
	/* filter to check for extended ID only */
	C1RXF3SID=CAN_FILTERSTD(C1RXF3SID);
	/* acceptance filter to use buffer 4 for incoming messages */
	C1BUFPNT1bits.F3BP=0b0100;
	/* enable filter 3 */
	C1FEN1bits.FLTEN3=1;
    
     /*4.5 select acceptance mask 0 filter 4 and buffer 5 */
    C1FMSKSEL1bits.F4MSK=0;
	/* configure acceptance filter 4 */ 
	C1RXF4SID=CAN_FILTERMASK2REG_SID(0x6);		
	/* filter to check for extended ID only */
	C1RXF4SID=CAN_FILTERSTD(C1RXF4SID);
	/* acceptance filter to use buffer 5 for incoming messages 注：C1BUFPNT2：过滤器4-7缓冲区指针寄存器*/
	C1BUFPNT2bits.F4BP=0b0101;
	/* enable filter 4 */
	C1FEN1bits.FLTEN4=1;
	         
	/* clear window bit to access ECAN control registers */
	C1CTRL1bits.WIN=0;
	
	/* 5.put the module in normal mode */
	C1CTRL1bits.REQOP=0;
	while(C1CTRL1bits.OPMODE != 0);	
	
	/* clear the buffer and overflow flags 不用改 缓冲区为空 无溢出条件*/
	C1RXFUL1=C1RXFUL2=C1RXOVF1=C1RXOVF2=0x0000; //C1RXFUL1接收缓冲区满寄存器 1(buffer0-15)
    
    /* 6.设置发送/接收缓冲区 */
	/* ECAN1, Buffer 0 is a Transmit Buffer C1TR01：0 1缓冲区*/
	C1TR01CONbits.TXEN0=1;			
	/* ECAN1, Buffer 1 is a Receive Buffer */
	C1TR01CONbits.TXEN1=0;	
	/* ECAN1, Buffer 2 is a Receive Buffer C1TR23：2 3缓冲区*/
	C1TR23CONbits.TXEN2=0;	
	/* ECAN1, Buffer 3 is a Receive Buffer */
	C1TR23CONbits.TXEN3=0;	
    /* ECAN1, Buffer 4 is a Receive Buffer  C1TR45：4 5缓冲区*/
	C1TR45CONbits.TXEN4=0;	
    /* ECAN1, Buffer 5 is a Receive Buffer */
	C1TR45CONbits.TXEN5=0;	
    /* ECAN1, Buffer 6 is a Transmit Buffer */
	C1TR67CONbits.TXEN6=1;	
    
	/* Message Buffer 0、6 Priority Level 发送优先级*/
	C1TR01CONbits.TX0PRI=0b11; 	
    C1TR67CONbits.TX6PRI=0b11; 		
	
	
	/* configure the device to interrupt on the receive buffer full flag */
	/* clear the buffer full flags */
	C1RXFUL1=0;
	C1INTFbits.RBIF=0;//接收缓冲区中断标志位 =1 请求

   /* 7.设置发送/接收缓冲区中断 */ 
	/* Enable ECAN1 Interrupt */     	
	IEC2bits.C1IE=1;	
	/* enable Transmit interrupt */
	C1INTEbits.TBIE=1;
	/* Enable Receive interrupt */
	C1INTEbits.RBIE=1;
}

/******************************************************************************
*                                                                             
*    Function:			initDMAECAN
*    Description:       Initialises the DMA to be used with ECAN module                                                        
*                       Channel 0 of the DMA is configured to Tx ECAN messages
* 						of ECAN module 1. 
*						Channel 2 is uconfigured to Rx ECAN messages of module 1.                                                      
*                       不用修改                                                      
******************************************************************************/
void initDMAECAN(void)
{
	/* initialise the DMA channel 0 for ECAN Tx */
	/* clear the collission flags */
	DMACS0=0;	
    /* setup channel 0 for peripheral indirect addressing mode 
    normal operation, word operation and select as Tx to peripheral */
    DMA0CON=0x2020; 
    /* setup the address of the peripheral ECAN1 (C1TXD) */ 
	DMA0PAD=0x0442;
	/* Set the data block transfer size of 8 */
 	DMA0CNT=7;
 	/* automatic DMA Tx initiation by DMA request */
	DMA0REQ=0x0046;	
	/* DPSRAM atart adddress offset value */ 
	DMA0STA=__builtin_dmaoffset(&ecan1msgBuf);	
	/* enable the channel */
	DMA0CONbits.CHEN=1;
	
	/* initialise the DMA channel 2 for ECAN Rx */
	/* clear the collission flags */
	DMACS0=0;
    /* setup channel 2 for peripheral indirect addressing mode 
    normal operation, word operation and select as Rx to peripheral */
    DMA2CON=0x0020;
    /* setup the address of the peripheral ECAN1 (C1RXD) */ 
	DMA2PAD=0x0440;	
 	/* Set the data block transfer size of 8 */
 	DMA2CNT=7;
 	/* automatic DMA Rx initiation by DMA request */
	DMA2REQ=0x0022;	
	/* DPSRAM atart adddress offset value */ 
	DMA2STA=__builtin_dmaoffset(&ecan1msgBuf);	
	/* enable the channel */
	DMA2CONbits.CHEN=1;
}

/******************************************************************************
*                                                                             
*    Function:			sendECAN
*    Description:       sends the message on a CAN bus  
*                       两个发送缓冲区，最后的报文发送设置需修改
*                                                                                                    
*                                                                              
******************************************************************************/

/* Define ECAN Message Buffers */
mID canTxMessage1;
mID canTxMessage2;

//
ECAN1MSGBUF ecan1msgBuf __attribute__((space(dma),aligned(ECAN1_MSG_BUF_LENGTH*16)));

void sendECAN(mID *message)
{
	unsigned long word0=0;
	unsigned long word1=0;
	unsigned long word2=0;
	
	/*
	Message Format: 
	Word0 : 0bUUUx xxxx xxxx xxxx
			     |____________|||
 					SID10:0   SRR IDE(bit 0)     
	Word1 : 0bUUUU xxxx xxxx xxxx
			   	   |____________|
						EID17:6
	Word2 : 0bxxxx xxx0 UUU0 xxxx
			  |_____||	     |__|
			  EID5:0 RTR   	  DLC
	
	Remote Transmission Request Bit for standard frames 
	SRR->	"0"	 Normal Message 
			"1"  Message will request remote transmission
	Substitute Remote Request Bit for extended frames 
	SRR->	should always be set to "1" as per CAN specification
	
	Extended  Identifier Bit			
	IDE-> 	"0"  Message will transmit standard identifier
	   		"1"  Message will transmit extended identifier
	
	Remote Transmission Request Bit for extended frames 
	RTR-> 	"0"  Message transmitted is a normal message
			"1"  Message transmitted is a remote message
	Don't care for standard frames 
	*/
		
	/* check to see if the message has an extended ID */
	if(message->frame_type==CAN_FRAME_EXT)
	{
		/* get the extended message id EID28..18*/		
		word0=(message->id & 0x1FFC0000) >> 16;			
		/* set the SRR and IDE bit */
		word0=word0+0x0003;
		/* the the value of EID17..6 */
		word1=(message->id & 0x0003FFC0) >> 6;
		/* get the value of EID5..0 for word 2 */
		word2=(message->id & 0x0000003F) << 10;			
	}	
	else
	{
		/* get the SID */
		word0=((message->id & 0x000007FF) << 2);	
	}
	
    /* check to see if the message is an RTR message */
	if(message->message_type==CAN_MSG_RTR)
	{		
		if(message->frame_type==CAN_FRAME_EXT)
			word2=word2 | 0x0200;
		else
			word0=word0 | 0x0002;	
								
		ecan1msgBuf[message->buffer][0]=word0;
		ecan1msgBuf[message->buffer][1]=word1;
		ecan1msgBuf[message->buffer][2]=word2;
	}
	else
	{
		word2=word2+(message->data_length & 0x0F);
		ecan1msgBuf[message->buffer][0]=word0;
		ecan1msgBuf[message->buffer][1]=word1;
		ecan1msgBuf[message->buffer][2]=word2;
		/* fill the data */
		ecan1msgBuf[message->buffer][3]=((message->data[1] << 8) + message->data[0]);
		ecan1msgBuf[message->buffer][4]=((message->data[3] << 8) + message->data[2]);
		ecan1msgBuf[message->buffer][5]=((message->data[5] << 8) + message->data[4]);
		ecan1msgBuf[message->buffer][6]=((message->data[7] << 8) + message->data[6]);
	}
	/* set the message for transmission  设置发送缓冲区报文发送 */
	C1TR01CONbits.TXREQ0=1;
    C1TR67CONbits.TXREQ6=1;
}

//发送
int f1,f2,f3,f4,f5;
void SendMsn(int f1,int f2,int f3,int f4,int f5)
{
    unsigned char f1h,f1l,f2h,f2l,f3h,f3l,f4h,f4l,f5h,f5l;
    f1h=f1/256;
    f1l=f1%256;
    f2h=f2/256;
    f2l=f2%256;
    f3h=f3/256;
    f3l=f3%256;
    f4h=f4/256;
    f4l=f4%256;
    f5h=f5/256;
    f5l=f5%256;
    
    
	/* configure and send a message */
	canTxMessage1.message_type=CAN_MSG_DATA;
	//canTxMessage.message_type=CAN_MSG_RTR;
	//canTxMessage.frame_type=CAN_FRAME_EXT;
	
    canTxMessage1.frame_type=CAN_FRAME_STD;
	canTxMessage1.buffer=0;
	canTxMessage1.id=0x1;
	
//	canTxMessage1.data[0]=f1l;
//	canTxMessage1.data[1]=f1h;
//	canTxMessage1.data[2]=f2l;
//	canTxMessage1.data[3]=f2h;
//	canTxMessage1.data[4]=f3l;
//	canTxMessage1.data[5]=f3h;
//	canTxMessage1.data[6]=f4l;
//	canTxMessage1.data[7]=f4h;
    canTxMessage1.data[0]=f1h;
	canTxMessage1.data[1]=f2h;
	canTxMessage1.data[2]=f3h;
	canTxMessage1.data[3]=f4h;
	canTxMessage1.data[4]=f5h;
	canTxMessage1.data[5]=0x00;
	canTxMessage1.data[6]=0x00;
	canTxMessage1.data[7]=0x00;
	canTxMessage1.data_length=8;
	/* send a CAN message */
	sendECAN(&canTxMessage1);
  
    
    /* configure and send a message 发送第二条*/
	canTxMessage2.message_type=CAN_MSG_DATA;
	//canTxMessage.message_type=CAN_MSG_RTR;
	//canTxMessage.frame_type=CAN_FRAME_EXT;
	
    canTxMessage2.frame_type=CAN_FRAME_STD;
	canTxMessage2.buffer=6;
	canTxMessage2.id=0x7;
	
	canTxMessage2.data[0]=f5l;
	canTxMessage2.data[1]=f5h;
	canTxMessage2.data[2]=0x00;
	canTxMessage2.data[3]=0x00;
	canTxMessage2.data[4]=0x00;
	canTxMessage2.data[5]=0x00;
	canTxMessage2.data[6]=0x00;
	canTxMessage2.data[7]=0x00;
	canTxMessage2.data_length=8;
	/* send a CAN message */
	sendECAN(&canTxMessage2);
    
}

void SendCan(unsigned int f1,int f2,int f3,int f4,int f5)
{

while(C1TR01CONbits.TXREQ0==1 || C1TR67CONbits.TXREQ6==1);

SendMsn(f1,f2,f3,f4,f5);
}

/******************************************************************************
*    ECAN接收                                                                                                                                                                                                                        
******************************************************************************/
mID canRxMessage;

unsigned int MD01,MD02,MD03,MD04,MD05; //接收数据

void __attribute__((interrupt,no_auto_psv))_C1Interrupt(void)  
{
    /* check to see if the interrupt is caused by receive */     	 
    if(C1INTFbits.RBIF)
    {
//        U1TXREG=0x15;
	    /* check to see if buffer 1 is full C1RXFUL1bits.RXFUL1=1 满 */
	    if(C1RXFUL1bits.RXFUL1)
	    {			
			/* set the buffer full flag and the buffer received flag */
			canRxMessage.buffer_status=CAN_BUF_FULL;
			canRxMessage.buffer=1;	
		}		
		/* check to see if buffer 2 is full */
		else if(C1RXFUL1bits.RXFUL2)
		{
			/* set the buffer full flag and the buffer received flag */
			canRxMessage.buffer_status=CAN_BUF_FULL;
			canRxMessage.buffer=2;					
		}
		/* check to see if buffer 3 is full */
		else if(C1RXFUL1bits.RXFUL3)
		{
			/* set the buffer full flag and the buffer received flag */
			canRxMessage.buffer_status=CAN_BUF_FULL;
			canRxMessage.buffer=3;	
        }
        else if(C1RXFUL1bits.RXFUL4)
		{
			/* set the buffer full flag and the buffer received flag */
			canRxMessage.buffer_status=CAN_BUF_FULL;
			canRxMessage.buffer=4;	
        }
        else if (C1RXFUL1bits.RXFUL5)
		{
            /* set the buffer full flag and the buffer received flag */
			canRxMessage.buffer_status=CAN_BUF_FULL;
			canRxMessage.buffer=5;	
		}
		else;
		/* clear flag */
		C1INTFbits.RBIF = 0; //接收缓冲区中断标志位 =1请求
	}
	else if(C1INTFbits.TBIF)
    {    
        /* clear flag */
		C1INTFbits.TBIF = 0;	//发送缓冲区中断标志位    
	}
	else;

	/* clear interrupt flag */
	IFS2bits.C1IF=0;
	
    ReadCan();
}
/******************************************************************************
*    ECAN接收                                                                           
*    Function:			rxECAN
*    Description:       moves the message from the DMA memory to RAM
*                       不用修改
*                                                                                          
*	                                                                                                                                              
******************************************************************************/	
void rxECAN(mID *message)
{
	unsigned int ide=0;
	unsigned int rtr=0;
	unsigned long id=0;
			
	/*
	Standard Message Format: 
	Word0 : 0bUUUx xxxx xxxx xxxx
			     |____________|||
 					SID10:0   SRR IDE(bit 0)     
	Word1 : 0bUUUU xxxx xxxx xxxx
			   	   |____________|
						EID17:6
	Word2 : 0bxxxx xxx0 UUU0 xxxx
			  |_____||	     |__|
			  EID5:0 RTR   	  DLC
	word3-word6: data bytes
	word7: filter hit code bits
	
	Remote Transmission Request Bit for standard frames 
	SRR->	"0"	 Normal Message 
			"1"  Message will request remote transmission
	Substitute Remote Request Bit for extended frames 
	SRR->	should always be set to "1" as per CAN specification
	
	Extended  Identifier Bit			
	IDE-> 	"0"  Message will transmit standard identifier
	   		"1"  Message will transmit extended identifier
	
	Remote Transmission Request Bit for extended frames 
	RTR-> 	"0"  Message transmitted is a normal message
			"1"  Message transmitted is a remote message
	Don't care for standard frames 
	*/
		
	/* read word 0 to see the message type */
	ide=ecan1msgBuf[message->buffer][0] & 0x0001;			
	
	/* check to see what type of message it is */
	/* message is standard identifier */
	if(ide==0)
	{
		message->id=(ecan1msgBuf[message->buffer][0] & 0x1FFC) >> 2;	
        U1TXREG=message->id;
		message->frame_type=CAN_FRAME_STD;
		rtr=ecan1msgBuf[message->buffer][0] & 0x0002;
	}
	/* mesage is extended identifier */
	else
	{
		id=ecan1msgBuf[message->buffer][0] & 0x1FFC;		
		message->id=id << 16;
		id=ecan1msgBuf[message->buffer][1] & 0x0FFF;
		message->id=message->id+(id << 6);
		id=(ecan1msgBuf[message->buffer][2] & 0xFC00) >> 10;
		message->id=message->id+id;		
		message->frame_type=CAN_FRAME_EXT;
		rtr=ecan1msgBuf[message->buffer][2] & 0x0200;
	}
	/* check to see what type of message it is */
	/* RTR message */
	if(rtr==1)
	{
		message->message_type=CAN_MSG_RTR;	
	}
	/* normal message */
	else
	{
		message->message_type=CAN_MSG_DATA;
		message->data[0]=(unsigned char)ecan1msgBuf[message->buffer][3];
		message->data[1]=(unsigned char)((ecan1msgBuf[message->buffer][3] & 0xFF00) >> 8);
		message->data[2]=(unsigned char)ecan1msgBuf[message->buffer][4];
		message->data[3]=(unsigned char)((ecan1msgBuf[message->buffer][4] & 0xFF00) >> 8);
		message->data[4]=(unsigned char)ecan1msgBuf[message->buffer][5];
		message->data[5]=(unsigned char)((ecan1msgBuf[message->buffer][5] & 0xFF00) >> 8);
		message->data[6]=(unsigned char)ecan1msgBuf[message->buffer][6];
		message->data[7]=(unsigned char)((ecan1msgBuf[message->buffer][6] & 0xFF00) >> 8);
		message->data_length=(unsigned char)(ecan1msgBuf[message->buffer][2] & 0x000F);
	}
	clearRxFlags(message->buffer);	
}

/******************************************************************************
*                                                                             
*    Function:			ReadCan
*    Description:       can读数程序 设置读取数赋值 重点修改                                                                                                           
*                                                                              
******************************************************************************/
    
void ReadCan()
{ 
	if((canRxMessage.buffer_status==CAN_BUF_FULL)&& (canRxMessage.buffer==1))
	{
		rxECAN(&canRxMessage);
//        MD01=canRxMessage.data[0]+(canRxMessage.data[1]<<8);
//        currh=canRxMessage.data[1];
        U1TXREG=canRxMessage.data[0];
        U1TXREG=canRxMessage.data[1];
        _LATA8=canRxMessage.data[0];
		canRxMessage.buffer_status=CAN_BUF_EMPTY;        
	}
	else if((canRxMessage.buffer_status==CAN_BUF_FULL)&& (canRxMessage.buffer==2))
    {
		rxECAN(&canRxMessage);
//        MD02=canRxMessage.data[0]+(canRxMessage.data[1]<<8);
        U1TXREG=canRxMessage.data[0];
        U1TXREG=canRxMessage.data[1];
		canRxMessage.buffer_status=CAN_BUF_EMPTY;       
	}
    else if((canRxMessage.buffer_status==CAN_BUF_FULL)&& (canRxMessage.buffer==3))
    {
		rxECAN(&canRxMessage);
        MD03=canRxMessage.data[0]+(canRxMessage.data[1]<<8);
        U1TXREG=canRxMessage.data[0];
        U1TXREG=canRxMessage.data[1];
		canRxMessage.buffer_status=CAN_BUF_EMPTY;       
	}
    else if((canRxMessage.buffer_status==CAN_BUF_FULL)&& (canRxMessage.buffer==4))
    {
		rxECAN(&canRxMessage);
//        MD04=canRxMessage.data[0]+(canRxMessage.data[1]<<8);
        U1TXREG=canRxMessage.data[0];
        U1TXREG=canRxMessage.data[1];
		canRxMessage.buffer_status=CAN_BUF_EMPTY;       
	}
    else if((canRxMessage.buffer_status==CAN_BUF_FULL)&& (canRxMessage.buffer==5))
    {
		rxECAN(&canRxMessage);
        MD05=canRxMessage.data[0]+(canRxMessage.data[1]<<8);
		canRxMessage.buffer_status=CAN_BUF_EMPTY; 
        U1TXREG=canRxMessage.data[0];
        U1TXREG=canRxMessage.data[1];

	}
    else
	;
}
/******************************************************************************
*                                                                             
*    Function:			clearRxFlags
*    Description:       clears the rxfull flag after the message is read
*                       每个接收缓冲区满的标志位都要清零                                                      
                                                     
*                                                                              
******************************************************************************/

void clearRxFlags(unsigned char buffer_number)
{
	buffer_number=canRxMessage.buffer;
    if((C1RXFUL1bits.RXFUL1) && (buffer_number==1))
		/* clear flag */
		C1RXFUL1bits.RXFUL1=0;		
	/* check to see if buffer 2 is full */
	else if((C1RXFUL1bits.RXFUL2) && (buffer_number==2))
		/* clear flag */
		C1RXFUL1bits.RXFUL2=0;				
	/* check to see if buffer 3 is full */
	else if((C1RXFUL1bits.RXFUL3) && (buffer_number==3))
		/* clear flag */
		C1RXFUL1bits.RXFUL3=0;	
    else if((C1RXFUL1bits.RXFUL4) && (buffer_number==4))
		/* clear flag */
		C1RXFUL1bits.RXFUL4=0;	
    else if((C1RXFUL1bits.RXFUL5) && (buffer_number==5))
		/* clear flag */
		C1RXFUL1bits.RXFUL5=0;	
	else;

}

