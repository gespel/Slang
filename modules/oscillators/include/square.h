//
// Created by sten on 16.07.25.
//

#ifndef SQUARE_H
#define SQUARE_H
#include <stdlib.h>
#include "oscillator_types.h"

void tickSquareOscillator(SquareOscillator* oscillator);
SquareOscillator *createSquareOscillator(float frequency, char* name, int sampleRate, int isOutput, int isCV);

float getSquareSample(SquareOscillator* oscillator);

#endif //SQUARE_H
