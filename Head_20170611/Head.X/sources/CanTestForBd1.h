
#ifndef RTW_HEADER_CanTestForBd1_h_
#define RTW_HEADER_CanTestForBd1_h_

#include <string.h>
#include "rtwtypes.h"
#include "p33fxxxx.h"
#include "timer.h"

#define BRGVAL1 ((40000000/115200)/16)-1    //²¨ÌØÂÊ
#define Ts     0.01f
#define T0L    5u
typedef struct {
  uint8_T VectorConcatenate[11];       /* '<S2>/Vector Concatenate' */
  boolean_T DataTypeConversion;        /* '<Root>/Data Type Conversion' */
} BlockIO_Can_3_No0;
extern BlockIO_Can_3_No0 Can_3_No0_B;


/* Model entry point functions */
extern void rt_OneStep(void);
extern void CanTestForBd1_initialize(boolean_T firstTime);
extern void UartInit(void);
void Can_3_No0();
void Wrap_UART1();
void __attribute__((__interrupt__)) _U1RXInterrupt(void);
void __attribute__((__interrupt__)) _U1TXInterrupt(void);
#endif                                

