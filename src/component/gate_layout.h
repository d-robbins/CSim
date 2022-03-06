#ifndef GATE_LAYOUT_H
#define GATE_LAYOUT_H

struct PinLayout AND_LAYOUT;
struct PinLayout OR_LAYOUT;

struct OffsetPair
{
    int _x;
    int _y;
};

struct PinLayout
{
    struct OffsetPair* _in;
    struct OffsetPair* _out;
    int _i;
    int _o;
};


#endif // GATE_LAYOUT_H