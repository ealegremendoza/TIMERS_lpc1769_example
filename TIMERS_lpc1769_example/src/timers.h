/*
 * SensorUltrasonido_hcsr04.h
 *
 *  Created on: 19 mar. 2021
 *      Author: eze
 */

#ifndef TIMERS_H_
#define TIMERS_H_
#include "headers.h"

#define	PIN_LED_RED	0,22	// LED INTEGRADO
#define	PIN_LED_EXT	0,5		// COLOCAR UN LED EXTERNO

void TIMER_Init(void);

#if TESTING == TEST0 // TIMER0 - Ejemplo de uso de Match0 y Match1
void TIMER_LED_Init(void);
void TIMER0_Init(void);
void TIMER0_IRQHandler(void);
#endif
#if TESTING == TEST1 // TIMER0 y TIMER1 - Ejemplo usando los M0 de cada timer.
void TIMER_LED_Init(void);
void TIMER0_Init(void);
void TIMER0_IRQHandler(void);
void TIMER_LED_Init(void);
void TIMER1_Init(void);
void TIMER1_IRQHandler(void);
#endif

#if TESTING == TEST2 // TIMER0 - Modificando el estado de un pin MATx.y con el registro EMR

#define PIN_MAT0_1	1,29

void TIMER0_Init(void);
#endif
#if TESTING == TEST3 // TIMER2- Ejemplo de uso de la funcion CAPTURE
#define PIN_CAP0_0	1,26
#define PIN_CAP2_0	0,4
void TIMER2_Init(void);
void TIMER2_IRQHandler(void);
#endif
#endif /* TIMERS_H_ */
