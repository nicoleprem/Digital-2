/*
 * File:   main.c
 * Author: Nicole Prem 18337
 * LAB 3
 *
 * Created on 4 de febrero de 2021, 06:00 PM
 */

//*****************************************************************************
//Configuración de palabra
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
#include <stdio.h> //Librería para usar sprintf
#include "LCD.h"
#include "ADC.h"
#include "UART.h"
#define _XTAL_FREQ 8000000

//*****************************************************************************
//Variables
//*****************************************************************************
uint8_t S1; //Variable para guardar valor del sensor 1
uint8_t S2; //Variable para guardar valor del sensor 1
uint8_t banderaADC = 1; //bandera del ADC
uint8_t adc;
uint8_t pot; //bandera para determinar cuál valor de los pots se mostrará
uint8_t Num_Pot = 1; //
uint8_t mensaje;
uint8_t contador = 0;

double conversor;
char s[20];



//*****************************************************************************
//Declaración de entradas, salidas y limpieza de puertos
//*****************************************************************************

void setup(void) {
    ANSEL = 0b00000011; //Entrada analógica
    //ANSELH = 0; //Entrada analogicca
    TRISB = 0b00000000;
    TRISD = 0b00000000;
    //limpieza de puertos
    PORTB = 0;
    PORTD = 0;
    //PORTA = 0;
   }

//*****************************************************************************
//Interrupciones
//*****************************************************************************

void __interrupt() ISR(void) {
    //Interrupción UART - Recepción
    if (PIR1bits.RCIF == 1) {
        if (RCSTAbits.OERR == 1) { //Verificar si fue un error
            RCSTAbits.CREN = 0;
            __delay_us(200);
        } else {
            mensaje = RCREG; //Se carga el + o el -
        }
    }


    //Intrerrupción del ADC
    if (PIR1bits.ADIF == 1) {
        if (pot == 1) { //Para imprimir el valor del S1
            S1 = ADRESH;
            Num_Pot = 0;
            banderaADC = 1;
        } else if (pot == 0) { //Para imprimir el valor del S2
            S2 = ADRESH;
            Num_Pot = 1;
            banderaADC = 1;
        }
        PIR1bits.ADIF = 0;
    }

}

void main(void) {
    unsigned int a;
    setup();
    INIT_UART();
    read();
    Lcd_Init();
    Lcd_Clear();
    while (1) {
        pot = AADC(banderaADC, Num_Pot);
        //Comienzo de la impresión de S1 y S2
        //Lcd_Clear();       
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("S1:   S2:    S3:"); //Primera fila
        conversor = 0.0195 * S1; //Conversión de binario a decimal (5*S1)/2^8
        Lcd_Set_Cursor(2, 1); //Posición S1
        sprintf(s, "%3.2fV", conversor); //Valor S1
        Lcd_Write_String(s); //Imprimir S1
        conversor = 0.0195 * S2;
        Lcd_Set_Cursor(2, 7); //Pisición S2
        sprintf(s, "%3.2fV", conversor); //Valor S2
        Lcd_Write_String(s);
        //Comienzo de la impresión contador
        Lcd_Set_Cursor(2, 14); //Posición S3
        sprintf(s, "%d", contador); //Valor contador
        Lcd_Write_String(s);
        write(s); //mandar el valor y verificar que se mande el dato
        __delay_ms(250);
        if (mensaje == 0x2B) {
            contador++;
            mensaje = 0;
        } else if (mensaje == 0x2D) {
            contador--;
            mensaje = 0;
        }
        if (contador >=0 && contador <10){
            Lcd_Clear();
        }



    }
}