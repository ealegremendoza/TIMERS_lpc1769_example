/*
 * SensorUltrasonido_hcsr04.c
 *
 *  Created on: 19 mar. 2021
 *      Author: eze
 */
#include "timers.h"

void TIMER_LED_Init(void)
{
	GPIO_Func(PIN_LED_RED,FUNC_GPIO);
	GPIO_Dir(PIN_LED_RED,DIR_SALIDA);
	GPIO_Set(PIN_LED_RED,0);

	GPIO_Func(PIN_LED_EXT,FUNC_GPIO);
	GPIO_Dir(PIN_LED_EXT,DIR_SALIDA);
	GPIO_Set(PIN_LED_EXT,1);
}

#if TESTING == TEST0
void TIMER0_Init(void)
{
	PCONP |=1<<1;	// Enciendo el periferico
	PCLKSEL0 |=1<<2;	// CCLK -> 100MHz
	T0PC=CCLK/1000000-1;// Prescaler = 100-1 (cuenta hasta el 0)

	/*	MATCH0	*/
	T0MR0 = (1000000);//MR0= 1000000us (1seg)
	T0MCR = 0;
	T0MCR |= (1<<0)|	//	INT ACTIVADA
			 (0<<1)|	//	RESET DESACTIVADO
			 (0<<2);	//	STOP DESACTIVADO

	/*	MATCH1	*/
	T0MR1 = (2000000);//MR0= 1000000us
	T0MCR |= (1<<3)|	//	INT ACTIVADA
			 (1<<4)|	//	RESET ACTIVADO
			 (0<<5);	//	STOP DESACTIVADO

	/*	HABILITO INTERRUPCIONES DE LOS MATCH	*/
	T0IR = 0;
	T0IR = (1<<0)|(1<<1);

	/*	INICIO EL TEMPORIZADOR	*/
	T0TCR = 0;
	T0TCR = (1<<0);

	/*	HABILITO INTERRUPCION DEL TIMER0 EN EL LPC	*/
	ISER0 |=1<<1;

}

void TIMER0_IRQHandler(void)
{
	uint32_t Temporal = T0IR;
	if(((Temporal>>0) & 0x01)==0x01)//MR0 interrumpe
	{
		T0IR|= 1 <<0 ;	//BORRO EL FLAG
		GPIO_Set(PIN_LED_RED,!GPIO_Get(PIN_LED_RED));
		GPIO_Set(PIN_LED_EXT,!GPIO_Get(PIN_LED_EXT));
	}
	if(((Temporal>>1) & 0x01)==0x01)//MR1 interrumpe
	{
		T0IR|= 1 <<1 ;	//BORRO EL FLAG
		GPIO_Set(PIN_LED_RED,!GPIO_Get(PIN_LED_RED));
		GPIO_Set(PIN_LED_EXT,!GPIO_Get(PIN_LED_EXT));
	}
}
#endif
#if TESTING == TEST1
void TIMER0_Init(void)
{
	PCONP |=1<<1;	// Enciendo el periferico
	PCLKSEL0 |=1<<2;	// CCLK -> 100MHz
	TIMER0.PR=CCLK/1000000-1;// Prescaler = 100-1 (cuenta hasta el 0)

	/*	MATCH0	*/
	T0MR0 = (1000000);//MR0= 1000000us (1seg)
	T0MCR = 0;
	T0MCR |= (1<<0)|	//	INT ACTIVADA
			 (1<<1)|	//	RESET DESACTIVADO
			 (0<<2);	//	STOP DESACTIVADO


	/*	HABILITO INTERRUPCIONES DE LOS MATCH	*/
	T0IR = 0;
	T0IR = (1<<0);

	/*	INICIO EL TEMPORIZADOR	*/
	T0TCR = 0;
	T0TCR = (1<<0);

	/*	HABILITO INTERRUPCION DEL TIMER0 EN EL LPC	*/
	ISER0 |=1<<1;

}

void TIMER0_IRQHandler(void)
{
	uint32_t Temporal = T0IR;
	if(((Temporal>>0) & 0x01)==0x01)//MR0 interrumpe
	{
		T0IR|= 1 <<0 ;	//BORRO EL FLAG
		GPIO_Set(PIN_LED_RED,!GPIO_Get(PIN_LED_RED));
	}
}
void TIMER1_Init(void)
{
	PCONP |=1<<2;	// Enciendo el periferico
	PCLKSEL0 |=1<<4;	// CCLK -> 100MHz
	//T1PC=CCLK/1000000-1;// Prescaler = 100-1 (cuenta hasta el 0)
	TIMER1.PR=CCLK/1000000-1;// Prescaler = 100-1 (cuenta hasta el 0)
	/*	MATCH0	*/
	T1MR0 = (1000000);//MR0= 1000000us (1seg)
	T1MCR = 0;
	T1MCR |= (1<<0)|	//	INT ACTIVADA
			 (1<<1)|	//	RESET ACTIVADO
			 (0<<2);	//	STOP DESACTIVADO

	/*	HABILITO INTERRUPCIONES DE LOS MATCH	*/
	T1IR = 0;
	T1IR = (1<<0);

	/*	INICIO EL TEMPORIZADOR	*/
	T1TCR = 0;
	T1TCR = (1<<0);

	/*	HABILITO INTERRUPCION DEL TIMER1 EN EL LPC	*/
	ISER0 |=1<<2;

}

void TIMER1_IRQHandler(void)
{
	uint32_t Temporal = T1IR;
	if(((Temporal>>0) & 0x01)==0x01)//MR0 interrumpe
	{
		T1IR|= 1 <<0 ;	//BORRO EL FLAG
		GPIO_Set(PIN_LED_EXT,!GPIO_Get(PIN_LED_EXT));
	}

}
#endif
