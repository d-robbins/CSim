#ifndef GATE_H__
#define GATE_H__    

#include <SDL.h>
#include "../util/pin_layout.h"

struct Gate;

typedef float (*gate_condition) (struct Gate* gate);

enum GATEID
{
    AND_ID,
    OR_ID,
    IPIN_ID
};

#define LAST_ID IPIN_ID

struct Gate
{
    enum GATEID _id;

    struct PinLayout _pins;

    gate_condition _condition;

    SDL_Rect _body;
};

float DEFAULT_CONDITION(struct Gate* gate);

void move_gate(struct Gate* gate, int x, int y);

extern struct Gate GATES[LAST_ID];
extern struct Gate DEFAULT_GATE;

extern SDL_Texture* GATE_TEXTURES[LAST_ID];

#define DECLARE_GATE(name)\
    extern void name##_init();\
    name##_init();

#define DECLARE_GATE_TEXTURE(name)\
    extern void name##_init_texture(); \
    name##_init_texture();

static inline void init_gates()
{
    DECLARE_GATE(and);
    DECLARE_GATE_TEXTURE(and);

    DECLARE_GATE(or);
    DECLARE_GATE_TEXTURE(or);
}

#endif