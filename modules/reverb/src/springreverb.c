#include "modules/reverb/include/springreverb.h"
#include "stdlib.h"
#include "math.h"
//#include "stdio.h"

SpringReverb *createSpringReverb(float allpassSize, float feedback, float diffusion, float drywet, int sampleRate) {
    SpringReverb *out = malloc(sizeof(SpringReverb));
    out->sampleRate = sampleRate;
    
    /* Early reflections - simulate first reflections from cave walls */
    int earlyDelays[6] = {
        sampleRate * 0.019f,   // 19ms
        sampleRate * 0.027f,   // 27ms
        sampleRate * 0.031f,   // 31ms
        sampleRate * 0.037f,   // 37ms
        sampleRate * 0.041f,   // 41ms
        sampleRate * 0.043f    // 43ms
    };
    
    for (int i = 0; i < 6; i++) {
        out->earlySize[i] = earlyDelays[i];
        out->earlyIdx[i] = 0;
        out->earlyReflections[i] = calloc(out->earlySize[i], sizeof(float));
    }
    
    /* 8 parallel comb filters for dense late reverb - MUCH longer delays! */
    int combDelays[8] = {
        sampleRate * 0.1013f,  // ~101ms
        sampleRate * 0.1193f,  // ~119ms
        sampleRate * 0.1277f,  // ~128ms
        sampleRate * 0.1381f,  // ~138ms
        sampleRate * 0.1511f,  // ~151ms
        sampleRate * 0.1667f,  // ~167ms
        sampleRate * 0.1831f,  // ~183ms
        sampleRate * 0.1973f   // ~197ms
    };

    for (int i = 0; i < 8; i++) {
        out->combSize[i] = combDelays[i];
        out->combIdx[i] = 0;
        out->comb[i] = calloc(out->combSize[i], sizeof(float));
        out->prevCombOut[i] = 0.0f;
    }

    /* 4 allpass filters in series for dense diffusion - also longer */
    int allpassDelays[4] = {
        sampleRate * 0.0089f,  // 8.9ms
        sampleRate * 0.0099f,  // 9.9ms
        sampleRate * 0.0322f,  // 32.2ms
        sampleRate * 0.0377f   // 37.7ms
    };
    
    for (int i = 0; i < 4; i++) {
        out->allpassSize[i] = allpassDelays[i];
        out->allpassIdx[i] = 0;
        out->allpass[i] = calloc(out->allpassSize[i], sizeof(float));
    }

    /* Parameters for natural hall/cave sound */
    out->feedback = feedback * 0.95f;  // scale up for longer decay
    out->apGain   = diffusion * 0.7f;  // moderate diffusion
    out->mix      = drywet;            // dry/wet
    out->damping  = 0.4f;              // stone absorbs highs moderately

    return out;
}

float applySpringReverb(SpringReverb *reverb, float sample) {
    /* Early reflections - discrete echoes from cave walls (subtle) */
    float earlySum = 0.0f;
    float earlyGains[6] = {0.4f, 0.35f, 0.3f, 0.25f, 0.2f, 0.15f};
    
    for (int i = 0; i < 6; i++) {
        float early = reverb->earlyReflections[i][reverb->earlyIdx[i]];
        reverb->earlyReflections[i][reverb->earlyIdx[i]] = sample;
        reverb->earlyIdx[i] = (reverb->earlyIdx[i] + 1) % reverb->earlySize[i];
        earlySum += early * earlyGains[i];
    }
    
    /* Prepare input for late reverb (early reflections + direct) */
    float lateInput = sample + earlySum * 0.15f;
    
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

    /* Mix early reflections + late reverb tail (mostly tail for smooth sound) */
    float wetSignal = earlySum * 0.15f + diffuseIn * 0.85f;
    
    /* Dry / Wet mix */
    return sample * (1.0f - reverb->mix) + wetSignal * reverb->mix;
}