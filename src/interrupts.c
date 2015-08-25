/*
 * interrupts.c
 *
 *  Created on: Aug 23, 2015
 *      Author: mauzy
 */

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "globals.h"

void TIM3_IRQHandler(void) {
	//ADD FLAG STUFF
	__HAL_TIM_CLEAR_IT(&TIM_Handle, TIM_IT_UPDATE);

	/*static int ayy = 0;
	if (ayy < 10) {			// Divide TIM3 by 10
		ayy++;
	} else {
		ayy = 0;
		hw8stuff();
		asm_get_switch();
	}*/

	asm_get_switch();
	//hw8stuff();
	asm_vdisplay();
}


void SysTick_Handler(void) {
	//asm_get_switch();
	//asm_vdisplay();
	/*static int ayy = 0;

	if (ayy < 1) {		// Update every second
		ayy++;
	} else {
		ayy = 0;

		asm_vdisplay();
		//vdisplay[0] = (vdisplay[0] + 1) % 16;
		//vdisplay[1] = (vdisplay[1] + 1) % 16;
		//vdisplay[2] = (vdisplay[2] + 1) % 16;
		//vdisplay[3] = (vdisplay[3] + 1) % 16;
	}*/
}
