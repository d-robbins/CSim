#ifndef GATES_H
#define GATES_H

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include "wire.h"

/// OR gate gate_condition
#define AND_LOGIC     ANDCondition

/// AND gate gate_condition
#define OR_LOGIC    ORCondition

typedef struct CSimWire wire_t;
typedef struct CSimGate gate_t;
typedef struct CSimPort port_t;

/**
 @brief determines power flow out of gate
 
 @param gate gate_t* the gate to test the condition of
 @return float that determines power out
 */
typedef float (*gate_condition) (gate_t* gate);

enum GATE_TYPE
{
    AND,
    OR
};

enum PORT_TYPE
{
    IN,
    OUT
};

typedef struct CSimPort
{
    SDL_Rect _portRect;
    enum PORT_TYPE _type;
    gate_t* _gate;
    wire_t* _wire;
    int _offX;
    int _offY;

} port_t;

typedef struct CSimGate
{   
    gate_condition _propogate;
    
    SDL_Rect _sdlgate;
    
    int _powered;
    
    enum GATE_TYPE _type;

    int _portsize;

    port_t* _ports;
} gate_t;

gate_t* createGate(int sinks, int drains, enum GATE_TYPE type);

void freeGate(gate_t* gate);

float ANDCondition(gate_t* gate);
float ORCondition(gate_t* gate);

void moveGate(gate_t* gate, int x, int y);

port_t* getPortClicked(gate_t* gate, SDL_Rect* click);

#endif // GATES_H
