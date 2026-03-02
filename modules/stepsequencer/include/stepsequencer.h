//
// Created by Sten on 24.07.2025.
//

#ifndef STEPSEQUENCER_H
#define STEPSEQUENCER_H
#include "stepsequencer_types.h"

StepSequencer *createStepSequencer(int sampleRate, int speed, float *steps, int numSteps);
RandomStepSequencer *createRandomStepSequencer(int sampleRate, int speed, float *steps, float *probabilities, int numSteps);

void tickStepSequencer(StepSequencer* seq);
float getStepSequencerSample(StepSequencer *seq);

void tickRandomStepSequencer(RandomStepSequencer* seq);
float getRandomStepSequencerSample(RandomStepSequencer *seq);

int pseudoRandom(float probability);

#endif //STEPSEQUENCER_H
