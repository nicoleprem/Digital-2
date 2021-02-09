/*
 * File:   ADC.c
 * Author: User
 *
 * Created on 8 de febrero de 2021, 12:41 PM
 */


#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 8000000
uint8_t banderaADC;


uint8_t AADC (uint8_t banderaADC, uint8_t Num_Pot) {
    uint8_t pot;
    ADCON1bits.ADFM = 0;
    INTCON = 0b11101000; 
    //ANSEL = 0b00000011;
   
    
    PIE1bits.ADIE = 1; //Habilitar ADC interrupt enable 
    PIR1bits.ADIF = 0; //ADC interrupt flag
    if (banderaADC == 1 && Num_Pot ==1){
         ADCON0 = 0b01000001; //Activar canal AN0
        __delay_us(20); //Delay para volver a hacer la conversion
        ADCON0bits.GO = 1; //Se empieza a hacer la conversión
        banderaADC = 0;
        pot=1;
    } else if (banderaADC==1 && Num_Pot ==0){
        ADCON0 = 0b01000101; //Activar canal AN1
        __delay_us(20); //Delay para volver a hacer la conversion
        ADCON0bits.GO = 1; //Se empieza a hacer la conversión
        banderaADC = 0;
        pot=0;
    }
    return(pot);
}