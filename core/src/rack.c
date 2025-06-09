#include "../include/rack.h"

void addSineOscillator(Rack* rack, SineOscillator* input) {
    rack->sine_oscillators[rack->num_sine_oscillators] = input;
    rack->num_sine_oscillators = rack->num_sine_oscillators + 1;
}