// dsk_audio4.c
// configuration programming interface for the DSK_AUDIO4 daughtercard
// Educational DSP, LLC - 2007

#include "dsk_audio4.h"

Int16 DskAudio4_SelectInputSource(Uint8 codec, Uint8 left_input, Uint8 right_input)
{
	Uint8 ain_sel_data = 0, vcom_data = PCM3793_REG_VCM_POWER_CMT_NOM;

	switch(left_input) {
	case DSK_AUDIO4_INPUT_MIC_0DB:
		ain_sel_data |= PCM3793_REG_AIN_SEL_AIL_AIN1;
		break;
	case DSK_AUDIO4_INPUT_MIC_20DB:
		ain_sel_data |= PCM3793_REG_AIN_SEL_AIL_AIN1;
		vcom_data |= PCM3793_REG_VCM_POWER_CMT_G20L; 
		break;
	default: // DSK_AUDIO4_INPUT_LINE
		ain_sel_data |= PCM3793_REG_AIN_SEL_AIL_AIN3;
		break;
	}

	switch(right_input) {
	case DSK_AUDIO4_INPUT_MIC_0DB:
		ain_sel_data |= PCM3793_REG_AIN_SEL_AIR_AIN1;
		break;
	case DSK_AUDIO4_INPUT_MIC_20DB:
		ain_sel_data |= PCM3793_REG_AIN_SEL_AIR_AIN1;
		vcom_data |= PCM3793_REG_VCM_POWER_CMT_G20R; 
		break;
	default: // DSK_AUDIO4_INPUT_LINE
		ain_sel_data |= PCM3793_REG_AIN_SEL_AIR_AIN3;
		break;
	}

	if( (DskAudio4_WriteCodecSetting(codec, PCM3793_REG_AIN_SEL, ain_sel_data) == -1) || 
	 	(DskAudio4_WriteCodecSetting(codec, PCM3793_REG_VCM_POWER, vcom_data) == -1) )
		return -1;
	return 0;
}



Int16 DskAudio4_SetAdcAnalogGain(Uint8 codec, Uint8 channel, float gain)
{
	Uint8 data, address;

	// convert gain to allowable setting values
	if(gain < -12.0F) {	
		data = 0x00;					// min gain -12b
	}
	else if(gain <= 30.0F) {			// 1db steps
		data = gain + 12.0F;
	}
	else { 								// limited to 30db
		data = 0x2A;
	}
	address = (channel == PCM3793_REG_LEFT)?PCM3793_REG_ADC_VOLL:PCM3793_REG_ADC_VOLR;
	return DskAudio4_WriteCodecSetting(codec, address, data);
}

Int16 DskAudio4_SetDacInputAttenuation(Uint8 codec, Uint8 channel, float gain)
{
	Uint8 data, address;

	// convert gain to allowable setting values
	if(gain < -62.0F) {	
		data = PCM3793_REG_DAC_MUTE + 0x00;// mute for gain < -61db
	}
	else if(gain <= 0.0F) {				// 1db steps
		data = (gain + 62.0F) + 0x01;
	}
	else { 								// limited to 0db
		data = 0x3F;
	}
	address = (channel == PCM3793_REG_LEFT)?PCM3793_REG_DAC_ATTNL:PCM3793_REG_DAC_ATTNR;
	return DskAudio4_WriteCodecSetting(codec, address, data);
}

Int16 DskAudio4_SetLineOutAnalogGain(Uint8 codec, Uint8 channel, float gain)
{
	Uint8 data, address;

	// convert gain to allowable setting values
	if(gain < -70.0F) {	
		data = PCM3793_REG_HPAx_VOL_MUTE + 0x00;// mute for gain < -70db
	}
	else if(gain < -42.0F) {			// 4db steps
		data = ((gain + 70.0F) * 0.25F) + 0x00;
	}
	else if(gain < -24.0F) {			// 2db steps
		data = ((gain + 42.0F) * 0.5F) + 0x07;
	}
	else if(gain < -11.0F) {			// 1db steps
		data = ((gain + 24.0F)       ) + 0x10;
	}
	else if(gain <= 6.0F) {				// 0.5db steps
		data = ((gain + 11.0F) * 2.0F) + 0x1D;
	}
	else { 								// limited to 6db
		data = 0x3F;
	}
	address = (channel == PCM3793_REG_LEFT)?PCM3793_REG_HPAL_VOL:PCM3793_REG_HPAR_VOL;
	return DskAudio4_WriteCodecSetting(codec, address, data);
}

Int16 DskAudio4_ResetDaughtercardToDefaults()
{
	return DskAudio4_SendDaughtercardCommand(DSK_AUDIO4_CMD_RESET, 0, 0);
}

Int32 DskAudio4_GetDaughtercardInfo()
{
	Uint32 data;
	Int32 retval;

	retval = DskAudio4_SendDaughtercardCommand(DSK_AUDIO4_CMD_READ, DSK_AUDIO4_READ_DCARD_DCARDTYPE, 0);
	if(retval == -1)
		return retval;
	data = (Uint8)(retval & 0xFF);
	data <<= 8;

	retval = DskAudio4_SendDaughtercardCommand(DSK_AUDIO4_CMD_READ, DSK_AUDIO4_READ_DCARD_HWREV, 0);
	if(retval == -1)
		return retval;
	data |= (Uint8)(retval & 0xFF);
	data <<= 8;

	retval = DskAudio4_SendDaughtercardCommand(DSK_AUDIO4_CMD_READ, DSK_AUDIO4_READ_DCARD_SWREV_H, 0);
	if(retval == -1)
		return retval;
	data |= (Uint8)(retval & 0xFF);
	data <<= 8;

	retval = DskAudio4_SendDaughtercardCommand(DSK_AUDIO4_CMD_READ, DSK_AUDIO4_READ_DCARD_SWREV_L, 0);
	if(retval == -1)
		return retval;
	data |= (Uint8)(retval & 0xFF);

	return (Int32) data;
}


Int16 DskAudio4_WriteCodecSetting(Uint8 codec, Uint8 address, Uint8 data)
{
	return DskAudio4_SendDaughtercardCommand(codec?DSK_AUDIO4_CMD_WRITE1:DSK_AUDIO4_CMD_WRITE0, address, data);
}

#define MAX_ITERATIONS 100000

Int32 DskAudio4_SendDaughtercardCommand(Uint8 command, Uint8 address, Uint8 data)
{
	Uint32 packet, bit_count, iterations;
	Int32 data_out = 0;
	
	packet = (((Uint32)0x07) << 21) | ((Uint32)command << 19) | ((Uint32)address << 11) | ((Uint32)data << 3);
	DskAudio4_SetClock(0);					// set clock low
	for(iterations=0;iterations < MAX_ITERATIONS;iterations++)
		if(DskAudio4_ReadClock() == 0)		// wait for daughtercard to respond
			break;
	if(iterations >= MAX_ITERATIONS)
		return -1;

	for(bit_count = 0;bit_count < 24;bit_count++) {
		DskAudio4_SetData((packet & 0x800000)?1:0);	// set data to current bit in packet
		packet <<= 1;
		DskAudio4_SetClock(1);				// set clock high
		for(iterations=0;iterations < MAX_ITERATIONS;iterations++)
			if(DskAudio4_ReadClock() != 0)	// wait for daughtercard to respond
				break;
		if(iterations >= MAX_ITERATIONS)
			return -1;
		data_out <<= 1;						// save returned data from daughtercard
		if(DskAudio4_ReadData())
			data_out |= 1;
		DskAudio4_SetClock(0);				// set clock low
		for(iterations=0;iterations < MAX_ITERATIONS;iterations++)
			if(DskAudio4_ReadClock() == 0)	// wait for daughtercard to respond
				break;
		if(iterations >= MAX_ITERATIONS)
			return -1;
	}
	return data_out >> 3;
}


