/*
 * File:   main.c
 * Author: Nicole Prem 18337
 *LAB 2
 * Created on 28 de enero de 2021, 05:22 PM
 */
//*****************************************************************************
//Configuración de la palabra
//*****************************************************************************
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


#include <xc.h>
#include <stdint.h>
#include "ADC.h"
#include "7segmentos.h"

//*****************************************************************************
//Prototipos de funciones
//*****************************************************************************


//*****************************************************************************
//Variables
//*****************************************************************************
#define aumentar PORTBbits.RB0  //botón para aumentar el contador
#define disminuir PORTBbits.RB1 //botón para disminuir el contador
#define XTAL_FREQ 8000000

uint8_t count; //contador de 8 bits
uint8_t tabla_segmentos[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, 0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001};
uint8_t banderaADC; //bandera del ADC
uint8_t segmentoD; //segmento de la derecha
uint8_t segmentoI; //segmento de la izquierda
uint8_t valorD;
uint8_t valorI;
uint8_t adc;
//*****************************************************************************
//Declaración de entradas, salidas y limpieza de puertos
//*****************************************************************************

void setup(void) {
    ANSEL = 0x01; //Entrada analógica
    ANSELH = 0; //Entrada analógica
    TRISB = 0x03; //Puerto de botones para el contador
    INTCON = 0xE8; /*Activación de Global Interrupt Enable, Peripherial
                          Interrupt E.,,Timer0 Overflow Interrupt E.,
                          PortB interrupt on change*/
    TRISD = 0; //Puerto de los led del contador
    TRISE = 0b00000000;; //Puerto de la alarma
    TRISC = 0b00000000;;
    //TRISA = 0; //Puerto del ADC y salidas a transistores
    //limpieza de puertos
    PORTB = 0;
    PORTD = 0;
    PORTE = 0;
    //PORTC = 0;
    PORTA = 0;
    //bits de interrupciones
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    PORTEbits.RE0 = 1;

}

//*****************************************************************************
//Interrupciones
//*****************************************************************************

void __interrupt() ISR(void) {
    //Interrupción de los botones para incrementar o disminuir contador
    if (INTCONbits.RBIF == 1) {
        if (aumentar == 0) {
            count++; //Si se presiona el botón aumentar, el contador suma
        } else if (disminuir == 0) {
            count--;
        }
        INTCONbits.RBIF = 0;
    }
    //Interrupcuón del ADC
    if (PIR1bits.ADIF == 1) {
        banderaADC = 1;
        valorI = ADRESH >> 4; //corrimiento para desplegar valor izquierda
        valorD = ADRESH & 0b00001111; //escoger bits para valor derecha
        adc = ADRESH;
        PIR1bits.ADIF = 0; //Se apaga bandera ADC

    }
    //Interrupción timer para multiplexar
    if (INTCONbits.T0IF == 1) {
        TMR0 = 10;
        if (PORTEbits.RE0 == 1) {
            PORTEbits.RE0 = 0;
            PORTEbits.RE1 = 1;
            PORTC = segmentoD;
        } else if (PORTEbits.RE1 == 1) {
            PORTEbits.RE1 = 0;
            PORTEbits.RE0 = 1;
            PORTC = segmentoI;

        }
        INTCONbits.T0IF = 0; //Se apaga bandera timer0
    }




}

void main(void) {
    setup();
    count = 0; //condición inicial de los leds, todos apagados
    banderaADC = 1;
    Segmentos();
    while (1) {
        AADC(banderaADC);
        PORTD = count;
        segmentoI = tabla_segmentos[valorI]; //Despliegue del valor 7seg Izqui.
        segmentoD = tabla_segmentos[valorD]; //Despliegue valor 7 seg Der.
        if (adc > count) {
            PORTEbits.RE2 = 1; //Actuvación de la alarma
        } else {
            PORTEbits.RE2 = 0;

        }

    }
}
