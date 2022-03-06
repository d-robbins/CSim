#include "gate_layout.h"

struct PinLayout AND_LAYOUT = {
    ._in = (struct OffsetPair[2]) {
        {._x = 0, ._y = 10}, 
        {._x = 0, ._y = 36} 
        },
    ._out = (struct OffsetPair[1]) {
        {._x = 90, ._y = 22}},
    ._i = 2,
    ._o = 1
};

struct PinLayout OR_LAYOUT = {
    ._in = (struct OffsetPair[2]) {
        {._x = 0, ._y = 10}, 
        {._x = 0, ._y = 36} 
        },
    ._out = (struct OffsetPair[1]) {
        {._x = 90, ._y = 22}},
    ._i = 2,
    ._o = 1
};

