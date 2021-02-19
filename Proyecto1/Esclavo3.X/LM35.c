/*
 * File:   LM35.c
 * Author: User
 *
 * Created on 18 de febrero de 2021, 04:19 PM
 */


#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 8000000






uint8_t banderaLM;


void LM (uint8_t banderaLM) {
    ADCON1bits.ADFM = 0; //Right justified
    INTCON = 0b11101000; //Habilitado: Interrupciones, interrupciones 
    //periféricas, interrupción del Timer0, interrupciones PortB
    ANSEL = 0b00000001; //Entrada analógica ANS0
    ADCON0 = 0b01000001; //Fosc/8 y GO/DONE habilitado
    PIE1bits.ADIE = 1; //Habilitar ADC interrupt enable 
    PIR1bits.ADIF = 0; //ADC interrupt flag
    if (banderaLM == 1){
        __delay_us(20); //Delay para volver a hacer la conversion
        ADCON0bits.GO = 1; //Se empieza a hacer la conversión
        banderaLM = 0;
       
    }
}
