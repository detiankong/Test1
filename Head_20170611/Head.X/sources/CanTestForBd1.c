
#include "CanTestForBd1.h"
#include "math.h"
#include <uart.h>
#include "timer.h"

extern unsigned int curr;
extern int currl, currh;
int initialstate;
static int parameter[6] = {0};
float a, omiga, phi;
char ReceivedChar;
extern int f1, f2, f3, f4, f5;
float T = 0;
float T1;

volatile uint8_T ToUartTx[10];
volatile real32_T ReVel[5];
BlockIO_Can_3_No0 Can_3_No0_B;

/* Model output function
 * UART1接收上位机发送A OMIGA PHI(中断)
 * 求sin函数 各个关节运动角度
 * CAN发送给各个关节角度
 * CAN接收各个关节反馈的电流（中断）
 * UART1将各个关节电流发送给上位机 */
void rt_OneStep(void) 
{
   
    sinusoid(); 
    SendCan(f1,f2,f3,f4,f5);
//    Wrap_UART1();
//    Can_3_No0();
}

/* Model initialize function 初始化*/
void CanTestForBd1_initialize(boolean_T firstTime) 
{
    (void) firstTime;

    /* CONFIG TIMER 1 for scheduling steps 配置时钟1分频、步数，  Timer1定时1/(40/8)*PR1*1e-6=10ms*/
    ConfigIntTimer1(T1_INT_PRIOR_0 & T1_INT_OFF);
    T1CON = 0x8010; /* T1_PS_1_8	八分频*/
    PR1 = 50000;

    /* Configuration TRIS  配置输入输出引脚，用到那个配哪个*/
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA8 = 0;

    /*配置引脚 */
    /*unlock */
    OSCCON = 0x46;
    OSCCON = 0x57;
    OSCCONbits.IOLOCK = 0;
    /* CAN总线引脚配置*/
    RPINR26bits.C1RXR = 24; //RP24为CAN总线C RX
    RPOR7bits.RP14R = 16;  //RP14为CAN总线TX
    /*串口引脚配置*/
    RPINR18bits.U1RXR = 21;//RP21为串口U RX RPIN 定义功能 查手册
    RPOR10bits.RP20R = 3;  //RP20为串口TX   RPO
    /*lock*/
    OSCCON = 0x46;
    OSCCON = 0x57;
    OSCCONbits.IOLOCK = 1;

    
    UartInit();
     /*CAN总线初始化*/
    initECAN();
    initDMAECAN();
}

/*sin函数*/
void sinusoid() 
{
    T = T + Ts;  //Ts采样时间 sint
    T1 = T - T0L;  //T0L等待时间

    if (T <= T0L) 
    {
        f1 = 0;
        f2 = 0;
        f3 = 0;
        f4 = 0;
        f5 = 0;
    }
    else 
    {
        f1 = 100 * a * sin(omiga * T1);
       // f1 = 100 * a * T1;
        f2 = 100 * a * sin(omiga * T1 + phi);   
        f3 = 100 * a * sin(omiga * T1 + 2 * phi);
        f4 = 100 * a * sin(omiga * T1 + 3 * phi);
        f5 = 100 * a * sin(omiga * T1 + 4 * phi);
    }
}

 /*串口1初始化*/
void UartInit(void) 
{

    U1MODEbits.STSEL = 0; // 1-stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8-data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U1MODEbits.BRGH = 0; // Low Speed mode
    U1MODEbits.LPBACK = 0;
    U1BRG = BRGVAL1; // 波特率 BAUD Rate Setting for 115200
    U1STAbits.UTXISEL0 = 0; // Interrupt after one Tx character is transmitted
    U1STAbits.UTXISEL1 = 0;
    U1STAbits.URXISEL = 0;
    IEC0bits.U1TXIE = 1; // Enable UART Tx interrupt
    IEC0bits.U1RXIE = 1; // Enable UART Rx interrupt
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART Tx

}

/*串口接收中断*/
void __attribute__((__interrupt__)) _U1RXInterrupt(void)
{
    ReceivedChar = U1RXREG;
    /*接收6个字节：a fai omiga */
    if (initialstate > 0) 
    {
        parameter[initialstate - 1] = ReceivedChar;
        initialstate++;
        if (initialstate > 6) 
        {
            initialstate = 0;
            a = (parameter[0]*256 + parameter[1]) / 100.0f;
            phi = (parameter[2]*256 + parameter[3]) / 100.0f;
            omiga = (parameter[4]*256 + parameter[5]) / 100.0f; 
        }
    }
    if ((ReceivedChar == 0x75) && (initialstate == 0)) 
    {
        initialstate++;
    }
    IFS0bits.U1RXIF = 0;
}

/*串口1发送中断*/
void __attribute__((__interrupt__)) _U1TXInterrupt(void)
{
    IFS0bits.U1TXIF = 0; // clear TX interrupt flag
}

/*串口发送*/
void Wrap_UART1() {
    (void) memset(&ToUartTx, 0, 11 * sizeof (uint8_T));


    
    //   current2=(int16_T)(ReVel[1]*100);
    //   current3=(int16_T)(ReVel[2]*100);
    //   current4=(int16_T)(ReVel[3]*100);
    //   current5=(int16_T)(ReVel[4]*100);

    //   current1=(int16_T)(ReVel[0]*100);
    //   current2=(int16_T)(ReVel[1]*100);
    //   current3=(int16_T)(ReVel[2]*100);
    //   current4=(int16_T)(ReVel[3]*100);
    //   current5=(int16_T)(ReVel[4]*100);

    //   Measured and Observed Vx
    ToUartTx[0] = 0x00;
    ToUartTx[1] = currh;
    //     ToUartTx[0] =(uint8_T)((uint16_T)current1 & 0x00FF);
    //     ToUartTx[1] =(uint8_T)(((uint16_T)current1& 0xFF00)>> 8);

    //     ToUartTx[2] =(uint8_T)((uint16_T)current2  & 0x00FF);
    //     ToUartTx[3] =(uint8_T)(((uint16_T)current2 & 0xFF00)>> 8);
    //
    ////   Measured and Observed Vy
    //
    //     ToUartTx[4] =(uint8_T)((uint16_T) current3 & 0x00FF);
    //     ToUartTx[5] =(uint8_T)(((uint16_T) current3 & 0xFF00)>> 8);
    //
    //     ToUartTx[6] =(uint8_T)((uint16_T)current4 & 0x00FF);
    //     ToUartTx[7] =(uint8_T)(((uint16_T)current4 & 0xFF00)>> 8);
    //
    ////   Measured and Observed Vt
    //
    //     ToUartTx[8] =(uint8_T)((uint16_T) current5 & 0x00FF);
    //     ToUartTx[9] =(uint8_T)(((uint16_T) current5 & 0xFF00)>> 8);
    return;
}
/*串口发送*/
void Can_3_No0(void) 
{
    int16_T i;

    Can_3_No0_B.VectorConcatenate[0] = 0x3b;
    
    for (i = 0; i < 3; i++) 
    {
        Can_3_No0_B.VectorConcatenate[i + 1] = ToUartTx[i];
    }

    /* S-Function "UART_Tx" Block: <S2>/Tx Output */
    {
        int_T i1;
        const uint8_T *u0 = Can_3_No0_B.VectorConcatenate;

//        for (i1 = 0; i1 < 3; i1++) {
//            while (BusyUART1());
//            WriteUART1(u0[i1]);
//        }
    }
}


