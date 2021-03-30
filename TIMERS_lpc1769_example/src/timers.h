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
#define	PIN_LED_EXT	0,4		// COLOCAR UN LED EXTERNO

#if TESTING == TEST0
void TIMER_LED_Init(void);
void TIMER0_Init(void);
void TIMER0_IRQHandler(void);
#endif
#if TESTING == TEST1
void TIMER_LED_Init(void);
void TIMER0_Init(void);
void TIMER0_IRQHandler(void);
void TIMER_LED_Init(void);
void TIMER1_Init(void);
void TIMER1_IRQHandler(void);
#endif
#endif /* TIMERS_H_ */
