#include "gate.h"

struct Gate GATES[LAST_ID];
SDL_Texture* GATE_TEXTURES[LAST_ID];

struct Gate DEFAULT_GATE = {
    ._body = {.w = 60, .h = 50, .x = 0, .y = 0},
    ._condition = DEFAULT_CONDITION,
    ._id = -1,
    ._pins = {}
};

void move_gate(struct Gate* gate, int x, int y)
{
    //TODO: move pins too!
    gate->_body.x = x;
    gate->_body.y = y;
}

float DEFAULT_CONDITION(struct Gate* gate)
{   
    return 1.0f;
}