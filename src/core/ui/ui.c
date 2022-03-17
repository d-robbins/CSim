#include "ui.h"

#include "../state.h"

void init_ui(struct UI* ui)
{
    init_buttons();

    for (int i = 0; i < BUTTON_SIZE; i++)
    {
        ui->_buttons[i]._body.x = 540;
        ui->_buttons[i]._body.y = i * 35;
        ui->_buttons[i]._body.w = 100;
        ui->_buttons[i]._body.h = 30;
    }
}

void render_ui(struct UI* ui)
{
    for (int i = 0; i < BUTTON_SIZE; i++)
    {
        SDL_RenderCopy(window._renderer, ui->_buttons[i]._texture, NULL, &ui->_buttons[i]._body);
    }
}

void update_ui(struct UI* ui)
{
    if ((window._mouse._lX == -1) || (window._mouse._lY == -1))
        return;

    SDL_Rect click = { .x = state._window->_mouse._lX, .y = state._window->_mouse._lY, .w = 10, .h = 10 };

    propogate_click(ui, click);

    window._mouse._lX = -1;
    window._mouse._lY = -1;
}

void propogate_click(struct UI* ui, SDL_Rect click)
{
    for (int i = 0; i < BUTTON_SIZE; i++)
    {
        SDL_Rect result;

        if (SDL_IntersectRect(&click, &ui->_buttons[i]._body, &result) == SDL_TRUE)
        {
            ui->_buttons[i]._handler();
            break;
        }
    }

    propogate_event(&state._env);
}

void delete_ui(struct UI* ui)
{

}