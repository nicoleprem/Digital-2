/*
 * File:   LCD.c
 * Author: https://electrosome.com/lcd-pic-mplab-xc8/ Librer�a modificada para
 *8 bits
 * Created on 4 de febrero de 2021, 06:20 PM
 */
//Librer�a del Lab 2

#include<stdint.h>
#include <xc.h>
#define _XTAL_FREQ 8000000
#define RS PORTEbits.RE0
#define EN PORTEbits.RE1
//LCD Functions Developed by electroSome

void Lcd_Port(char a) {
    PORTB = a; //se carga a al puerto D completo
}

void Lcd_Cmd(char a) {
    RS = 0; // => RS = 0 se mandan comandos
    Lcd_Port(a);
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

void Lcd_Clear(void) {
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b) {
    char temp;
    if (a == 1) {
        temp = 0x80 + b - 1; //direcci�n de posicion de DDRAM al puerto
        Lcd_Cmd(temp);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        Lcd_Cmd(temp);
    }
}

void Lcd_Init(void) {
    Lcd_Port(0x00);
    __delay_ms(20);
    Lcd_Cmd(0x3F); //0b00111111 valores de iniciaci�n de LCD
    __delay_ms(10);
    Lcd_Cmd(0x3F);//0b00111111
    __delay_us(200);
    Lcd_Cmd(0x3F);//0b00111111
    /////////////////////////////////////////////////////
    Lcd_Cmd(0x38);//0b00111000 modo de funcionamiento
    Lcd_Cmd(0x0C);//0b00001100 encender visualizador
    Lcd_Cmd(0x06);//0b00000110 modo de entrada
}

void Lcd_Write_Char(char a) {
    RS = 1; // => RS = 1 envio de datos
    Lcd_Port(a); //cargando los datos al puerto
    EN = 1;
    __delay_us(40); //transici�n EN:1->0 para indicar que se mandan datos/comandos
    EN = 0;
    __delay_us(40);
}

void Lcd_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++) //ciclo cargar direcciones/valores a LCD
        Lcd_Write_Char(a[i]);
}