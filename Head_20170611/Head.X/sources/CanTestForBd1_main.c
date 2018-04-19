
#include "CanTestForBd1.h"

#ifdef _FSS                            /* for chip with memory protection options */
_FSS(RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF)
#endif

_FGS(GCP_OFF & GSS_OFF & GWRP_OFF)
_FOSCSEL(FNOSC_PRIPLL & IESO_OFF & 0xFFFF)
_FOSC(FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMD_XT)
_FPOR(FPWRT_PWR64)
_FWDT(FWDTEN_OFF)
_FICD(JTAGEN_OFF & ICS_PGD1)

int main(void) {
    /* configure clock speed ≈‰÷√œµÕ≥ ±÷”40Mhz*/
    PLLFBD = 150;
    CLKDIV = 5;

    /* Initialize model */
    CanTestForBd1_initialize(1);

    for (;;) 
    {
        /* Associate rt_OneStep() with a timer that executes at the base rate of the model */
        while (!_T1IF);
        _T1IF = 0;

        /* Busy Flag */
        LATAbits.LATA0 = 1;

        rt_OneStep();

        /* Busy Flag */
        LATAbits.LATA0 = 0;

        /* Overrun Flag */
        LATAbits.LATA1 = _T1IF;
    }
}
