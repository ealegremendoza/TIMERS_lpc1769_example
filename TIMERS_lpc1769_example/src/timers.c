/*
 * SensorUltrasonido_hcsr04.c
 *
 *  Created on: 19 mar. 2021
 *      Author: eze
 */
#include "timers.h"
uint32_t capture=0;


void TIMER_LED_Init(void)
{
	GPIO_Func(PIN_LED_RED,FUNC_GPIO);
	GPIO_Dir(PIN_LED_RED,DIR_SALIDA);
	GPIO_Set(PIN_LED_RED,0);

	GPIO_Func(PIN_LED_EXT,FUNC_GPIO);
	GPIO_Dir(PIN_LED_EXT,DIR_SALIDA);
	GPIO_Set(PIN_LED_EXT,1);
}

void TIMER_Init(void)
{
#if TESTING == TEST0 // TIMER0 - Ejemplo de uso de Match0 y Match1
	TIMER0_Init();
#endif
#if TESTING == TEST1 // TIMER0 y TIMER1 - Ejemplo usando los M0 de cada timer.
	TIMER0_Init();
	TIMER1_Init();
#endif
#if TESTING == TEST2 // TIMER0- Modificando el estado de un pin MATx.y con el registro EMR
	TIMER0_Init();
#endif
#if TESTING == TEST3 // TIMER2- Ejemplo de uso de la funcion CAPTURE
	TIMER2_Init();
#endif

}


#if TESTING == TEST0 // TIMER0 - Ejemplo de uso de Match0 y Match1
void TIMER0_Init(void)
{
	PCONP |=1<<1;		// Enciendo el periferico
	PCLKSEL0 |=1<<2;	// CCLK -> 100MHz
	TIMER0.PR=CCLK/1000000-1;// Prescaler = 100-1 (cuenta hasta el 0)
	/*	MATCH0	*/
	T0MR0 = (1000000-1);//MR0= 1000000us (1seg)
	T0MCR = 0;
	T0MCR |= (1<<0)|	//	INT ACTIVADA
			 (0<<1)|	//	RESET DESACTIVADO
			 (0<<2);	//	STOP DESACTIVADO

	/*	MATCH1	*/
	T0MR1 = (2000000-1);//MR1= 1000000us
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
#if TESTING == TEST1 // TIMER0 y TIMER1 - Ejemplo usando los M0 de cada timer.
void TIMER0_Init(void)
{
	PCONP |=1<<1;	// Enciendo el periferico
	PCLKSEL0 |=1<<2;	// CCLK -> 100MHz
	TIMER0.PR=CCLK/1000000-1;// Prescaler = 100-1 (cuenta hasta el 0)

	/*	MATCH0	*/
	T0MR0 = (1000000-1);//MR0= 1000000us (1seg)
	T0MCR = 0;
	T0MCR |= (1<<0)|	//	INT ACTIVADA
			 (1<<1)|	//	RESET ACTIVADO
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
	TIMER1.PR=CCLK/1000000-1;// Prescaler = 100-1 (cuenta hasta el 0)
	/*	MATCH0	*/
	T1MR0 = (1000000-1);//MR0= 1000000us (1seg)
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
#if TESTING == TEST2 // TIMER0- Modificando el estado de un pin MATx.y con el registro EMR
/*	Nota: Solo los pines MATn.m pueden ser usados con este registro.
 * 	Sirve para independizar el comportamiento de un pin del resto del sistema.
 * 	No utiliza interrupciones.	*/
void TIMER0_Init(void)
{
	/*	ALIMENTO EL PERIFERICO */
	PCONP |=1<<1;	// Enciendo el periferico
	PCLKSEL0 |=1<<2;	// CCLK -> 100MHz

	/*	RESETEO EL TIMER */
	T0TCR = 2;	//RESET TIMER
	TIMER0.PR=CCLK/1000000-1;// Prescaler = 100-1 (cuenta hasta el 0)

	/*	CONFIGURO EL PIN MAT0.1	*/;
	GPIO_Func(PIN_MAT0_1,FUNC_FUNC3);

	/*	MATCH1	*/
	// Uso Match 1 porque es el que se corresponde con el pin configurado arriba.
	T0MR1 = (1000000-1);//MR1= 1000000us // resto 1 porque contemplo el cero!
	T0MCR = 0;

	T0MCR |= (0<<3)|	//	INT ACTIVADA
			 (1<<4)|	//	RESET ACTIVADO
			 (0<<5);	//	STOP DESACTIVADO

	/* EMR Funciones
	 * DoNothig		0
	 * Pin_Low		1
	 * Pin_High		2
	 * Pin_Toggle	3
	 * */
	TIMER0.EMR = 0;
	TIMER0.EMR |= 3<<6;
	/*	INICIO EL TEMPORIZADOR	*/
	T0TCR = 0;
	T0TCR = (1<<0);
	/*	NOTAR QUE NO SE USAN INTERRUPCIONES !	*/
}
#endif

#if TESTING == TEST3	// TIMER2- Ejemplo de uso de la funcion CAPTURE
void TIMER2_Init(void)
{
	/*	ALIMENTO EL PERIFERICO */
	PCONP |=1<<22;	// Enciendo el periferico TIMER2
	PCLKSEL1 |=1<<12;	// CCLK -> 100MHz para TIMER2

	/*	RESETEO EL TIMER */
	T2TCR = 2;	//RESET TIMER
	TIMER2.PR=CCLK/1000000-1;// Prescaler = 100-1 (cuenta hasta el 0)

	/*	CONFIGURO EL PIN CAP0.0
	 *  El pin CAPn.m es el único que tiene esta funcionalidad 	*/
	GPIO_Func(PIN_CAP2_0,FUNC_FUNC3);

	T2CCR=0;
	T2CCR|=(0<<0);	//NO Capturo cuando CAP2.0 tiene un flanco ascendente
	T2CCR|=(1<<1);	//SI Capturo cuando CAP2.0 tiene un flanco descendente
	T2CCR|=(1<<2);	//SI Activo la interrupcion

	/*	MATCH0	*/
	T2MR0 = (500000-1);//MR0= 1000000us	// resto 1 porque contemplo el cero!
	T2MCR = 0;
	T2MCR |= (1<<0)|	//	INT ACTIVADA
			 (0<<1)|	//	RESET DESACTIVADO
			 (0<<2);	//	STOP DESACTIVADO
	/*	MATCH1	*/
	T2MR1 = (3000000-1);//MR0= 1000000us // resto 1 porque contemplo el cero!
	T2MCR |= (0<<3)|	//	INT DESACTIVADA
			 (1<<4)|	//	RESET ACTIVADO
			 (0<<5);	//	STOP DESACTIVADO

	/*	Apago el funcionamiento del EMR por las dudas */
	TIMER2.EMR = 0;
	/*	HABILITO INTERRUPCIONES DE LOS MATCH	*/
	T2IR = 0;
	T2IR = (1<<0);
	//T0IR = (1<<0)|(1<<1)|(1<<4);

	/*	INICIO EL TEMPORIZADOR	*/
	T2TCR = 0;
	T2TCR = (1<<0);

	/*	HABILITO INTERRUPCION DEL TIMER0 EN EL LPC	*/
	ISER0 |=1<<3;

}

void TIMER2_IRQHandler(void)
{
	uint32_t Temporal = T2IR;
	if(((Temporal>>0) & 0x01)==0x01)//MR0 interrumpe
	{
		T2IR|= 1 <<0 ;	//BORRO EL FLAG
		GPIO_Set(PIN_LED_EXT,!GPIO_Get(PIN_LED_EXT));
	}
	if(((Temporal>>4) & 0x01)==0x01)//CR0 interrumpe
	{
		T2IR|= 1 <<4 ;	//BORRO EL FLAG
		capture=T2CR0;	//leo el valor de TC al momento de la captura
		printf("cap0! %d\n",capture);
	}
}

#endif

