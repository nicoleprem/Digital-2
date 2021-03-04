//Librería hecha en base a https://libstock.mikroe.com/projects/view/3755/lm75-i2c-temperature-sensor
//Creada por Bugs Bensce

#ifndef LM75
#define	LM75

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>

//#define  FRACTION_FLAG = 0x0080   // 0.5 Bit Flag
//------------------------------------------------------------------------------
void  LM75_init(void);
float LM75_read(char regAddress);
void  LM75_setConfig(char data);
char  LM75_readConfig(void);
void  LM75_set(char regAddress, int data);
float toFloat(signed int tempr);
//------------------------------------------------------------------------------


#endif	/* XC_HEADER_TEMPLATE_H */
