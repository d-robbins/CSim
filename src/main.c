
//
//  main.c
//  csim
//
//  Created by David Robbins on 2/22/22.
//

#include "csim.h"

#include <SDL.h>

#include <stdio.h>

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        errorExit(SDL_GetError());
    }

    csim* game = create_csim();

    run(game);
    cleanup(game);

    free(game);
    SDL_Quit();

    return 0;
}
