#include "ui.h"

#include "../state.h"

#include "../util/util.h"

void or_button_handler()
{
    struct Gate gate = GATES[OR_ID];
    add_gate(&state._env, gate);
}   

void or_button_init()
{
    struct Button button;
    button._handler = or_button_handler;
    button._texture = initialize_texture(state._window->_renderer, "textures/add_or.png");
    state._ui._buttons[ADD_OR] = button;
}