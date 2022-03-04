#include "csim.h"

/// run the sandbox
/// @param sim sandbox
void run(csim* sim)
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
            { onClick(sim, &e); } break;
                
            case SDL_MOUSEBUTTONDOWN:
            { onMouseDown(sim, &e); } break;
                
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

void render_menu(csim* sim)
{
    for (int i = 0; i < sim->_menu->_numButtons; i++)
    {
        BUTTON_COLOR
        SDL_RenderFillRect(sim->_renderer, &sim->_menu->_buttons[i]._button);
    }
}

void onClickAddAND(csim* sim)
{
    add_gate(sim, 2, 1, AND, AND_GATE);
}

void onClickAddOR(csim* sim)
{
    add_gate(sim, 2, 1, OR, OR_GATE);
}

/// create a sandbox
csim* create_csim(void)
{
    csim* game = (csim*)malloc(sizeof(csim));
    game->_window = SDL_CreateWindow(CSIM_NAME, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (game->_window == NULL)
    {
        errorExit(SDL_GetError());
    }

    game->_renderer = SDL_CreateRenderer(game->_window, -1, 0);
    game->_state = RUNNING;
    
    game->_wires = (wire_t**)malloc(sizeof(wire_t*) * MAX_WIRES);
    game->_gates = (gate_t**)malloc(sizeof(gate_t*) * MAX_GATES);
    
    game->_ortexture = NULL;
    game->_andtexture = NULL;
    
    game->_attachedGate = NULL;
    
    for (int i = 0; i < MAX_WIRES; i++)
    {
        game->_wires[i] = NULL;
    }
    
    for (int i = 0; i < MAX_GATES; i++)
    {
        game->_gates[i] = NULL;
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

SDL_Texture* intialize_texture(csim* sim, const char* path)
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
void cleanup(csim* sim)
{
    for (int i = 0; i < MAX_WIRES; i++)
    {
        if (sim->_wires[i] != NULL)
        {
            free(sim->_wires[i]);
        }
    }
    
    for (int i = 0; i < MAX_GATES; i++)
    {
        if (sim->_gates[i] != NULL)
        {
            free(sim->_gates[i]);
        }
    }
    
    destroy_menu(sim->_menu);

    free(sim->_menu);
    free(sim->_wires);
    free(sim->_gates);

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
gate_t* add_gate(csim* sim, int inports, int outports, enum GATE_TYPE type, gate_condition cond)
{
    gate_t* newGate = create_gate(inports, outports, type, cond);
    
    sim->_gates[sim->_curgate++] = newGate;
    
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
wire_t* add_wire(csim* sim, gate_t* g1, gate_t* g2)
{
    wire_t* wire = out_to_in(g1, g2);
    if (wire != NULL)
    {
        sim->_wires[sim->_curwire++] = wire;
        
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

void onClick(csim* sim, SDL_Event* e)
{
    if (e->button.button == SDL_BUTTON_LEFT)
    {
        SDL_Rect mouseClick = {.x = e->button.x, .y = e->button.y, .w = 10, .h = 10};
        SDL_Rect result;

        if ((sim->_state & MOVE_GATE) != 0)
        {
            sim->_state &= (~MOVE_GATE);
            sim->_attachedGate = NULL;
            return;
        }
        else
        {
            for (int i = 0; i < sim->_menu->_numButtons; i++)
            {
                if (SDL_IntersectRect(&sim->_menu->_buttons[i]._button, &mouseClick, &result) == SDL_TRUE)
                {
                    sim->_menu->_buttons[i]._handler(sim);
                    return;
                }
            }
        }

        for (int i = 0; i < MAX_GATES; i++)
        {
            if (sim->_gates[i] != NULL)
            {
                if (SDL_IntersectRect(&sim->_gates[i]->_sdlgate, &mouseClick, &result) == SDL_TRUE)
                {
                    sim->_attachedGate = sim->_gates[i];
                    sim->_state |= MOVE_GATE;
                    break;
                }
            }
        }
    }
}

/**
 * @brief recursively send power through wires/gates
 * 
 * @param wire current wire receiving power
 * @param power power to send
 */
void send_power(wire_t* wire, float power)
{
    if (wire == NULL)
        return;

    if (wire->_sinkgate == NULL)
    {
        printf("No sink port connection");
    }
    
    if (wire->_draingate == NULL)
    {
        printf("No drain port connection");
        return;
    }

    gate_t* draingate = wire->_draingate;

    // if wire is powered, set the port power on next gate
    wire->_power = power;

    // propogate power if gates condition met
    float sendPower = draingate->_propogate(draingate);

    int i;
    for (i = 0; i < draingate->_drainsize; i++)
    {
        // sendPower propogated to all the gates drains
        send_power(draingate->_drains[i], sendPower);
    }
}

void render_wires(csim* sim)
{
    int i;
    for (i = 0; i < MAX_WIRES; i++)
    {
        if (sim->_wires[i] != NULL)
        {
            WIRE_COLOR
            gate_t* wire_sink_gate = sim->_wires[i]->_sinkgate;
            gate_t* wire_drain_gate = sim->_wires[i]->_draingate;
            
            int x1 = wire_drain_gate->_sdlgate.x - 30;
            int y1 = wire_drain_gate->_sdlgate.y + wire_drain_gate->_sdlgate.w / 2;
            
            if (wire_sink_gate != NULL)
            {
                float sink_interval = wire_sink_gate->_sdlgate.w / (wire_sink_gate->_sinksize);
                x1 = wire_sink_gate->_sdlgate.x + wire_sink_gate->_sdlgate.w;
                y1 = wire_sink_gate->_sdlgate.y + sink_interval + sink_interval * sim->_wires[i]->_sinkport;
            }
            
            int x2 = wire_drain_gate->_sdlgate.x;
            
            float drain_interval = (float)wire_drain_gate->_sdlgate.w / (float)(wire_drain_gate->_sinksize);
            
            int y2 = wire_drain_gate->_sdlgate.y + drain_interval + drain_interval * sim->_wires[i]->_drainport;
            
            
            SDL_RenderDrawLine(sim->_renderer, x1, y1, x2, y2);
        }
    }
}

void onMouseDown(csim* sim, SDL_Event* e)
{
    
}

void render_gates(csim* sim)
{
    int i;
    for (i = 0; i < MAX_GATES; i++)
    {
        if (sim->_gates[i] != NULL)
        {
            SDL_Texture * gateTex = NULL;
            switch(sim->_gates[i]->_type)
            {
                case OR:
                    gateTex = sim->_ortexture;
                    break;
                case AND:
                    gateTex = sim->_andtexture;
                    break;
                default: break;
            }
            
             if (gateTex != NULL)
             {
                SDL_RenderCopy(sim->_renderer, gateTex, NULL, &sim->_gates[i]->_sdlgate);
             }
             else
             {             
                GATE_COLOR
                printf("could not load gate texture for gate type: %d\n", sim->_gates[i]->_type);
                SDL_RenderFillRect(sim->_renderer, &sim->_gates[i]->_sdlgate);
             }
        }
    }
}


