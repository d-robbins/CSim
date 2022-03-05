#ifndef CSIM_UTIL_H
#define CSIM_UTIL_H

#include <SDL.h>
#include <SDL_image.h>

SDL_Texture* initializeTexture(SDL_Renderer* renderer, const char* path);

#endif // CSIM_UTIL_H