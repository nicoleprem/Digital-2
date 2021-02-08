/*
 * File:   LCD.c
 * Author: https://electrosome.com/lcd-pic-mplab-xc8/
 *
 * Created on 4 de febrero de 2021, 06:20 PM
 */


#include <xc.h>
#include "LCD.h"
#define _XTAL_FREQ 8000000
    #define RS PORTDbits.RD2
    #define EN PORTDbits.RD3
    #define C0 PORTCbits.RC0
    #define C1 PORTCbits.RC1
    #define C2 PORTCbits.RC2
    #define C3 PORTCbits.RC3
    #define C4 PORTCbits.RC4
    #define C5 PORTCbits.RC5
    #define C6 PORTCbits.RC6
    #define C7 PORTCbits.RC7
//#define RS PORTDbits.RD2
//#define EN RD3
//#define C0 RC0
//#define C1 RC1
//#define C2 RC2
//#define C3 RC3
//#define C4 RC4
//#define C5 RC5
//#define C6 RC6
//#define C7 RC7
//void setup(void) {
//    ANSEL = 0; //Entrada analógica
//    ANSELH = 0; //Entrada analógica
//    TRISC = 0;
//    TRISD = 0;
//    //limpieza de puertos
//    PORTC = 0;
//    PORTD = 0;
//    PORTA = 0;
//
//}
void Lcd_Port(char a)
{
    
    PORTC = a;
    

}
void Lcd_Cmd(char a)
{
	RS = 0;             // => RS = 0
	Lcd_Port(a);
	EN  = 1;             // => E = 1
        __delay_ms(4);
        EN  = 0;             // => E = 0
}

void Lcd_Clear(void)
{
	Lcd_Cmd(0);
	Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b)
{
	char temp,z,y;
	if(a == 1)
	{
	  temp = 0x80 + b - 1;
//		z = temp>>4;
//		y = temp & 0x0F;
//		Lcd_Cmd(z);
//		Lcd_Cmd(y);
      Lcd_Cmd(temp);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b - 1;
//		z = temp>>4;
//		y = temp & 0x0F;
//		Lcd_Cmd(z);
//		Lcd_Cmd(y);
        Lcd_Cmd(temp);
	}
}

void Lcd_Init(void)
{
  Lcd_Port(0x00);
   __delay_ms(20);
  Lcd_Cmd(0x3F);
	__delay_ms(10);
  Lcd_Cmd(0x3F);
	__delay_us(200);
  Lcd_Cmd(0x3F);
  //  __delay_us(200);
  Lcd_Cmd (0x32); //Set interface lenght 0b00000010
  Lcd_Cmd (0x38); // 00111000
  Lcd_Cmd (0x0C);// 00001100
  Lcd_Cmd (0x06); //Set cursor move direction últimos 2 no estoy segura 0b00000110
//  Lcd_Cmd (0b00000110); //Enable desplay/cursor últimos 3 no estoy segura
    
  /////////////////////////////////////////////////////
//  Lcd_Cmd(0x038);
//  Lcd_Cmd(0x02);
//  Lcd_Cmd(0x08);
//  Lcd_Cmd(0x00);
//  Lcd_Cmd(0x0C);
//  Lcd_Cmd(0x00);
//  Lcd_Cmd(0x06);
}

void Lcd_Write_Char(char a)
{
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RS = 1;             // => RS = 1
   Lcd_Port(a);             //Data transfer
   EN = 1;
   __delay_us(40);
   EN = 0;
   //Lcd_Port(temp);
   //EN = 1;
   __delay_us(40);
   //EN = 0;
}

void Lcd_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right(void)
{
	Lcd_Cmd(0x01);
	Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left(void)
{
	Lcd_Cmd(0x01);
	Lcd_Cmd(0x08);
}
