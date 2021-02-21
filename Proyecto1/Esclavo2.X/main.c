/*
 * File:   main.c
 * Author: User
 *
 * Created on 18 de febrero de 2021, 01:58 PM
 */

//******************************************************************************
// PALABRA DE CONFIGURACIÓN
//******************************************************************************

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config MCLRE = OFF      
#pragma config CP = OFF         
#pragma config CPD = OFF        
#pragma config BOREN = OFF      
#pragma config IESO = OFF       
#pragma config FCMEN = OFF      
#pragma config LVP = OFF        

// CONFIG2
#pragma config BOR4V = BOR40V   
#pragma config WRT = OFF        

#include <xc.h>
#include <stdint.h>
#include "SPI.h"
//*****************************************************************************
//Variables
//*****************************************************************************
#define aumentar PORTBbits.RB0  //botón para aumentar el contador
#define disminuir PORTBbits.RB1 //botón para disminuir el contador
#define _XTAL_FREQ 8000000

uint8_t count; //contador de 8 bits
uint8_t flag;
uint8_t esclavo1;

//*****************************************************************************
//Prototipos de funciones
//*****************************************************************************
void setup(void);
void __interrupt() ISR(void);
//*****************************************************************************
//Declaración de entradas, salidas y limpieza de puertos
//*****************************************************************************

void setup(void) {
    TRISAbits.TRISA5 = 1;
    TRISB = 0b11000011; //Puerto de botones para el contador
    INTCON = 0xE8; /*Activación de Global Interrupt Enable, Peripherial
                          Interrupt E.,,Timer0 Overflow Interrupt E.,
                          PortB interrupt on change*/
    TRISD = 0b00000000; //Puerto de los led del contador
   // TRISC = 0b00011000;
    //limpieza de puertos
    PORTB = 0;
    PORTD = 0;
    //bits de interrupciones
    IOCBbits.IOCB6 = 1; //boton 1
    IOCBbits.IOCB7 = 1; //boton 2
    flag = 0;
    //Bits de comunicación SPI
    SSPIF = 0;
    PORTAbits.RA5 = 1;
    SSPIE = 1;
    INTCON = 0b11101000; //se configuran las interrupciones GIE, PIE, T0IE y RBIE
    TRISCbits.TRISC3 = 0;
}
//*****************************************************************************
//Interrupciones
//*****************************************************************************

void __interrupt() ISR(void) {
    //Interrupción del contador
    if (INTCONbits.RBIF == 1) {//verificamos si fue interrupt on change
        if (PORTBbits.RB6 == 0) {//antirebote aumentar
            while (flag == 0) {
                if (PORTBbits.RB6 == 1) {
                    flag = 1;
                }
            }
            flag = 0;
            count++;

        } else if (PORTBbits.RB7 == 0) { //antirebote disminuir
            while (flag == 0) {
                if (PORTBbits.RB7 == 1) {
                    flag = 1;
                }
            }
            flag = 0;
            count--;

        }
        
        //Interrupción SPI
        if (PIR1bits.SSPIF == 1){ //&& SSPSTATbits.BF == 1) {
            esclavo1 = spiRead();
            spiWrite(count);
            PIR1bits.SSPIF = 0;
        }
    }
    INTCONbits.RBIF = 0; //apagamos la bandera de interrupt on change
}

        

void main(void) {
    setup();
    //count = 0;
    esclavo1 = 0;
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    while (1) {
        //        __delay_ms(500);
        PORTD = count;

    }

}
