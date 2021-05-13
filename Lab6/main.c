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

uint32_t ui32Period;

int main(void)
{
    //****************PARTE 2***********************************
    //Configuración del reloj a 40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //Configuración del reloj para habilitar el puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //Habilitar los pines como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); //1 es rojo, 2 es azul y 3 es verde

    //Habilitar el Timer0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    // Configuración del Timer 0 como temporizador períodico
        TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

        // Se calcula el período para el temporizador (1 seg)
        ui32Period = (SysCtlClockGet()) / 2;
        // Establecer el periodo del temporizador
        TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period - 1);

        // Se habilita la interrupción por el TIMER0A
        IntEnable(INT_TIMER0A);
        // Se establece que exista la interrupción por Timeout
        TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
        // Se habilitan las interrupciones Globales
        IntMasterEnable();
        // Se habilita el Timer
        TimerEnable(TIMER0_BASE, TIMER_A);
while(1){
}
}

void Timer0IntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    // Read the current state of the GPIO pin and
    // write back the opposite state
    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2))
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
    }
}
