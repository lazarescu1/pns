/* 
 * Tema 2 
 * Procesoare Numerice de Semnal
 * Comandã servomotoare 
 */

#include "p33Fxxxx.h"
#include "lib.h"

_FOSCSEL(FNOSC_FRC);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF);
_FWDT(FWDTEN_OFF);

int
main (int argc, char *argv[]) 
{
    TRISB = 0x0000;
    _TRISB7 = 1;    // Buton S2
    _TRISB2 = 1;
    PORTB = 0xF000;
    /* initPLL(); */
    initTIMER3();
    initTIMER1();
    initPWM1();	   
	initADC1(); 

    /* Setari buton S2 */
    _INT0IF = 0;
    _INT0IE = 1;
    _INT0EP = 0;    // Front pozitiv
	
    while(1) {}
    return (0);
}
