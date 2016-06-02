#include "Clock.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "ST7735.h"
#include "fixed.h"
#include "Alarm.h"
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"

int cx = 64;
int cy = 90;
int radius = 50;

volatile int currentSeconds = 0;
volatile int currentMinutes = 0;
volatile int currentHours = 0;
volatile int updateSeconds = 0;
volatile int updateMinutes = 0;
volatile int updateHours = 0;
volatile int modeSet = 0;

void drawClock(void){
	ST7735_Circle(cx, cy, radius, ST7735_YELLOW);
	if (currentMinutes != 0) {
		ST7735_Line(cx, cy, xVals[currentMinutes - 1], yVals[currentMinutes - 1], ST7735_BLACK);
	} else {
		ST7735_Line(cx, cy, xVals[59], yVals[59], ST7735_BLACK);
	}
	if (currentHours != 0) {
		ST7735_Line(cx, cy, xValh[currentHours - 1], yValh[currentHours - 1], ST7735_BLACK);
	} else {
		ST7735_Line(cx, cy, xValh[23], yValh[23], ST7735_BLACK);
	}
	if (alarmMinutes != 0) {
		ST7735_Line(cx, cy, xVals[alarmMinutes - 1], yVals[alarmMinutes - 1], ST7735_BLACK);
	} else {
		ST7735_Line(cx, cy, xVals[59], yVals[59], ST7735_BLACK);
	}
	if (alarmHours != 0) {
		ST7735_Line(cx, cy, xValh[alarmHours - 1], yValh[alarmHours - 1], ST7735_BLACK);
	} else {
		ST7735_Line(cx, cy, xValh[23], yValh[23], ST7735_BLACK);
	}
	if (alarmSet == 1) {
		ST7735_Line(cx, cy, xVals[alarmMinutes], yVals[alarmMinutes], ST7735_BLUE);
		ST7735_Line(cx, cy, xValh[alarmHours], yValh[alarmHours], ST7735_BLUE);
	}
	ST7735_Line(cx, cy, xVals[currentMinutes], yVals[currentMinutes], ST7735_YELLOW);
	ST7735_Line(cx, cy, xValh[currentHours], yValh[currentHours], ST7735_YELLOW);
}

void updateDigitalTime(void){
	currentSeconds++;
	if(currentSeconds == 60){
		currentMinutes++;
		currentSeconds = 0;
		if(currentMinutes == 60){
			currentHours++;
			currentMinutes = 0;
			if(currentHours == 24){
				currentHours = 0;
			}
		}
	}
	ST7735_SetCursor(0,1);
	printf("%02d:%02d:%02d", currentHours, currentMinutes, currentSeconds);
}

void increaseSeconds(void){
	if(currentSeconds == 59){
		increaseMinutes();
		currentSeconds = 0;
	} else {
		currentSeconds++;
	}
}

void increaseMinutes(void){
	if(currentMinutes == 59){
		increaseHours();
		currentMinutes = 0;
	} else {
		currentMinutes++;
	}
}

void increaseHours(void){
	if(currentHours == 23){
		currentHours = 0;
	} else {
		currentHours++;
	}
}

void checkInput(void) {
	if(updateSeconds == 1){
		increaseSeconds();
		updateSeconds = 0;
	}
	if(updateMinutes == 1){
		increaseMinutes();
		updateMinutes = 0;
	}
	if(updateHours == 1){
		increaseHours();
		updateHours = 0;
	}
}

void drawMode(void){
	if (modeSet == 0){
		ST7735_SetCursor(0,0);
		printf("Current Time*");
		ST7735_SetCursor(0,2);
		printf("Alarm Time ");
	} else {
		ST7735_SetCursor(0,0);
		printf("Current Time ");
		ST7735_SetCursor(0,2);
		printf("Alarm Time*");
	}
}
