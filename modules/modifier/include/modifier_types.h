typedef enum ModifierType {
    FILTER, BITCRUSHER
} ModifierType;

typedef struct Modifier {
    void *modifier;
    ModifierType type;
} Modifier;