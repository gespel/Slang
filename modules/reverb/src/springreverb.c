#include "modules/reverb/include/springreverb.h"
#include "stdlib.h"
#include "math.h"
//#include "stdio.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

SpringReverb *createSpringReverb(float allpassSize, float feedback, float diffusion, float drywet, int sampleRate) {
    SpringReverb *out = malloc(sizeof(SpringReverb));
    out->sampleRate = sampleRate;
    
    /* Prime-based delays for less resonance artifacts */
    int combDelays[4] = {
        sampleRate * 0.0297f,  // ~30ms
        sampleRate * 0.0371f,  // ~37ms
        sampleRate * 0.0411f,  // ~41ms
        sampleRate * 0.0437f   // ~44ms
    };

    for (int i = 0; i < 4; i++) {
        out->combSize[i] = combDelays[i];
        out->combIdx[i] = 0;
        out->comb[i] = calloc(out->combSize[i], sizeof(float));
        out->combDamping[i] = 0.2f + (i * 0.1f); // varying damping per comb
        out->prevCombOut[i] = 0.0f;
        
        /* LFO for spring wobble - different rates per spring */
        out->lfoRate[i] = (2.0f + i * 0.7f) / sampleRate; // 2-4.1 Hz
        out->lfoPhase[i] = (float)i * 0.25f; // phase offset
    }

    /* Cascade of 3 allpass filters for better diffusion */
    int allpassDelays[3] = {
        sampleRate * 0.005f,   // 5ms
        sampleRate * 0.0017f,  // 1.7ms
        sampleRate * 0.0013f   // 1.3ms
    };
    
    for (int i = 0; i < 3; i++) {
        out->allpassSize[i] = allpassDelays[i];
        out->allpassIdx[i] = 0;
        out->allpass[i] = calloc(out->allpassSize[i], sizeof(float));
    }

    /* Parameters */
    out->feedback = feedback;    // decay time
    out->apGain   = diffusion;   // diffusion
    out->mix      = drywet;      // dry/wet
    out->modDepth = 0.3f;        // modulation depth for spring wobble
    out->damping  = 0.3f;        // high frequency damping

    return out;
}

float applySpringReverb(SpringReverb *reverb, float sample) {
    float combSum = 0.0f;

    /* Parallel comb filters with damping and modulation */
    for (int i = 0; i < 4; i++) {
        /* Update LFO for spring wobble */
        reverb->lfoPhase[i] += reverb->lfoRate[i];
        if (reverb->lfoPhase[i] >= 1.0f) reverb->lfoPhase[i] -= 1.0f;
        
        /* Simple LFO modulation (sine wave) */
        float lfo = sinf(reverb->lfoPhase[i] * 2.0f * M_PI);
        float modAmount = lfo * reverb->modDepth;
        
        /* Read from delay line with fractional delay (simple linear interpolation) */
        float readPos = reverb->combIdx[i] - (modAmount * reverb->combSize[i] * 0.01f);
        if (readPos < 0) readPos += reverb->combSize[i];
        
        int idx1 = (int)readPos;
        int idx2 = (idx1 + 1) % reverb->combSize[i];
        float frac = readPos - idx1;
        
        float y = reverb->comb[i][idx1] * (1.0f - frac) + reverb->comb[i][idx2] * frac;
        
        /* One-pole lowpass damping filter */
        y = reverb->prevCombOut[i] + reverb->damping * (y - reverb->prevCombOut[i]);
        reverb->prevCombOut[i] = y;
        
        /* Write to delay line with feedback */
        reverb->comb[i][reverb->combIdx[i]] = sample + y * reverb->feedback;
        
        reverb->combIdx[i] = (reverb->combIdx[i] + 1) % reverb->combSize[i];
        combSum += y;
    }

    /* Scale down parallel comb sum */
    float diffuseIn = combSum * 0.25f;
    
    /* Cascade of 3 allpass filters for dense diffusion */
    for (int i = 0; i < 3; i++) {
        float delayOut = reverb->allpass[i][reverb->allpassIdx[i]];
        
        float apOut = -reverb->apGain * diffuseIn + delayOut;
        reverb->allpass[i][reverb->allpassIdx[i]] = diffuseIn + reverb->apGain * delayOut;
        
        reverb->allpassIdx[i] = (reverb->allpassIdx[i] + 1) % reverb->allpassSize[i];
        diffuseIn = apOut; // cascade
    }

    /* Dry / Wet mix */
    return sample * (1.0f - reverb->mix) + diffuseIn * reverb->mix;
}