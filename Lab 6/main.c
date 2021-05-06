#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
volatile uint32_t i;

int main(void)
{

//Configuración del reloj
   // SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //40 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //50 MHz

    //Habilitar puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //Habilitar los pines como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); //1 es rojo, 2 es azul y 3 es verde

    //Habilitar botón como input
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);

    //Configuración del botón como pull-up
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);


    while(1)
    {
        if (!GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)){


                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x08); //Máscara = 1000, se enciende verde
                    for (i=0;i<2000000;i++){}

                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todos
                    for (i=0;i<1000000;i++){}

                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x08); //Se enciende verde (parpadeo)
                    for (i=0;i<1000000;i++){}

                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todos
                    for (i=0;i<1000000;i++){}

                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x08); //Se enciende verde (parpadeo)
                    for (i=0;i<1000000;i++){}

                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todos
                    for (i=0;i<1000000;i++){}

                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x08); //Se enciende verde (parpadeo)
                    for (i=0;i<1000000;i++){}

                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todos
                    for (i=0;i<1000000;i++){}

                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Máscara = 1010, se enciende rojo y verde para crear amarillo
                    for (i=0;i<2000000;i++){}

                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x02); //Máscara = 10, se enciende el rojo
                    for (i=0;i<2000000;i++){} //delay

                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1,0x00); //Se apagan todos
                     for (i=0;i<1000000;i++){}


                }

            }
    }

