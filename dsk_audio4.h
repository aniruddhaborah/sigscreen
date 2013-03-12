// dsk_audio4.h
// configuration programming interface for the DSK_AUDIO4 daughtercard
// Educational DSP, LLC - 2007

#ifndef DSK_AUDIO4_H_INCLUDED
#define DSK_AUDIO4_INCLUDED

#include <tistdtypes.h>						// for standard type definitions
#include "pcm3793.h"

// defines for SelectInputSource function arguments
#define DSK_AUDIO4_INPUT_LINE			0	// use line input
#define DSK_AUDIO4_INPUT_MIC_0DB		1	// use microphone, no preamp
#define DSK_AUDIO4_INPUT_MIC_20DB		2	// use microphone with 20db preamp

// API function declarations
void DskAudio4_Init(void);
Int16 DskAudio4_SelectInputSource(Uint8, Uint8, Uint8);
Int16 DskAudio4_SetAdcAnalogGain(Uint8, Uint8, float);
Int16 DskAudio4_SetDacInputAttenuation(Uint8, Uint8, float);
Int16 DskAudio4_SetLineOutAnalogGain(Uint8, Uint8, float);
Int16 DskAudio4_ResetDaughtercardToDefaults(void);
Int32 DskAudio4_GetDaughtercardInfo(void);
Int16 DskAudio4_WriteCodecSetting(Uint8, Uint8, Uint8);

// support function declarations
Int32 DskAudio4_SendDaughtercardCommand(Uint8, Uint8, Uint8);

// DSK hardware abstraction layer (HAL) functions
void DskAudio4_ResetDaughtercard(void);
void DskAudio4_SetClock(Uint8);
void DskAudio4_SetData(Uint8);
Uint8 DskAudio4_ReadClock();
Uint8 DskAudio4_ReadData();

// commands for daughtercard communications
#define DSK_AUDIO4_CMD_RESET				0
#define DSK_AUDIO4_CMD_READ					1
#define DSK_AUDIO4_CMD_WRITE0				2
#define DSK_AUDIO4_CMD_WRITE1				3

#define DSK_AUDIO4_READ_DCARD_DCARDTYPE		0
#define DSK_AUDIO4_READ_DCARD_HWREV			1
#define DSK_AUDIO4_READ_DCARD_SWREV_H		2
#define DSK_AUDIO4_READ_DCARD_SWREV_L		3


#endif	// DSK_AUDIO4_H_INCLUDED
