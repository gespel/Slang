#include "modules/modifier/include/modifier_types.h"

Modifier *createModifier(void *modifier, ModifierType type);

float applyModifier(Modifier *modifier, float sample);