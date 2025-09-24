#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "oscillator_types.h"

TriangleOscillator* createTriangleOscillator(float* frequency, float frequencyMultiplier, float volume, int sampleRate, char* name, int isOutput, int isCV);
float getTriangleSample(TriangleOscillator* osc);

#endif //TRIANGLE_H