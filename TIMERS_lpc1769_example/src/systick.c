/*
 * systick.c
 *
 *  Created on: 19 mar. 2021
 *      Author: ealegremendoza
 */
#include "systick.h"

/*void MedirDistancia(void)
{
	uint32_t Temporal;
	uint32_t echoTime=0;
	uint32_t distance;
	static uint8_t flg_echo_timer=1;
	Temporal=GPIO_Get(PIN_SENSORULTRASONIDO_ECHO);
	switch(Temporal)
	{
		case 1:
    		if(flg_echo_timer)
    		{
    			flg_echo_timer = 0;//en el orden de los microsegundos
    			TIMER1_Start();
    		}
			break;
		case 0:
			echoTime=TIMER1_Stop();
			break;
		default:
			break;

	}
	//distance = (0.0343 * echoTime)/2; //Find the distance
	distance = (343 * echoTime)/2; //Find the distance *10000
	printf("Distance = %d.%d cm.\n",distance/10000,distance%10000);
}*/

void SysTick_Init(uint32_t frecuencia)
{
	uint32_t Temporal=0;
	if(frecuencia > 0xffffff)
		return;
	Temporal=CCLK/frecuencia - 1;
	STCURR = 0;
	STRELOAD = Temporal;
	STCTRL = (1<<0)|(1<<1)|(1<<2);
}
void SysTick_Handler(void)
{
	static uint32_t Divisor_1seg=0;
	static uint32_t Divisor_1min=0;
	Divisor_1seg++;
	if(Divisor_1seg==1000)
	{
		//1seg!
		Divisor_1seg=0;
		Divisor_1min++;
		Divisor_1min%=60;
	}
}
