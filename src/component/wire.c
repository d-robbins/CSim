#include "wire.h"

#include "gates.h"

/**
 * @brief create a wire from one gate to another
 * 
 * @param g1 the gate whos output port will have wire attached
 * @param g2 the gate whos input port will have wire attached
 * @return wire_t* created wire
 */
wire_t* createWire(gate_t* g1, gate_t* g2)
{
    wire_t* newWire = (wire_t*)malloc(sizeof(wire_t));
    
    newWire->_drainport = 0;
    newWire->_sinkport = 0;
    newWire->_power = 0.0;
    
    newWire->_draingate = NULL;
    newWire->_sinkgate = NULL;
    
    // allow ability for no output to wire
    // for input pins
    if (g1 != NULL)
    {
        attachWireSink(g1, newWire);
    }
    
    if (g2 != NULL)
    {
        attachWireDrain(g2, newWire);
    }
    else
    {
        perror("Could not attach wire to drain\n");
        return NULL;
    }
    
    return newWire;
}

/// attach wires sink to gates drain
/// @param gate gate whos drain will be attached to wires sink
/// @param wire wire
void attachWireSink(gate_t* gate, wire_t* wire)
{
    wire->_sinkgate = gate;

    gate->_drains[gate->_curdrain++] = wire;
    wire->_sinkport = gate->_curdrain - 1;

    gate->_curdrain %= gate->_drainsize;
}

/// attach wires drain to gates sink
/// @param gate gate whos sink will be attached to wires drain
/// @param wire wire
void attachWireDrain(gate_t* gate, wire_t* wire)
{
    wire->_draingate = gate;

    gate->_sinks[gate->_cursink++] = wire;
    wire->_drainport = gate->_cursink - 1;

    gate->_cursink %= gate->_sinksize;
}

/**
 * @brief recursively send power through wires/gates
 * 
 * @param wire current wire receiving power
 * @param power power to send
 */
void sendPower(wire_t* wire, float power)
{
    if (wire == NULL)
        return;

    if (wire->_sinkgate == NULL)
    {
        printf("No sink port connection");
    }
    
    if (wire->_draingate == NULL)
    {
        printf("No drain port connection");
        return;
    }

    gate_t* draingate = wire->_draingate;

    // if wire is powered, set the port power on next gate
    wire->_power = power;

    // propogate power if gates condition met
    float propPower = draingate->_propogate(draingate);

    int i;
    for (i = 0; i < draingate->_drainsize; i++)
    {
        // sendPower propogated to all the gates drains
        sendPower(draingate->_drains[i], propPower);
    }
}

void freeWire(wire_t* wire)
{
    free(wire);
}