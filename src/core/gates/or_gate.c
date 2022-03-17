#include "gate.h"
#include "../window.h"
#include "../util/util.h"

#include <stdio.h>

float or_condition(struct Gate* gate) 
{
    if (gate->_pins._i != 2)
    {
        perror("improper and gate...\n");
        exit(1); 
    }

    if ((gate->_pins._in[0]._power > 0.0f) || (gate->_pins._in[1]._power > 0.0f))
    {
        return 1.0f;
    }   

    return 0.0f;
}

struct PinLayout or_layout = {
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

void or_init()
{
    struct Gate gate = DEFAULT_GATE;
    gate._condition = or_condition;
    gate._id = OR_ID;
    GATES[OR_ID] = gate;
}

void or_init_texture()
{
    SDL_Texture* andTex = initialize_texture(window._renderer, "textures/or_gate.png");
    GATE_TEXTURES[OR_ID] = andTex;
}


