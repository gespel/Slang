//
// Created by Sten on 24.07.2025.
//
#include "stepsequencer/include/stepsequencer.h"

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
    //printf("sample rate: %d, speed: %d, num steps: %d\n", seq->sampleRate, seq->speed, seq->numSteps);
    float step_duration = (float)seq->sampleRate/ (float)(seq->numSteps);
    //printf("Step duration: %f, step index: %d, index: %d", step_duration, seq->stepIndex, seq->index);
    if ((float)seq->stepIndex >= step_duration) {
        seq->stepIndex = 0;
        seq->index += 1;
    }
    if (seq->index >= seq->numSteps) {
        seq->index = 0;
    }
    seq->stepIndex += 1 * seq->speed;
    seq->sample = seq->steps[seq->index];
    return seq->steps[seq->index];
}

