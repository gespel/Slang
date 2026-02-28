#include "modules/envelope/include/envelope.h"
#include "stdlib.h"
#include "modules/stepsequencer/include/stepsequencer_types.h"

EnvelopeGenerator* createEnvelopeGenerator(void* envelopeGenerator, EnvelopeType type, StepSequencer* triggerSequencer) {
    EnvelopeGenerator* out = malloc(sizeof(EnvelopeGenerator));

    out->envelope = envelopeGenerator;
    out->type = type;
    out->triggerSequencer = triggerSequencer;

    return out;
}