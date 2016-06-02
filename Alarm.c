// Alarm.c

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "ST7735.h"
#include "fixed.h"
#include "Alarm.h"
#include "PLL.h"
#include "Clock.h"
#include "../inc/tm4c123gh6pm.h"

#define PB0       (*((volatile uint32_t *)0x40005004))

volatile int alarmMinutes = 0;
volatile int alarmHours = 0;
volatile int alarmSet = 0;


void Alarm_Init(){
	volatile uint32_t delay;
	
  SYSCTL_RCGCGPIO_R |= 0x02;  // 1) activate clock for Port B
  delay = SYSCTL_RCGCGPIO_R;        // allow time for clock to start
  GPIO_PORTB_CR_R |= 0x01;          // allow changes to PD1
	GPIO_PORTB_DIR_R |= 0x01;         // make PB0 output
  GPIO_PORTB_AFSEL_R &= ~0x01;      // disable alt funct on PB0
  GPIO_PORTB_DEN_R |= 0x01;         // enable digital I/O on PB0
																		// configure PB0 as GPIO
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFFF0);
  GPIO_PORTB_AMSEL_R &= ~0x01;
	
}

const unsigned short Wave[32] = {  
  125,143,159,175,189,200,208,213,215,213,208,
  200,189,175,159,143,125,107,91,75,61,50,
  42,37,35,37,42,50,61,75,91,107
};  

void checkAlarm(void){
	if (alarmSet == 1) {
		if (currentMinutes == alarmMinutes && currentHours == alarmHours){
			//alarmSet = 0;
			soundAlarm();
		}
	}
}

void soundAlarm(void){
	for(int j = 0; j <= 100; j++){
		for(int i = 0; i <= 240; i++){
			PB0 = Wave[i];
		}
	}
}

void updateAlarmTime(void){
	ST7735_SetCursor(0,3);
	printf("%02d:%02d", alarmHours, alarmMinutes);
}

void increaseAlarmMinutes(void){
	if(alarmMinutes == 59){
		increaseAlarmHours();
		alarmMinutes = 0;
	} else {
		alarmMinutes++;
	}
}

void increaseAlarmHours(void){
	if(alarmHours == 23){
		alarmHours = 0;
	} else {
		alarmHours++;
	}
}

void drawAlarm(void){
	if (alarmSet == 0){
		ST7735_DrawPixel( 122,  3, ST7735_BLACK);
		ST7735_DrawPixel( 123,  2, ST7735_BLACK);
		ST7735_DrawPixel( 123,  3, ST7735_BLACK);
		ST7735_DrawPixel( 123,  4, ST7735_BLACK);
		ST7735_DrawPixel( 124,  1, ST7735_BLACK);
		ST7735_DrawPixel( 124,  2, ST7735_BLACK);
		ST7735_DrawPixel( 124,  3, ST7735_BLACK);
		ST7735_DrawPixel( 124,  4, ST7735_BLACK);
		ST7735_DrawPixel( 124,  5, ST7735_BLACK);
		ST7735_DrawPixel( 126,  1, ST7735_BLACK);
		ST7735_DrawPixel( 126,  5, ST7735_BLACK);
		ST7735_DrawPixel( 127,  2, ST7735_BLACK);
		ST7735_DrawPixel( 127,  3, ST7735_BLACK);
		ST7735_DrawPixel( 127,  4, ST7735_BLACK);
	} else if (alarmSet == 1){
		ST7735_DrawPixel( 122,  3, ST7735_YELLOW);
		ST7735_DrawPixel( 123,  2, ST7735_YELLOW);
		ST7735_DrawPixel( 123,  3, ST7735_YELLOW);
		ST7735_DrawPixel( 123,  4, ST7735_YELLOW);
		ST7735_DrawPixel( 124,  1, ST7735_YELLOW);
		ST7735_DrawPixel( 124,  2, ST7735_YELLOW);
		ST7735_DrawPixel( 124,  3, ST7735_YELLOW);
		ST7735_DrawPixel( 124,  4, ST7735_YELLOW);
		ST7735_DrawPixel( 124,  5, ST7735_YELLOW);
		ST7735_DrawPixel( 126,  1, ST7735_YELLOW);
		ST7735_DrawPixel( 126,  5, ST7735_YELLOW);
		ST7735_DrawPixel( 127,  2, ST7735_YELLOW);
		ST7735_DrawPixel( 127,  3, ST7735_YELLOW);
		ST7735_DrawPixel( 127,  4, ST7735_YELLOW);
	}
}

