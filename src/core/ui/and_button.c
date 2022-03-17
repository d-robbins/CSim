#include "ui.h"


#include "../state.h"

#include "../util/util.h"

void and_button_handler()
{
    struct Gate gate = GATES[AND_ID];
    add_gate(&state._env, gate);
}   

void and_button_init()
{
    struct Button button;
    button._handler = and_button_handler;
    button._texture = initialize_texture(state._window->_renderer, "textures/add_and.png");
    state._ui._buttons[ADD_AND] = button;
}