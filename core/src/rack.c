#include "../include/rack.h"

void addSineOscillator(Rack* rack, SineOscillator* input) {
    rack->sine_oscillators[rack->numSineOscillators] = input;
    rack->numSineOscillators = rack->numSineOscillators + 1;
}
