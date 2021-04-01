/*
 * GPIO.c
 *
 *  Created on: 1 abr. 2021
 *      Author: ealegremendoza
 */

#include "GPIO.h"

void GPIO_Func(uint32_t Port, uint32_t Pin, uint32_t Function)
{
	uint32_t Temporal = Port*2;
	if(Pin>15)
	{
		Temporal++;
		Pin-=16;//Pin-=15;//editado
	}
	PINSEL[Temporal]&= ~(3<<2*Pin);
	PINSEL[Temporal]|= (Function<<2*Pin);
}
void GPIO_Mode(uint32_t Port,uint32_t Pin, uint32_t Mode)
{
	uint32_t Temporal = Port*2;
	if(Pin>15)
	{
		Temporal++;
		Pin-=16;//Pin-=15;//editado
	}
	PINMODE[Temporal]&= ~(3<<(2*Pin));
	PINMODE[Temporal]|= (Mode<<(2*Pin));
}

void GPIO_Dir(uint32_t Port, uint32_t Pin, uint32_t Dir)
{
	if(Dir)
		GPIOs[Port].FIODIR |= 1<<Pin;
	else
		GPIOs[Port].FIODIR |= 0<<Pin;

}
void GPIO_Set(uint32_t Port, uint32_t Pin, uint32_t Estate)
{
	if(Estate)
		GPIOs[Port].FIOSET |= 1<<Pin;
	else
		GPIOs[Port].FIOCLR |= 1<<Pin;
}

uint32_t GPIO_Get (uint32_t Port, uint32_t Pin)
{
	if(GPIOs[Port].FIOPIN & (1<<Pin))
		return 1;
	else
		return 0;
}
