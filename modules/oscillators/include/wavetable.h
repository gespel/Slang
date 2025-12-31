//
// Created by Sten on 13.07.2025.
//

#ifndef WAVETABLE_H
#define WAVETABLE_H
#define M_PI 3.14159265358979323846
#define WAVETABLE_FILE_PATH "waves"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../data/include/binaryData.h"
#include "oscillator_types.h"
#include <errno.h>
#include <locale.h>

float getWavetableSample(WavetableOscillator* oscillator);

WavetableOscillator* createWavetableOscillator(float frequency, char* name, float* waveTable, int wavetableLength, int sampleRate, int isOutput, int isCV);

float* loadWavetableByName(char* name);

#endif //WAVETABLE_H
