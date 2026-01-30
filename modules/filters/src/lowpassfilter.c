#include "modules/filters/include/lowpassfilter.h"
#include "modules/filters/include/filter_types.h"
#include <stdlib.h>

LowPassFilter* createLowPassFilter(float cutoff, int sampleRate) {
    LowPassFilter* filter = malloc(sizeof(LowPassFilter));
    filter->sampleRate = sampleRate;
    updateCoefficients(filter, cutoff, sampleRate);
    return filter;
}

void updateCoefficients(LowPassFilter* filter, float cutoff, int sampleRate) {
    if (cutoff == 0) {
        cutoff = 1;
    } 
    filter->cutoff = cutoff;
    filter->sampleRate = sampleRate;
    recalculateFilterCoefficients(filter);
    //filter->currentInput = 0.0f;
    //filter->currentOutput = 0.0f;
}

void recalculateFilterCoefficients(LowPassFilter* filter) {
    float rc = 1.0f / (2.0f * 3.14159265f * filter->cutoff);
    float dt = 1.0f / filter->sampleRate;
    filter->alpha = dt / (rc + dt);
    filter->dt = dt;
    filter->RC = rc;
}

float processLowPassSample(LowPassFilter* filter, float inputSample) {
    filter->currentInput = inputSample;
    filter->currentOutput = filter->alpha * filter->currentInput + (1.0f - filter->alpha) * filter->currentOutput;
    return filter->currentOutput;
}