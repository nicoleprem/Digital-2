//Misma librería que en lab3
#ifndef UART
#define	UART

#include <xc.h> // include processor files - each processor file is guarded.  

//Write, read e init

void INIT_UART (void);
void write (char *entrada); //puntero
void read (void); 


#endif	/* XC_HEADER_TEMPLATE_H */