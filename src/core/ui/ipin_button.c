#include "ui.h"

#include "../state.h"

#include "../util/util.h"

void ipin_button_handler()
{
    struct Gate gate = GATES[IPIN_ID];
    add_gate(&state._env, gate);
}   

void ipin_button_init()
{
    struct Button button;
    button._handler = ipin_button_handler;
    button._texture = initialize_texture(state._window->_renderer, "textures/add_input.png");
    state._ui._buttons[ADD_IPIN] = button;
}