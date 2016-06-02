#include <stdint.h>

#ifndef DAC_H
#define DAC_H 1

void DAC_Init(uint16_t initialData);
void DAC_Output(uint16_t outputVoltage);

#endif
