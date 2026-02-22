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
    float *comb[4];
    int combSize[4];
    int combIdx[4];
    float combDamping[4];  // damping per comb
    int sampleRate;

    /* Allpass filters (cascade) */
    float *allpass[3];
    int allpassSize[3];
    int allpassIdx[3];

    /* Modulation (spring wobble) */
    float lfoPhase[4];
    float lfoRate[4];
    float modDepth;
    
    /* Previous sample for damping */
    float prevCombOut[4];

    float feedback;   // comb feedback (decay)
    float apGain;     // allpass gain (diffusion)
    float mix;
    float damping;    // high frequency damping
} SpringReverb;
#endif // REVERB_TYPES_H