#ifndef MODIFIER_TYPES_H
#define MODIFIER_TYPES_H
typedef enum ModifierType {
    FILTER, BITCRUSHER
} ModifierType;

typedef struct Modifier {
    void *modifier;
    ModifierType type;
} Modifier;
#endif // MODIFIER_TYPES_H