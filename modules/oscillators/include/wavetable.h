//
// Created by Sten on 13.07.2025.
//

#ifndef WAVETABLE_H
#define WAVETABLE_H
#define M_PI 3.14159265358979323846
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../../data/include/binaryData.h"
#include "oscillator_types.h"

float getWavetableSample(WavetableOscillator* oscillator);

WavetableOscillator* createWavetableOscillator(float* frequency, float frequencyMultiplier, char* name, float* waveTable, int wavetableLength, int sampleRate, int isOutput);

float* getWavetableByName(char* name);

#endif //WAVETABLE_H
