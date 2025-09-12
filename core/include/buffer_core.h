//
// Created by Sten on 07.06.2025.
//

#ifndef BUFFER_CORE_H
#define BUFFER_CORE_H
#include "interpreter.h"
#include "core_types.h"

SlangBufferCore* createBufferCore(SlangInterpreter* si, int sampleRate, int bufferSize);
void destroyBufferCore(SlangBufferCore* sbc);
float* renderBuffer(SlangBufferCore* sbc);

#endif //BUFFER_CORE_H
