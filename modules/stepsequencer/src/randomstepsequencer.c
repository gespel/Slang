#include "modules/stepsequencer/include/stepsequencer_types.h"
#include "modules/stepsequencer/include/randomstepsequencer.h"
#include <stdio.h>
#include <stdlib.h>

void tickRandomStepSequencer(RandomStepSequencer* seq) {
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
        //printf("======================\n");
        int pr = pseudoRandom(seq->probabilities[seq->index]);
        //printf("Step %d, probability: %f, random value: %d\n", seq->index, seq->probabilities[seq->index], pr);
        seq->trigger = pr;
        //printf("======================\n");

    }
}

float getRandomStepSequencerSample(RandomStepSequencer *seq) {
    return seq->steps[seq->index];
}

int getTrigger(Sequencer *sequencer) {
    switch (sequencer->type) {
        case STEPSEQUENCER:
            return ((StepSequencer*)sequencer->sequencer)->trigger;
        case RANDOMSTEPSEQUENCER:
            return ((RandomStepSequencer*)sequencer->sequencer)->trigger;
        default:
            return 0;
    }
}

int pseudoRandom(float probability) {
    float r = (float)rand() / (float)RAND_MAX;
    //printf("Random value: %f, probability: %f\n", r, probability);
    if (r > probability) {
        //printf("Triggering step!\n");
        return 1;
    }
    else {
        //printf("Not triggering step.\n");
        return 0;
    }
}