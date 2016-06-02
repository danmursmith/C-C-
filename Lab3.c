// filename ******** Lab3.c ************** 


#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "ST7735.h"
#include "fixed.h"
#include "Lab2.h"
#include "Alarm.h"
#include "PLL.h"
#include "Heartbeat.h"
#include "Timer0A.h"
#include "Switch.h"
#include "Clock.h"
#include "../inc/tm4c123gh6pm.h"

#define PF1             (*((volatile uint32_t *)0x40025008))
#define M_PI 						acos(-1.0)
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode


void checkInput(void);
void drawMode(void);
void drawAlarm(void);

//volatile uint32_t ADCvalue;
//int i = 0;







unsigned int Errors,AnError;

int main(void){
	PLL_Init(Bus80MHz);                   // 80 MHz
	switchInit();
	Alarm_Init();
	Heartbeat_Init();
	Output_Init();              					// initialize output device
	EnableInterrupts();
	ST7735_SetCursor(0,0);
	printf("Current Time*");
	ST7735_SetCursor(0,1);
	printf("%02d:%02d:%02d", currentHours, currentMinutes, currentSeconds);
	ST7735_SetCursor(0,2);
	printf("Alarm Time");
	ST7735_SetCursor(0,3);
	printf("%02d:%02d", alarmHours, alarmMinutes);
  while(1){
    //PF1 ^= 0x02;  // toggles when running in main
		if(updateTime == 1){
			updateDigitalTime();
			updateTime = 0;
		}
		ST7735_SetCursor(0,1);
		printf("%02d:%02d:%02d", currentHours, currentMinutes, currentSeconds);
		updateAlarmTime();
		checkButtons();
		checkInput();
		drawClock();
		drawMode();
		drawAlarm();
		checkAlarm();
		Errors = 0;
	}
}




