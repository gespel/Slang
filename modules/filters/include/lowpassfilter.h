#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H

#include "filter_types.h"

LowPassFilter* createLowPassFilter(float cutoff, int sampleRate);

float processLowPassSample(LowPassFilter* filter, float inputSample);

void updateCoefficients(LowPassFilter* filter, float cutoff, int sampleRate);

void recalculateFilterCoefficients(LowPassFilter* filter);

#endif // LOWPASSFILTER_H