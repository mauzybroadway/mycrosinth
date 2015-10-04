/*
 * interrupts.c
 *
 *  Created on: Aug 23, 2015
 *      Author: mauzy
 */

#include "stm32f4xx.h"
//#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_tim.h"
#include "p24.h"
#include "spl/stm32f4xx_tim.h"
#include "globals.h"

void TIM3_IRQHandler(void) {
	// Clear flag
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

		// Do stuff
		//asm_get_switch(0,12);
		rot_enc();
		asm_vdisplay();
		//hw8stuff();
	}
}

void TIM4_IRQHandler(void) {
	// Clear flag
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		asm_get_switch(0,12);
		synthstuff();
	}
}

void TIM6_IRQHandler(void) {
	while(1);
}

void EXTI1_IRQHandler() {
	vdisplay[0] += vdisplay[0] % 10;

	while(1);
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
