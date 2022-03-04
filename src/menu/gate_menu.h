//
//  gate_menu.h
//  csim
//
//  Created by David Robbins on 2/24/22.
//

#ifndef GATE_MENU_H
#define GATE_MENU_H

#include <stdio.h>
#include <stdint.h>

#include <SDL.h>

#define MAX_BUTTONS 10

struct CSim;

typedef void (*button_handler) (struct CSim* sim);

typedef struct CSimButton {
    button_handler _handler;
    SDL_Rect _button;
    int _id;
} button_t;

struct CSimMenu {
    button_t* _buttons;
    int _numButtons;
    int _nextx;
    int _nexty;
};

void add_button(struct CSimMenu* menu, button_handler func);

struct CSimMenu* create_menu(void);

void destroy_menu(struct CSimMenu* menu);

#endif /* GATE_MENU_H */
