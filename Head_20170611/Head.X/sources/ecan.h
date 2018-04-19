
#ifndef __ecan_H
#define __ecan_H

/* CAN Baud Rate Configuration 	波特率配置	*/
#define FCAN  	      	4000000 
#define BITRATE 		100000  
#define NTQ 			20		// 20 Time Quanta in a Bit Time
#define BRP_VAL			((FCAN/(2*NTQ*BITRATE))-1)


/* ECAN message type identifiers */
#define CAN_MSG_DATA	0x01
#define CAN_MSG_RTR		0x02
#define CAN_FRAME_EXT	0x03
#define CAN_FRAME_STD	0x04
#define CAN_BUF_FULL	0x05
#define CAN_BUF_EMPTY	0x06

/* 用于报文过滤的宏	*/
#define CAN_FILTERMASK2REG_SID(x) ((x & 0x07FF)<< 5)
#define CAN_SETMIDE(sid) (sid | 0x0008)
#define CAN_FILTERXTD(sid) (sid | 0x0008)
#define CAN_FILTERSTD(sid) (sid & 0xFFF7)
#define CAN_FILTERMASK2REG_EID0(x) (x & 0xFFFF)
#define CAN_FILTERMASK2REG_EID1(x) (((x & 0x1FFC)<< 3)|(x & 0x3))

/* DMA CAN Message Buffer Configuration 报文缓冲区长度*/
#define ECAN1_MSG_BUF_LENGTH 	4
typedef unsigned int ECAN1MSGBUF [ECAN1_MSG_BUF_LENGTH][8];
extern ECAN1MSGBUF  ecan1msgBuf __attribute__((space(dma)));

/* message structure in RAM */
typedef struct{
	/* keep track of the buffer status */
	unsigned char buffer_status;
	/* RTR message or data message */
	unsigned char message_type;
	/* frame type extended or standard */
	unsigned char frame_type;
	/* buffer being used to send and receive messages */
	unsigned char buffer;
	/* 29 bit id max of 0x1FFF FFFF 
	*  11 bit id max of 0x7FF */
	unsigned long id; 
	unsigned char data[8];	
	unsigned char data_length;
}mID;

/* function prototypes as defined in can.c */
void initECAN (void);
void initDMAECAN(void);
void sendECAN(mID *message);
void SendCan(f1,f2,f3,f4,f5);
void rxECAN(mID *message);
void clearRxFlags(unsigned char buffer_number);
void ReadCan();	
#endif
