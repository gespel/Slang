#include "modules/reverb/include/springreverb.h"
#include "stdlib.h"
#include "math.h"
//#include "stdio.h"

SpringReverb *createSpringReverb(float allpassSize, float feedback, float diffusion, float drywet, int sampleRate) {
    SpringReverb *out = malloc(sizeof(SpringReverb));
    out->sampleRate = sampleRate;
    
    /* Early reflections - simulate first reflections from cave walls */
    int earlyDelays[6] = {
        sampleRate * 0.0043f,  // 4.3ms
        sampleRate * 0.0215f,  // 21.5ms
        sampleRate * 0.0225f,  // 22.5ms
        sampleRate * 0.0268f,  // 26.8ms
        sampleRate * 0.0270f,  // 27ms
        sampleRate * 0.0298f   // 29.8ms
    };
    
    for (int i = 0; i < 6; i++) {
        out->earlySize[i] = earlyDelays[i];
        out->earlyIdx[i] = 0;
        out->earlyReflections[i] = calloc(out->earlySize[i], sizeof(float));
    }
    
    /* 8 parallel comb filters for dense late reverb (Freeverb-style) */
    int combDelays[8] = {
        sampleRate * 0.0297f,  // ~30ms
        sampleRate * 0.0371f,  // ~37ms
        sampleRate * 0.0411f,  // ~41ms
        sampleRate * 0.0437f,  // ~44ms
        sampleRate * 0.0521f,  // ~52ms
        sampleRate * 0.0617f,  // ~62ms
        sampleRate * 0.0683f,  // ~68ms
        sampleRate * 0.0741f   // ~74ms
    };

    for (int i = 0; i < 8; i++) {
        out->combSize[i] = combDelays[i];
        out->combIdx[i] = 0;
        out->comb[i] = calloc(out->combSize[i], sizeof(float));
        out->prevCombOut[i] = 0.0f;
    }

    /* 4 allpass filters in series for dense diffusion */
    int allpassDelays[4] = {
        sampleRate * 0.0051f,  // 5.1ms
        sampleRate * 0.0117f,  // 11.7ms
        sampleRate * 0.0181f,  // 18.1ms
        sampleRate * 0.0299f   // 29.9ms
    };
    
    for (int i = 0; i < 4; i++) {
        out->allpassSize[i] = allpassDelays[i];
        out->allpassIdx[i] = 0;
        out->allpass[i] = calloc(out->allpassSize[i], sizeof(float));
    }

    /* Parameters for natural hall/cave sound */
    out->feedback = feedback;     // longer decay for cave
    out->apGain   = diffusion;    // high diffusion for smooth tail
    out->mix      = drywet;       // dry/wet
    out->damping  = 0.5f;         // stone absorbs highs

    return out;
}

float applySpringReverb(SpringReverb *reverb, float sample) {
    /* Early reflections - discrete echoes from cave walls */
    float earlySum = 0.0f;
    float earlyGains[6] = {0.841f, 0.504f, 0.491f, 0.379f, 0.380f, 0.346f};
    
    for (int i = 0; i < 6; i++) {
        float early = reverb->earlyReflections[i][reverb->earlyIdx[i]];
        reverb->earlyReflections[i][reverb->earlyIdx[i]] = sample;
        reverb->earlyIdx[i] = (reverb->earlyIdx[i] + 1) % reverb->earlySize[i];
        earlySum += early * earlyGains[i];
    }
    
    /* Prepare input for late reverb (early reflections + direct) */
    float lateInput = sample + earlySum * 0.3f;
    
    /* 8 parallel comb filters with damping for late reverb */
    float combSum = 0.0f;
    for (int i = 0; i < 8; i++) {
        float y = reverb->comb[i][reverb->combIdx[i]];
        
        /* One-pole lowpass damping (stone walls absorb highs) */
        y = reverb->prevCombOut[i] + reverb->damping * (y - reverb->prevCombOut[i]);
        reverb->prevCombOut[i] = y;
        
        /* Write with feedback */
        reverb->comb[i][reverb->combIdx[i]] = lateInput + y * reverb->feedback;
        
        reverb->combIdx[i] = (reverb->combIdx[i] + 1) % reverb->combSize[i];
        combSum += y;
    }

    /* Scale down parallel comb sum */
    float diffuseIn = combSum * 0.125f; // 1/8 for 8 combs
    
    /* Cascade of 4 allpass filters for smooth, dense diffusion */
    for (int i = 0; i < 4; i++) {
        float delayOut = reverb->allpass[i][reverb->allpassIdx[i]];
        
        float apOut = -reverb->apGain * diffuseIn + delayOut;
        reverb->allpass[i][reverb->allpassIdx[i]] = diffuseIn + reverb->apGain * delayOut;
        
        reverb->allpassIdx[i] = (reverb->allpassIdx[i] + 1) % reverb->allpassSize[i];
        diffuseIn = apOut;
    }

    /* Mix early reflections + late reverb tail */
    float wetSignal = earlySum * 0.3f + diffuseIn * 0.7f;
    
    /* Dry / Wet mix */
    return sample * (1.0f - reverb->mix) + wetSignal * reverb->mix;
}