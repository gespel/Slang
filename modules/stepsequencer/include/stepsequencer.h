//
// Created by Sten on 24.07.2025.
//

#ifndef STEPSEQUENCER_H
#define STEPSEQUENCER_H
#include "stepsequencer_types.h"

StepSequencer *createStepSequencer(int sampleRate, int speed, float *steps, int numSteps);

void tickStepSequencer(StepSequencer* seq);
float getStepSequencerSample(StepSequencer *seq);

#endif //STEPSEQUENCER_H
