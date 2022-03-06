#ifndef WIRE_H
#define WIRE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct CSimGate gate_t;
typedef struct CSimPort port_t;

typedef struct CSimWire
{
    float _power;
    
    /// sink gate_t connection of this wire, null if none.
    /// default power in
    port_t* _sinkport;
    
    /// drain gate_t connection of this wire, null if none.
    /// default power out
    port_t* _drainport;
} wire_t;

wire_t* createWire(port_t* g1, port_t* g2);

void freeWire(wire_t* wire);

void sendPower(wire_t* wire, float power);

#endif // WIRE_H