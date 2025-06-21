#include "../include/rack.h"

void addSineOscillator(Rack* rack, SineOscillator* input) {
    rack->sine_oscillators[rack->numSineOscillators] = input;
    rack->numSineOscillators = rack->numSineOscillators + 1;
}

SineOscillator* getSineOscillator(Rack* rack, char* name) {
    for (int i = 0; i < rack->numSineOscillators; i++) {
        if (strcmp(rack->sine_oscillators[i]->name, name) == 0) {
            printf("found!");
            return rack->sine_oscillators[i];
        }
    }
    return NULL;
}

void setSampleRateForAllOscillators(Rack* rack, int sampleRate) {
    for (int i = 0; i < rack->numSineOscillators; i++) {
        rack->sine_oscillators[i]->sampleRate = sampleRate;
    }
}
