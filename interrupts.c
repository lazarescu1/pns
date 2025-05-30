/* Functiile de intrerupere */

#include "p33Fxxxx.h"
#include "lib.h"

void
__attribute__ ((interrupt, no_auto_psv)) _T3Interrupt (void) 
{
    _T3IF = 0;
}

void
__attribute__((interrupt, no_auto_psv)) _T1Interrupt (void)
{
    _T1IF = 0;
}


/* Logica butonului S2 */
void
__attribute__ ((interrupt, no_auto_psv)) _INT0Interrupt (void) 
{
    _INT0IF = 0;
}

int adc_val;
void 
__attribute__((interrupt, no_auto_psv)) _ADC1Interrupt (void) 
{
	adc_val = ADC1BUF0;
	int min = 3690;
	int max = 7380;
	int pulse_width_us = min + (((long)adc_val * (max - min)) / 4095);
	P1DC1 = pulse_width_us;
    IFS0bits.AD1IF = 0; /* Achita intreruperea convertorului AD */
}
