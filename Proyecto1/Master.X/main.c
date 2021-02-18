/*
 * File:   newmain.c
 * Author: User
 *
 * Created on 17 de febrero de 2021, 10:13 PM
 */

//*****************************************************************************
//Configuración de palabra
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
#include <stdint.h>
#include <stdio.h> //Librería para usar sprintf
#include "LCD.h"
#include "UART.h"
#define _XTAL_FREQ 8000000

//*****************************************************************************
//Variables
//*****************************************************************************
uint8_t banderaADC = 1; //bandera del ADC
uint8_t adc;
uint8_t mensaje;
char s[20];


//*****************************************************************************
//Declaración de entradas, salidas y limpieza de puertos
//*****************************************************************************
void setup(void) {
    ANSEL = 0b00000011; //Entrada analógica
    //ANSELH = 0; //Entrada analogicca
    TRISB = 0b00000000; //Puerto para la LCD (D0-D7)
    TRISD = 0b00000000; //Puerto para la LCD (RS y E)
    //limpieza de puertos
    PORTB = 0;
    PORTD = 0;
    //PORTA = 0;
}

void main(void) {
    //************************************************************************
    //Configuración del PIC como master
    //************************************************************************
    SSPCONbits.SSPEN == 1;
    SSPSTATbits.SMP == 0;
    
    unsigned int a;
    setup();
    INIT_UART();
    read();
    Lcd_Init();
    Lcd_Clear();
    while (1) {
        
        //Comienzo de la impresión de S1 y S2
        //Lcd_Clear();       
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("S1:   S2:    S3:"); //Primera fila
    }
}
