/*
 * File:   ADC.c
 * Author: User
 *
 * Created on 4 de febrero de 2021, 01:39 AM
 */


#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 8000000
uint8_t banderaADC;


void AADC (uint8_t banderaADC) {
    ADCON1bits.ADFM = 0;
    INTCON = 0b11101000; 
    ANSEL = 0b00000001;
    ADCON0 = 0b01000001;
    PIE1bits.ADIE = 1; //Habilitar ADC interrupt enable 
    PIR1bits.ADIF = 0; //ADC interrupt flag
    if (banderaADC == 1){
        __delay_us(20); //Delay para volver a hacer la conversion
        ADCON0bits.GO = 1; //Se empieza a hacer la conversión
        banderaADC = 0;
    
    
    }
    
    
    
}
