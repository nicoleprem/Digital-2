/*
 * File:   main.c
 * Author: Nicole Prem
 *
 * Created on 15 de febrero de 2021, 03:32 PM
 */



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
#include <xc.h>
#include "Libreria_ADC.h"
#include "SPI.h"
#include <stdint.h>
//*****************************************************************************
//Variables
//*****************************************************************************
#define XTAL_FREQ 8000000
uint8_t banderaADC; //bandera del ADC
uint8_t adc;
uint8_t esclavo1;
void __interrupt() ISR(void);
void setup(void);
//*****************************************************************************
//Declaración de entradas, salidas y limpieza de puertos
//*****************************************************************************

void setup(void) {
    //    TRISA = 0b11111111; //puerto A configurado como input
    TRISAbits.TRISA5 = 1;
//    PORTA = 0;
    TRISC = 0b00011000;
    TRISB = 0b00000001;
    TRISD = 0b00000000;
    PORTD = 0;
    PORTB = 0;
    //Bits para comunicación SPI
    SSPIF = 0;
    PORTAbits.RA5=1;
    SSPIE = 1;
    INTCON = 0b11101000; //se configuran las interrupciones GIE, PIE, T0IE y RBIE

}

//*****************************************************************************
//Interrupciones
//*****************************************************************************

void __interrupt() ISR(void) {
    //Interrupcuón del ADC
    if (PIR1bits.ADIF == 1) {
        banderaADC = 1;
        adc = ADRESH;
        PORTD = adc;
        PIR1bits.ADIF = 0; //Se apaga bandera ADC
    }
    //Interrupción del SPI
    if (PIR1bits.SSPIF == 1 && SSPSTATbits.BF == 1) {
        esclavo1 = spiRead();
        spiWrite(adc);
        PIR1bits.SSPIF = 0;
    }
}

void main(void) {
    setup();
    banderaADC = 1;
    esclavo1 = 0;
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    while (1) {
        AADC(banderaADC);
    }
}