#ifndef CSIM_UTIL_H
#define CSIM_UTIL_H

#include <SDL.h>
#include <SDL_image.h>

SDL_Texture* initialize_texture(SDL_Renderer* renderer, const char* path);

#endif // CSIM_UTIL_H