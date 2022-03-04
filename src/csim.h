#ifndef CSIM_H
#define CSIM_H

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include <SDL_image.h>

#include "gates.h"

#include "gate_menu.h"

#define CSIM_NAME "CSIM"
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

typedef struct CSim
{
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    
    gate_t** _gates;
    wire_t** _wires;
    
    menu* _menu;
    
    // int _gatesize;
    // int _wiresize;
    
    int _curwire;
    int _curgate;
    
    SDL_Texture* _ortexture;
    SDL_Texture* _andtexture;
    
    gate_t* _attachedGate;

    enum STATE _state;
} csim;

void run(csim* sim);

void cleanup(csim* sim);

void errorExit(const char* err);

void power_wire(wire_t* wire);

gate_t* add_gate(csim* sim, int inports, int outports, enum GATE_TYPE type, gate_condition cond);
wire_t* add_wire(csim* sim, gate_t* g1, gate_t* g2);

void render_wires(csim* sim);
void render_gates(csim* sim);

void send_power(wire_t* wire, float power);

void onClick(csim* sim, SDL_Event* e);
void onMouseDown(csim* sim, SDL_Event* e);

void render_menu(csim* sim);

SDL_Texture* intialize_texture(csim* sim, const char* path);

csim* create_csim(void);

void onClickAddAND(csim* sim);
void onClickAddOR(csim* sim);

#endif // CSIM_H
