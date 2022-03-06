#include "csim.h"

#include "../component/gate_layout.h"

/// run the sandbox
/// @param sim sandbox
void run(struct CSim* sim)
{
    SDL_Event e;
    int x, y;
    
    addButton(sim->_menu, onClickAddOR);
    addButton(sim->_menu, onClickAddAND);

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
            {  } break;
                
            case SDL_MOUSEBUTTONDOWN:
            { onClickRelease(sim, &e); } break;
                
            case SDL_KEYDOWN:
            {
                if (e.key.keysym.sym == SDLK_w)
                {
                    sim->_state = DRAW_WIRE;
                }

            } break;
            
            default: break;
        }
        
        if (sim->_state == MOVE_GATE)
        {
            SDL_GetMouseState(&x, &y);
            sim->_attachedGate->_sdlgate.x = x;
            sim->_attachedGate->_sdlgate.y = y;
            moveGate(sim->_attachedGate, x, y);
        }

        SDL_SetRenderDrawColor(sim->_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(sim->_renderer);
        
        renderGates(sim);
        renderWires(sim);
        renderMenu(sim);
        
        SDL_RenderPresent(sim->_renderer);
    }
}


void onClickAddAND(struct CSim* sim)
{
    addGate(sim, &AND_LAYOUT, AND);
}

void onClickAddOR(struct CSim* sim)
{
    addGate(sim, &OR_LAYOUT, OR);
}

/// create csim instance
struct CSim* createCSim(void)
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
    
    game->_textures._andtexture = NULL;
    game->_textures._ortexture = NULL;
    
    game->_attachedGate = NULL;

    game->_ingate = NULL;
    game->_outgate = NULL;
    
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
        errorExit(IMG_GetError());
    }
    
    game->_textures._ortexture = initializeTexture(game->_renderer, "textures/or_gate.png");
    game->_textures._andtexture = initializeTexture(game->_renderer, "textures/and_gate.png");

    game->_components._curgate = 0;
    game->_components._curwire = 0;
    
    game->_menu = createMenu();

    return game;
}


/// free all memory for gates and wires. SDL objects
/// @param sim workspace
void cleanup(struct CSim* sim)
{
    for (int i = 0; i < MAX_WIRES; i++)
    {
        if (sim->_components._wires[i] != NULL)
        {
            freeWire(sim->_components._wires[i]);
        }
    }
    
    for (int i = 0; i < MAX_GATES; i++)
    {
        if (sim->_components._gates[i] != NULL)
        {
            freeGate(sim->_components._gates[i]);
        }
    }
    
    destroyMenu(sim->_menu);

    free(sim->_menu);
    free(sim->_components._wires);
    free(sim->_components._gates);

    SDL_DestroyTexture(sim->_textures._andtexture);
    SDL_DestroyTexture(sim->_textures._ortexture);

    SDL_DestroyRenderer(sim->_renderer);
    SDL_DestroyWindow(sim->_window);
}

void errorExit(const char* err)
{
    perror(err);
    exit(1);
}


/// add a gate
/// @param sim  environment
/// @param cond  type of gate
/// @param inports number of input pins
/// @param outports number of output pins
gate_t* addGate(struct CSim* sim, struct PinLayout* gateLayout, enum GATE_TYPE type)
{
    gate_t* newGate = createGate(gateLayout, type);
    
    sim->_components._gates[sim->_components._curgate++] = newGate;
    
    // make sure max wires have been reached
    if (sim->_components._curgate == MAX_GATES)
    {
        errorExit("max gates reached\n");
    }
    
    return newGate;
}


/// add a wire
/// @param sim environment
/// @param g1 output gate of wire
/// @param g2 input gate of wire
wire_t* addWire(struct CSim* sim, port_t* g1, port_t* g2)
{
    wire_t* wire = createWire(g1, g2);
    if (wire != NULL)
    {
        sim->_components._wires[sim->_components._curwire++] = wire;
        
        // make sure max wires have been reached
        // TODO: make _wires and _gates for sim dynamic
        if (sim->_components._curwire == MAX_WIRES)
        {
            errorExit("max wires reached\n");
        }
        
        return wire;
    }
    
    return NULL;
}

void onClickRelease(struct CSim* sim, SDL_Event* e)
{
    if (e->button.button == SDL_BUTTON_LEFT)
    {       
        SDL_Rect mouseClick = {.x = e->button.x, .y = e->button.y, .w = 50, .h = 50};

        if (sim->_state == MOVE_GATE)
        {
            sim->_state = RUNNING;
            sim->_attachedGate = NULL;
            return;
        }

        button_t* bClicked = buttonClicked(sim, mouseClick);
        if (bClicked != NULL)
        {
            bClicked->_handler(sim);
            return;
        }

        gate_t* gClicked = gateClicked(sim, mouseClick);
        if (gClicked != NULL)
        {
            if (sim->_state == DRAW_WIRE)
            {
                buildWire(sim, gClicked, &mouseClick);
                return;
            }

            sim->_attachedGate = gClicked;
            sim->_state = MOVE_GATE;
            return;
        }
    }
}

void buildWire(struct CSim* sim, gate_t* gateclicked, SDL_Rect* click)
{
    if (sim->_selec == 0)
    {
        port_t* port = getPortClicked(gateclicked, click);
        if (port != NULL)
        {
            if (port->_type == IN)
            {
                return;  
            }

            if (port->_wire != NULL)
            {
                removeWire(sim, port->_wire);                
            }

            sim->_outgate = port;
        }
        else
        {
                        printf("was null\n");

            return;
        }

        sim->_selec++;
    }
    else
    {
        port_t* port = getPortClicked(gateclicked, click);
        if (port != NULL)
        {
            if (port->_type == OUT)
            {
                return;  
            }

            if (port->_wire != NULL)
            {
                removeWire(sim, port->_wire);
            }

            sim->_ingate = port;
        }
        else
        {
            printf("was null\n");
            return;
        }

        addWire(sim, sim->_outgate, sim->_ingate);

        sim->_ingate = NULL;
        sim->_outgate = NULL;
        sim->_selec = 0;
        sim->_state = RUNNING;
    }          
}

void removeWire(struct CSim* sim, wire_t* wire)
{
    // TODO: may be possible dangling pointer or mem leak

    wire->_drainport->_wire = NULL;
    wire->_sinkport->_wire = NULL;
    for (int j = 0; j < MAX_WIRES; j++)
    {
        if (wire == sim->_components._wires[j])
        {
            free(sim->_components._wires[j]);
            sim->_components._wires[j] = NULL;
        }
    }
}

button_t* buttonClicked(struct CSim* sim, SDL_Rect click)
{
    SDL_Rect result;
    for (int i = 0; i < sim->_menu->_numButtons; i++)
    {
        if (SDL_IntersectRect(&sim->_menu->_buttons[i]._button, &click, &result) == SDL_TRUE)
        {
            return &sim->_menu->_buttons[i];
        }
    }
    return NULL;
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

