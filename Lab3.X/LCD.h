

// This is a guard condition so that contents of this file are not included
// more than once.  
//Funciones obtenidas de https://electrosome.com/lcd-pic-mplab-xc8/
#ifndef LCD
#define	LCD

#include <xc.h> // include processor files - each processor file is guarded.  
#define _XTAL_FREQ 8000000

void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear(void);
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init(void);
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Shift_Right(void);
void Lcd_Shift_Left(void);


#endif	/* XC_HEADER_TEMPLATE_H */

