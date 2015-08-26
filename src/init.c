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
void DMA_init(void);

void init_all(void)
{
	vdisplay_init();
	TIM3_init();
	GPIO_init();
	P24_init();
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

void DMA_init() {
	DMA_HandleTypeDef dma_handle;

	// Enable the DMA clock
	__HAL_RCC_DMA1_CLK_ENABLE();

	// Configure the DMA
	dma_handle.Instance	= DMA1_Stream5;						// WHY THIS STREAM???
	dma_handle.Init.Channel = DMA_CHANNEL_7;				// WHY THIS CHANNEL??? WHAT IS A CHANNEL???
	dma_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;		// will be moving data in memory to the DAC
	dma_handle.Init.PeriphInc = DMA_PINC_DISABLE;			// periph shall not be incremented
	dma_handle.Init.MemInc = DMA_MINC_ENABLE;				// memory shall be incremented
	dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	dma_handle.Init.Mode = DMA_CIRCULAR;
	dma_handle.Init.Priority = DMA_PRIORITY_HIGH;
	dma_handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	dma_handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
	dma_handle.Init.MemBurst = DMA_MBURST_SINGLE;
	dma_handle.Init.PeriphBurst = DMA_PBURST_SINGLE;

	HAL_DMA_Init(&dma_handle);
	HAL_DMA_Start_IT(&dma_handle);

	// Enable the interrupt
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_init(void) {
	//TIM_HandleTypeDef TIM_Handle;

	__TIM3_CLK_ENABLE();

	// Configure TIM3
	TIM_Handle.Instance = TIM3;
	TIM_Handle.Init.Prescaler = 1 - 1;
	TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM_Handle.Init.Period = 65535;

	// Initialize the timer
	HAL_TIM_Base_Init(&TIM_Handle);
	HAL_TIM_Base_Start_IT(&TIM_Handle);

	// Enable the interrupt
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void GPIO_init(void) {
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
}
