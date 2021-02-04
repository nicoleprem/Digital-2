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
#include <pic16f887.h>
#include <stdint.h>

//*****************************************************************************
//Prototipos de funciones
//*****************************************************************************


//*****************************************************************************
//Variables
//*****************************************************************************
#define aumentar PORTBbits.RB0  //botón para aumentar el contador
#define disminuir PORTBbits.RB1 //botón para disminuir el contador
uint8_t count;  //contador de 8 bits


//*****************************************************************************
//Declaración de entradas, salidas y limpieza de puertos
//*****************************************************************************
void setup (void) {
    ANSEL = 1; //Entrada analógica
    ANSELH = 1; //Entrada analógica
    TRISB = 1; //Puerto de botones para el contador
    INTCON = 0b11101000; /*Activación de Global Interrupt Enable, Peripherial
                          Interrupt E.,,Timer0 Overflow Interrupt E.,
                          PortB interrupt on change*/
    TRISD = 0; //Puerto de los led del contador
    TRISE = 0; //Puerto de la alarma
    TRISA = 0; //Puerto del ADC y salidas a transistores
    //limpieza de puertos
    PORTB = 0;
    PORTD = 0;
    PORTE = 0;
    PORTA = 0;


}

//*****************************************************************************
//Interrupciones
//*****************************************************************************



void main(void) {
    setup ();
    count = 0; //condición inicial de los leds, todos apagados
    
    while (1){
        PORTD = count;
    }
}
