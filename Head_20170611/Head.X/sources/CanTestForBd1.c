
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
 * UART1������λ������A OMIGA PHI(�ж�)
 * ��sin���� �����ؽ��˶��Ƕ�
 * CAN���͸������ؽڽǶ�
 * CAN���ո����ؽڷ����ĵ������жϣ�
 * UART1�������ؽڵ������͸���λ�� */
void rt_OneStep(void) 
{
   
    sinusoid(); 
    SendCan(f1,f2,f3,f4,f5);
//    Wrap_UART1();
//    Can_3_No0();
}

/* Model initialize function ��ʼ��*/
void CanTestForBd1_initialize(boolean_T firstTime) 
{
    (void) firstTime;

    /* CONFIG TIMER 1 for scheduling steps ����ʱ��1��Ƶ��������  Timer1��ʱ1/(40/8)*PR1*1e-6=10ms*/
    ConfigIntTimer1(T1_INT_PRIOR_0 & T1_INT_OFF);
    T1CON = 0x8010; /* T1_PS_1_8	�˷�Ƶ*/
    PR1 = 50000;

    /* Configuration TRIS  ��������������ţ��õ��Ǹ����ĸ�*/
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA8 = 0;

    /*�������� */
    /*unlock */
    OSCCON = 0x46;
    OSCCON = 0x57;
    OSCCONbits.IOLOCK = 0;
    /* CAN������������*/
    RPINR26bits.C1RXR = 24; //RP24ΪCAN����C RX
    RPOR7bits.RP14R = 16;  //RP14ΪCAN����TX
    /*������������*/
    RPINR18bits.U1RXR = 21;//RP21Ϊ����U RX RPIN ���幦�� ���ֲ�
    RPOR10bits.RP20R = 3;  //RP20Ϊ����TX   RPO
    /*lock*/
    OSCCON = 0x46;
    OSCCON = 0x57;
    OSCCONbits.IOLOCK = 1;

    
    UartInit();
     /*CAN���߳�ʼ��*/
    initECAN();
    initDMAECAN();
}

/*sin����*/
void sinusoid() 
{
    T = T + Ts;  //Ts����ʱ�� sint
    T1 = T - T0L;  //T0L�ȴ�ʱ��

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

 /*����1��ʼ��*/
void UartInit(void) 
{

    U1MODEbits.STSEL = 0; // 1-stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8-data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U1MODEbits.BRGH = 0; // Low Speed mode
    U1MODEbits.LPBACK = 0;
    U1BRG = BRGVAL1; // ������ BAUD Rate Setting for 115200
    U1STAbits.UTXISEL0 = 0; // Interrupt after one Tx character is transmitted
    U1STAbits.UTXISEL1 = 0;
    U1STAbits.URXISEL = 0;
    IEC0bits.U1TXIE = 1; // Enable UART Tx interrupt
    IEC0bits.U1RXIE = 1; // Enable UART Rx interrupt
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART Tx

}

/*���ڽ����ж�*/
void __attribute__((__interrupt__)) _U1RXInterrupt(void)
{
    ReceivedChar = U1RXREG;
    /*����6���ֽڣ�a fai omiga */
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

/*����1�����ж�*/
void __attribute__((__interrupt__)) _U1TXInterrupt(void)
{
    IFS0bits.U1TXIF = 0; // clear TX interrupt flag
}

/*���ڷ���*/
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
/*���ڷ���*/
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


