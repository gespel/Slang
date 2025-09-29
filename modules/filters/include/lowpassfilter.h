#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H

#include "filter_types.h"

LowPassFilter* createLowPassFilter(float cutoff, int sampleRate);

float processLowPassSample(LowPassFilter* filter, float inputSample);

#endif // LOWPASSFILTER_H