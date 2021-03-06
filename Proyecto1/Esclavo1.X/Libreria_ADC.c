/*
 * File:   Libreria_ADC.c
 * Author: User
 *
 * Created on 15 de febrero de 2021, 03:33 PM
 */

//Misma libería del lab 2 con modificación de pines
#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 8000000
uint8_t banderaADC;


void AADC (uint8_t banderaADC) {
    ADCON1bits.ADFM = 0; //left justified
    INTCON = 0b11101000; //Habilitado: Interrupciones, interrupciones 
    //periféricas, interrupción del Timer0, interrupciones PortB
    ANSEL = 0b00001100; //Entrada analógica AN12
    ADCON0 = 0b01110001; //Fosc/8 y GO/DONE habilitado
    PIE1bits.ADIE = 1; //Habilitar ADC interrupt enable 
    PIR1bits.ADIF = 0; //ADC interrupt flag
    if (banderaADC == 1){
        __delay_us(20); //Delay para volver a hacer la conversion
        ADCON0bits.GO = 1; //Se empieza a hacer la conversión
        banderaADC = 0;
    
    
    }
    
    
    
}
