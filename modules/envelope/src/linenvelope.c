#include "modules/envelope/include/linenvelope.h"
#include "stdlib.h"
#include <asm-generic/errno.h>

LinearEnvelopeGenerator* createLinearEnvelopeGenerator(char* name, int sampleRate, float attack, float decay, float sustain, float release) {
    LinearEnvelopeGenerator* out = malloc(sizeof(LinearEnvelopeGenerator));

    out->name = name;
    out->sampleRate = sampleRate;
    out->attack = attack;
    out->decay = decay;
    out->sustain = sustain;
    out->release = release;

    out->numSamplesAttack = attack * sampleRate;
    out->numSamplesDecay = decay * sampleRate;
    out->numSamplesSustain = sustain * sampleRate;
    out->numSamplesRelease = release * sampleRate;

    out->index = 0;
    out->volume = 1;
    out->sample = 0;
    out->state = -1;

    return out;
}

float getLinearEnvelopeGeneratorSample(LinearEnvelopeGenerator *envelope) {
    return envelope->sample;
}

void triggerLinearEnvelopeGenerator(LinearEnvelopeGenerator* envelope) {
    envelope->index = 0;
    envelope->state = 0;
}

void tickLinearEnvelopeGenerator(LinearEnvelopeGenerator *envelope) {
    if (envelope->state == 0) {
        if (envelope->index > envelope->numSamplesAttack) {
            envelope->state = 1;
        }
        envelope->sample = envelope->sample + 
            (envelope->index / envelope->numSamplesAttack);
    }
    else if (envelope->state == 1) {
        if (envelope->index > envelope->numSamplesAttack + 
                envelope->numSamplesDecay) {
            envelope->state = 2;            
        }
        envelope->sample = envelope->sample - 
            ((envelope->index - envelope->numSamplesAttack) / 
            envelope->numSamplesDecay) * 0.3;
    }
    else if (envelope->state == 2) {
        if (envelope->index > envelope->numSamplesAttack + 
                envelope->numSamplesDecay + 
                envelope->numSamplesSustain) {
            envelope->state = 3;            
            envelope->tmp = envelope->sample * 
                ((envelope->index - 
                    envelope->numSamplesAttack - 
                    envelope->numSamplesDecay - 
                    envelope->numSamplesSustain) / 
                envelope->numSamplesRelease
            );
        }
    }
    else if (envelope->state == 3) {
        if (envelope->index > envelope->numSamplesAttack + 
                envelope->numSamplesDecay + 
                envelope->numSamplesSustain + 
                envelope->numSamplesRelease
            ) {
            envelope->state = -1;
        }
        envelope->sample = envelope->sample - envelope->tmp;
    }
    envelope->index += 1;
}