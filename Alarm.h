extern volatile int alarmMinutes;
extern volatile int alarmHours;
extern volatile int alarmSet;

void Alarm_Init(void);
void checkAlarm(void);
void soundAlarm(void);
void updateAlarmTime(void);
void increaseAlarmMinutes(void);
void increaseAlarmHours(void);
