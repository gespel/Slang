#pragma once
#include "modules/envelope/include/envelope_types.h"

LinearEnvelopeGenerator* createLinearEnvelopeGenerator(char* name, int sampleRate, float attack, float decay, float sustain, float release);

float getLinearEnvelopeGeneratorSample(LinearEnvelopeGenerator* envelope);

void triggerLinearEnvelopeGenerator(LinearEnvelopeGenerator* envelope);

void tickLinearEnvelopeGenerator(LinearEnvelopeGenerator* envelope);