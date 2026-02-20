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
    int sampleRate;

    /* Allpass filter */
    float *allpass;
    int allpassSize;
    int allpassIdx;

    float feedback;   // comb feedback (decay)
    float apGain;     // allpass gain (diffusion)
    float mix;      
} SpringReverb;
#endif // REVERB_TYPES_H