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
#if TESTING == TEST0
	TIMER_LED_Init();
	TIMER0_Init();
#endif
#if TESTING == TEST1
	TIMER_LED_Init();
	TIMER0_Init();
	TIMER1_Init();
#endif

}
int main(void)
{
	SystemInit();
    while(1)
    {
    	/*	ver timers.c	*/
    	/*	Hacer algo aquí, el periferico TIMERx se ejecuta en paralelo	*/
    }
    return 0 ;
}

