/*
 * File:   UART.c
 * Author: Nicole Prem
 * Created on 9 de febrero de 2021, 09:42 PM
 */


#include <xc.h>
#define _XTAL_FREQ 8000000
void INIT_UART (void) {
    TRISC = 0b10000000;
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1;
    PIE1bits.RCIE = 1; //Habilitar interrupci�n del receptor
    INTCONbits.GIE = 1; //Habilitar interrupciones globales
    TXSTAbits.BRGH = 0; //Velocidad de transmici�n lenta
    BAUDCTLbits.BRG16 = 1; //Boundgate de 16 bits
    TXSTAbits.TXEN = 1; //Activaci�n transmisi�n
    SPBRG = 25;  //19230bps

}


void write (char *entrada){ //funci�n para el contador de 4 bits de ancho
    TXREG = entrada[0]; //bit 1
    while (TRMT == 0) {
    }
    TXREG = entrada[1]; //bit 2
    while (TRMT == 0) {
    }
    TXREG = entrada[2]; //bit 3
    while (TRMT == 0) {
    }
    TXREG = entrada[3]; //bit 4
    while (TRMT == 0) {
    }
    TXREG = 0x20;
    while (TRMT == 0) {
    }
} //puntero
void read (void) {
    RCSTAbits.CREN = 1;
    RCSTAbits.FERR = 0;
    PIE1bits.RCIE = 1;
    RCSTAbits.OERR = 0;

}