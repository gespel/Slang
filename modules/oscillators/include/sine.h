//
// Created by sten on 16.07.25.
//

#ifndef SINE_H
#define SINE_H
#define M_PI 3.14159265358979323846
#include <math.h>
#include <stdlib.h>
#include "oscillator_types.h"

void tickSineOscillator(SineOscillator* oscillator);
float getSineSample(SineOscillator* oscillator);

SineOscillator *createSineOscillator(float frequency, char* name, int sampleRate, int isOutput, int isCV);

#endif //SINE_H
