#ifndef RANDOMSTEPSEQUENCER_H
#define RANDOMSTEPSEQUENCER_H
#include "stepsequencer_types.h"

RandomStepSequencer *createRandomStepSequencer(int sampleRate, int speed, float *steps, float *probabilities, int numSteps);

void tickRandomStepSequencer(RandomStepSequencer* seq);
float getRandomStepSequencerSample(RandomStepSequencer *seq);

int pseudoRandom(float probability);


#endif //RANDOMSTEPSEQUENCER_H