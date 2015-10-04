//*************************************
//
//  codec related functions
//
//	author: mind-dump.net
//
//  heavily edited-by: brandon wetzel
//
//*************************************


#include "codec.h"

void codec_init(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;

	__HAL_RCC_I2C1_CLK_ENABLE();

	/* Initialize Reset Pin */
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;	/* 50MHz */
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* Turn off the audio driver */
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);

	/* I2C -> SCL */
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* I2C -> SDA */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* Setup I2C */
	I2C_InitStruct.I2C_ClockSpeed 		= 100000;
	I2C_InitStruct.I2C_Mode				= I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1		= 99;
	I2C_InitStruct.I2C_Ack				= I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress	= I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_DutyCycle			= I2C_DutyCycle_2;
	I2C_Init(I2C1, &I2C_InitStruct);
	I2C_Cmd(I2C1, ENABLE);
}

void codec_ctrl_init()
{
	uint32_t delaycount;
	uint8_t CodecCommandBuffer[5];

	uint8_t regValue = 0xFF;

	//GPIO_SetBits(GPIOD, CODEC_RESET_PIN);

	/* Turn on the audio driver */
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);

	/* STABILIZE */
	delaycount = 1000000;
	while (--delaycount > 0)

	//keep codec OFF
	CodecCommandBuffer[0] = CODEC_MAP_PWR_CTRL1;
	CodecCommandBuffer[1] = 0x01;
	send_codec_ctrl(CodecCommandBuffer, 2);

	//begin initialization sequence (p. 32)
	CodecCommandBuffer[0] = 0x00;				//
	CodecCommandBuffer[1] = 0x99;				//
	send_codec_ctrl(CodecCommandBuffer, 2);		// I
												// N
	CodecCommandBuffer[0] = 0x47;				// I
	CodecCommandBuffer[1] = 0x80;				// T
	send_codec_ctrl(CodecCommandBuffer, 2);		//
												// I
	regValue = read_codec_register(0x32);		// N
												// I
	CodecCommandBuffer[0] = 0x32;				// T
	CodecCommandBuffer[1] = regValue | 0x80;	//
	send_codec_ctrl(CodecCommandBuffer, 2);		// I
												// N
	regValue = read_codec_register(0x32);		// I
												// T
	CodecCommandBuffer[0] = 0x32;				//
	CodecCommandBuffer[1] = regValue & (~0x80);	// I
	send_codec_ctrl(CodecCommandBuffer, 2);		// N
												// I
	CodecCommandBuffer[0] = 0x00;				// T
	CodecCommandBuffer[1] = 0x00;				//
	send_codec_ctrl(CodecCommandBuffer, 2);		//
	//end of initialization sequence

	CodecCommandBuffer[0] = CODEC_MAP_PWR_CTRL2;
	CodecCommandBuffer[1] = 0xAF;
	send_codec_ctrl(CodecCommandBuffer, 2);

	/**
	 * ANLGSFTA
	 * ANLGGZCA
	 * PASSB=A
	 * PASSAMUTE
	 * PASSAVOL[7:0] (+12dB/-60dB .5dB steps)
	 */


	CodecCommandBuffer[0] = CODEC_MAP_PLAYBACK_CTRL1;
	CodecCommandBuffer[1] = 0x70;
	send_codec_ctrl(CodecCommandBuffer, 2);

	/* PASSB=A (p.42) */
	CodecCommandBuffer[0] = CODEC_MAP_PASSTHROUGH_GANG_CTRL;
	CodecCommandBuffer[1] = 0x80;
	send_codec_ctrl(CodecCommandBuffer, 2);

	/* ANLGSFTA + ANLGZCA (p. 42) */
	CodecCommandBuffer[0] = CODEC_MAP_ANALOG_SET;
	CodecCommandBuffer[1] = 0xF;
	send_codec_ctrl(CodecCommandBuffer, 2);

	/* PASSASEL1 (p.42) - DEFAULT */
	//CodecCommandBuffer[0] = CODEC_MAP_PASSTHROUGH_A_SELECT;
	//CodecCommandBuffer[1] = 0x1;
	//send_codec_ctrl(CodecCommandBuffer, 2);

	/* PASSAMUTE (p. 44) */
	//CodecCommandBuffer[0] = CODEC_MAP_MISC_CTRL;
	//CodecCommandBuffer[1] = ;
	//send_codec_ctrl(CodecCommandBuffer, 2);

	/* PASSAVOL[7:0] - initialize to half-vol (p. 46) */
	//CodecCommandBuffer[0] = CODEC_MAP_PASSTHROUGH_A_VOL;
	//CodecCommandBuffer[1] = 0x7F;
	//send_codec_ctrl(CodecCommandBuffer, 2);

	/* PASSAVOL[7:0] - initialize to half-vol (p. 46) */
	//CodecCommandBuffer[0] = CODEC_MAP_PASSTHROUGH_B_VOL;
	//CodecCommandBuffer[1] = 0x7F;
	//send_codec_ctrl(CodecCommandBuffer, 2);

	/* PASSTHRUA/B (p.44) */
	CodecCommandBuffer[0] = CODEC_MAP_MISC_CTRL;
	CodecCommandBuffer[1] = 0xC2;
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x1A | CODEC_MAPBYTE_INC;
	CodecCommandBuffer[1] = 0x0A;
	CodecCommandBuffer[2] = 0x0A;
	send_codec_ctrl(CodecCommandBuffer, 3);

	//CodecCommandBuffer[0] = CODEC_MAP_MASTER_A_VOL;
	//CodecCommandBuffer[1] = 0x7F;
	//send_codec_ctrl(CodecCommandBuffer, 2);

	//CodecCommandBuffer[0] = CODEC_MAP_MASTER_B_VOL;
	//CodecCommandBuffer[1] = 0x7F;
	//send_codec_ctrl(CodecCommandBuffer, 2);

	//CodecCommandBuffer[0] = CODEC_MAP_HP_A_VOL;
	//CodecCommandBuffer[1] = 0x7F;
	//send_codec_ctrl(CodecCommandBuffer, 2);

	//CodecCommandBuffer[0] = CODEC_MAP_HP_B_VOL;
	//CodecCommandBuffer[1] = 0x7F;
	//send_codec_ctrl(CodecCommandBuffer, 2);



	// CHECK 20/21,22/23,

	/*CodecCommandBuffer[0] = CODEC_MAP_CLK_CTRL;
	CodecCommandBuffer[1] = 0x81; //auto detect clock
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = CODEC_MAP_IF_CTRL1;
	CodecCommandBuffer[1] = 0x07;
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x0A;
	CodecCommandBuffer[1] = 0x00;
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x27;
	CodecCommandBuffer[1] = 0x00;
	send_codec_ctrl(CodecCommandBuffer, 2);

	CodecCommandBuffer[0] = 0x1A | CODEC_MAPBYTE_INC;
	CodecCommandBuffer[1] = 0x0A;
	CodecCommandBuffer[2] = 0x0A;
	send_codec_ctrl(CodecCommandBuffer, 3);

	CodecCommandBuffer[0] = 0x1F;
	CodecCommandBuffer[1] = 0x0F;
	send_codec_ctrl(CodecCommandBuffer, 2);*/

	// Turn the bad boy on...
	CodecCommandBuffer[0] = CODEC_MAP_PWR_CTRL1;
	CodecCommandBuffer[1] = 0x9E;
	send_codec_ctrl(CodecCommandBuffer, 2);

}

void send_codec_ctrl(uint8_t controlBytes[], uint8_t numBytes)
{
	uint8_t bytesSent=0;

	while (I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_BUSY))
	{
		//just wait until no longer busy
	}

	I2C_GenerateSTART(CODEC_I2C, ENABLE);
	while (!I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_SB))
	{
		//wait for generation of start condition
	}
	I2C_Send7bitAddress(CODEC_I2C, CODEC_I2C_ADDRESS, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(CODEC_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		//wait for end of address transmission
	}
	while (bytesSent < numBytes)
	{
		I2C_SendData(CODEC_I2C, controlBytes[bytesSent]);
		bytesSent++;
		while (!I2C_CheckEvent(CODEC_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING))
		{
			//wait for transmission of byte
		}
	}
	while(!I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_BTF))
	{
	    //wait until it's finished sending before creating STOP
	}
	I2C_GenerateSTOP(CODEC_I2C, ENABLE);

}

uint8_t read_codec_register(uint8_t mapbyte)
{
	uint8_t receivedByte = 0;

	while (I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_BUSY))
	{
		//just wait until no longer busy
	}

	I2C_GenerateSTART(CODEC_I2C, ENABLE);
	while (!I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_SB))
	{
		//wait for generation of start condition
	}

	I2C_Send7bitAddress(CODEC_I2C, CODEC_I2C_ADDRESS, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(CODEC_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		//wait for end of address transmission
	}

	I2C_SendData(CODEC_I2C, mapbyte); //sets the transmitter address
	while (!I2C_CheckEvent(CODEC_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTING))
	{
		//wait for transmission of byte
	}

	I2C_GenerateSTOP(CODEC_I2C, ENABLE);

	while (I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_BUSY))
	{
		//just wait until no longer busy
	}

	I2C_AcknowledgeConfig(CODEC_I2C, DISABLE);

	I2C_GenerateSTART(CODEC_I2C, ENABLE);
	while (!I2C_GetFlagStatus(CODEC_I2C, I2C_FLAG_SB))
	{
		//wait for generation of start condition
	}

	I2C_Send7bitAddress(CODEC_I2C, CODEC_I2C_ADDRESS, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(CODEC_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
		//wait for end of address transmission
	}

	while (!I2C_CheckEvent(CODEC_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED))
	{
		//wait until byte arrived
	}
	receivedByte = I2C_ReceiveData(CODEC_I2C);

	I2C_GenerateSTOP(CODEC_I2C, ENABLE);

	return receivedByte;
}
