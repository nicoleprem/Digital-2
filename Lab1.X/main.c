/*
 * File:   main.c
 * Author: Nicole Prem
 *
 * Created on 21 de enero de 2021, 06:39 PM
 */

//*****************************************************************************
//Configuración de la palabra
//*****************************************************************************
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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
//Prototipos de funciones
//*****************************************************************************
void setup (void);
void semaforo (void); 

//*****************************************************************************
//Variables
//*****************************************************************************
#define LEDR PORTEbits.RE0 //Led Rojo
#define LEDA PORTEbits.RE1 //Led Amarillo
#define LEDV PORTEbits.RE2 //Led verde
#define _XTAL_FREQ 8000000 //Frecuencia de eintrada



#include <xc.h>

void main(void) {
    setup ();
    while (1){
        semaforo ();
            
    
    }

}


void setup (void) {
    ANSEL = 0;
    ANSELH = 0;
    TRISE = 0; //Puerto de los LEDS          
}

//Rutina para que se haga el inicio de la carrera con semaforo
void semaforo (void) {
        LEDR=1;
        LEDA=0;
        LEDV=0;
        __delay_ms(500);
        
        LEDR=0;
        LEDA=1;
        LEDV=0;
        __delay_ms(500);
        
        LEDR=0;
        LEDA=0;
        LEDV=1;
        __delay_ms(500);

}