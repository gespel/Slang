#include "modules/reverb/include/springreverb.h"
#include "stdlib.h"

SpringReverb *createSpringReverb(int sampleRate) {
    SpringReverb *out = malloc(sizeof(SpringReverb));
    int combDelays[4] = {
        sampleRate * 0.0297f,
        sampleRate * 0.0371f,
        sampleRate * 0.0411f,
        sampleRate * 0.0437f
    };

    for (int i = 0; i < 4; i++) {
        out->combSize[i] = combDelays[i];
        out->combIdx[i] = 0;
        out->comb[i] = calloc(out->combSize[i], sizeof(float));
    }

    /* Allpass delay */
    out->allpassSize = sampleRate * 0.005f; // ~5ms
    out->allpassIdx = 0;
    out->allpass = calloc(out->allpassSize, sizeof(float));

    /* Parameters */
    out->feedback = 0.78f;   // decay time
    out->apGain   = 0.7f;    // diffusion
    out->mix      = 0.35f;   // dry/wet

    return out;
}

float applySpringReverb(SpringReverb *reverb, float sample) {
    float combSum = 0.0f;

    /* Parallel comb filters */
    for (int i = 0; i < 4; i++) {
        float y = reverb->comb[i][reverb->combIdx[i]];
        reverb->comb[i][reverb->combIdx[i]] = sample + y * reverb->feedback;

        reverb->combIdx[i]++;
        if (reverb->combIdx[i] >= reverb->combSize[i])
            reverb->combIdx[i] = 0;

        combSum += y;
    }

    /* Allpass diffusion */
    float apOut = reverb->allpass[reverb->allpassIdx];
    float apIn  = combSum + apOut * reverb->apGain;

    float wet = -combSum + apOut;
    reverb->allpass[reverb->allpassIdx] = apIn;

    reverb->allpassIdx++;
    if (reverb->allpassIdx >= reverb->allpassSize)
        reverb->allpassIdx = 0;

    /* Dry / Wet mix */
    return sample * (1.0f - reverb->mix) + wet * reverb->mix;
}
