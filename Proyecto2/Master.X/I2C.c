
#define _XTAL_FREQ 4000000

#include <xc.h> // include processor files - each processor file is guarded.  
#include "I2C.h"
#include <stdint.h>
//---------------------------DIRECTION------------------------------------------
#define SCK_dir TRISCbits.TRISC3			//Clock pin direction
#define SDA_dir TRISCbits.TRISC4			//Data pin direction

//--------------Function Purpose: Configure I2C module--------------------------
void I2C_init(unsigned char speed)
{
  SCK_dir = 1;		// SCK pins input
  SDA_dir = 1;		// Make SDA and 

  SSPADD  = ((_XTAL_FREQ/4000)/speed) - 1;
  SSPSTAT = 0x80;		// Slew Rate control is disabled 0x80=10000000
  SSPCON  = 0x28;		// Select and enable I2C in master mode 0x28=00101000
}
//---------------Function Purpose: I2C_Start sends start bit sequence-----------
void I2C_start(void)
{
  SSPCON2 = 00000001;			// Send start bit, SSPCON2 = 00000001
  while(!PIR1bits.SSPIF);		// Wait for it to complete sspif=pir1
  PIR1bits.SSPIF = 0;			// Clear the flag bit
}
//---------------Function Purpose: I2C_ReStart sends start bit sequence---------
void I2C_restart(void) //No la usan en presentación
{
  SSPCON2bits.RSEN = 1;			// Send Restart bit en SDA y SCL pins
  while(!PIR1bits.SSPIF);		// Wait for it to complete sspif=pir1
  PIR1bits.SSPIF = 0;			// Clear the flag bit
}
//---------------Function : I2C_Stop sends stop bit sequence--------------------
void I2C_stop(void)
{
  SSPCON2bits.PEN = 1;			// Send stop bit, SSPCON2=00000100
  while(!PIR1bits.SSPIF);		// Wait for it to complete
  PIR1bits.SSPIF = 0;			// Clear the flag bit
}
//---------------Function : Send ACK/NACK bit sequence--------------------------
void I2C_ack(char acknowledge)
{
  SSPCON2bits.ACKDT = acknowledge;	        // 0 means ACK, 1 means NACK
  SSPCON2bits.ACKEN = 1;			// Send ACKDT value
  while(!PIR1bits.SSPIF);		// Wait for it to complete
  PIR1bits.SSPIF = 0;			// Clear the flag bit
}
//---------------Function Purpose: I2C_Write_Byte transfers one byte------------
unsigned char I2C_write(unsigned char data)
{
  SSPBUF = data;		// Send Byte value
  while(!PIR1bits.SSPIF);		// Wait for it to complete
  PIR1bits.SSPIF = 0;			// Clear the flag bit

  return SSPCON2bits.ACKSTAT;		// Return ACK/NACK from slave
}
//----------------Function Purpose: I2C_Read_Byte reads one byte----------------
unsigned char I2C_read(char acknowledge)
{
   SSPCON2bits.RCEN = 1;			// Enable reception of 8 bits sspcon2=00010000 enables receive mode
   while(!PIR1bits.SSPIF);		// Wait for it to complete
   PIR1bits.SSPIF = 0;			// Clear the flag bit
   I2C_ack(acknowledge);

   return SSPBUF;		// Return received byte
}
//------------------------------------------------------------------------------
/*OR R/nW bit with SEN, RSEN, PEN, RCEN or ACKEN will indicate if the MSSP is in
 * Idle mode*/
//char I2C_busy()
//{
//  char isBusy = (SSPCON2  & 0x1F) | R_W;
//
//  return isBusy;
//}



