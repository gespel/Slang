#include "modules/reverb/include/reverb.h"
#include "stdlib.h"

Reverb *createReverb(void *reverb, ReverbType type) {
    Reverb *out = malloc(sizeof(Reverb));
    out->reverb = reverb;
    out->type = type;
    return out;
}

float applyReverb(Reverb *reverb, float sample) {
    if (reverb->type == SPRINGREVERB) {
        return 0;
    }
    else {
        return 0;
    }
}
