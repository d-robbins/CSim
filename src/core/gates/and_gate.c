#include "gate.h"
#include "../window.h"
#include "../util/util.h"

#include <stdio.h>

float and_condition(struct Gate* gate)
{
    if (gate->_pins._i != 2)
    {
        perror("improper and gate...\n");
        exit(1); 
    }

    if ((gate->_pins._in[0]._power > 0.0f) && (gate->_pins._in[1]._power > 0.0f))
    {
        return 1.0f;
    }   

    return 0.0f;
}

struct PinLayout and_layout = {
    ._in = (struct Pin[2]) {
        {._x = 0, ._y = 6, ._power = 0}, 
        {._x = 0, ._y = 32, ._power = 0} 
        },
    ._out = (struct Pin[1]) {
        {._x = 53, ._y = 20, ._power = 0}
        },
    ._i = 2,
    ._o = 1
};

void and_init()
{
    struct Gate and_gate = DEFAULT_GATE;
    and_gate._condition = &and_condition;
    and_gate._pins = and_layout;
    and_gate._id = AND_ID;
    GATES[AND_ID] = and_gate;
}

void and_init_texture()
{
    SDL_Texture* andTex = initialize_texture(window._renderer, "textures/and_gate.png");
    GATE_TEXTURES[AND_ID] = andTex;
}