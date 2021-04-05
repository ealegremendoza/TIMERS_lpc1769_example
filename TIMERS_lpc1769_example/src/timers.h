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

#if TESTING == TEST0 // TIMER0
void TIMER_LED_Init(void);
void TIMER0_Init(void);
void TIMER0_IRQHandler(void);
#endif
#if TESTING == TEST1 // TIMER0 and TIMER1
void TIMER_LED_Init(void);
void TIMER0_Init(void);
void TIMER0_IRQHandler(void);
void TIMER_LED_Init(void);
void TIMER1_Init(void);
void TIMER1_IRQHandler(void);
#endif

#if TESTING == TEST2 // Modificando el estado de un pin MATx.y con el registro EMR

#define PIN_MAT0_1	1,29
#define EMC_DoNothig	0
#define EMC_Pin_Low		1
#define EMC_Pin_High	2
#define EMC_Pin_Toggle	3

void TIMER0_Init(void);
#endif
#if TESTING == TEST3 // Usando Capture

#define PIN_CAP0_0	1,26
#define PIN_CAP2_0	0,4
void TIMER_Init(void);
void TIMER2_IRQHandler(void);
#endif
#endif /* TIMERS_H_ */
