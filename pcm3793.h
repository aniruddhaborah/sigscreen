// PCM3793.h
// register definitions for the PCM3793/PCM3794 codec
// Educational DSP, LLC - 2007

#ifndef PCM3793_H_INCLUDED
#define PCM3793_H_INCLUDED

// register address definitions
#define PCM3793_REG_LEFT  				0
#define PCM3793_REG_RIGHT 				1

// headphone/line output volume control
#define PCM3793_REG_HPAL_VOL			0x40
#define PCM3793_REG_HPAR_VOL			0x41
#define PCM3793_REG_HPAx_VOL_MUTE		(0x1 << 6)

// speaker output volume control
#define PCM3793_REG_SPAL_VOL			0x42	// not used in PCM3794
#define PCM3793_REG_SPAR_VOL			0x43	// not used in PCM3794

// DAC attentuation control
#define PCM3793_REG_DAC_ATTNL			0x44
#define PCM3793_REG_DAC_ATTNR			0x45
#define PCM3793_REG_DAC_MUTE			(0x1 << 6)

// DAC configuration control
#define PCM3793_REG_DAC_CNFIG			0x46
#define PCM3793_REG_DAC_CNFIG_DEM_OFF	(0x0 << 6)
#define PCM3793_REG_DAC_CNFIG_DEM_32k	(0x1 << 6)
#define PCM3793_REG_DAC_CNFIG_DEM_44k	(0x2 << 6)
#define PCM3793_REG_DAC_CNFIG_DEM_48k	(0x3 << 6)
#define PCM3793_REG_DAC_CNFIG_PFM_I2S	(0x0 << 4)
#define PCM3793_REG_DAC_CNFIG_PFM_RJUST	(0x1 << 4)
#define PCM3793_REG_DAC_CNFIG_PFM_LJUST	(0x2 << 4)
#define PCM3793_REG_DAC_CNFIG_PFM_DSP	(0x3 << 4)
#define PCM3793_REG_DAC_CNFIG_OVER		(0x1 << 0)

// speaker amplifier configuration
#define PCM3793_REG_SPA_FREQ			0x47	// not used in PCM3794

// analog mixer power cotrol
#define PCM3793_REG_MIX_POWER			0x48
#define PCM3793_REG_MIX_POWER_PMXL		(0x01 << 0)
#define PCM3793_REG_MIX_POWER_PMXR		(0x01 << 1)

// DAC/HPA/SPA power control
#define PCM3793_REG_OUT_POWER			0x49
#define PCM3793_REG_OUT_POWER_PBIS		(0x01 << 7)	
#define PCM3793_REG_OUT_POWER_PDAR		(0x01 << 6)	
#define PCM3793_REG_OUT_POWER_PDAL		(0x01 << 5)	
#define PCM3793_REG_OUT_POWER_PHPC		(0x01 << 4)	
#define PCM3793_REG_OUT_POWER_PHPR		(0x01 << 3)	
#define PCM3793_REG_OUT_POWER_PHPL		(0x01 << 2)	
#define PCM3793_REG_OUT_POWER_PSPR		(0x01 << 1)	
#define PCM3793_REG_OUT_POWER_PSPL		(0x01 << 0)	

// analog output configuration
#define PCM3793_REG_OUT_CNFIG			0x4A
#define PCM3793_REG_OUT_CNFIG_CMS_COM	(0x00 << 4)
#define PCM3793_REG_OUT_CNFIG_CMS_MON	(0x01 << 4)
#define PCM3793_REG_OUT_CNFIG_CMS_HPL	(0x02 << 4)
#define PCM3793_REG_OUT_CNFIG_CMS_HPR	(0x04 << 4)
#define PCM3793_REG_OUT_CNFIG_HPS_STE	(0x00 << 2)
#define PCM3793_REG_OUT_CNFIG_HPS_SIN	(0x01 << 2)
#define PCM3793_REG_OUT_CNFIG_HPS_DIF	(0x02 << 2)
#define PCM3793_REG_OUT_CNFIG_PCOM		(0x01 << 0)

// headphone insertion detection
#define PCM3793_REG_HPA_INS				0x4B

// speaker amp shutdown release
#define PCM3793_REG_SPA_SDREL			0x4C	// not used in PCM3794

// speaker amp shutdown readback
#define PCM3793_REG_SD_RDBACK			0x4D	// not used in PCM3794

// ADC input volume control
#define PCM3793_REG_ADC_VOLL			0x4F
#define PCM3793_REG_ADC_VOLR			0x50

// ADC configuration control
#define PCM3793_REG_ADC_CNFIG			0x51
#define PCM3793_REG_ADC_CNFIG_HPF_4HZ	(0x00 << 6)
#define PCM3793_REG_ADC_CNFIG_HPF_240HZ	(0x01 << 6)
#define PCM3793_REG_ADC_CNFIG_HPF_DIS	(0x03 << 6)
#define PCM3793_REG_ADC_CNFIG_RFM_I2S	(0x00 << 0)
#define PCM3793_REG_ADC_CNFIG_RFM_RJUST	(0x01 << 0)
#define PCM3793_REG_ADC_CNFIG_RFM_LJUST	(0x02 << 0)
#define PCM3793_REG_ADC_CNFIG_RFM_DSP	(0x03 << 0)

// ADC/MIC/PGA power control
#define PCM3793_REG_ADC_POWER			0x52
#define PCM3793_REG_ADC_POWER_PAIR		(0x01 << 5)
#define PCM3793_REG_ADC_POWER_PAIL		(0x01 << 4)
#define PCM3793_REG_ADC_POWER_PADS		(0x01 << 3)
#define PCM3793_REG_ADC_POWER_PMCB		(0x01 << 2)
#define PCM3793_REG_ADC_POWER_PADR		(0x01 << 1)
#define PCM3793_REG_ADC_POWER_PADL		(0x01 << 0)

// automatic level control
#define PCM3793_REG_ALC					0x53
#define PCM3793_REG_ALC_RALC			(0x01 << 7)
#define PCM3793_REG_ALC_RRTC			(0x01 << 5)
#define PCM3793_REG_ALC_RATC			(0x01 << 4)
#define PCM3793_REG_ALC_RCP_2DB			(0x00 << 2)
#define PCM3793_REG_ALC_RCP_6DB			(0x01 << 2)
#define PCM3793_REG_ALC_RCP_12DB		(0x02 << 2)
#define PCM3793_REG_ALC_RLV_0DB			(0x00 << 0)
#define PCM3793_REG_ALC_RLV_6DB			(0x01 << 0)
#define PCM3793_REG_ALC_RLV_12DB		(0x02 << 0)
#define PCM3793_REG_ALC_RLV_24DB		(0x03 << 0)

// master/slave select for audio interface
#define PCM3793_REG_MODE				0x54
#define PCM3793_REG_MODE_SLAVE			(0x00 << 2)
#define PCM3793_REG_MODE_MASTER			(0x01 << 2)
#define PCM3793_REG_MODE_BIT0			(0x01 << 0)

// system reset and clock selection
#define PCM3793_REG_SYS_RESET			0x55
#define PCM3793_REG_SYS_RESET_SRST		(0x01 << 7)

// BCK config, sample rate control, zero-cross
#define PCM3793_REG_SYS_CNFIG			0x56
#define PCM3793_REG_SYS_CNFIG_MBST		(0x01 << 7)
#define PCM3793_REG_SYS_CNFIG_ATOD		(0x01 << 3)
#define PCM3793_REG_SYS_CNFIG_ZCRS		(0x01 << 0)
#define PCM3793_REG_SYS_CNFIG_MSR_SHIFT	4

// analog input selection
#define PCM3793_REG_AIN_SEL				0x57
#define PCM3793_REG_AIN_SEL_AD2S_SIN	(0x00 << 7)
#define PCM3793_REG_AIN_SEL_AD2S_DIF	(0x01 << 7)
#define PCM3793_REG_AIN_SEL_AIL_DISC	(0x00 << 0)
#define PCM3793_REG_AIN_SEL_AIL_AIN1	(0x01 << 0)
#define PCM3793_REG_AIN_SEL_AIL_AIN2	(0x02 << 0)
#define PCM3793_REG_AIN_SEL_AIL_AIN3	(0x03 << 0)
#define PCM3793_REG_AIN_SEL_AIR_DISC	(0x00 << 4)
#define PCM3793_REG_AIN_SEL_AIR_AIN1	(0x01 << 4)
#define PCM3793_REG_AIN_SEL_AIR_AIN2	(0x02 << 4)
#define PCM3793_REG_AIN_SEL_AIR_AIN3	(0x03 << 4)

// analog mixer select
#define PCM3793_REG_AIN_MIX				0x58
#define PCM3793_REG_AIN_MIX_MXR2		(0x01 << 6)
#define PCM3793_REG_AIN_MIX_MXR1		(0x01 << 5)
#define PCM3793_REG_AIN_MIX_MXR0		(0x01 << 4)
#define PCM3793_REG_AIN_MIX_MXL2		(0x01 << 2)
#define PCM3793_REG_AIN_MIX_MXL1		(0x01 << 1)
#define PCM3793_REG_AIN_MIX_MXL0		(0x01 << 0)

// analog input path gain
#define PCM3793_REG_AIN_PATH			0x59

// VCOM control, mic boost
#define PCM3793_REG_VCM_POWER			0x5A
#define PCM3793_REG_VCM_POWER_CMT_NOM	(0x00 << 4)
#define PCM3793_REG_VCM_POWER_CMT_SLOW	(0x01 << 4)
#define PCM3793_REG_VCM_POWER_CMT_FST	(0x02 << 4)
#define PCM3793_REG_VCM_POWER_CMT_FSTR	(0x03 << 4)
#define PCM3793_REG_VCM_POWER_CMT_G20R	(0x01 << 1)
#define PCM3793_REG_VCM_POWER_CMT_G20L	(0x01 << 0)

// base boost gain control
#define PCM3793_REG_BST_BASE			0x5C
#define PCM3793_REG_BST_BASE_LPAE		(0x01 << 7)

// midrange boost gain control
#define PCM3793_REG_BST_MID				0x5D

// treble boost gain control
#define PCM3793_REG_BST_TREB			0x5E

// sound effect control
#define PCM3793_REG_SND_3D				0x5F
#define PCM3793_REG_SND_3D_SDAS			(0x01 << 7)
#define PCM3793_REG_SND_3D_3DEN			(0x01 << 6)
#define PCM3793_REG_SND_3D_3FL0			(0x01 << 4)

// notch filter control
#define PCM3793_REG_NCH_EN				0x60
#define PCM3793_REG_NCH_EN_NEN2			(0x01 << 7)
#define PCM3793_REG_NCH_EN_NEN1			(0x01 << 6)
#define PCM3793_REG_NCH_EN_NUP2			(0x01 << 5)
#define PCM3793_REG_NCH_EN_NUP1			(0x01 << 4)
#define PCM3793_REG_NCH_EN_MXEN			(0x01 << 0)

// 1st stage notch filter coefficients
#define PCM3793_REG_NCH_1A1L			0x61
#define PCM3793_REG_NCH_1A1H			0x62
#define PCM3793_REG_NCH_1A2L			0x63
#define PCM3793_REG_NCH_1A2H			0x64

// 2nd stage notch filter coefficients
#define PCM3793_REG_NCH_2A1L			0x65
#define PCM3793_REG_NCH_2A1H			0x66
#define PCM3793_REG_NCH_2A2L			0x67
#define PCM3793_REG_NCH_2A2H			0x68



#endif	// PCM3793_H_INCLUDED
