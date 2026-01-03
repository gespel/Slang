#include "modules/envelope/include/envelope.h"
#include "stdlib.h"

EnvelopeGenerator* createEnvelopeGenerator(void* envelopeGenerator, EnvelopeType type) {
    EnvelopeGenerator* out = malloc(sizeof(EnvelopeGenerator));

    out->envelope = envelopeGenerator;
    out->type = type;

    return out;
}