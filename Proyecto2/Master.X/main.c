//------------------------------------------------------------------------------
//******************************************************************************
//Configuración de la palabra
//******************************************************************************
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
#define _XTAL_FREQ 4000000
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
//------------------------------------------------------------------------------
#include "LM75.h"
#include "UART.h"
#include <pic16f887.h>
//------------------------------------------------------------------------------
char out[20];

float x;
//------------------------------------------------------------------------------
void setup (void);
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    PORTB = 0;
    //UART
    TRISC = 0b10000000; //activamos el RX como entrada
    PORTC = 0; //limpiamos puertos
    TRISD = 0b00000000; //configuramos el puerto D como salida
    PORTD = 0b00000000;
//    
}
void main(void) 
{
  
  //LCD_init();
  setup ();
  LM75_init();
  INIT_UART();
  
  while(1)
  {
    sprintf(out,"%3.0f",LM75_read(TEMPERATURE_ADDRESS));
    //LCD_string(0,0,out);
//    PORTB = LM75_read(TEMPERATURE_ADDRESS);
    __delay_ms(3000);
//    char uart = LM75_read(TEMPERATURE_ADDRESS);
    write(out);
    write(0xA);
    //LCD_command(clear);
     PORTD= 0b00000001;
        __delay_ms(1000);
  }
}
//------------------------------------------------------------------------------