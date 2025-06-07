//
// Created by Sten on 07.06.2025.
//
#include "buffer_core.h"

SlangBufferCore* createBufferCore(SlangInterpreter* si, int bufferSize) {
    SlangBufferCore* bufferCore = malloc(sizeof(SlangBufferCore));
    bufferCore->interpreter = si;
    bufferCore->buffer = malloc(sizeof(double) * bufferSize);
    return bufferCore;
}

void renderBuffer(SlangBufferCore* sbc) {

}