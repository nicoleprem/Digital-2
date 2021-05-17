//Nicole Prem 18337 Lab 7
//****************PARTE 1************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
//**************************************************************************************************************
// Variables Globales
//**************************************************************************************************************

uint32_t recibido = 0x0;
uint32_t recibido2 = 0x0;
volatile uint32_t i = 0x0;
bool verificar = 0;

int main(void)
{
    //****************PARTE 2***********************************
    //Reloj del sistema
    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //Configuración del reloj a 40MHz

    //Reloj para habilitar el puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //Configuración del reloj para habilitar el puerto F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
    GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); //Habilitar los pines como salidas 1 es rojo, 2 es azul y 3 es verde

    //Configuración timer 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); //Habilitar el Timer0
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC); // Configuración del Timer 0 como temporizador períodico
    TimerLoadSet(TIMER0_BASE, TIMER_BOTH, 20000000 - 1); // Establecer el periodo del temporizador
    IntEnable(INT_TIMER0A); //Se habilita la interrupción por el TIMER0A
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Se establece que exista la interrupción por Timeout
    IntMasterEnable(); // Se habilitan las interrupciones Globales
    TimerEnable(TIMER0_BASE, TIMER_A); // Se habilita el Timer

    //***********************PARTE 5**********************
    //Habilitar UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); //Habilotar GPIO puerto A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); //Habilitar periferico UART modulo 0
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1); //Pines UART
    UARTConfigSetExpClk(
            UART0_BASE, SysCtlClockGet(), 115200,
            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); //Configuración UART

    //Habilitar interrupciones de UART
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX);
    UARTIntDisable(
            UART0_BASE,
            UART_INT_9BIT | UART_INT_TX | UART_INT_OE | UART_INT_BE
                    | UART_INT_PE | UART_INT_FE | UART_INT_RT | UART_INT_DSR
                    | UART_INT_DCD | UART_INT_CTS | UART_INT_RI);
    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
    UARTEnable(UART0_BASE);

    while (1)
    {
    }
}

//***********************PARTE 4 y 7**********************
void Timer0IntHandler(void)
{
    if (verificar == 0)
    {

        //Led rojo se enciende
        if (recibido == 'r')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1,
                         0x02);
        }

        //Led verde se enciende
        if (recibido == 'g')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1,
                         0x08);
        }
        //Led azul se enciende
        if (recibido == 'b')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1,
                         0x04);
        }
    }

        //verificar = 1;

    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1,
                     0x00);
        verificar = 0;
    }

    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

}

//****************PARTE 6****************************
void UARTIntHandler(void)
{
    //se determina si hay caracteres recibidos
    if (UARTCharsAvail(UART0_BASE) == true)
    {
        //Se guarda el dato recibido
        recibido = UARTCharGet(UART0_BASE);
    }
    //Se limpian los errores recibidos
    UARTRxErrorClear(UART0_BASE);
    //Se limpian las interrupciones UART
    UARTIntClear(UART0_BASE, UART_INT_RX);

}
