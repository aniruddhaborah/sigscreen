// talkthru.c
// test program for DSK_AUDIO4 daughterboard on 6713 DSK
// Educational DSP, LLC - 2007

#include <stdio.h>
#include <c6x.h>
#include <math.h>
#include "c6x11dsk.h"  
#include "dsk_audio4.h"

int main()
{    

	DskAudio4_Init();					// reset daughtercard and init 

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

	while(1); // Stalls main and waits for interrupts

  		
}   
