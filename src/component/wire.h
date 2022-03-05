#ifndef WIRE_H
#define WIRE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct CSimGate gate_t;

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

wire_t* createWire(gate_t* g1, gate_t* g2);

void freeWire(wire_t* wire);

void attachWireSink(gate_t* gate, wire_t* wire);
void attachWireDrain(gate_t* gate, wire_t* wire);
void sendPower(wire_t* wire, float power);

#endif // WIRE_H