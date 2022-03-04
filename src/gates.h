#ifndef GATES_H
#define GATES_H

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

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

typedef struct CSimWire
{
    int _sinkport;
    int _drainport;
    
    float _power;
    
    /// sink gate_t connection of this wire, null if none.
    /// default power in
    gate_t* _sinkgate;
    
    /// drain gate_t connection of this wire, null if none.
    /// default power out
    gate_t* _draingate;
} wire_t;

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

wire_t* out_to_in(gate_t* g1, gate_t* g2);

gate_t* create_gate(int sinks, int drains, enum GATE_TYPE type, gate_condition cond);

void attach_wire_sink(gate_t* gate, wire_t* wire);
void attach_wire_drain(gate_t* gate, wire_t* wire);

float and_condition(gate_t* gate);
float or_condition(gate_t* gate);

#endif // GATES_H
