#define PF2             (*((volatile uint32_t *)0x40025010))

extern volatile int updateTime;

void Timer0A_Init100HzInt(void);
void Timer0A_Handler(void);
