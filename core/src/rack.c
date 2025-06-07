#include "../include/rack.h"

void addSineOscillator(Rack* rack, SineOscillator* input) {
    rack->sine_oscs[rack->num_sine_oscs] = input;
    rack->num_sine_oscs = rack->num_sine_oscs + 1; 
}