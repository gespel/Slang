#include "../include/lowpassfilter.h"
#include <stdlib.h>

LowPassFilter* createLowPassFilter(float cutoff, int sampleRate) {
    LowPassFilter* filter = malloc(sizeof(LowPassFilter));
    filter->cutoff = cutoff;
    float rc = 1.0f / (2.0f * 3.14159265f * cutoff);
    float dt = 1.0f / sampleRate;
    filter->alpha = dt / (rc + dt);
    filter->dt = dt;
    filter->RC = rc;
    filter->currentInput = 0.0f;
    filter->currentOutput = 0.0f;
    return filter;
}

float processLowPassSample(LowPassFilter* filter, float inputSample) {
    filter->currentInput = inputSample;
    filter->currentOutput = filter->alpha * filter->currentInput + (1.0f - filter->alpha) * filter->currentOutput;
    return filter->currentOutput;
}