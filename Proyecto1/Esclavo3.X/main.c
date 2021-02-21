/*
 * File:   main.c
 * Author: User
 *
 * Created on 18 de febrero de 2021, 04:17 PM
 */


#include <xc.h>
#include "LM35.h"
#include "SPI.h"
#define _XTAL_FREQ 8000000
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
uint8_t banderaLM;
uint8_t lmm;
uint8_t color; //variable para almacenar el valor del voltaje y devolver color
uint8_t esclavo3;
uint8_t conversor;


//*****************************************************************************
//Prototipos de funciones
//*****************************************************************************
void __interrupt() ISR(void);
void setup(void);

//*****************************************************************************
//Declaración de entradas, salidas y limpieza de puertos
//*****************************************************************************

void setup(void) {
    TRISAbits.TRISA5 = 1;
    TRISD = 0b00000000;
    TRISB = 0b00000001;
    PORTB = 0;
    PORTD = 0;
    SSPIF = 0;
    PORTAbits.RA5 = 1;
    SSPIE = 1;
    INTCON = 0b11101000; //se configuran las interrupciones GIE, PIE, T0IE y RBIE

}

//*****************************************************************************
//Interrupciones
//*****************************************************************************

void __interrupt() ISR(void) {
    //Interrupcuón del ADC
    if (PIR1bits.ADIF == 1) {
        banderaLM = 1;
        lmm = ADRESH;
        //PORTD = lmm;
        PIR1bits.ADIF = 0; //Se apaga bandera ADC
    }
    //Interrupción del SPI
    if (PIR1bits.SSPIF == 1 && SSPSTATbits.BF == 1) {
        esclavo3 = spiRead();
        spiWrite(lmm);
        PIR1bits.SSPIF = 0;
    }
}

void main(void) {
    setup();
    banderaLM = 1;
    esclavo3 = 0;
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    while (1) {
        LM(banderaLM);
        conversor = 1.95 * lmm;
        if (conversor < 21) {
            PORTDbits.RD2 = 1; //encender color verde
            PORTDbits.RD1 = 0;
            PORTDbits.RD0 = 0;
            __delay_ms(500);
        }
        else if (conversor > 21 && conversor < 36) {
            PORTDbits.RD2 = 0;
            PORTDbits.RD1 = 1; //encender color amarillo
            PORTDbits.RD0 = 0;
            __delay_ms(500);
        } else if (conversor > 36) {
            PORTDbits.RD2 = 0;
            PORTDbits.RD1 = 0;
            PORTDbits.RD0 = 1; //encender color verde
            __delay_ms(500);
        }

    }
}
