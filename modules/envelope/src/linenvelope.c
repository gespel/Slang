#include "modules/envelope/include/linenvelope.h"
#include "stdlib.h"
#include "stdio.h"
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
    printf("Switching to state attack!\n");
}

void tickLinearEnvelopeGenerator(LinearEnvelopeGenerator *envelope) {
    if (envelope->state == 0) {
        if (envelope->index > envelope->numSamplesAttack) {
            printf("Switching to state decay!\n");
            envelope->state = 1;
        }
        envelope->sample = envelope->sample + 
            (envelope->index / envelope->numSamplesAttack);
    }
    else if (envelope->state == 1) {
        if (envelope->index > envelope->numSamplesAttack + 
                envelope->numSamplesDecay) {
            printf("Switching to state sustain!\n");
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
            printf("Switching to state release!\n");        
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
                envelope->numSamplesRelease) {
            printf("Switching to state inactive!\n");
            envelope->state = -1;
        }
        envelope->sample = envelope->sample - envelope->tmp;
    }
    envelope->index += 1;
}