
//
//  main.c
//  csim
//
//  Created by David Robbins on 2/22/22.
//

#include "sim/csim.h"

#include <SDL.h>

#include <stdio.h>

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        errorExit(SDL_GetError());
    }

    struct CSim* game = createCSim();

    run(game);
    cleanup(game);

    free(game);
    SDL_Quit();

    return 0;
}
