#include "modules/oscillators/include/random.h"
#include <stdlib.h>

RandomOscillator* createRandomOscillator(char* name, int isOutput, int isCV) {
    RandomOscillator* oscillator = malloc(sizeof(RandomOscillator));
    oscillator->name = name;
    oscillator->isOutput = isOutput;
    oscillator->isCV = isCV;
    oscillator->volume = 1;
    return oscillator;
}

float getRandomSample(RandomOscillator* oscillator) {
    return oscillator->sample;
    
}

void tickRandomOscillator(RandomOscillator* oscillator) {
    oscillator->sample = ((float)rand() / (float)(RAND_MAX) * oscillator->volume * 2) - 1;
}