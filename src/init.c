/*
 * init.c
 *
 *  Created on: Aug 23, 2015
 *      Author: mauzy
 */

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_dac.h"
//#include "stm32f4xx_hal_tim.h"
#include "spl/stm32f4xx_rcc.h"
#include "spl/stm32f4xx_dac.h"
#include "spl/stm32f4xx_dma.h"
#include "spl/stm32f4xx_tim.h"
#include "codec.h"
#include "globals.h"
#include "init.h"

#define   OUT_FREQ          1000                                 // Output waveform frequency
#define   SINE_RES          128                                  // Waveform resolution
#define   DAC_DHR12R1_ADDR  0x40007408                           // DMA writes into this reg on every request
#define   CNT_FREQ          42000000                             // TIM6 counter clock (prescaled APB1)
#define   TIM_PERIOD        ((2*CNT_FREQ)/((SINE_RES)*(OUT_FREQ))) // Autoreload reg value

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
void TIM4_init(void);
void TIM6_init(void);
void GPIO_init(void);
void DAC_DMA_init(void);

void init_all(void)
{
	GPIO_init();
	DAC_DMA_init();
	P24_init();
	vdisplay_init();
	codec_init();
	codec_ctrl_init();
	TIM6_init();			/* Initialize timer */
	TIM3_init();			/* interrupts last... */
	TIM4_init();
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
	asm_vdisplay();
}

void TIM3_init() {
	TIM_TimeBaseInitTypeDef TIM3_TimeBase;
	NVIC_InitTypeDef NVIC_InitStructure;

	//RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	__TIM3_CLK_ENABLE();

	TIM_TimeBaseStructInit(&TIM3_TimeBase);
	TIM3_TimeBase.TIM_Period = 65535;
	TIM3_TimeBase.TIM_Prescaler = 0;
	TIM3_TimeBase.TIM_ClockDivision = 0;
	TIM3_TimeBase.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM3_TimeBase);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM3, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//HAL_NVIC_SetPriority(TIM3_IRQn, 1, 1);
	//HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM4_init() {
	TIM_TimeBaseInitTypeDef TIM3_TimeBase;
	NVIC_InitTypeDef NVIC_InitStructure;

	//RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	__TIM4_CLK_ENABLE();

	TIM_TimeBaseStructInit(&TIM3_TimeBase);
	TIM3_TimeBase.TIM_Period = 65535;
	TIM3_TimeBase.TIM_Prescaler = 2;
	TIM3_TimeBase.TIM_ClockDivision = 0;
	TIM3_TimeBase.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM3_TimeBase);

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM4, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//HAL_NVIC_SetPriority(TIM3_IRQn, 1, 1);
	//HAL_NVIC_EnableIRQ(TIM3_IRQn);
}


void TIM6_init(void){
	TIM_TimeBaseInitTypeDef TIM6_TimeBase;

	//RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	__TIM6_CLK_ENABLE();

	TIM_TimeBaseStructInit(&TIM6_TimeBase);
	TIM6_TimeBase.TIM_Period = (uint16_t)TIM_PERIOD;
	TIM6_TimeBase.TIM_Prescaler = 0;
	TIM6_TimeBase.TIM_ClockDivision = 0;
	TIM6_TimeBase.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, &TIM6_TimeBase);
	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

	TIM_Cmd(TIM6, ENABLE);
}

void GPIO_init(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
}

void DAC_DMA_init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	DAC_InitTypeDef DAC_INIT;
	DMA_InitTypeDef DMA_INIT;

	__HAL_RCC_DMA1_CLK_ENABLE();
	__HAL_RCC_DAC_CLK_ENABLE();

	/* DAC output pin */
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	//GPIO_InitStruct.Speed = GPIO_SPEED_FAST;	/* 50MHz */
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	DAC_INIT.DAC_Trigger = DAC_Trigger_T6_TRGO;
	DAC_INIT.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_INIT.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_INIT.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_INIT);

	DMA_DeInit(DMA1_Stream5);
	DMA_INIT.DMA_Channel				= DMA_Channel_7;
	DMA_INIT.DMA_PeripheralBaseAddr		= (uint32_t)DAC_DHR12R1_ADDR;
	DMA_INIT.DMA_Memory0BaseAddr		= (uint32_t) &function;
	DMA_INIT.DMA_DIR					= DMA_DIR_MemoryToPeripheral;
	DMA_INIT.DMA_BufferSize				= SINE_RES;
	DMA_INIT.DMA_PeripheralInc			= DMA_PeripheralInc_Disable;
	DMA_INIT.DMA_MemoryInc				= DMA_MemoryInc_Enable;
	DMA_INIT.DMA_PeripheralDataSize		= DMA_PeripheralDataSize_HalfWord;
	DMA_INIT.DMA_MemoryDataSize			= DMA_MemoryDataSize_HalfWord;
	DMA_INIT.DMA_Mode					= DMA_Mode_Circular;
	DMA_INIT.DMA_Priority				= DMA_Priority_High;
	DMA_INIT.DMA_FIFOMode				= DMA_FIFOMode_Disable;
	DMA_INIT.DMA_FIFOThreshold			= DMA_FIFOThreshold_HalfFull;
	DMA_INIT.DMA_MemoryBurst			= DMA_MemoryBurst_Single;
	DMA_INIT.DMA_PeripheralBurst		= DMA_PeripheralBurst_Single;

	DMA_Init(DMA1_Stream5, &DMA_INIT);

	DMA_Cmd(DMA1_Stream5, ENABLE);
	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_DMACmd(DAC_Channel_1,ENABLE);
}
