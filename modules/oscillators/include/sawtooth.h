//
// Created by sten on 16.07.25.
//

#ifndef SAWTOOTH_H
#define SAWTOOTH_H
#include "oscillator_types.h"

float getSawtoothSample(SawtoothOscillator* oscillator);

SawtoothOscillator *createSawtoothOscillator(float* frequency, float frequencyMultiplier, char* name, int sampleRate, int isOutput, int isCV);

#endif //SAWTOOTH_H
