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
#include "SPI.h"
#define _XTAL_FREQ 8000000

#include <xc.h>
#include <stdint.h>
#include <stdio.h> //Librería para usar sprintf
#include "LCD.h"
#include "UART.h"
#include "SPI.h"
#define _XTAL_FREQ 8000000

//*****************************************************************************
//Variables
//*****************************************************************************
uint8_t banderaADC = 1; //bandera del ADC
uint8_t adc;
uint8_t mensaje;
uint8_t esclavo1; //variable para leer al esclavo 1
uint8_t lmm = 0;
uint8_t count;
//Variables para desplegar los valores en pantallas
char s[20];
char l[20];
char c[20];
//Variables donde se guarda el valor convertido de los ADCs
float x;
float p;
float n;

//*****************************************************************************
//Prototipo de funciones
//*****************************************************************************
void __interrupt() ISR(void);
//*****************************************************************************
//Declaración de entradas, salidas y limpieza de puertos
//*****************************************************************************

void setup(void) {
    TRISD = 0b00000000; // puerto D como salida
    TRISC = 0b10010000; //activamos el RX como entrada
    TRISE = 0b00000000;
    TRISB = 0b00000000;
    ANSEL = 0b00000011;
    PORTC = 0; //limpiamos puertos
    PORTD = 0;
    PORTE = 0;
    PORTB = 0;
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 1;

}

void main(void) {
    //    unsigned int a;
    setup();
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    INIT_UART();
    //    read();
    Lcd_Init();
    Lcd_Clear();
    //    PORTCbits.RC0 = 1;
    
    while (1) {

        
        //Configuración de lo que se mostrará en la LCD      
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("S1:   S2:    S3: \n"); //Primera fila
        //********************************************************************
        //Configuración d elo que se mostrará en la terminal virtual
        write("S1:");
        write(s);
        write("S2:");
        write(c);
        write("S3:");
        write(l);
        write(0xA);
        //*********************************************************************
        //Valor del ADC
        x = adc * 0.0195; 
        Lcd_Set_Cursor(2, 1); //Posición S1
        sprintf(s, "%3.2fV", x); //Valor S1
        Lcd_Write_String(s);

        //Valor del Contador
        Lcd_Set_Cursor(2, 8);
        sprintf(c, "%d", count);
        Lcd_Write_String(c);

        //Valor de la temperatura
        p = 1.95 * lmm;
        //Lcd_Clear();
        Lcd_Set_Cursor(2, 13); //Posición S1
        sprintf(l, "%3.0fC", p); //Valor S1
        Lcd_Write_String(l);

        
        //configuración del Slave Select
        //Select Esclavo 1
        __delay_ms(1);
        PORTCbits.RC0 = 0;
        __delay_ms(1);
        SSPBUF = 0;
        adc = spiRead();
        __delay_ms(1);
        PORTCbits.RC0 = 1;
        __delay_ms(200);

        //Select esclavo 2
        __delay_ms(10);
        PORTCbits.RC1 = 0;
        __delay_ms(10);
        SSPBUF = PORTD;
        count = spiRead();
        __delay_ms(1);
        PORTCbits.RC1 = 1;
        __delay_ms(200);

        //Select esclavo 3
        __delay_ms(10);
        PORTCbits.RC2 = 0;
        __delay_ms(10);
        SSPBUF = 0;
        lmm = spiRead();
        __delay_ms(1);
        PORTCbits.RC2 = 1;
        __delay_ms(200);

    }

}
