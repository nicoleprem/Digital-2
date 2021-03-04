
#ifndef LM75
#define	LM75

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>
//------------------------------------------------------------------------------
//uint8_t  LM75_ADDRESS = 0x90;     // Address + Read bit 10010000
//unsigned char  TEMPERATURE_ADDRESS = 0x00;
//uint8_t  CONFIGURATION_ADDRESS = 0x01;
//#define  THYST_ADDRESS            0x02     
//#define  TOS_ADDRESS              0x03
#define  FRACTION_FLAG = 0x0080   // 0.5 Bit Flag
//------------------------------------------------------------------------------
void  LM75_init(void);
float LM75_read(char regAddress);
void  LM75_setConfig(char data);
char  LM75_readConfig(void);
void  LM75_set(char regAddress, int data);
float toFloat(signed int tempr);
//------------------------------------------------------------------------------


#endif	/* XC_HEADER_TEMPLATE_H */

