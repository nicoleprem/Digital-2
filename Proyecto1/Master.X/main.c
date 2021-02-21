/*
 * File:   newmain.c
 * Author: User
 *
 * Created on 17 de febrero de 2021, 10:13 PM
 */

//*****************************************************************************
//Configuraci�n de palabra
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
#include <stdio.h> //Librer�a para usar sprintf
#include "LCD.h"
#include "UART.h"
#include "SPI.h"
#define _XTAL_FREQ 8000000

#include <xc.h>
#include <stdint.h>
#include <stdio.h> //Librer�a para usar sprintf
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
char s[20];
char l[20];
char c[20];
unsigned char CC;
float x;
float p;
float n;

//*****************************************************************************
//Prototipo de funciones
//*****************************************************************************
void __interrupt() ISR(void);
//*****************************************************************************
//Declaraci�n de entradas, salidas y limpieza de puertos
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
//*****************************************************************************
//Interrupciones
//*****************************************************************************

//void __interrupt() ISR(void) {
//    //Interrupci�n UART - Recepci�n
//    if (PIR1bits.RCIF == 1) {
//        if (RCSTAbits.OERR == 1) { //Verificar si fue un error
//            RCSTAbits.CREN = 0;
//            __delay_us(200);
//        } else {
//            mensaje = RCREG; //Se carga el + o el -
//        }
//    }
//}

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

        //Comienzo de la impresi�n de S1 y S2
        //Lcd_Clear();       
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("S1:   S2:    S3: \n"); //Primera fila
        write("S1:");
        write(s);
        write("S2:");
        write(c);
        write("S3:");
        write(l);
        write(0xA);
        x = adc * 0.0195; //ADC
        Lcd_Set_Cursor(2, 1); //Posici�n S1
        sprintf(s, "%3.2fV", x); //Valor S1
        Lcd_Write_String(s);
//        write(s);
//        write(c);
//        write(l);
//        write("\n");

        //Contador
        n = 1 * count;
        Lcd_Set_Cursor(2, 8);
        sprintf(c, "%d", count);
        Lcd_Write_String(c);
//        mensaje = c;

        //Temperatura
        p = 1.95 * lmm;
        //Lcd_Clear();
        Lcd_Set_Cursor(2, 13); //Posici�n S1
        sprintf(l, "%3.0fC", p); //Valor S1
        Lcd_Write_String(l);
//        mensaje = p;





        //ADC
        __delay_ms(1);
        PORTCbits.RC0 = 0;
        __delay_ms(1);
        SSPBUF = 0;
        adc = spiRead();
        __delay_ms(1);
        PORTCbits.RC0 = 1;
        __delay_ms(200);

        //Contador
        __delay_ms(10);
        PORTCbits.RC1 = 0;
        __delay_ms(10);
        SSPBUF = PORTD;
        count = spiRead();
        __delay_ms(1);
        PORTCbits.RC1 = 1;
        __delay_ms(200);

        //Temperatura
        __delay_ms(10);
        PORTCbits.RC2 = 0;
        __delay_ms(10);
        SSPBUF = 0;
        lmm = spiRead();
        __delay_ms(1);
        PORTCbits.RC2 = 1;
        __delay_ms(200);
        //        __delay_ms(250);

    }

}
