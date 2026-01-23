#include "envelope_types.h"
#include "stepsequencer/include/stepsequencer_types.h"

EnvelopeGenerator* createEnvelopeGenerator(void* envelopeGenerator, EnvelopeType type, StepSequencer* triggerSequencer);

float getEnvelopeGeneratorSample(EnvelopeGenerator* input);