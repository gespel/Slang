//
// Created by Sten on 24.07.2025.
//
#include "modules/stepsequencer/include/stepsequencer.h"

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
    seq->trigger = 0;
    seq->stepsDuration = (float)seq->sampleRate * 60 / (float)(seq->speed);
    return seq;
}

void tickStepSequencer(StepSequencer *seq) {
    //printf("sample rate: %d, speed: %d, num steps: %d\n", seq->sampleRate, seq->speed, seq->numSteps);
    //printf("Step duration: %f, step index: %d, index: %d", step_duration, seq->stepIndex, seq->index);
    if ((float)seq->stepIndex >= (float)seq->stepsDuration) {
        seq->stepIndex = 0;
        seq->index += 1;
        if (seq->steps[seq->index] != 0.0f) {
            seq->trigger = 1;
        }
    }
    else {
        seq->trigger = 0;
    }
    if (seq->index >= seq->numSteps) {
        seq->index = 0;
    }
    seq->stepIndex += 1;
    seq->sample = seq->steps[seq->index];
}

float getStepSequencerSample(StepSequencer *seq) {
    return seq->steps[seq->index];
}

