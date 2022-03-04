#include "gates.h"


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
