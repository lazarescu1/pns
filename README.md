# Comandă servomotoare

Să se proiecteze şi să se realizeze o aplicaţie încorporată cu un microcontroller _dsPIC33FJ128MC802_ care să aibă următoarele caracteristici:
  - Să se efectuze achiziţii AD de pe canalul AN4 la fiecare 0,1s. Tensiunea aplicată pe pinul RB2 va fi obţinută de la un potenţiometru conectat între GND şi 3,3V.
  - Rezultatul conversiei va fi scalat în intervalul 1-2ms, interval ce va reprezenta lăţimea impulsului pentru semnalul generat pe pinul PWM1H şi aplicat unui servomotor. Perioada semnalului PWM generat pe pinul PWM1H va fi de 20ms.
  - Să genereze pe pinul RB12 un semnal PWM cu perioada de 20ms şi factor de umplere de 5% ce va fi aplicat unui al doilea servomotor.
  - La fiecare apăsare a butonului S2 să se producă incrementarea cu 0,2ms a lăţimii impulsului semnalului PWM generat pe RB12 până la valoarea maximă de 2,2ms. Atingerea valorii de 2,2ms va determina decrementarea cu 0,2ms a lăţimii impulsului până la valoarea minimă de 0,2ms de unde va fi incrementat din nou cu 0,2ms.
  - Să comute starea pinului RB5 cu o perioadă de 1s. Comutarea va fi pusă în evidenţă de unul dintre LED-urile disponibile pe placă. 

### Plăcuța de Dezvoltare cu _**dsPIC33FJ32MC302**_
<img width="853" alt="Placuta de Dezvlotare" src="https://github.com/lazarescu1/pns/blob/master/dspic.jpg">

### To Do
- [ ] 
- [ ]
