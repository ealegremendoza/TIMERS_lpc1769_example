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
#if TESTING == TEST0 // TIMER0
	TIMER_LED_Init();
	TIMER0_Init();
#endif
#if TESTING == TEST1 // TIMER0 and TIMER1
	TIMER_LED_Init();
	TIMER0_Init();
	TIMER1_Init();
#endif
#if TESTING == TEST2 // Modificando el estado de un pin MATx.y con el registro EMR
	TIMER_LED_Init();
	TIMER0_Init();
#endif
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

