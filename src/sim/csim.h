#ifndef CSIM_H
#define CSIM_H

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include <SDL_image.h>

#include "../component/gates.h"
#include "../menu/gate_menu.h"
#include "util.h"
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
    MOVE_GATE,
    DRAW_WIRE
};

struct CSimComponents
{
    gate_t** _gates;
    wire_t** _wires;

    int _curwire;
    int _curgate;
};

struct CSimTexture
{
    SDL_Texture* _ortexture;
    SDL_Texture* _andtexture;
};

struct CSim
{
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    
    struct CSimMenu* _menu;
    struct CSimComponents _components;
    struct CSimTexture _textures;
    
    gate_t* _attachedGate;

    port_t* _outgate;
    port_t* _ingate;

    enum STATE _state;
    int _selec;
};

struct CSim* createCSim(void);
void run(struct CSim* sim);
void cleanup(struct CSim* sim);

void errorExit(const char* err);

gate_t* addGate(struct CSim* sim, int inports, int outports, enum GATE_TYPE type);
wire_t* addWire(struct CSim* sim, port_t* g1, port_t* g2);

void onClickRelease(struct CSim* sim, SDL_Event* e);
void onClickDown(struct CSim* sim, SDL_Event* e);

gate_t* gateClicked(struct CSim* sim, SDL_Rect click);
button_t* buttonClicked(struct CSim* sim, SDL_Rect click);

void onClickAddAND(struct CSim* sim);
void onClickAddOR(struct CSim* sim);

void buildWire(struct CSim* sim, gate_t* gateclicked, SDL_Rect* click);
void removeWire(struct CSim* sim, wire_t* wire);
#endif // CSIM_H