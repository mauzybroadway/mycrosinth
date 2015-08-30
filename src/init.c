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

#define   OUT_FREQ          5000                                 // Output waveform frequency
#define   SINE_RES          128                                  // Waveform resolution
#define   DAC_DHR12R1_ADDR  0x40007408                           // DMA writes into this reg on every request
#define   CNT_FREQ          42000000                             // TIM6 counter clock (prescaled APB1)
#define   TIM_PERIOD        ((CNT_FREQ)/((SINE_RES)*(OUT_FREQ))) // Autoreload reg value

const uint16_t function[SINE_RES] = { 2048, 2145, 2242, 2339, 2435, 2530, 2624, 2717, 2808, 2897,
                                      2984, 3069, 3151, 3230, 3307, 3381, 3451, 3518, 3581, 3640,
                                      3696, 3748, 3795, 3838, 3877, 3911, 3941, 3966, 3986, 4002,
                                      4013, 4019, 4020, 4016, 4008, 3995, 3977, 3954, 3926, 3894,
                                      3858, 3817, 3772, 3722, 3669, 3611, 3550, 3485, 3416, 3344,
                                      3269, 3191, 3110, 3027, 2941, 2853, 2763, 2671, 2578, 2483,
                                      2387, 2291, 2194, 2096, 1999, 1901, 1804, 1708, 1612, 1517,
                                      1424, 1332, 1242, 1154, 1068, 985, 904, 826, 751, 679,
                                      610, 545, 484, 426, 373, 323, 278, 237, 201, 169,
                                      141, 118, 100, 87, 79, 75, 76, 82, 93, 109,
                                      129, 154, 184, 218, 257, 300, 347, 399, 455, 514,
                                      577, 644, 714, 788, 865, 944, 1026, 1111, 1198, 1287,
                                      1378, 1471, 1565, 1660, 1756, 1853, 1950, 2047 };

// private function descriptions
void vdisplay_init();
void TIM3_init(void);
void TIM6_init(void);
void GPIO_init(void);
void DAC_init(void);
void DMA_init(void);
void EXTI_init(void);

void init_all(void)
{
	vdisplay_init();
	TIM3_init();
	GPIO_init();
	P24_init();
	DAC_init();
	DMA_init();
	TIM6_init();
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


}

void DAC_init(void) {
		DMA_HandleTypeDef dma_handle;

	// Enable the DMA clock
	__HAL_RCC_DMA1_CLK_ENABLE();

	// Configure the DMA
	dma_handle.Instance	= DMA1_Stream5;						// Initialize DMA for DAC1
	dma_handle.Init.Channel = DMA_CHANNEL_7;				// ...

	dma_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;		// will be moving data in memory TO the DAC
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
	HAL_DMA_Start(&dma_handle, (uint32_t)&function, DAC_DHR12R1_DACC1DHR, SINE_RES);
	//HAL_DMAEx_MultiBufferStart_IT(&dma_handle, (uint32_t)&PINGBUF, DAC_DHR12R1_DACC1DHR, (uint32_t)&PONGBUF, (uint32_t)128);

	//HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
	//HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);



	DAC_HandleTypeDef dac_handle;
	DAC_ChannelConfTypeDef dac_conf;

	// Enable the DAC clock
	__HAL_RCC_DAC_CLK_ENABLE();

	// Configure the DAC
	dac_handle.Instance = DAC;
	dac_handle.DMA_Handle1 = &dma_handle;

	dac_conf.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
	dac_conf.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
	HAL_DAC_Init(&dac_handle);

	HAL_DAC_ConfigChannel(&dac_handle, &dac_conf, DAC_CHANNEL_1);
	HAL_DAC_Start(&dac_handle, DAC_CHANNEL_1);
	HAL_DAC_Start_DMA(&dac_handle, DAC_CHANNEL_1, (uint32_t *)function, SINE_RES,DAC_ALIGN_12B_R);

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
	HAL_NVIC_SetPriority(TIM3_IRQn, 1, 1);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM6_init(void) {
	TIM_HandleTypeDef TIM6_Handle;

	__TIM6_CLK_ENABLE();

	// Configure TIM3
	TIM6_Handle.Instance = TIM6;
	TIM6_Handle.Init.Prescaler = 1 - 1;
	TIM6_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM6_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM6_Handle.Init.Period = (uint16_t)TIM_PERIOD;

	// Initialize the timer
	HAL_TIM_Base_Init(&TIM6_Handle);

	// Set Master mode
	TIM_MasterConfigTypeDef tim6master;
	tim6master.MasterOutputTrigger = TIM_TRGO_UPDATE;
	tim6master.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;

	HAL_TIMEx_MasterConfigSynchronization(&TIM6_Handle, &tim6master);

	HAL_TIM_Base_Start(&TIM6_Handle);

	// Enable the interrupt
	//HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 1, 1);
	//HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

void GPIO_init(void) {
	// Init clock for LED's and switches
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	// Rotary encoder
	__HAL_RCC_GPIOG_CLK_ENABLE();

	GPIO_TypeDef g2_td;
	GPIO_InitTypeDef g2_init;

	g2_init.Pin = GPIO_PIN_2;
	g2_init.Mode = GPIO_MODE_IT_RISING_FALLING;
	g2_init.Speed = GPIO_SPEED_MEDIUM;
	g2_init.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(&g2_td, &g2_init);

	HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 2);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);


}

