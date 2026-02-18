#include "modules/reverb/include/reverb.h"
#include "reverb/include/reverb_types.h"
#include "reverb/include/springreverb.h"
#include "stdlib.h"

Reverb *createReverb(void *reverb, ReverbType type) {
    Reverb *out = malloc(sizeof(Reverb));
    out->reverb = reverb;
    out->type = type;
    return out;
}

float getReverbSample(Reverb *reverb, float sample) {
    if (reverb->type == SPRINGREVERB) {

    }
}

void tickReverb(Reverb *reverb) {
    if (reverb->type == SPRINGREVERB) {
        tickSpringReverb(reverb->reverb);
    }
}