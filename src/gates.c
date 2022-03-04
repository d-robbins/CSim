#include "gates.h"

/**
 * @brief create a wire from one gate to another
 * 
 * @param g1 the gate whos output port will have wire attached
 * @param g2 the gate whos input port will have wire attached
 * @return wire_t* created wire
 */
wire_t* out_to_in(gate_t* g1, gate_t* g2)
{
    wire_t* newWire = (wire_t*)malloc(sizeof(wire_t));
    
    newWire->_drainport = 0;
    newWire->_sinkport = 0;
    newWire->_power = 0.0;
    
    newWire->_draingate = NULL;
    newWire->_sinkgate = NULL;
    
    // allow ability for now output to wire
    // for input pins
    if (g1 != NULL)
    {
        attach_wire_sink(g1, newWire);
    }
    
    if (g2 != NULL)
    {
        attach_wire_drain(g2, newWire);
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
void attach_wire_sink(gate_t* gate, wire_t* wire)
{
    wire->_sinkgate = gate;

    gate->_drains[gate->_curdrain++] = wire;
    wire->_sinkport = gate->_curdrain - 1;

    gate->_curdrain %= gate->_drainsize;
}

/// attach wires drain to gates sink
/// @param gate gate whos sink will be attached to wires drain
/// @param wire wire
void attach_wire_drain(gate_t* gate, wire_t* wire)
{
    wire->_draingate = gate;

    gate->_sinks[gate->_cursink++] = wire;
    wire->_drainport = gate->_cursink - 1;

    gate->_cursink %= gate->_sinksize;
}

/// create a new gate
/// @param sinks number of input pins
/// @param drains number of output pins
/// @param cond gates condition
gate_t* create_gate(int sinks, int drains, enum GATE_TYPE type, gate_condition cond)
{
    gate_t* newGate = (gate_t*)malloc(sizeof(gate_t));
    
    newGate->_drainsize = drains;
    newGate->_sinksize = sinks;
    
    newGate->_sinks = (wire_t**)malloc(sizeof(wire_t*) * sinks);
    newGate->_drains = (wire_t**)malloc(sizeof(wire_t*) * drains);
    
    newGate->_curdrain = 0;
    newGate->_cursink = 0;
    
    newGate->_sdlgate.x = 0;
    newGate->_sdlgate.y = 0;
    newGate->_sdlgate.w = 100;
    newGate->_sdlgate.h = 50;
    
    newGate->_type = type;
    
    int i;
    for (i = 0; i < sinks; i++)
    {
        newGate->_sinks[i] = NULL;
    }
    
    for (i = 0; i < drains; i++)
    {
        newGate->_drains[i] = NULL;
    }
    
    newGate->_powered = 0;

    newGate->_propogate = cond;
    return newGate;
}

/// AND gate condition
/// @param gate gate to test
float and_condition(gate_t* gate)
{
    int i;
    
    // ports that are recieving power
    int portsPowered = 0;
    float powerOut = 0.0;
    
    for (i = 0; i < gate->_sinksize; i++)
    {
        if (gate->_sinks[i] != NULL)
        {
            float power = gate->_sinks[i]->_power;
            if (power > 0.0)
            {
                portsPowered++;
                powerOut += power;
            }
        }
    }
    
    if (portsPowered >= 2)
    {
        printf("AND GATE ON\n");
        gate->_powered = 1;
        return (powerOut / (float)portsPowered);
    }
    else
    {
        printf("AND GATE OFF\n");
        gate->_powered = 0;
        return 0.0;
    }
}

/// OR gate condition
/// @param gate gate to test
float or_condition(gate_t* gate)
{
    int i;
    
    // ports that are recieving power
    int portsPowered = 0;
    
    float powerOut = 0.0;
    
    for (i = 0; i < gate->_sinksize; i++)
    {
        if (gate->_sinks[i] != NULL)
        {
            float power = gate->_sinks[i]->_power;
            if (power > 0.0)
            {
                portsPowered++;
                powerOut += power;
            }
        }
    }
    
    if (portsPowered >= 1)
    {
        printf("OR GATE ON\n");
        gate->_powered = 1;
        return powerOut;
    }
    else
    {
        printf("OR GATE OFF\n");
        gate->_powered = 0;
        return 0.0;
    }
}
