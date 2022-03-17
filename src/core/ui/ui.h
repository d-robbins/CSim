#ifndef UI_H__
#define UI_H__

#include <SDL.h>

typedef void (*button_handler) ();

enum BUTTONS
{
    ADD_AND,
    ADD_OR,
    ADD_IPIN
};
#define BUTTON_SIZE ADD_IPIN+1

struct Button
{
    SDL_Rect _body;
    SDL_Texture* _texture;
    button_handler _handler;
};

struct UI
{   
    struct Button _buttons[BUTTON_SIZE];
};

#define DECLARE_BUTTON(name) \
    extern void name##_button_init(); \
    name##_button_init();

void propogate_click(struct UI* ui, SDL_Rect click);

void init_ui(struct UI* ui);
void render_ui(struct UI* ui);
void update_ui(struct UI* ui);
void delete_ui(struct UI* ui);

static inline void init_buttons()
{
    DECLARE_BUTTON(and);
    DECLARE_BUTTON(or);
    DECLARE_BUTTON(ipin);
}

#endif 