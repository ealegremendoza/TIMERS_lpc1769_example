/*
 * headers.h
 *
 *  Created on: 19 mar. 2021
 *      Author: ealegremendoza
 */

#ifndef HEADERS_H_
#define HEADERS_H_


#include <cr_section_macros.h>
#include <stdio.h>
#include "Regs.h"
#include "Oscilador.h"
#include "GPIO.h"
#include "systick.h"
#include "debug.h"
#include "timers.h"

#ifndef DEBUG_H_
#define DEBUGOUT(a);
#else
#define DEBUGOUT(a);  printf(a);
#endif

#define TEST0	0	// TIMER0 - Ejemplo de uso de Match0 y Match1
#define TEST1	1	// TIMER0 y TIMER1 - Ejemplo usando los M0 de cada timer.
#define TEST2	2	// Modificando el estado de un pin MATx.y con el registro EMR
#define TEST3	3	// TIMER2- Ejemplo de uso de la funcion CAPTURE
#define TESTING	TEST3

#endif /* HEADERS_H_ */
