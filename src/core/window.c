#include "window.h"

struct Window window;

void intialize_window(SFunc init, SFunc update, SFunc render, SFunc destroy)
{
    window._window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
        , WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    window._renderer = SDL_CreateRenderer(window._window, -1, 0);

    window._destroy = destroy;
    window._render = render;
    window._update = update;
    window._init = init;
}

void game_loop(void)
{
    window._init();
    int run = 1;

    while (run)
    {
        SDL_Event e;
        SDL_WaitEvent(&e);
        if (e.type == SDL_QUIT) { run = 0; }
  
        if (e.type == SDL_MOUSEBUTTONDOWN) 
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            window._mouse._lX = x;
            window._mouse._lY = y;
        }
        
        SDL_SetRenderDrawColor(window._renderer, 255, 255, 255, 255);
        SDL_RenderClear(window._renderer);

        window._update();

        window._render();

        SDL_RenderPresent(window._renderer);
    }

    window._destroy();
}
