//
// Created by Sten on 07.06.2025.
//

#ifndef BUFFER_CORE_H
#define BUFFER_CORE_H
#include "interpreter.h"

typedef struct SlangBufferCore {
    SlangInterpreter* interpreter;
    float* buffer;
    int bufferSize;
    int sampleRate;
} SlangBufferCore;

SlangBufferCore* createBufferCore(SlangInterpreter* si, int sampleRate, int bufferSize);
float* renderBuffer(SlangBufferCore* sbc);

#endif //BUFFER_CORE_H
