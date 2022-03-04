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

typedef struct CSim csim;
typedef void (*button_handler) (csim* sim);

typedef struct CSimButton {
    button_handler _handler;
    SDL_Rect _button;
    int _id;
} button_t;

typedef struct CSimMenu {
    button_t* _buttons;
    int _numButtons;
    int _nextx;
    int _nexty;
} menu;

void add_button(menu* menu, button_handler func);

menu* create_menu(void);

void destroy_menu(menu* menu);

#endif /* GATE_MENU_H */
