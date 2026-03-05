#include "envelope_types.h"
#include "modules/stepsequencer/include/stepsequencer_types.h"

EnvelopeGenerator* createEnvelopeGenerator(void* envelopeGenerator, EnvelopeType type, Sequencer* triggerSequencer);

float getEnvelopeGeneratorSample(EnvelopeGenerator* input);