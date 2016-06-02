extern int cx;
extern int cy;
extern int radius;

extern volatile int currentSeconds;
extern volatile int currentMinutes;
extern volatile int currentHours;
extern volatile int updateSeconds;
extern volatile int updateMinutes;
extern volatile int updateHours;
extern volatile int modeSet;


static int xVals[60] = {64,70,76,81,87,
93,97,102,103,104,
106,107,109,110,112,
114,112,110,109,107,
106,104,103,102,97,
93,87,81,76,70,
64,58,52,47,41,
35,31,26,25,23,
21,19,18,17,15,
14,15,17,18,19,
21,23,25,26,31,
35,41,47,52,58};

static int yVals[60] = {40,42,43,45,47,
48, 52, 56, 61, 65,
70, 76, 81, 87, 90,
93, 99, 104, 110, 115,
106, 111, 115, 124, 128,
132, 133, 135, 137, 138,
140, 138, 137, 135, 133,
132, 128, 124, 115, 111,
106, 115, 110, 104, 99,
93, 90, 87, 81, 76,
70, 65, 61, 56, 52, 
48, 47, 45, 43, 42};

static int xValh[24] = {64, 72, 79,
84, 77, 70,
64, 56, 49,
44, 51, 58,
64, 72, 79,
84, 77, 70,
64, 56, 49,
44, 51, 58
};

static int yValh[24] = {70, 78, 85,
90, 97, 104,
110, 104, 97,
90,	85, 78,
70, 78, 85,
90, 97, 104,
110, 104, 97,
90,	85, 78
};

void increaseSeconds(void);
void increaseMinutes(void);
void increaseHours(void);
void drawClock(void);
void updateDigitalTime(void);
void drawMode(void);
