typedef struct StepSequencer {
    int sampleRate;
    int speed;
    float *steps;
    int numSteps;
    float sample;
    int index;
    int stepIndex;
} StepSequencer;