#pragma once
#include "modules/stepsequencer/include/stepsequencer_types.h"
typedef enum EnvelopeType {
    LINENVELOPE, EXPENVELOPE
} EnvelopeType;

typedef struct EnvelopeGenerator {
    void* envelope;
    EnvelopeType type;
    StepSequencer *triggerSequencer;
} EnvelopeGenerator;

typedef struct LinearEnvelopeGenerator {
    float attack;
    int numSamplesAttack;
    float decay;
    int numSamplesDecay;
    float sustain;
    int numSamplesSustain;
    float release;
    int numSamplesRelease;
    float sample;
    float volume;
    float index;
    int state;
    int sampleRate;
    int fullNumSamples;
    float tmp;
    char* name;
} LinearEnvelopeGenerator;

