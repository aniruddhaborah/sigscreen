// dsk_audio4_hal_dsk6713.c
// configuration programming interface for the DSK_AUDIO4 daughtercard
// hardware abstraction functions for the TMS320C6713 DSK
// Educational DSP, LLC - 2007

#include "dsk_audio4.h"

static volatile Uint8 *pDcReg = (Uint8 *)0x90080001;

#define DSK_AUDIO4_HAL_CLOCK_OUT_BIT	0x01
#define DSK_AUDIO4_HAL_DATA_OUT_BIT		0x02
#define DSK_AUDIO4_HAL_CLOCK_IN_BIT		0x10
#define DSK_AUDIO4_HAL_DATA_IN_BIT		0x20
#define DSK_AUDIO4_HAL_RESET_BIT		0x08

static Uint8 DcRegPhantom;

void DskAudio4_Init(void)
{
	DcRegPhantom = 0;
	*pDcReg = DcRegPhantom;
}

void DskAudio4_ResetDaughtercard(void)
{
	DcRegPhantom = DSK_AUDIO4_HAL_RESET_BIT;
	*pDcReg = DcRegPhantom;
	DcRegPhantom = 0;
	*pDcReg = DcRegPhantom;
}

void DskAudio4_SetClock(Uint8 value)
{
	if(value)
		DcRegPhantom |= DSK_AUDIO4_HAL_CLOCK_OUT_BIT;
	else
		DcRegPhantom &= ~DSK_AUDIO4_HAL_CLOCK_OUT_BIT;
	*pDcReg = DcRegPhantom;
}

void DskAudio4_SetData(Uint8 value)
{
	if(value)
		DcRegPhantom |= DSK_AUDIO4_HAL_DATA_OUT_BIT;
	else
		DcRegPhantom &= ~DSK_AUDIO4_HAL_DATA_OUT_BIT;
	*pDcReg = DcRegPhantom;
}


Uint8 DskAudio4_ReadClock()
{
	return *pDcReg & DSK_AUDIO4_HAL_CLOCK_IN_BIT;
}

Uint8 DskAudio4_ReadData()
{
	return *pDcReg & DSK_AUDIO4_HAL_DATA_IN_BIT;
}

