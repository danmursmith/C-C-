#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "ST7735.h"
#include "fixed.h"
#include "PLL.h"
#include "Clock.h"
#include "Alarm.h"
#include "../inc/tm4c123gh6pm.h"


void switchInit(void){
	SYSCTL_RCGCGPIO_R |= 0x00000008;           // Port D clock
  long delay = SYSCTL_RCGC2_R;      // wait 3-5 bus cycles
  GPIO_PORTD_DIR_R &= ~0x3E;        // PD4,3,2,1 input 
  GPIO_PORTD_AFSEL_R &= ~0x3E;      // not alternative
  GPIO_PORTD_AMSEL_R &= ~0x3E;      // no analog
  GPIO_PORTD_PCTL_R &= ~0x000FFFFF; // bits for PD4,PD3,PD2,PD1
  GPIO_PORTD_DEN_R |= 0x3E;         // enable PD4,PD3,PD2,PD1
}

void checkButtons(void){
	long hours = GPIO_PORTD_DATA_R&0x02;    // PD1
	long minutes = GPIO_PORTD_DATA_R&0x04;  // PD2
	long mode = GPIO_PORTD_DATA_R&0x08;  		// PD3
	long alarm = GPIO_PORTD_DATA_R&0x20;  	// PD4
	if(mode == 0x08){
		if (modeSet == 1){
			modeSet = 0;
		} else {
			modeSet = 1;
		}
	}
	if(modeSet == 0){
		if(minutes == 0x04){
			increaseMinutes();
		}
		if(hours == 0x02){
			increaseHours();
		}
	} else {
		if(minutes == 0x04){
			increaseAlarmMinutes();
		}
		if(hours == 0x02){
			increaseAlarmHours();
		}
	}
	if(alarm == 0x20){
		if (alarmSet == 1){
			alarmSet = 0;
			ST7735_Line(cx, cy, xVals[alarmMinutes - 1], yVals[alarmMinutes - 1], ST7735_BLACK);
			ST7735_Line(cx, cy, xValh[alarmHours - 1], yValh[alarmHours - 1], ST7735_BLACK);
		} else {
			alarmSet = 1;
		}
	}
}
