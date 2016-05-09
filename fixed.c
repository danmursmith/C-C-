


#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"


void ST7735_sDecOut3(int32_t n){

	int nfirst=n/1000;																//n_temp will be the bit 

	if((n>9999)||(n<-9999)){										//top limit is 9999, minimum is -9999, print " *.***" each time n out of bounds
		printf(" *.***");
	  return;
		
	}else if(nfirst==0 && n<0){
		
		printf("-%d", nfirst);
		n*=-1;
		printf(".%03d", n%1000);
	}
	else if(n<0){															//negative values of n to print exactly 6 characters to the screen
	  printf("%d", nfirst);
		n*=-1;
		printf(".%03d", n%1000);
		
		
	}else if (n>=0){											
		printf(" %d.", nfirst);
		printf("%03d",n%1000);
	}
}
void ST7735_uBinOut8(uint32_t n){
	  //double ndiv=n>>8;
		//double ndiv=n/256;
	  uint16_t fract=0;							//right side of decimal for output
		uint16_t num=0;									//left side
		
		if(n>=256000){
				printf("***.**");
		}else{		
			  fract=(n%256)*100;				//conversion in this else statement 
				
		  	num=n/256;

			  fract/=256;					 
				printf("%3d.%.2d",num,fract);//truncate decimals for fract to 2 without rounding
			
		
		}
}
/**************ST7735_XYplotInit***************
 Specify the X and Y axes for an x-y scatter plot
 Draw the title and clear the plot area
 Inputs:  title  ASCII string to label the plot, null-termination
          minX   smallest X data value allowed, resolution= 0.001
          maxX   largest X data value allowed, resolution= 0.001
          minY   smallest Y data value allowed, resolution= 0.001
          maxY   largest Y data value allowed, resolution= 0.001
 Outputs: none
 assumes minX < maxX, and miny < maxY
*/

int32_t xSmallBound, xBigBound, ySmallBound, yBigBound;

void ST7735_XYplotInit(char *title, int32_t minX, int32_t maxX, int32_t minY, int32_t maxY){
		
		xSmallBound=minX;														//store bounds to be used outside initialization function
		xBigBound=maxX;
	  ySmallBound=minY;
	  yBigBound=maxY;
		ST7735_FillScreen(0);
		ST7735_SetCursor(0,0);
		ST7735_OutString(title);
	  ST7735_PlotClear(minY, maxY);
		
	
}
void ST7735_XYplot(uint32_t num, int32_t bufX[], int32_t bufY[]){
		for(uint32_t k=0;k<num;k+=1){
				uint32_t i,j;
				i=127*(bufX[k]-xSmallBound)/(xBigBound-xSmallBound);
				j=32+(127*(yBigBound-bufY[k]))/(yBigBound-ySmallBound);
				ST7735_DrawPixel(i, j, ST7735_BLUE);
		}

}
