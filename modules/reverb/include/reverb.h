#ifndef REVERB_H
#define REVERB_H
#include "modules/reverb/include/reverb_types.h"

Reverb *createReverb(void *reverb, ReverbType type);

float applyReverb(Reverb *reverb, float sample);

#endif