#include "modules/reverb/include/springreverb.h"
#include "stdlib.h"
#include "stdio.h"

SpringReverb *createSpringReverb(float allpassSize, float feedback, float drywet, int sampleRate) {
    SpringReverb *out = malloc(sizeof(SpringReverb));
    out->sampleRate = sampleRate;
    
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
    out->allpassSize = sampleRate * allpassSize; // ~5ms
    out->allpassIdx = 0;
    out->allpass = calloc(out->allpassSize, sizeof(float));

    /* Parameters */
    out->feedback = feedback;    // reduced decay time for stability
    out->apGain   = 0.6f;    // reduced diffusion for stability
    out->mix      = drywet;    // dry/wet

    return out;
}

float applySpringReverb(SpringReverb *reverb, float sample) {
    float combSum = 0.0f;

    /* Parallel comb filters */
    for (int i = 0; i < 4; i++) {
        float y = reverb->comb[i][reverb->combIdx[i]];
        reverb->comb[i][reverb->combIdx[i]] = sample + y * reverb->feedback;

        reverb->combIdx[i] = (reverb->combIdx[i] + 1) % reverb->combSize[i];
        combSum += y;
    }

    /* Allpass diffusion - corrected implementation */
    float delayOut = reverb->allpass[reverb->allpassIdx];
    float input = combSum * 0.25f; // scale down parallel comb sum
    
    float apOut = -reverb->apGain * input + delayOut;
    reverb->allpass[reverb->allpassIdx] = input + reverb->apGain * delayOut;

    reverb->allpassIdx = (reverb->allpassIdx + 1) % reverb->allpassSize;
    //printf("in reverb\n");

    /* Dry / Wet mix */
    return sample * (1.0f - reverb->mix) + apOut * reverb->mix;
}