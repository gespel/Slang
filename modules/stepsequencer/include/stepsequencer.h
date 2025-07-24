//
// Created by Sten on 24.07.2025.
//

#ifndef STEPSEQUENCER_H
#define STEPSEQUENCER_H

typedef struct StepSequencer {
    int sampleRate;
    int speed;
    float *steps;
    int numSteps;
    float sample;
    int index;
    int stepIndex;
} StepSequencer;

StepSequencer *createStepSequencer(int sampleRate, int speed, float *steps, int numSteps);

float getSample(StepSequencer *seq);

#endif //STEPSEQUENCER_H
