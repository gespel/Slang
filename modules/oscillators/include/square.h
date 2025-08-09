//
// Created by sten on 16.07.25.
//

#ifndef SQUARE_H
#define SQUARE_H
#include <stdlib.h>
#include "oscillator_types.h"


SquareOscillator *createSquareOscillator(float* frequency, float frequencyMultiplier, char* name, int sampleRate, int isOutput);

float getSquareSample(SquareOscillator* oscillator);

#endif //SQUARE_H
