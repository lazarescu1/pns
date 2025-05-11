/* Tema 2 - Procesoare Numerice de Semnal */
/* Comand� servomotoare */

#include "p33Fxxxx.h"

_FOSCSEL(FNOSC_FRC);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF);
_FWDT(FWDTEN_OFF);

void
initPLL (void) 
{
    /* Configure PLL prescaler, PLL postscaler, PLL divisor */
    PLLFBD = 41; 		/* M = 43 FRC */
    CLKDIVbits.PLLPRE = 0;	/* N1 = 2 */
    CLKDIVbits.PLLPOST = 0; 	/* N2 = 2 */	

    /* Initiate Clock Switch to Internal FRC with PLL (NOSC = 0b001) */
    __builtin_write_OSCCONH(0x01);		/* FRC */
    /* __builtin_write_OSCCONH(0x03); */	/* XT */
    __builtin_write_OSCCONL(0x01);

    /* Wait for Clock switch to occur */
    while (OSCCONbits.COSC != 0b001);		/* FRC */
    /* while (OSCCONbits.COSC != 0b011); */	/* XT */

    /* Wait for PLL to lock */
    while(OSCCONbits.LOCK != 1) {};
}

/* Setare timer 3 s� fac� achizitii AD la fiecare 0.1s */
void
init_Timer3 (void) 
{
    T3CON = 0;
    T3CONbits.TCKPS = 1;
    TMR3 = 0;
    PR3 = 46125;
    _T3IF = 0;
    _T3IP = 1;
    _T3IE = 1;
    T3CONbits.TON = 1;
}

void
init_PWM1 (void) 
{
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
initAdc1 (void) 
{
    AD1CON1bits.AD12B = 1;	/* Conversie AD pe 12 biti */
    AD1CON1bits.FORM = 0;	/* Rezultat conversie integer */
    AD1CON1bits.SSRC = 2;	/* Timerul 3 starteaza conversia */
    AD1CON1bits.ASAM = 1;	/* Incepe esantionarea noii valori imediat 
				dupa terminarea unei conversii */
    AD1CON2bits.CSCNA = 1;	/* Scaneaza intrarile pe CH0+ in timpul 
				achizitiei A */
    AD1CON2bits.CHPS = 0;	/* Converteste doar CH0 */
    AD1CON2bits.SMPI = 0;	/* Incrementeaza adresa DMA dupa terminarea
				fiecarei conversii */
    AD1CON3bits.ADRC = 0;	/* Foloseste ceasul magistralei */
    AD1CON3bits.ADCS = 63;	/* Timpul necesar unei conversii este de 22.4us */
    /*
     * Ceasul pentru conversia AD are formula Tad = Tcy * (adcs + 1) 
     * Tad = Tcy * (adcs + 1) = (1 / 40) * 64 = 1.6us
     * Se seteaza intrarile analogice
     */
    AD1CSSLbits.CSS4 = 1;	
    /* 
     * Selectam intrarea analogica AN4(RB2) pentru a fi scanata.
     * Scriem registrul de configurare al portului.
     * Se va folosi doar registrul low al portului de configurare
     * deoarece dsPIC33fj128MC802 nu are implementati mai mult de 6
     * pini pentru ADC.
     */
    AD1PCFGL = 0xFFFF;		/* Setam toti pinii portului ADC1 pe modul
				digital, si activeaza citirea la intrarea portului */
    AD1PCFGLbits.PCFG4 = 0;	/* Setam pinul AN4(RB2) pe intrare analogica,
				ADC verifica voltajele pe acel pin (achizitie AD) */
    IFS0bits.AD1IF = 0;		/* Reseteaza flag-ul intreruperii convertorului AD */
    IPC3bits.AD1IP = 6;		/* Seteaza prioritatea intreruperii convertorului AD */
    IEC0bits.AD1IE = 1;		/* Permite intreruperea convertorului AD */
    AD1CON1bits.ADON = 1;
}

/*
void
__attribute__ ((interrupt, no_auto_psv)) _T3Interrupt(void) 
{
    _RB15 = ~_RB15;
	_RB14 = ~_RB14;
	_RB13 = ~_RB13;
	_RB12 = ~_RB12;
    _T3IF = 0;
}
*/

/* Logica butonului S2 */
void
__attribute__ ((interrupt, no_auto_psv)) _INT0Interrupt (void) 
{
    _INT0IF = 0;
}

void 
__attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void) 
{
 	
    IFS0bits.AD1IF = 0; /* Achita intreruperea convertorului AD */
}

int
main (int argc, char *argv[]) 
{
    TRISB = 0x0000;
    _TRISB7 = 1;
    _TRISB2 = 1;	    /* Setare pin RB2 ca IN pt. achizitia A/D */
    PORTB = 0xF000;
    /* initPLL(); */
    init_Timer3();
    init_PWM1();	    /* Functioneaz� */

    _INT0IF = 0;
    _INT0IE = 1;
    _INT0EP = 1;
	
    while(1) {}
    return (0);
}
