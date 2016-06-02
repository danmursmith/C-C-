#include "DAC.h"
#include "Music.h"

const unsigned short wave1[64] = {
	2048,2224,2399,2571,2737,2897,3048,3190,3321,3439,3545,3635,3711,3770,3813,3839,3848,3839,3813,3770,
	3711,3635,3545,3439,3321,3190,3048,2897,2737,2571,2399,2224,2048,1872,1697,1525,1359,1199,1048,906,775,
	657,551,461,385,326,283,257,248,257,283,326,385,461,551,657,775,906,1048,1199,1359,1525,1697,1872
};

const unsigned short wave2[64] = {
	2014,2504,2748,3096,3396,3594,3650,3594,3350,3124,2766,2438,2184,2014,1826,1780,1666,1694,1620,1554,
	1488,1348,1196,1102,1018,952,990,1066,1178,1318,1516,1752,2014,2504,2748,3096,3396,3594,3650,3594,
	3350,3124,2766,2438,2184,2014,1826,1780,1666,1694,1620,1554,1488,1348,1196,1102,1018,952,990,1066,
	1178,1318,1516,1752
};

uint16_t Instrument_CurrentVoltage(uint32_t voiceIndex) {
	Instrument currentVoice = Song_CurrentNote()->sound;
		switch(currentVoice) {
		case Wave1: return wave1[voiceIndex %64];
		case Wave2: return wave2[voiceIndex % 64];
	}	
		return wave1[voiceIndex % 64];
}

uint32_t noteIndex = 0;
uint32_t beatIndex = 0;
Song currentSong;

void Song_PlayInit(Song song) {
	currentSong = song;
	noteIndex = 0;
	beatIndex = 0;
}

Note* Song_CurrentNote() {
	return &currentSong.notes[noteIndex];
}

void Song_PlayHandler(void){
	Note currentNote = *Song_CurrentNote();
	beatIndex += 1;
	if(beatIndex >= currentNote.duration * 2) {
		noteIndex += 1;
		beatIndex = 0;
	}
}

Note Star_Wars[]={
	{D4, Triplet, Wave1},
	{D4, Triplet, Wave1},
	{D4, Triplet, Wave1},
	{G4, Half, Wave1},
	{D5, Half, Wave1},
	{C5, Triplet, Wave1},
	{B4, Triplet, Wave1},
	{A4, Triplet, Wave1},
	{G5, Half, Wave1},
	{D5, Half, Wave1},
	{C5, Triplet, Wave1},
	{B4, Triplet, Wave1},
	{A4, Triplet, Wave1},
	{G5, Half, Wave1},
	{D5, Half, Wave1},
	{C5, Triplet, Wave1},
	{B4, Triplet, Wave1},
	{C5, Triplet, Wave1},
	{A4, Half, Wave1},
	
	{D4, Triplet, Wave1},
	{D4, Triplet, Wave1},
	{D4, Triplet, Wave1},
	{G5, Half, Wave1},
	{D5, Half, Wave1},
	{C5, Triplet, Wave1},
	{B4, Triplet, Wave1},
	{A4, Triplet, Wave1},
	{G5, Half, Wave1},
	{D5, Half, Wave1},
	{C5, Triplet, Wave1},
	{B4, Triplet, Wave1},
	{A4, Triplet, Wave1},
	{G5, Half, Wave1},
	{D5, Half, Wave1},
	{C5, Triplet, Wave1},
	{B4, Triplet, Wave1},
	{C5, Triplet, Wave1},
	{A4, Half, Wave1},
	
	{D4, Triplet*2, Wave1},
	{D4, Triplet, Wave1},
	{E4, Eighth*3, Wave1},
	{E4, Eighth, Wave1},
	{C5, Eighth, Wave1},
	{B4, Eighth, Wave1},
	{A4, Eighth, Wave1},
	{G4, Eighth, Wave1},
	{C5, Triplet, Wave1},
	{A4, Triplet, Wave1},
	{B4, Triplet, Wave1},
	{A4, Triplet*2, Wave1},
	{E4, Triplet, Wave1},
	{GF4, Quarter, Wave1},
	
	{D4, Triplet*2, Wave1},
	{D4, Triplet, Wave1},
	{E4, Eighth*3, Wave1},
	{E4, Eighth, Wave1},
	{C5, Eighth, Wave1},
	{B4, Eighth, Wave1},
	{A4, Eighth, Wave1},
	{G4, Eighth, Wave1},
	{D5, Quarter, Wave1},
	{A4, Half, Wave1},
	{D4, Triplet*2, Wave1},
	{D4, Triplet, Wave1},
	{0, Whole, Wave1}
};
