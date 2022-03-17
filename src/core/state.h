#ifndef STATE_H_
#define STATE_H_

#include <SDL.h>   

#include "window.h"
#include "environment.h"
#include "ui/ui.h"

struct GameState
{
    struct Window* _window;
    struct Environment _env;
    struct UI _ui;
};

extern struct GameState state;

#endif 