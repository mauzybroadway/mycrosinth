/*
 * init.c
 *
 *  Created on: Aug 23, 2015
 *      Author: mauzy
 */

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "globals.h"
#include "init.h"

// private function descriptions
void vdisplay_init();
void TIM3_init(void);
void GPIO_init(void);

void init_all(void)
{
	vdisplay_init();
	TIM3_init();
	GPIO_init();
}

void vdisplay_init(void) {
	vdisplay[0]	= 0;
	vdisplay[1] = 0;
	vdisplay[2] = 0;
	vdisplay[3] = 0;
	vdisplay[4] = 0;
	vdisplay[5] = 0;
	vdisplay[6] = 0;
	vdisplay[7] = 0;
	vdisplay[8] = 0;
	vdisplay[9] = 0;
	vdisplay[10]= 0;
}

void TIM3_init(void) {
	//TIM_HandleTypeDef TIM_Handle;

	__TIM3_CLK_ENABLE();


	//TIM_Handle.Init.Prescaler = 65535;
	TIM_Handle.Init.Prescaler = 1 - 1;
	TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	//TIM_Handle.Init.Period = 62499;
	TIM_Handle.Init.Period = 65535;
	TIM_Handle.Instance = TIM3;

	//htim = TIM_Handle;

	HAL_TIM_Base_Init(&TIM_Handle);
	HAL_TIM_Base_Start_IT(&TIM_Handle);

	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void GPIO_init(void) {
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
}
