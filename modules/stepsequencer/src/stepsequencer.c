//
// Created by Sten on 24.07.2025.
//
#include "modules/stepsequencer/include/stepsequencer.h"
#include "modules/stepsequencer/include/randomstepsequencer.h"
#include "stepsequencer/include/stepsequencer_types.h"

#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

Sequencer *createSequencer(void *sequencer, StepSequencerType type) {
    Sequencer *s = malloc(sizeof(Sequencer));
    s->type = type;
    s->sequencer = sequencer;
    return s;
}
void tickSequencer(Sequencer *sequencer) {
    switch (sequencer->type) {
        case STEPSEQUENCER:
            tickStepSequencer((StepSequencer*)sequencer->sequencer);
            break;
        case RANDOMSTEPSEQUENCER:
            tickRandomStepSequencer((RandomStepSequencer*)sequencer->sequencer);
            break;
        default:
            break;
    }
}
float getSequencerSample(Sequencer *sequencer) {
    switch (sequencer->type) {
        case STEPSEQUENCER:
            return getStepSequencerSample((StepSequencer*)sequencer->sequencer);
        case RANDOMSTEPSEQUENCER:
            return getRandomStepSequencerSample((RandomStepSequencer*)sequencer->sequencer);
        default:
            return 0.f;
    }
}

StepSequencer *createStepSequencer(int sampleRate, int speed, float *steps, int numSteps, int *rackTrigger, SequencerSyncType syncType) {
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
    seq->rackTrigger = rackTrigger;
    seq->syncType = syncType;
    return seq;
}

void tickStepSequencer(StepSequencer *seq) {
    if (seq->syncType == STANDALONE) {
        int switched = 0;
        if ((float)seq->stepIndex >= (float)seq->stepsDuration) {
            seq->stepIndex = 0;
            seq->index += 1;
            switched = 1;
        }
        else {
            seq->trigger = 0;
        }
        if (seq->index >= seq->numSteps) {
            seq->index = 0;
        }
        seq->stepIndex += 1;
        seq->sample = seq->steps[seq->index];
        if (seq->sample!= 0.0f && switched == 1) {
            seq->trigger = 1;
        }
    }
    else if (seq->syncType == DAWSYNC) {
        if (*(seq->rackTrigger) == 1) {
            seq->trigger = 1;
            seq->index += 1;
            if (seq->index >= seq->numSteps) {
                seq->index = 0;
            }
            seq->sample = seq->steps[seq->index];
        }
        else {
            seq->trigger = 0;
        }
    }
}

float getStepSequencerSample(StepSequencer *seq) {
    return seq->steps[seq->index];
}

RandomStepSequencer *createRandomStepSequencer(int sampleRate, int speed, float *steps, float *probabilities, int numSteps) {
    RandomStepSequencer *seq = malloc(sizeof(RandomStepSequencer));
    seq->sampleRate = sampleRate;
    seq->speed = speed;
    seq->numSteps = numSteps;
    seq->steps = steps;
    seq->probabilities = probabilities;
    seq->sample = 0;
    seq->index = 0;
    seq->stepIndex = 0;
    seq->trigger = 0;
    seq->stepsDuration = (float)seq->sampleRate * 60 / (float)(seq->speed);
    return seq;
}