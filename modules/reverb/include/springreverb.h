#ifndef SPRING_REVERB_H
#define SPRING_REVERB_H
#include "modules/reverb/include/reverb_types.h"

SpringReverb *createSpringReverb();

float getSpringReverbSample(SpringReverb *reverb, float sample);

void tickSpringReverb(SpringReverb *reverb);

#endif