#include "gates.h"


/// create a new gate
/// @param sinks number of input pins
/// @param drains number of output pins
/// @param cond gates condition
gate_t* createGate(struct PinLayout* gate_layout, enum GATE_TYPE type)
{
    gate_t* newGate = (gate_t*)malloc(sizeof(gate_t));
    newGate->_ports = (port_t*)malloc(sizeof(port_t) * (gate_layout->_i + gate_layout->_o));
    newGate->_portsize = gate_layout->_i + gate_layout->_o;
    intitalizePorts(newGate, gate_layout);
    
    for (int i = 0; i < newGate->_portsize; i++)
    {
        newGate->_ports[i]._gate = newGate;
        newGate->_ports[i]._wire = NULL;
        newGate->_ports[i]._portRect.w = 10;
        newGate->_ports[i]._portRect.h = 10;
        newGate->_ports[i]._portRect.x = newGate->_ports[i]._offX;
        newGate->_ports[i]._portRect.y = newGate->_ports[i]._offY;
    }

    SDL_Rect gateStructure = {.x = 0, .y = 0, .w = 100, .h = 50};
    newGate->_sdlgate = gateStructure;
    newGate->_type = type;
    newGate->_powered = 0;

    switch(type)
    {
        case AND:
        newGate->_propogate = AND_LOGIC;
        break;
        case OR:
        newGate->_propogate = OR_LOGIC;
        break;
        default:break;
    }

    return newGate;
}

void intitalizePorts(gate_t* gate, struct PinLayout* gateLayout)
{
    for (int in = 0; in < gateLayout->_i; in++)
    {
        gate->_ports[in]._offX = gateLayout->_in[in]._x;
        gate->_ports[in]._offY = gateLayout->_in[in]._y;
        gate->_ports[in]._type = IN;
    }

    for (int out = 0; out < gateLayout->_o; out++)
    {
        gate->_ports[out + gateLayout->_i]._offX = gateLayout->_out[out]._x;
        gate->_ports[out + gateLayout->_i]._offY = gateLayout->_out[out]._y;
        gate->_ports[out + gateLayout->_i]._type = OUT;
    }

}

void moveGate(gate_t* gate, int x, int y)
{
    gate->_sdlgate.x = x;
    gate->_sdlgate.y = y;

    for (int i = 0; i < gate->_portsize; i++)
    {
        gate->_ports[i]._portRect.x = gate->_sdlgate.x + gate->_ports[i]._offX;
        gate->_ports[i]._portRect.y = gate->_sdlgate.y + gate->_ports[i]._offY;
    }
}

port_t* getPortClicked(gate_t* gate, SDL_Rect* click)
{
    for (int i = 0; i < gate->_portsize; i++)
    {
        SDL_Rect result;
        if (SDL_IntersectRect(click, &gate->_ports[i]._portRect, &result) == SDL_TRUE)
        {
            return &gate->_ports[i];
        }
    }
    return NULL;
}

/// AND gate condition
/// @param gate gate to test
float ANDCondition(gate_t* gate)
{
    // int i;
    
    // // ports that are recieving power
    // int portsPowered = 0;
    // float powerOut = 0.0;
    
    // for (i = 0; i < gate->_sinksize; i++)
    // {
    //     if (gate->_sinks[i] != NULL)
    //     {
    //         float power = gate->_sinks[i]->_power;
    //         if (power > 0.0)
    //         {
    //             portsPowered++;
    //             powerOut += power;
    //         }
    //     }
    // }
    
    // if (portsPowered >= 2)
    // {
    //     printf("AND GATE ON\n");
    //     gate->_powered = 1;
    //     return (powerOut / (float)portsPowered);
    // }
    // else
    // {
    //     printf("AND GATE OFF\n");
    //     gate->_powered = 0;
    //     return 0.0;
    // }
    return 0.0;
}

void freeGate(gate_t* gate)
{
    free(gate->_ports);

    free(gate);
}

/// OR gate condition
/// @param gate gate to test
float ORCondition(gate_t* gate)
{
    // int i;
    
    // // ports that are recieving power
    // int portsPowered = 0;
    
    // float powerOut = 0.0;
    
    // for (i = 0; i < gate->_sinksize; i++)
    // {
    //     if (gate->_sinks[i] != NULL)
    //     {
    //         float power = gate->_sinks[i]->_power;
    //         if (power > 0.0)
    //         {
    //             portsPowered++;
    //             powerOut += power;
    //         }
    //     }
    // }
    
    // if (portsPowered >= 1)
    // {
    //     printf("OR GATE ON\n");
    //     gate->_powered = 1;
    //     return powerOut;
    // }
    // else
    // {
    //     printf("OR GATE OFF\n");
    //     gate->_powered = 0;
    //     return 0.0;
    // }
    return 0.0;
}
