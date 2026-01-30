#include "modules/oscillators/include/triangle.h"
#include <stdlib.h>

TriangleOscillator* createTriangleOscillator(float frequency, char *name, int sampleRate, int isOutput, int isCV) {
    TriangleOscillator* osc = malloc(sizeof(TriangleOscillator));
    osc->frequency = frequency;
    osc->volume = 1.f;
    osc->phase = 0.f;
    osc->sampleRate = sampleRate;
    osc->name = name;
    osc->isOutput = isOutput;
    osc->isCV = isCV;
    osc->sample = 0.f;
    osc->volume = 1;
    return osc;
}

void tickTriangleOscillator(TriangleOscillator *oscillator) {
    float freq = oscillator->frequency;
    float increment = freq / oscillator->sampleRate;
    oscillator->phase += increment;
    if (oscillator->phase >= 1.f) {
        oscillator->phase -= 1.f;
    }
    if (oscillator->phase < 0.25f) {
        oscillator->sample = oscillator->phase * 4.f;
    } else if (oscillator->phase < 0.75f) {
        oscillator->sample = 2.f - (oscillator->phase * 4.f);
    } else {
        oscillator->sample = (oscillator->phase * 4.f) - 4.f;
    }
}

float getTriangleSample(TriangleOscillator* osc) {
    return osc->sample;
}
