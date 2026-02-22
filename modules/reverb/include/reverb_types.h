#ifndef REVERB_TYPES_H
#define REVERB_TYPES_H
typedef enum ReverbType {
    SPRINGREVERB
} ReverbType;

typedef struct Reverb {
    void *reverb;
    ReverbType type;
} Reverb;

typedef struct SpringReverb {
    float *comb[8];       // more combs for denser reverb
    int combSize[8];
    int combIdx[8];
    float combDamping[8];
    int sampleRate;

    /* Early reflections */
    float *earlyReflections[6];
    int earlySize[6];
    int earlyIdx[6];

    /* Allpass filters (cascade) */
    float *allpass[4];
    int allpassSize[4];
    int allpassIdx[4];
    
    /* Previous sample for damping */
    float prevCombOut[8];

    float feedback;   // comb feedback (decay)
    float apGain;     // allpass gain (diffusion)
    float mix;
    float damping;    // high frequency damping
} SpringReverb;
#endif // REVERB_TYPES_H