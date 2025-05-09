/* Tema 2 - Procesoare Numerice de Semnal */
/* Comandă servomotoare */
#if defined(__dsPIC33F__)
#include "p33Fxxxx.h"
#elif defined(__dsPIC24H__)
#include "p24Hxxxx.h"
#endif

_FOSCSEL(FNOSC_FRC);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF);
_FWDT(FWDTEN_OFF);

void
initPLL(void) {
	/* Configure PLL prescaler, PLL postscaler, PLL divisor */
	PLLFBD = 41; 		/* M = 43 FRC */
	CLKDIVbits.PLLPRE=0;	/* N1 = 2 */
	CLKDIVbits.PLLPOST=0; 	/* N2 = 2 */	

	/* Initiate Clock Switch to Internal FRC with PLL (NOSC = 0b001) */
	__builtin_write_OSCCONH(0x01);	/* FRC */
	/* __builtin_write_OSCCONH(0x03); */	/* XT */
	__builtin_write_OSCCONL(0x01);

	/* Wait for Clock switch to occur */
	while (OSCCONbits.COSC != 0b001);	/* FRC */
	/* while (OSCCONbits.COSC != 0b011); */	/* XT */

	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1) {};
}

/* Funcțional */
/* Setare timer 3 să facă achiziții AD la fiecare 0.1s */
void
init_Timer3(void) {
	T3CON = 0;
	T3CONbits.TCKPS = 1;
	TMR3 = 0;
	PR3 = 46125;
	_T3IF = 0;
	_T3IP = 1;
	_T3IE = 1;
	T3CONbits.TON = 1;
}

/* Are erori? */
void
init_PWM1(void) {
	P1TCONbits.PTOPS = 0;
	P1TCONbits.PTMOD = 0;
	P1TCONbits.PTCKPS = 1;
	P1TMRbits.PTDIR = 0;
	P1TMRbits.PTMR = 0;
	P1DC2 = 7380;
	P1TPER = 73800;
	PWM1CON1bits.PMOD1 = 1;
 	PWM1CON1bits.PMOD2 = 1;
 	PWM1CON1bits.PMOD3 = 1;
 	PWM1CON1bits.PEN1H = 0;
 	PWM1CON1bits.PEN1L = 0; 
 	PWM1CON1bits.PEN2H = 1;
 	PWM1CON1bits.PEN2L = 0; 
 	PWM1CON1bits.PEN3H = 0; 
 	PWM1CON1bits.PEN3L = 0; 
 	PWM1CON2bits.UDIS = 1; 
	P1TCONbits.PTEN = 1;
}

void
__attribute__ ((interrupt, no_auto_psv)) _T3Interrupt(void) {
	_RB14 = ~_RB14;
	_T3IF = 0;
}

/* Funcția care implementeaza logica apăsării butonului S2 */
void
__attribute__ ((interrupt, no_auto_psv)) _INT0Interrupt (void) {
    _INT0IF = 0;
}

/* Main function */
int
main(int argc, char **argv) 
{
    TRISB = 0x0000;
    _TRISB7 = 1;
    PORTB = 0xF000;
    //initPLL();
    //init_Timer3();
    init_PWM1(); /* Funcționează */

    _INT0IF = 0;
    _INT0IE = 1;
    _INT0EP = 1;

    while(1) {}
    return 0;
}
