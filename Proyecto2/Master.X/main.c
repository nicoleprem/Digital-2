/*
 * File:   main.c
 * Author: User
 *
 * Created on 3 de marzo de 2021, 10:13 AM
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h> //Librería para usar sprintf
#include "I2C.h"
#include "LM75.h"
#include "UART.h"
#define _XTAL_FREQ 4000000
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

/* 
 * File:   main.c
 * Author: Chisanga
 *
 * Created on 06 May 2020, 11:33 AM
 */

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
//#include "Lcd4.h"
//------------------------------------------------------------------------------
char out[15] = {0};
//------------------------------------------------------------------------------
void setup (void);
void setup(void){
    TRISB = 0;
    PORTB = 0;
    
}
void main(void) 
{
  LM75_init();
  //LCD_init();
  setup ();
  
  while(1)
  {
    //sprintf( out,"Tempr:%3.2fC",LM75_read(TEMPERATURE_ADDRESS) );
    //LCD_string(0,0,out);
    PORTB = LM75_read(TEMPERATURE_ADDRESS);
    __delay_ms(1000);
    //LCD_command(clear);
  }
}
//------------------------------------------------------------------------------