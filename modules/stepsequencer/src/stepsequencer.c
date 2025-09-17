//
// Created by Sten on 24.07.2025.
//
#include "../include/stepsequencer.h"

#include <stdlib.h>
#include <strings.h>

StepSequencer *createStepSequencer(int sampleRate, int speed, float *steps, int numSteps) {
    StepSequencer *seq = malloc(sizeof(StepSequencer));
    seq->sampleRate = sampleRate;
    seq->speed = speed;
    seq->numSteps = numSteps;
    seq->steps = steps;
    seq->sample = 0;
    seq->index = 0;
    seq->stepIndex = 0;
    return seq;
}

float getStepSequencerSample(StepSequencer *seq) {
    if (seq->stepIndex >= (seq->sampleRate/seq->numSteps)) {
        seq->stepIndex = 0;
        seq->index += 1;
    }
    if (seq->index >= seq->numSteps) {
        seq->index = 0;
    }
    return seq->steps[seq->index];
}
