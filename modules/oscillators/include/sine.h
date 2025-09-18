//
// Created by sten on 16.07.25.
//

#ifndef SINE_H
#define SINE_H
#define M_PI 3.14159265358979323846
#include <math.h>
#include <stdlib.h>
#include "oscillator_types.h"


float getSineSample(SineOscillator* oscillator);

SineOscillator *createSineOscillator(float* frequency, float frequencyMultiplier, char* name, int sampleRate, int isOutput, int isCV);

#endif //SINE_H
