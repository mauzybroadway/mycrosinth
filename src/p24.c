/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"	//!!wmh
#include "stm32f4xx_hal_gpio.h"	//!!wmh
#include "p24.h"
#include "globals.h"
#include "fifo.h"

//#include "misc.h"			//!!wmh

//#include "fifo.h"
//!!wmh #include "stm32f4xx_sdio.h"
//!!wmh #include "stm32f4xx_dma.h"
//!!wmh #include "stm32f4xx_i2c.h"


//extern int vdisplay[11] = {0,0,0,0,0,0,0,0,0,0,0};
int vdisplay[11] = {0};
extern int note[2] = {0,5};

GPIO_TypeDef* ANCA_PORT[ANCAn] = {CA_A_GPIO_PORT, CA_B_GPIO_PORT,
                                 CA_C_GPIO_PORT, CA_D_GPIO_PORT, CA_E_GPIO_PORT,
																 CA_F_GPIO_PORT, CA_G_GPIO_PORT, CA_DP_GPIO_PORT, CA_EN_GPIO_PORT, 
																 CA_CLK_GPIO_PORT, AN_EN_GPIO_PORT, AN_CLK_GPIO_PORT};
const uint16_t ANCA_PIN[ANCAn] = {CA_A_PIN, CA_B_PIN,
                                 CA_C_PIN, CA_D_PIN, CA_E_PIN,
																 CA_F_PIN, CA_G_PIN, CA_DP_PIN, CA_EN_PIN, CA_CLK_PIN,
																 AN_EN_PIN, AN_CLK_PIN};
const uint32_t ANCA_CLK[ANCAn] = {CA_A_GPIO_CLK, CA_B_GPIO_CLK,
                                 CA_C_GPIO_CLK, CA_D_GPIO_CLK, CA_E_GPIO_CLK,
																 CA_F_GPIO_CLK, CA_G_GPIO_CLK, CA_DP_GPIO_CLK, CA_EN_GPIO_CLK, 
																 CA_CLK_GPIO_CLK, AN_EN_GPIO_CLK, AN_CLK_GPIO_CLK};

void ANCA_INIT_All() {
	// Initialize vdisplay to all 0's
	//int i = 0;
	//for (i = 0; i < 11; i++)
	//	vdisplay[i] = 0;

	// Initialize GPIO clocks
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	ANCAInit(A_COLON);
	ANCAInit(B_DIGIT4);
	ANCAInit(C_DIGIT2);
	ANCAInit(D_ROT_ENC);
	ANCAInit(E_R);
	ANCAInit(F_DIGIT1);
	ANCAInit(G_DIGIT3);
	ANCAInit(DP_G);
	ANCAInit(CA_EN);
	ANCAInit(CA_CLK);
	ANCAInit(AN_EN);
	ANCAInit(AN_CLK);
}

void ANCAInit(ANCA_TypeDef Anca)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.Pin = ANCA_PIN[Anca];
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  GPIO_InitStructure.Speed = GPIO_SPEED_MEDIUM;
  //GPIO_InitStructure.Alternate = GPIO_Speed_50MHz;
  HAL_GPIO_Init(ANCA_PORT[Anca], &GPIO_InitStructure);
}

/*
void ANCA_Set (int ANCA[8])
{
	int i;
	for (i = 0; i < 8; i++){
		if(ANCA[i])
			ANCA_PORT[i]->BSRRH = ANCA_PIN[i];
		else
			ANCA_PORT[i]->BSRRL = ANCA_PIN[i];
	}
}

void ANCA_Print_Num (int num, int digit, int dot)
{
	int CA[8] = {1,1,1,1,1,1,1,0};
	int AN[8] = {0,0,0,0,0,0,0,0};

	// disable cathode/anode
	ANCA_PORT[CA_EN]->BSRRL = ANCA_PIN[CA_EN];
	ANCA_PORT[AN_EN]->BSRRL = ANCA_PIN[AN_EN];

	if(dot)
		CA[7] = 1;

	// should probably use typedef vals, not numbers...
	switch(num) {
		case 0: CA[6] = 0; break;
		case 1: CA[0] = 0; CA[3] = 0; CA[4] = 0; CA[5] = 0; CA[6] = 0; break;
		case 2: CA[2] = 0; CA[5] = 0; break;
		case 3: CA[4] = 0; CA[5] = 0; break;
		case 4: CA[0] = 0; CA[3] = 0; CA[4] = 0; break;
		case 5: CA[1] = 0; CA[4] = 0; break;
		case 6: CA[1] = 0; break;
		case 7: CA[4] = 0; CA[5] = 0; CA[6] = 0; break;
		case 8: break;
		case 9: CA[4] = 0; break;
		case 10: CA[3] = 0;  break;
		case 11: CA[0] = 0; CA[1] = 0; break;
		case 12: CA[1] = 0; CA[2] = 0; CA[6] = 0; break;
		case 13: CA[0] = 0; CA[5] = 0;  break;
		case 14: CA[1] = 0; CA[2] = 0; break;
		case 15: CA[1] = 0; CA[2] = 0; CA[3] = 0; break;
		default: CA[0] = 0; CA[1] = 0; CA[2] = 0; CA[3] = 0; CA[4] = 0; CA[5] = 0; break;
	}
	
	switch(digit) {
		case 0: AN[F_DIGIT1] = 1; break;
		case 1: AN[C_DIGIT2] = 1; break;
		case 4: AN[A_COLON]  = 1; break;
		case 2: AN[G_DIGIT3] = 1; break;
		case 3: AN[B_DIGIT4] = 1; break;
	}
	
	// set/clock the cathode
	ANCA_Set(CA);
	ANCA_PORT[CA_CLK]->BSRRL = ANCA_PIN[CA_CLK];
	ANCA_PORT[CA_CLK]->BSRRH = ANCA_PIN[CA_CLK];
	
	// set/clock the anode
	ANCA_Set(AN);
	ANCA_PORT[AN_CLK]->BSRRL = ANCA_PIN[AN_CLK];
	ANCA_PORT[AN_CLK]->BSRRH = ANCA_PIN[AN_CLK];
	
	// enable the cathode
	ANCA_PORT[CA_EN]->BSRRH = ANCA_PIN[CA_EN];
	
	// enable the anode
	ANCA_PORT[AN_EN]->BSRRH = ANCA_PIN[AN_EN];
}

void ANCA_Print_Ascii (char c, int digit)
{
	
}*/

//unsigned int head = 0, tail = 0;

/*int queue(swevent_t * in) {
	if(tail < QSIZE){
		//fifo[tail].pr = in->pr;
		//fifo[tail].sw = in->sw;
		//fifo[tail++].msec = in->msec;
		fifo[tail++] = *in;
		return 0;
	} else {
		return -1;
	}
}

swevent_t dequeue() {
	unsigned int tmp = head, i;
	
	if(tail == 0) {
		swevent_t KILL;
		KILL.pr = 1;
		KILL.sw = 20;
		return KILL;			// return an invalid switch event
	}
	
	swevent_t tmpsw = fifo[0];
	
	//screw_it();
	
	for (i = 0; i < tail - 1; i++) {
		fifo[i] = fifo[i + 1];
	}
	
	tail--;
	
	return tmpsw;
}*/

/*swevent_t getswitch(void)
{
	swevent_t out = dequeue();
	return out;
}*/

/*void hw8stuff(void)
{
	static unsigned int things[4] = {0,0,0,0};
	swevent_t out = getswitch();
	
	if(out.sw <= 13) {
		if(out.pr != 0) {
			switch(out.sw) {
				case 1 : if (vdisplay[0] < 15) vdisplay[0]++; break;
				//case 3 : if (vdisplay[1] < 15) vdisplay[1]++; break;
				//case 5 : if (vdisplay[2] < 15) vdisplay[2]++; break;
				//case 7 : if (vdisplay[3] < 15) vdisplay[3]++; break;
			}
		} else {
			switch(out.sw) {
				case 2 : if (vdisplay[0] > 0) vdisplay[0]--; break;
				//case 4 : if (vdisplay[1] > 0) vdisplay[1]--; break;
				//case 6 : if (vdisplay[2] > 0) vdisplay[2]--; break;
				//case 8 : if (vdisplay[3] > 0) vdisplay[3]--; break;
			}
		}
	}
}

void synthstuff(void)
{
	swevent_t out = getswitch();
	
	if(out.sw <= 13) {
		if(out.pr != 0) {	// pressed
			//switch(out.sw) {
			//	case 1 : note[0] = 1;
			//}
			note[0] = out.sw;
			vdisplay[0] = out.sw;
		} else {					// released
			//switch(out.sw) {
			//	case 2 : note[0] = 0;
			//}
			note[0] = 0;
			vdisplay[0] = 0;
		}
	}
}*/


    
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
