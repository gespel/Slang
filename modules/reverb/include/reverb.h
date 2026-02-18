#ifndef REVERB_H
#define REVERB_H
#include "modules/reverb/include/reverb_types.h"

Reverb *createReverb(void *reverb, ReverbType type);

float getReverbSample(Reverb *reverb, float sample);

void tickReverb(Reverb *reverb);

#endif