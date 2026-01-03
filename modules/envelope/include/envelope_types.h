typedef enum EnvelopeType {
    LINENVELOPE, EXPENVELOPE
} EnvelopeType;

typedef struct EnvelopeGenerator {
    void* envelope;
    EnvelopeType type;
} EnvelopeGenerator;

typedef struct LinearEnvelopeGenerator {
    float sample;
    float volume;
    float phase;
    int sampleRate;
    char* name;
} LinearEnvelopeGenerator;

