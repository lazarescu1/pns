#ifndef DSPIC_LIB_H
#define DSPIC_LIB_H

/* Inits */
void initPLL (void);
void initTIMER3 (void);
void initPWM1 (void);
void initADC1 (void);

/* Interrupts */
void __attribute__ ((interrupt, no_auto_psv)) _T3Interrupt (void);
void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt (void);
void __attribute__ ((interrupt, no_auto_psv)) _ADC1Interrupt (void);
void __attribute__ ((interrupt, no_auto_psv)) _INT0Interrupt (void);

#endif
