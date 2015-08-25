/*
 * interrupts.h
 *
 *  Created on: Aug 23, 2015
 *      Author: mauzy
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

//----- INCLUDES -----//
#include "stm32f4xx.h"

//----- TYPDEFS -----//
typedef struct swevent {
	unsigned int pr : 1 ;  //press-release bit: 1 -- switch was pressed; 0 -- switch was released
	unsigned int sw : 7 ;  //switch number for this event  (with room for expansion)
	unsigned int msec : 24; //time in milliseconds the event occurred (rolls over at 2**24 ms).
} swevent_t;

//----- VARIABLES -----//
TIM_HandleTypeDef TIM_Handle;
extern int vdisplay[11];

#endif /* INTERRUPTS_H_ */
