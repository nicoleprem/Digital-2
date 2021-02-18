/*
 * File:   main.c
 * Author: User
 *
 * Created on 18 de febrero de 2021, 01:58 PM
 */


#include <xc.h>
#include <stdint.h>
//*****************************************************************************
//Variables
//*****************************************************************************
#define aumentar PORTBbits.RB0  //botón para aumentar el contador
#define disminuir PORTBbits.RB1 //botón para disminuir el contador
#define XTAL_FREQ 8000000

uint8_t count; //contador de 8 bits
//*****************************************************************************
//Declaración de entradas, salidas y limpieza de puertos
//*****************************************************************************
void setup (void){
    TRISB = 0x03; //Puerto de botones para el contador
    INTCON = 0xE8; /*Activación de Global Interrupt Enable, Peripherial
                          Interrupt E.,,Timer0 Overflow Interrupt E.,
                          PortB interrupt on change*/
    TRISD = 0; //Puerto de los led del contador
    //limpieza de puertos
    PORTB = 0;
    PORTD = 0;
    //bits de interrupciones
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
//*****************************************************************************
//Interrupciones
//*****************************************************************************
void __interrupt() ISR(void) {
    //Interrupción de los botones para incrementar o disminuir contador
    if (INTCONbits.RBIF == 1) {
        if (aumentar == 0) {
            count++; //Si se presiona el botón aumentar, el contador suma
        } else if (disminuir == 0) {
            count--;
        }
        INTCONbits.RBIF = 0;
    }

}
void main(void) {
    return;
}
