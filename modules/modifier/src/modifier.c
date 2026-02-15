#include "modules/modifier/include/modifier.h"
#include "modules/modifier/include/modifier_types.h"
#include "modules/filters/include/filter_types.h"
#include "modules/filters/include/filter.h"
#include "stdlib.h"

Modifier *createModifier(void *modifier, ModifierType type) {
    Modifier *out = malloc(sizeof(Modifier));
    out->modifier = modifier;
    out->type = type;
    return out;
}

float applyModifier(Modifier *modifier, float sample) {
    if (modifier->type == FILTER) {
        Filter *filter = modifier->modifier;
        return processFilterSample(filter, sample);
    }
    return 0.0f;
}