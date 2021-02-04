/*
 * File:   7segmentos.c
 * Author: User
 *
 * Created on 4 de febrero de 2021, 01:52 AM
 */


#include <xc.h>


void Segmentos (void) {
    OPTION_REG = 0b10000111; //Deshabilitar RPBU y prescaler de 1:256
    TMR0 = 10;
    
  
}
