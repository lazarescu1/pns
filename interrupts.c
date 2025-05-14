/* Functiile de intrerupere */

#include "p33Fxxxx.h"
#include "lib.h"

void
__attribute__ ((interrupt, no_auto_psv)) _T3Interrupt (void) 
{
    _RB15 = ~_RB15;
    _RB14 = ~_RB14;
    _RB13 = ~_RB13;
    _RB12 = ~_RB12;
    _T3IF = 0;
}

/* Logica butonului S2 */
void
__attribute__ ((interrupt, no_auto_psv)) _INT0Interrupt (void) 
{
    _INT0IF = 0;
}

void 
__attribute__((interrupt, no_auto_psv)) _ADC1Interrupt (void) 
{
    IFS0bits.AD1IF = 0; /* Achita intreruperea convertorului AD */
}
