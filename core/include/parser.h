//
// Created by Sten on 28.06.2025.
//
#pragma once
#include "interpreter.h"

#ifndef PARSER_H
#define PARSER_H

void parseOscillators(SlangInterpreter* si, int* i);

void parseFunction(SlangInterpreter* si, int* i);

void parseExpression(SlangInterpreter* si, int* i);

#endif //PARSER_H
