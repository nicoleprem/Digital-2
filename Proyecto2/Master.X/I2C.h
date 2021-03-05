#ifndef I2C_H
#define I2C_H
//------------------------------------------------------------------------------
#include "I2C_Pins.h"
//------------------------------------------------------------------------------
#define  ACK  0
#define  NACK 1
#define _XTAL_FREQ 4000000
//--------------Function Purpose: Configure I2C module--------------------------
void I2C_init(unsigned char speed)
{
  SCK_dir = 1;		// SCK pins input
  SDA_dir = 1;		// Make SDA and

  SSPADD  = ((_XTAL_FREQ/4000)/speed) - 1;
  SSPSTAT = 0x80;		// Slew Rate control is disabled
  SSPCON  = 0x28;		// Select and enable I2C in master mode
}
//---------------Function Purpose: I2C_Start sends start bit sequence-----------
void I2C_start(void)
{
  SEN = 1;			// Send start bit
  while(!SSPIF);		// Wait for it to complete
  SSPIF = 0;			// Clear the flag bit
}
//---------------Function Purpose: I2C_ReStart sends start bit sequence---------
void I2C_restart(void)
{
  RSEN = 1;			// Send Restart bit
  while(!SSPIF);		// Wait for it to complete
  SSPIF = 0;			// Clear the flag bit
}
//---------------Function : I2C_Stop sends stop bit sequence--------------------
void I2C_stop(void)
{
  PEN = 1;			// Send stop bit
  while(!SSPIF);		// Wait for it to complete
  SSPIF = 0;			// Clear the flag bit
}
//---------------Function : Send ACK/NACK bit sequence--------------------------
void I2C_ack(char acknowledge)
{
  ACKDT = acknowledge;	        // 0 means ACK, 1 means NACK
  ACKEN = 1;			// Send ACKDT value
  while(!SSPIF);		// Wait for it to complete
  SSPIF = 0;			// Clear the flag bit
}
//---------------Function Purpose: I2C_Write_Byte transfers one byte------------
unsigned char I2C_write(unsigned char data)
{
  SSPBUF = data;		// Send Byte value
  while(!SSPIF);		// Wait for it to complete
  SSPIF = 0;			// Clear the flag bit

  return ACKSTAT;		// Return ACK/NACK from slave
}
//----------------Function Purpose: I2C_Read_Byte reads one byte----------------
unsigned char I2C_read(char acknowledge)
{
   RCEN = 1;			// Enable reception of 8 bits
   while(!SSPIF);		// Wait for it to complete
   SSPIF = 0;			// Clear the flag bit
   I2C_ack(acknowledge);

   return SSPBUF;		// Return received byte
}
//------------------------------------------------------------------------------
/*OR R/nW bit with SEN, RSEN, PEN, RCEN or ACKEN will indicate if the MSSP is in
 * Idle mode*/
char I2C_busy()
{
  char isBusy = (SSPCON2  & 0x1F) | R_W;

  return isBusy;
}
//------------------------------------------------------------------------------
#endif