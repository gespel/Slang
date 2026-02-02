#ifndef RANDOM_H
#define RANDOM_H
#include "modules/oscillators/include/oscillator_types.h"

RandomOscillator* createRandomOscillator(char* name,int isOutput, int isCV);

float getRandomSample(RandomOscillator* oscillator);

void tickRandomOscillator(RandomOscillator* oscillator);

#endif //RANDOM_H