#ifndef SPRING_REVERB_H
#define SPRING_REVERB_H
#include "modules/reverb/include/reverb_types.h"

SpringReverb *createSpringReverb();

float applySpringReverb(SpringReverb *reverb, float sample);

#endif