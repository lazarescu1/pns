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
    _RB15 = ~_RB15;
    _T1IF = 0;
}

/* Logica butonului S2 */
void
__attribute__ ((interrupt, no_auto_psv)) _INT0Interrupt (void) 
{
    unsigned int pwm_values[] = {
        738,   // 0.2 ms
        1476,  // 0.4 ms
        2213,  // 0.6 ms
        2953,  // 0.8 ms
        3690,  // 1.0 ms
        4427,  // 1.2 ms
        5166,  // 1.4 ms
        5904,  // 1.6 ms
        6641,  // 1.8 ms
        7380,  // 2.0 ms
        8118   // 2.2 ms
    };
    int pwm_index = 4;
    int direction = 1; // 1 = urcare, -1 = coborire
    
    pwm_index = pwm_index + direction;
    
    if (pwm_index >= 10) {
        pwm_index = 10;
        direction = -1;
    } else if (pwm_index <= 0) {
        pwm_index = 0;
        direction = 1;
    }

    P1DC2 = pwm_values[pwm_index];

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
