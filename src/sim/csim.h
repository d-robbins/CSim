#ifndef CSIM_H
#define CSIM_H

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include <SDL_image.h>

#include "../component/gates.h"

#include "../menu/gate_menu.h"

#include "render.h"

#define CSIM_NAME "CSim"
#define MAX_GATES 100
#define MAX_WIRES 100

// TODO: fix these macros
#define GATE_COLOR SDL_SetRenderDrawColor(sim->_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
#define WIRE_COLOR SDL_SetRenderDrawColor(sim->_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
#define BUTTON_COLOR SDL_SetRenderDrawColor(sim->_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

enum GATE_TYPE;

enum STATE 
{
    RUNNING,
    EXIT,
    MOVE_GATE
};

struct CSimComponents
{
    gate_t** _gates;
    wire_t** _wires;
};

struct CSim
{
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    
    struct CSimMenu* _menu;
    struct CSimComponents _components;
    
    int _curwire;
    int _curgate;
    
    SDL_Texture* _ortexture;
    SDL_Texture* _andtexture;
    
    gate_t* _attachedGate;

    enum STATE _state;
};

void run(struct CSim* sim);

void cleanup(struct CSim* sim);

void errorExit(const char* err);

gate_t* add_gate(struct CSim* sim, int inports, int outports, enum GATE_TYPE type, gate_condition cond);
wire_t* add_wire(struct CSim* sim, gate_t* g1, gate_t* g2);

void onClickRelease(struct CSim* sim, SDL_Event* e);
void onClickDown(struct CSim* sim, SDL_Event* e);
gate_t* gateClicked(struct CSim* sim, SDL_Rect click);

SDL_Texture* intialize_texture(struct CSim* sim, const char* path);

struct CSim* create_csim(void);

void onClickAddAND(struct CSim* sim);
void onClickAddOR(struct CSim* sim);

#endif // CSIM_H