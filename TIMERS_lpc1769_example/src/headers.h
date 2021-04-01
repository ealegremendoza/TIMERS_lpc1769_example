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

#define TEST0	0	// 1 TIMER- T0
#define TEST1	1	// 2 TIMERS- T0 y T1
#define TEST2	2	// Modificando el estado de un pin MATx.y con el registro EMR
#define TESTING	TEST2

#endif /* HEADERS_H_ */
