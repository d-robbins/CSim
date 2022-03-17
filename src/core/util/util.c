#include "util.h"

SDL_Texture* initialize_texture(SDL_Renderer* renderer, const char* path)
{
    SDL_Texture* newTex = NULL;
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
    {
        printf("load image error %s\n", IMG_GetError());
        exit(1);
    }
    
    newTex = SDL_CreateTextureFromSurface(renderer, surface);
    if (newTex == NULL)
    {
        printf("create image error %s\n", SDL_GetError());
        exit(1);
    }

    SDL_FreeSurface(surface);
    printf("Succesfully created texture: %s\n", path);
    return newTex;   
}