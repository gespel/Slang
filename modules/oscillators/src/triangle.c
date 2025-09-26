#include "../include/triangle.h"
#include <stdlib.h>

TriangleOscillator* createTriangleOscillator(float* frequency, float frequencyMultiplier,char *name, int sampleRate, int isOutput, int isCV) {
    TriangleOscillator* osc = malloc(sizeof(TriangleOscillator));
    osc->frequency = frequency;
    osc->frequencyMultiplier = frequencyMultiplier;
    osc->volume = 1.f;
    osc->phase = 0.f;
    osc->sampleRate = sampleRate;
    osc->name = name;
    osc->isOutput = isOutput;
    osc->isCV = isCV;
    osc->sample = malloc(sizeof(float));
    *(osc->sample) = 0.f;
    return osc;
}

float getTriangleSample(TriangleOscillator* osc) {
    float freq = *(osc->frequency) * osc->frequencyMultiplier;
    float increment = freq / osc->sampleRate;
    osc->phase += increment;
    if (osc->phase >= 1.f) {
        osc->phase -= 1.f;
    }
    if (osc->phase < 0.25f) {
        *(osc->sample) = osc->phase * 4.f;
    } else if (osc->phase < 0.75f) {
        *(osc->sample) = 2.f - (osc->phase * 4.f);
    } else {
        *(osc->sample) = (osc->phase * 4.f) - 4.f;
    }

    return *(osc->sample);
}
