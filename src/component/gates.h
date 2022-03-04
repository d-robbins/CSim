#ifndef GATES_H
#define GATES_H

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include "wire.h"

#define MAX_PORTS 2

/// OR gate gate_condition
#define OR_GATE     or_condition

/// AND gate gate_condition
#define AND_GATE    and_condition

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

typedef struct CSimGate
{   
    gate_condition _propogate;
    
    SDL_Rect _sdlgate;
    
    int _powered;
    
    int _sinksize;
    int _drainsize;
    
    int _cursink;
    int _curdrain;

    enum GATE_TYPE _type;
    
    wire_t** _sinks;
    wire_t** _drains;
} gate_t;

gate_t* create_gate(int sinks, int drains, enum GATE_TYPE type, gate_condition cond);

float and_condition(gate_t* gate);
float or_condition(gate_t* gate);

#endif // GATES_H
