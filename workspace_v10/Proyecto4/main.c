//Nicole Prem 18337 Proyecto 4

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

int main(void)
{
    //Configuración de reloj
    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //40 MHz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD); //Habilitar puerto D (0 a 3 botones)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); //Habilitar puerto E

    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,
    GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); //Habilitar los pines como entradas a donde van push buttons
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,
    GPIO_PIN_1 | GPIO_PIN_2); //Habilitar los pines como salidas E1 verde y E2 rojo

    //Configuración del botones como pull-up
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPU);

   // GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0x02); //Máscara = 0010, se enciende el led verde

    while (1)
    {
        //GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0x02); //Máscara = 0010, se enciende el led verde
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0x00); //Máscara, led rojo apagado

        if (!GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0))
        {
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0x04); //Máscara = 100, se apaga el led verde y enciende el rojo
        }

        if (GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0))
        {
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0x02); //Máscara = 100, se apaga el led verde y enciende el rojo
        }

    }

}
