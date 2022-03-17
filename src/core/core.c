#include "core.h"

struct GameState state;

void update()
{
    update_ui(&state._ui);
    update_environment(&state._env);
}

void init()
{
    init_gates();
    
    init_environment(&state._env);
  
    struct Gate newGate = GATES[AND_ID];
    add_gate(&state._env, newGate);

    struct Gate newOrGate = GATES[OR_ID];
    add_gate(&state._env, newOrGate);

    init_ui(&state._ui);
}

void destroy()
{    
    destroy_environment(&state._env);
}

void render()
{
    render_environment(&state._env);
    render_ui(&state._ui);
}

void start()
{
    state._window = &window;

    intialize_window(init, update, render, destroy);

    game_loop();
}