#include "csim.h"

/// run the sandbox
/// @param sim sandbox
void run(struct CSim* sim)
{
    SDL_Event e;
    
    add_button(sim->_menu, onClickAddOR);
    add_button(sim->_menu, onClickAddAND);

    while (sim->_state != EXIT)
    {
        SDL_WaitEvent(&e);
        if (e.type == SDL_QUIT)
        {
            sim->_state = EXIT;
        }

        switch(e.type)
        {
            case SDL_QUIT:
            { sim->_state = EXIT; } break;

            case SDL_MOUSEBUTTONUP:
            { onClickRelease(sim, &e); } break;
                
            case SDL_MOUSEBUTTONDOWN:
            { onClickDown(sim, &e); } break;
                
            case SDL_KEYDOWN:
            {
                if (e.key.keysym.sym == SDLK_m)
                {
                    
                }
                
            } break;
            
            default: break;
        }
        
        if ((sim->_state & MOVE_GATE) != 0)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            sim->_attachedGate->_sdlgate.x = x;
            sim->_attachedGate->_sdlgate.y = y;
        }

        SDL_SetRenderDrawColor(sim->_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(sim->_renderer);
        
        render_gates(sim);
        render_wires(sim);
        render_menu(sim);
        
        SDL_RenderPresent(sim->_renderer);
    }
}


void onClickAddAND(struct CSim* sim)
{
    add_gate(sim, 2, 1, AND, AND_GATE);
}

void onClickAddOR(struct CSim* sim)
{
    add_gate(sim, 2, 1, OR, OR_GATE);
}

/// create a sandbox
struct CSim* create_csim(void)
{
    struct CSim* game = (struct CSim*)malloc(sizeof(struct CSim));
    game->_window = SDL_CreateWindow(CSIM_NAME, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (game->_window == NULL)
    {
        errorExit(SDL_GetError());
    }

    game->_renderer = SDL_CreateRenderer(game->_window, -1, 0);
    game->_state = RUNNING;
    
    game->_components._wires = (wire_t**)malloc(sizeof(wire_t*) * MAX_WIRES);
    game->_components._gates = (gate_t**)malloc(sizeof(gate_t*) * MAX_GATES);
    
    game->_ortexture = NULL;
    game->_andtexture = NULL;
    
    game->_attachedGate = NULL;
    
    for (int i = 0; i < MAX_WIRES; i++)
    {
        game->_components._wires[i] = NULL;
    }
    
    for (int i = 0; i < MAX_GATES; i++)
    {
        game->_components._gates[i] = NULL;
    }
    
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("SDL_image error %s\n", IMG_GetError());
        exit(1);
    }
    
    game->_ortexture = intialize_texture(game, "textures/or_gate.png");
    game->_andtexture = intialize_texture(game, "textures/and_gate.png");
        
    game->_curgate = 0;
    game->_curwire = 0;
    
    game->_menu = create_menu();

    return game;
}

SDL_Texture* intialize_texture(struct CSim* sim, const char* path)
{
    SDL_Texture* newTex = NULL;
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
    {
        printf("load image error %s\n", IMG_GetError());
        exit(1);
    }
    
    newTex = SDL_CreateTextureFromSurface(sim->_renderer, surface);
    if (newTex == NULL)
    {
        printf("create image error %s\n", SDL_GetError());
        exit(1);
    }

    SDL_FreeSurface(surface);
    return newTex;   
}


/// free all memory for gates and wires. SDL objects
/// @param sim workspace
void cleanup(struct CSim* sim)
{
    for (int i = 0; i < MAX_WIRES; i++)
    {
        if (sim->_components._wires[i] != NULL)
        {
            free(sim->_components._wires[i]);
        }
    }
    
    for (int i = 0; i < MAX_GATES; i++)
    {
        if (sim->_components._gates[i] != NULL)
        {
            free(sim->_components._gates[i]);
        }
    }
    
    destroy_menu(sim->_menu);

    free(sim->_menu);
    free(sim->_components._wires);
    free(sim->_components._gates);

    SDL_DestroyTexture(sim->_andtexture);
    SDL_DestroyTexture(sim->_ortexture);

    SDL_DestroyRenderer(sim->_renderer);
    SDL_DestroyWindow(sim->_window);
}

void errorExit(const char* err)
{
    perror(err);
    exit(1);
}


/// add a gate to the workspace
/// @param sim  workspace
/// @param cond  type of gate
/// @param inports number of input pins
/// @param outports number of output pins
gate_t* add_gate(struct CSim* sim, int inports, int outports, enum GATE_TYPE type, gate_condition cond)
{
    gate_t* newGate = create_gate(inports, outports, type, cond);
    
    sim->_components._gates[sim->_curgate++] = newGate;
    
    // make sure max wires have been reached
    if (sim->_curgate == MAX_GATES)
    {
        perror("MAX WIRES REACHED\n");
        exit(1);
    }
    
    return newGate;
}


/// add a wire to the workspace
/// @param sim workspace
/// @param g1 output gate of wire
/// @param g2 input gate of wire
wire_t* add_wire(struct CSim* sim, gate_t* g1, gate_t* g2)
{
    wire_t* wire = out_to_in(g1, g2);
    if (wire != NULL)
    {
        sim->_components._wires[sim->_curwire++] = wire;
        
        // make sure max wires have been reached
        // TODO: make _wires and _gates for sim dynamic
        if (sim->_curwire == MAX_WIRES)
        {
            perror("MAX WIRES REACHED\n");
            exit(1);
        }
        
        return wire;
    }
    
    return NULL;
}

void onClickRelease(struct CSim* sim, SDL_Event* e)
{
    if (e->button.button == SDL_BUTTON_LEFT)
    {       
        if ((sim->_state & MOVE_GATE) != 0)
        {
            sim->_state &= (~MOVE_GATE);
            sim->_attachedGate = NULL;
            return;
        }

        SDL_Rect mouseClick = {.x = e->button.x, .y = e->button.y, .w = 10, .h = 10};

        // for (int i = 0; i < sim->_menu->_numButtons; i++)
        // {
        //     if (SDL_IntersectRect(&sim->_menu->_buttons[i]._button, &mouseClick, &result) == SDL_TRUE)
        //     {
        //         sim->_menu->_buttons[i]._handler(sim);
        //         return;
        //     }
        // }

        gate_t* clicked = gateClicked(sim, mouseClick);
        if (clicked != NULL)
        {
            sim->_attachedGate = clicked;
            sim->_state |= MOVE_GATE;
        }
    }
}

gate_t* gateClicked(struct CSim* sim, SDL_Rect click)
{
    SDL_Rect result;
    for (int i = 0; i < MAX_GATES; i++)
        {
            if (sim->_components._gates[i] != NULL)
            {
                if (SDL_IntersectRect(&sim->_components._gates[i]->_sdlgate, &click, &result) == SDL_TRUE)
                {
                    return sim->_components._gates[i];
                }
            }
        }

    return NULL;
}

void onClickDown(struct CSim* sim, SDL_Event* e) {}

