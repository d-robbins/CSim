#ifndef PIN_LAYOUT_H__
#define PIN_LAYOUT_H__

#include <stdlib.h>

struct Pin
{
    int _power;
    int _x;
    int _y;
};

struct PinLayout
{
    struct Pin* _in;
    struct Pin* _out;
    int _i;
    int _o;
};

#endif