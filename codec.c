// codec.c
// test program for DSK_AUDIO4 daughterboard on 6713 DSK
// Educational DSP, LLC - 2007
// ZZ

#include <c6x.h>
#include <math.h>
#include "c6x11dsk.h"
#include "codec.h"  
#include "csl_irq.h"
#include "csl_irqhal.h"

#define LEFT  0
#define RIGHT 1

#define SPEED 3450
#define DISTANCE_LEFT_RIGHT 0.88
#define DISTANCE_RIGHT_BOTTOM 0.47

volatile union {
	unsigned int uint;
	short channel[2];
	} TxData;    

//bitrev_index

	FILE *f_right;
	FILE *f_left;

		void bitrev_index(short *index, int nx)
{
	int i, j, k, radix = 2;
	short nbits, nbot, ntop, ndiff, n2, raddiv2;
	nbits = 0;
	i = nx;
	while (i > 1)
	{
		i = i >> 1;
		nbits++;
	}

	raddiv2 = radix >> 1;
	nbot = nbits >> raddiv2;
	nbot = nbot << raddiv2 - 1;
	ndiff = nbits & raddiv2;
	ntop = nbot + ndiff;
	n2 = 1 << ntop;
	index[0] = 0;
	
	for ( i = 1, j = n2/radix + 1; i < n2 - 1; i++)
	{
		index[i] = j - 1;
		for (k = n2/radix; k*(radix-1) < j; k /= radix)
			j -= k*(radix-1);
		j += k;
	}
	index[n2 - 1] = n2 - 1;
}

	//--------------------FFT Function ------------------------//
/* 
    cfftr2_dit is a builtin function used to calculate the FFT as follows:
    x points to a floating-point array of length 2*n which holds n complex input samples. 
    x must be double-word aligned. After running the function, the output will also be stored in x. 
    
    The output must be bit-reversed using the bit reverse function found in the FFT support: bit_rev.
    w points to a floating-point array of length n which holds the n/2” twiddle factors. 
    w can be created with the radix 2 twiddle generation function found in the FFT support: tw_genr2fft. 
    After creating the array, w must be bit-reversed using bit_rev.
    n is the length of the FFT in complex samples. n must be a power of 2 and greater than or equal to 32.    
*/


float maxH, maxV;
int flag = 1;
//unsigned char codec, channel, input_source, flag = 0;

int indexH,indexV,i;
short iData[BUFFERLENGTH]; 

//Twiddle constants
Complex W[BUFFERLENGTH/RADIX];

//Input buffers
 Complex left[BUFFERLENGTH];
 Complex right[BUFFERLENGTH];
 Complex bottom[BUFFERLENGTH];

 int buff_index = 0;
 float angle_left;
 float angle_right;

int find_angle_right (float time_delay){
	angle_right = acos();
}

int find_angle_left (float time_delay){
	angle_left = acos();
	
}

void FFT(Complex* x, Complex* w, short n)
{
     
    DSPF_sp_cfftr2_dit(x, w, n) ;			    	//TI floating-pt complex FFT
    bitrev_index(iData, n);		//produces index for bitrev() X 
    DSPF_sp_bitrev_cplx(x, iData, n);			    	//freq scrambled->bit-reverse x
} // End of FFT Function.

//-------------------PHAT Function ------------------------//
void PHAT(Complex* L, Complex* R, short PHAT_Size)
{
  short i;
  float a,Dummy_real,Dummy_imag;

   for (i = 0; i < PHAT_Size; i++)
  { 
   
   a =  ((sqrt(L[i].re*L[i].re+L[i].im*L[i].im)) * (sqrt(R[i].re*R[i].re+R[i].im*R[i].im)));
  Dummy_real = (((L[i].re * R[i].re)+(L[i].im * R[i].im)) / a);
  Dummy_imag = (((L[i].re * R[i].im)-(L[i].im * R[i].re)) / a);
  L[i].re = Dummy_real;
  L[i].im = Dummy_imag;
  }
}  // End of PHAT Function ----------------


//extern int buff_idex = 0;

void fill_buffers(float fdata0, float fdata1, float fdata2, float fdata3 )
{
    int i; 
	left[buff_index].re = fdata0;
	left[buff_index].im = 0.0;
	right[buff_index].re = fdata1;
	right[buff_index].im = 0.0;
	bottom[buff_index].re = fdata2;
	bottom[buff_index].im = 0.0;

	//Calculating the Twiddle factor for FFT
	if (flag){
	    for( i = 0 ; i < BUFFERLENGTH/RADIX ; i++ ) 
	    {
	    	
	    	W[i].re = cos(DELTA*i);			//real component of W
	  	    W[i].im = sin(DELTA*i);			//neg imag component
	    }

		for (i=0; i<BUFFERLENGTH; i++){
			left[i].re=0.0;
			right[i].re=0.0;
			bottom[i].re=0.0;
		}
		flag = 0;
		file = fopen ("output.txt", "w+");
	}
	

	buff_index++;
	if (buff_index % 256 == 0){
	    printf ("should get here\n");
		//Buffers are full, need ffts.
  		// Horizontal
    	FFT(left , W , BUFFERLENGTH);        // Perform FFT of Input.----> Left Input
    	FFT(right , W , BUFFERLENGTH);       // Right Input.
	    PHAT(left, right, BUFFERLENGTH);
	   	FFT(left, W, BUFFERLENGTH);

  		// Vertical
	    FFT(bottom , W ,BUFFERLENGTH);      // Bottom Input.
	    PHAT(right, bottom, BUFFERLENGTH);
	    FFT(right, W, BUFFERLENGTH);

//weighting function
left[1].re  =  (left[1].re) /2.7;
left[2].re  =  (left[2].re) /2.2;
left[3].re  =  (left[3].re) /1.4;
left[BUFFERLENGTH-3].re  =  (left[BUFFERLENGTH-3].re) /1.4;
left[BUFFERLENGTH-2].re  =  (left[BUFFERLENGTH-2].re) /2.2;
left[BUFFERLENGTH-1].re  =  (left[BUFFERLENGTH-1].re) /2.7;

right[1].re  =  (right[1].re) /2.7;
right[2].re  =  (right[2].re) /2.2;
right[3].re  =  (right[3].re) /1.4;
right[BUFFERLENGTH-3].re  =  (right[BUFFERLENGTH-3].re) /1.4;
right[BUFFERLENGTH-2].re  =  (right[BUFFERLENGTH-2].re) /2.2;
right[BUFFERLENGTH-1].re  =  (right[BUFFERLENGTH-1].re) /2.7;
	   
		//----------Below the Max index is calculated for values--------------------

	       maxH = 0.0;  // Initializing the MaxH value
	       
		   for (i = 1; i <  85 ; i++)//3-44
	       {
	          if ( (left[i].re) > maxH )
	          { 
	              maxH = left[i].re;
				  indexH = 85-i ;//44-I/ Getting the exact delay in terms of index as you subtract the block length
	          }         
	        }
		      
		  	for (i = (BUFFERLENGTH - 88); i < BUFFERLENGTH-1 ; i++)
	        {
	          	if ( (left[i].re) > maxH )
	            { 
	              maxH = left[i].re;
				  indexH = 8274-i; //8226-I/ Getting the exact delay in terms of index as you subtract the block length
	     		 // if ((IndexH > Max_Index)) IndexH = Max_Index;
	    		}
	 
	        }
	   
	//-----------------------------------------------------------------------------


	 maxV = 0.0;  // Initializing the MaxH value
	       
		   for (i = 1; i <  85 ; i++)
	         {
	          if ( (right[i].re) > maxV )
	            { 
	              maxV = right[i].re;
				  indexV = 85-i ;/// Getting the exact delay in terms of index as you subtract the block length
	        }
	         
	            }
		      
		  for (i = (BUFFERLENGTH - 88); i < BUFFERLENGTH-1 ; i++)
	         {
	          if ( (right[i].re) > maxV )
	            { 
	              maxV = right[i].re;
				  indexV = 4178-i; /// Getting the exact delay in terms of index as you subtract the block length BUFFERLENGTH+82
	     		 // if ((IndexH > Max_Index)) IndexH = Max_Index;
	        }
	 
	    }

	    f_right = fopen ("f_right", "a+");
	    fprintf (f_right, "%d ", indexH);
	    fclose(f_right);
	    //we have the 3450
	}

	if (buff_index == BUFFERLENGTH) {
		buff_index = 0;
	    //file print
	    //append

		/*
	    f_left = fopen ("f_left", "a+");
	    f_right = fopen ("f_right", "a+");
	    for (i=0;i < BUFFERLENGTH;i++){
	    	fprintf (f_right, "%f ", right[i].re);
	    	fprintf (f_right, "%f ", right[i].im);
	    	fprintf (f_left, "%f ", left[i].re);
	    	fprintf (f_left, "%f ", left[i].im);
	    }
	    fclose(f_right);
	    fclose(f_left);
	    */

	}
	return;
}

// Data is received from the codec as 2 16-bit words (left/right)
// packed into one 32-bit word.  The union allows the data to be accessed
// as a single entitiy when transferring to and from the serial port, but
// still be able to manipulate the left and right channels independently. 


interrupt void McBSP1_Rx_ISR()
{
	McBSP *port; 
	float fdata0, fdata1, fdata2, fdata3;

    
	//puts("OOHOOOOOOOOOOOOOOOOOOOOOOOOO");
	
	port  = McBSP1_Base;  
	TxData.uint = port->drr; // get input data from serial 1
	
	// process data here
	fdata0 = TxData.channel[LEFT];
	fdata1 = TxData.channel[RIGHT];

	port->dxr = TxData.uint; // send output data to serial 1

	port  = McBSP0_Base;  
	TxData.uint = port->drr; // get input data from serial 0
	
	// process data here
	fdata2 = TxData.channel[LEFT];
	fdata3 = TxData.channel[RIGHT];
	fill_buffers(fdata0, fdata1, fdata2, fdata3);

	port->dxr = TxData.uint; // send output data to serial 0
}

void Init_McBSP(McBSP *port, int master)
{   
	if(master) {
		port->spcr = 0;          /* reset port */
		port->pcr  = 0x00000A03; /* fsx/clkx output, fsr, clkr input */                          
		/* srg set up or clks/8, 32 bits, fsr width = 16bits - 48kHz */
		port->srgr = (1 << 28) + (31 << 16) + (15 << 8) + (7);
		/* srg set up for clks/12, 32 bits, fsr width = 16bits - 32kHz */
//		port->srgr = (1 << 28) + (31 << 16) + (15 << 8) + (11);
		/* srg set up for clks/16, 32 bits, fsr width = 16bits - 24kHz */
//		port->srgr = (1 << 28) + (31 << 16) + (15 << 8) + (15);
		/* srg set up for clks/24, 32 bits, fsr width = 16bits - 16kHz */
//		port->srgr = (1 << 28) + (31 << 16) + (15 << 8) + (23);
		port->rcr  = 0x000400A0; /* 1-phase, 32-bits */
		port->xcr  = 0x000400A0; 
		port->spcr = 0x00400000; /* start srg */ 
		port->spcr = 0x00C00000; /* start fsg */ 
		port->spcr = 0x00C10001; /* enable tx/rx */
		port->dxr  = 0;
	}  
	else { // is i2s_slave
		port->spcr = 0;          /* reset port */
		port->pcr  = 0x00000003; /* fsx/clkx/fsr/clkr input */                          
		port->srgr = 0;  		 /* srgr disabled */
		port->rcr  = 0x000400A0; /* 1-phase, 32-bits */
		port->xcr  = 0x000400A0; 
		port->spcr = 0x00010001; /* enable tx/rx */
		port->dxr  = 0;
	}
	
}
