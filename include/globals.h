/*
 * interrupts.h
 *
 *  Created on: Aug 23, 2015
 *      Author: mauzy
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

//----- INCLUDES -----//
#include "stm32f4xx.h"

//----- DEFINES -----//
//#define NULL ((void *) 0)

//----- TYPDEFS -----//
typedef struct swevent {
	unsigned int pr : 1 ;  //press-release bit: 1 -- switch was pressed; 0 -- switch was released
	unsigned int sw : 7 ;  //switch number for this event  (with room for expansion)
	unsigned int msec : 24; //time in milliseconds the event occurred (rolls over at 2**24 ms).
} swevent_t;

//----- VARIABLES -----//
//TIM_HandleTypeDef TIM_Handle;

extern unsigned int vdisplay[11];
extern unsigned int rot_enc_arr[2];
uint16_t PINGBUF[128], PONGBUF[128];


#endif /* GLOBALS_H_ */
