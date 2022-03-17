#ifndef WINDOW_H__
#define WINDOW_H__

#include <SDL.h>

#define WINDOW_TITLE    "CircuitSim"
#define WINDOW_HEIGHT   480
#define WINDOW_WIDTH    640

typedef void (*SFunc)();

struct Mouse
{
    int _lX;
    int _lY;
};

struct Window
{
    SDL_Window* _window;
    SDL_Renderer* _renderer;

    struct Mouse _mouse;

    SFunc _init, _update, _render, _destroy;
};

void intialize_window(SFunc init, SFunc update, SFunc render, SFunc destroy);
void game_loop(void);

extern struct Window window;

#endif