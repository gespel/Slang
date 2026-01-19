#ifndef STEPSEQUENCER_TYPES_H
#define STEPSEQUENCER_TYPES_H
typedef struct StepSequencer {
    int sampleRate;
    int speed;
    float *steps;
    int numSteps;
    float sample;
    int index;
    int stepIndex;
    int stepsDuration;
    int trigger;
} StepSequencer;
#endif //STEPSEQUENCER_TYPES_H