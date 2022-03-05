//
//  gate_menu.c
//  csim
//
//  Created by David Robbins on 2/24/22.
//
#include "gate_menu.h"

void addButton(struct CSimMenu* menu, button_handler func)
{
    if (menu->_numButtons >= MAX_BUTTONS)
    {
        printf("Cannot add button, limit reached\n");
        return;
    }
    
    menu->_buttons[menu->_numButtons]._handler = func;
    menu->_buttons[menu->_numButtons]._button.w = 100;
    menu->_buttons[menu->_numButtons]._button.h = 30;
    menu->_buttons[menu->_numButtons]._button.x = menu->_nextx;
    menu->_buttons[menu->_numButtons]._button.y = menu->_nexty;
    menu->_buttons[menu->_numButtons]._id = menu->_numButtons;
    
    menu->_numButtons++;
    menu->_nexty += 35;
}

struct CSimMenu* createMenu(void)
{
    struct CSimMenu* newMenu = (struct CSimMenu*)malloc(sizeof(struct CSimMenu));
    newMenu->_numButtons = 0;
    newMenu->_buttons = (button_t*)malloc(sizeof(button_t) * MAX_BUTTONS);
    newMenu->_nextx = 540;
    newMenu->_nexty = 0;
    
    return newMenu;
}


void destroyMenu(struct CSimMenu* menu)
{
    free(menu->_buttons);
}

