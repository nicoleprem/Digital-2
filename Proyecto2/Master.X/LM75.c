/*
 * File:   LM75.c
 * Author: User
 *
 * Created on 3 de marzo de 2021, 11:44 AM
 */


#include <xc.h>
#include "LM75.h"
#include "I2C.h"

void LM75_init()
{
  I2C_Master_Init(100000);   //Start at 100Kb/s
  
  //For Thermostat functions ONLY... can be left out if so wished and device will still read Tempr
 // LM75_set(TOS_ADDRESS,0x2380);     //Over Temperature Threshold Activate - I set it to 35.50C
  //LM75_set(THYST_ADDRESS,0x1E80);   //Over Temperature Threshold deactivate - I set it to 30.50C
}
//------------------------------------------------------------------------------
float LM75_read(char regAddress)
{
//  signed int MSB,LSB;
  
  
  I2C_Master_Start();
  
  I2C_Master_Write(0b10010000);        //1001000 + 0 = Write             
  I2C_Master_Write(regAddress);        
  //I2C_restart();                           
  I2C_Master_Write(0b10010001);        //1001000 + 1 = Read   
//  MSB = I2C_Master_Read(1); //ack
//  LSB = I2C_Master_Read(0); //nack
  
  I2C_Master_Stop();
  __delay_ms(200);
  
//  return toFloat((MSB << 8) + LSB);
  //__delay_ms(200);
}
//------------------------------------------------------------------------------
void LM75_setConfig(char data)
{  
  I2C_Master_Start();                      
  
  I2C_Master_Write(0x90);                       
  I2C_Master_Write(0x01);              
  I2C_Master_Write(data);       
  
  I2C_Master_Stop();
}
//------------------------------------------------------------------------------
//char LM75_readConfig()
//{  
//  I2C_start();                      
//  
//  I2C_write(0x90 + 0);        // 0 = Write               
//  I2C_write(0x01);        
//  I2C_restart();                           
//  I2C_write(0x90 + 1);        // 1 = Read   
//  char config = I2C_read(NACK);
//  
//  I2C_stop();
//  
//  return config;
//}