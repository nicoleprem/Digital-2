/*
 * File:   main.c
 * Author: Nicole Prem
 *
 * Created on 15 de febrero de 2021, 03:32 PM
 */


#include <xc.h>
#include "Libreria_ADC.h"
#include <stdint.h>
//*****************************************************************************
//Configuración de la palabra
//*****************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
//Variables
//*****************************************************************************
#define XTAL_FREQ 8000000
uint8_t banderaADC; //bandera del ADC
uint8_t adc;

//*****************************************************************************
//Declaración de entradas, salidas y limpieza de puertos
//*****************************************************************************
void setup (void){
    ANSEL = 0x01; //Entrada analógica
    ANSELH = 0; //Entrada analógica
    INTCON = 0xE8; /*Activación de Global Interrupt Enable, Peripherial
                          Interrupt E.,,Timer0 Overflow Interrupt E.,
                          PortB interrupt on change*/
     //bits de interrupciones
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    PORTEbits.RE0 = 1;
    
}

//*****************************************************************************
//Interrupciones
//*****************************************************************************
    
void __interrupt() ISR(void) {
    //Interrupcuón del ADC
    if (PIR1bits.ADIF == 1) {
        banderaADC = 1;
        //valorI = ADRESH >> 4; //corrimiento para desplegar valor izquierda
        //valorD = ADRESH & 0b00001111; //escoger bits para valor derecha
        adc = ADRESH;
        PIR1bits.ADIF = 0; //Se apaga bandera ADC
    }
}

void main(void) {
    setup();
    banderaADC = 1;
    while (1) {
        AADC(banderaADC);
}
}
