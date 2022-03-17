#include "environment.h"

#include "window.h"

void init_environment(struct Environment* env)
{
    struct EnvironmentState state = { ._lastGateClicked = NULL, ._lastWireClicked = NULL };
    env->_state = state;

    struct GateArray gate_arr = { ._curgate = 0, ._size = 2, ._gates = (struct Gate*)malloc(sizeof(struct Gate) * 2) };
    env->_gateArr = gate_arr;

    struct WireArray wire_arr = { ._curwire = 0, ._size = 1, ._wires = (struct Wire*)malloc(sizeof(struct Wire) * env->_wireArr._size) };
    env->_wireArr = wire_arr;

}

void update_environment(struct Environment* env)
{
     printf("fdas\n");
    if (env->_state._lastGateClicked != NULL)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        move_gate(env->_state._lastGateClicked, x, y);
    }
}

void render_environment(struct Environment* env)
{
    for (int i = 0; i < env->_gateArr._size; i++)
    {
        SDL_RenderCopy(window._renderer, GATE_TEXTURES[env->_gateArr._gates[i]._id], NULL, &env->_gateArr._gates[i]._body);
    }

    // for (int i = 0; i < env->_wireArr._size; i++)
    // {
    //     struct Wire rwire = env->_wireArr._wires[i];
    //     if (rwire._drain != NULL && rwire._sink != NULL)
    //     {
    //         SDL_SetRenderDrawColor(window._renderer, 0, 0, 0, 255);
    //         SDL_RenderDrawLine(window._renderer, rwire._drain->_x,
    //             rwire._drain->_y,rwire._sink->_x, 
    //             rwire._sink->_y);
    //     }
    // }
}

void destroy_environment(struct Environment* env)
{
    free(env->_gateArr._gates);
    free(env->_wireArr._wires);
}

void add_gate(struct Environment* env, struct Gate newGate)
{
    struct GateArray* arr = &env->_gateArr;
    if ((arr->_curgate + 1) > arr->_size)
    {
        arr->_size *= 2;
        arr->_gates = (struct Gate*)realloc(arr->_gates, sizeof(struct Gate) * arr->_size);
        if (arr->_gates == NULL)
        {
            printf("realloc failed in gate array\n");
            exit(1);
        }

        printf("gate array resized to: %d\n", arr->_size);
    }

    printf("added gate!\n");
    arr->_gates[arr->_curgate] = newGate; 
    arr->_curgate++;
}

void add_wire(struct Environment* env, struct Pin* lhs, struct Pin* rhs)
{
    struct WireArray* arr = &env->_wireArr;
    if ((arr->_curwire + 1) > arr->_size)
    {
        arr->_size *= 2;
        arr->_wires = (struct Wire*)realloc(arr->_wires, sizeof(struct Wire) * arr->_size);
        if (arr->_wires == NULL)
        {
            printf("realloc failed in gate array\n");
            exit(1);
        }

        printf("gate array resized to: %d\n", arr->_size);
    }

    printf("added gate!\n");
    struct Wire newWire = {._sink = lhs, ._drain = rhs};
    arr->_wires[arr->_curwire] = newWire; 
    arr->_curwire++;
}

void propogate_event(struct Environment* env)
{
    for (int i = 0; i < env->_gateArr._size; i++)
    {
        SDL_Rect result;
        SDL_Rect mouseClick = { .x = window._mouse._lX, .y = window._mouse._lY, .w = 10, .h = 10 };
        if (SDL_IntersectRect(&env->_gateArr._gates[i]._body, &mouseClick, &result) == SDL_TRUE)
        {
            if (env->_state._lastGateClicked == NULL)
            {
                printf("attached\n");
                env->_state._lastGateClicked = &env->_gateArr._gates[i]._body;
            }
            else
            {
                env->_state._lastGateClicked = NULL;
            }
        }
    }
}