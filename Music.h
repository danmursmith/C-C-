#ifndef MUSIC_H
#define MUSIC_H 1

#include <stdint.h>

// if desired interrupt frequency is f, Timer0A_Init parameter is busfrequency/f
#define F16HZ (80000000/16)
#define F20KHZ (80000000/20000)
#define F64HZ	(80000000/64)

#define G2 98
#define C3 131
#define D3 147
#define E3 165
#define F3 175
#define G3 196
#define A3 220
#define B3 247
#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define GF4 370
#define G4 392
#define A4 440
#define B4 494
#define C5 523
#define D5 587
#define E5 659
#define F5 698
#define G5 784
#define A5 880
#define B5 988
#define C6 1047
#define D6 1175
#define E6 1319
#define F6 1397
#define G6 1568
#define A6 1760
#define B6 1976
#define C7 2093

#define Whole 16
#define Half 8
#define Quarter 4
#define Eighth 2
#define Triplet 4/3
#define Sixteenth 1

typedef enum {
	Wave1,
	Wave2,
} Instrument;

typedef struct {
	uint16_t pitch;    //frequency for note
	uint16_t duration; //duration of note
	Instrument sound;  
} Note;

typedef struct {
	uint16_t tempo;    //beats per minute
	Note *notes;       
} Song;

Note* Song_CurrentNote(void);

uint16_t Instrument_CurrentVoltage(uint32_t voiceIndex);

void Song_PlayInit(Song song);
void Song_PlayHandler(void);

extern Note Star_Wars[];

#endif
