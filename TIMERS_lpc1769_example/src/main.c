/*
===============================================================================
 Name        : TIMERS_lpc1769_example.c
 Author      : ealegremendoza
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "headers.h"

void SystemInit(void)
{
	InitPLL();
	SysTick_Init(1000);
	TIMER_LED_Init();
	TIMER_Init();
}

int main(void)
{
	SystemInit();
    while(1)
    {
    	/*	ver timers.c
    	 *  El ejemplo hace alternar los estados de dos LEDs.	*/
    	/*	Hacer algo aquí si se desea, el periferico TIMERx
    	 *  se ejecuta en paralelo	*/
    }
    return 0 ;
}

