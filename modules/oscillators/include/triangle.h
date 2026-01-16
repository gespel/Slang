#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "oscillator_types.h"

TriangleOscillator* createTriangleOscillator(float frequency, char *name, int sampleRate, int isOutput, int isCV);

void tickTriangleOscillator(TriangleOscillator* oscillator);
float getTriangleSample(TriangleOscillator* osc);

#endif //TRIANGLE_H