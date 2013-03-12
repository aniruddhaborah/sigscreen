// codec.h
// test program for DSK_AUDIO4 daughterboard on 6713 DSK
// Educational DSP, LLC - 2007
#ifndef CODEC_H_
#define CODEC_H_

//Pre processor defines
#define BUFFERLENGTH 4096
#define RADIX 2
#define DELTA (2*PI) / BUFFERLENGTH


//FFT struct.
typedef struct comp{
	float re;
	float im;
}Complex;


float maxH, maxV;
//unsigned char codec, channel, input_source, flag = 0;

int indexH,indexV,i;
short iData[BUFFERLENGTH]; 

//Twiddle constants
Complex W[BUFFERLENGTH/RADIX];

//Input buffers
Complex left[BUFFERLENGTH];
Complex right[BUFFERLENGTH];
Complex bottom[BUFFERLENGTH];

//extern int buff_idex = 0;
 short iData[BUFFERLENGTH];


 void Init_McBSP(McBSP *, int );
                                      

#endif
