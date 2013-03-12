// talkthru.c
// test program for DSK_AUDIO4 daughterboard on 6713 DSK
// Educational DSP, LLC - 2007
#include <stdio.h>
#include <c6x.h>
#include "c6x11dsk.h"   
#include "codec.h"
#include "dsk_audio4.h"


FILE *out;

float gain;
unsigned char codec, channel, input_source, flag = 0;
unsigned int data;

//Firas - Added the following variables, which will hold the data.
Uint8 Mic0L_data=0, Mic0L_20DB=0, Mic0R_data=0, Mic0R_20DB=0, Mic1L_data=0 , Mic1L_20DB=0, Mic1R_data=0, Mic1R_20DB=0;

//Firas - Buffer
#define BUFFERLENGTH 1024

Uint8 Mic0L_buffer[BUFFERLENGTH];
Uint8 Mic0R_buffer[BUFFERLENGTH];
Uint8 Mic1L_buffer[BUFFERLENGTH];
Uint8 Mic1R_buffer[BUFFERLENGTH];
int Mic0L_bufindex = 0, Mic0R_bufindex = 0, Mic1L_bufindex = 0, Mic1R_bufindex = 0;
int counter;


int main()
{    

	for (counter=0; counter<BUFFERLENGTH; counter ++){
		Mic0L_buffer[counter]=0;
		Mic0R_buffer[counter]=0;
		Mic1L_buffer[counter]=0;
		Mic1R_buffer[counter]=0;
	}


	DskAudio4_Init();					// reset daughtercard and init 
    //out = fopen( "Mic0L_buffer.txt", "w" );

	CSR=0x100;			        		// disable all interrupts
  	IER=1;								// disable all interrupts except NMI

	*(unsigned char *)0x90080006 = 0x03;// McBSPs to J3	

	*(unsigned volatile int *)IMH = 0x08203DC3; // assign McBSP1 to INT11/12	
	
	// configure serial port 1 as the master on the serial connection 
	// to the PCM3794 codec(s).  The McBSP generates the bit clock and L/R clock 
	// by dividing down the master clock sent to it from the daughtercard 	
	Init_McBSP(McBSP1_Base, 1); 		// master
	Init_McBSP(McBSP0_Base, 0); 		// slave

 	IER |= 0x1002;                     // enable McBSP1 Rx interrupt (12) 
  	ICR = 0xffff;                      // clear all pending interrupts 
  	CSR |= 1;                          // set GIE 

  	while(1) { 		


  		DskAudio4_SetLineOutAnalogGain(0, PCM3793_REG_LEFT, 5);
		DskAudio4_SetLineOutAnalogGain(0, PCM3793_REG_RIGHT, 5);
		DskAudio4_SetLineOutAnalogGain(1, PCM3793_REG_LEFT, 5);
		DskAudio4_SetLineOutAnalogGain(1, PCM3793_REG_RIGHT, 5);		 

		//Mic0R configuration
		Mic0R_20DB |= PCM3793_REG_VCM_POWER_CMT_G20R; 
		Mic0R_data |= PCM3793_REG_AIN_SEL_AIR_AIN1; 

		//Mic0R_buffer. Default to 20DB
		Mic0R_buffer[Mic0R_bufindex++] = Mic0R_data;
		//printf("Mic0R_buffer 0x%x\n", Mic0R_data );

		//DskAudio4_WriteCodecSetting(0, PCM3793_REG_VCM_POWER, Mic0R_buffer[Mic0R_bufindex]);
		//out = fopen( "Mic0R_buffer.txt", "a+" );
		printf("%x ", Mic0R_buffer[Mic0R_bufindex] );
		//fclose (out);
		//Send to register below for 0DB
		//DskAudio4_WriteCodecSetting(0, PCM3793_REG_AIN_SEL, Mic0R_buffer[Mic0R_bufindex]);
		if (Mic0R_bufindex >= BUFFERLENGTH) Mic0R_bufindex = 0; //check for end of buffer


		//Mic0L configuration
		Mic0L_20DB |= PCM3793_REG_VCM_POWER_CMT_G20L; 
		Mic0L_data |= PCM3793_REG_AIN_SEL_AIL_AIN1; 
		//Mic0L_buffer. Default to 20DB
		Mic0L_buffer[Mic0L_bufindex++] = Mic0L_20DB;
		//DskAudio4_WriteCodecSetting(0, PCM3793_REG_VCM_POWER, Mic0L_buffer[Mic0L_bufindex]);
		//printf("Mic0L_buffer %x\n", Mic0L_buffer[Mic0L_bufindex] );
		//printf ("Mic0L_buffer output <%d>\n", Mic0L_buffer[Mic0L_bufindex]);
		//out = fopen( "Mic0L_buffer.txt", "a+" );
		//fprintf(out, "%x ", Mic0L_buffer[Mic0L_bufindex] );
		//fclose (out);
		//Send to register below for 0DB
		//DskAudio4_WriteCodecSetting(0, PCM3793_REG_AIN_SEL, Mic0L_buffer[Mic0L_bufindex]);
		if (Mic0L_bufindex >= BUFFERLENGTH) Mic0L_bufindex = 0; //check for end of buffer

	  	//Mic1R configuration
		Mic1R_20DB |= PCM3793_REG_VCM_POWER_CMT_G20R; 
		Mic1R_data |= PCM3793_REG_AIN_SEL_AIR_AIN1; 
		//Mic1R_buffer. Default to 20DB
		Mic1R_buffer[Mic1R_bufindex++] = Mic1R_20DB;
		//DskAudio4_WriteCodecSetting(1, PCM3793_REG_VCM_POWER, Mic1R_buffer[Mic1R_bufindex]);
		//printf("Mic1R_buffer %x\n", Mic0L_buffer[Mic0L_bufindex] );
		//Send to register below for 0DB
		//DskAudio4_WriteCodecSetting(1, PCM3793_REG_AIN_SEL, Mic1R_buffer[Mic1R_bufindex]);
		if (Mic1R_bufindex >= BUFFERLENGTH) Mic1R_bufindex = 0; //check for end of buffer

	  	//Mic1L configuration
		Mic1L_20DB |= PCM3793_REG_VCM_POWER_CMT_G20L; 
		Mic1L_data |= PCM3793_REG_AIN_SEL_AIL_AIN1; 
		//Mic1L_buffer. Default to 20DB
		Mic1L_buffer[Mic1L_bufindex++] = Mic1L_20DB;
		//DskAudio4_WriteCodecSetting(1, PCM3793_REG_VCM_POWER, Mic1L_buffer[Mic1L_bufindex]);
		//Send to register below for 0DB
		//DskAudio4_WriteCodecSetting(1, PCM3793_REG_AIN_SEL, Mic1L_buffer[Mic1L_bufindex]);
		if (Mic1L_bufindex >= BUFFERLENGTH) Mic1L_bufindex = 0; //check for end of buffer
					
	}
}   
