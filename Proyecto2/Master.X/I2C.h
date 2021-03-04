
#ifndef I2C
#define	I2C
//-------------------------Define i2c pins--------------------------------------
#define SCK PORTCbits.RC3
#define SDA PORTCbits.RC4

//---------------------------DIRECTION------------------------------------------
#define SCK_dir TRISCbits.TRISC3			//Clock pin direction
#define SDA_dir TRISCbits.TRISC4			//Data pin direction

//------------------------------------------------------------------------------
#include <xc.h>
char  ACK = 0;
char  NACK = 1;



void I2C_init(uint8_t speed);

void I2C_start(void);

void I2C_restart(void);

void I2C_stop(void);

void I2C_ack(char acknowledge);

unsigned char I2C_write(unsigned char data);

unsigned char I2C_read(char acknowledge);

char I2C_busy(void);

#endif

