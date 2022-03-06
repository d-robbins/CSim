#include "gates.h"


/// create a new gate
/// @param sinks number of input pins
/// @param drains number of output pins
/// @param cond gates condition
gate_t* createGate(int sinks, int drains, enum GATE_TYPE type)
{
    gate_t* newGate = (gate_t*)malloc(sizeof(gate_t));
    
    newGate->_ports = (port_t*)malloc(sizeof(port_t) * (sinks + drains));
    newGate->_portsize = sinks+drains;
    
    for (int i = 0; i < sinks; i++)
    {
        newGate->_ports[i]._type = IN;
        printf("sink %d\n", i);
    }

    for (int i = sinks; i < (sinks + drains); i++)
    {
        newGate->_ports[i]._type = OUT;
        printf("out %d\n", i);
    }

    int in = 0;
    int out = 0;
    for (int i = 0; i < (drains + sinks); i++)
    {
        newGate->_ports[i]._wire = NULL;
        newGate->_ports[i]._gate = newGate;
        newGate->_ports[i]._portRect.w = 10;
        newGate->_ports[i]._portRect.h = 10;
        newGate->_ports[i]._portRect.y = 0;
        newGate->_ports[i]._portRect.x = 0;
        
        switch(newGate->_ports[i]._type)
        {
            case IN:
            if (in == 0)
            {
                newGate->_ports[i]._offX = 0;
                newGate->_ports[i]._offY = 10;
            }
            else if (in == 1)
            {
                newGate->_ports[i]._offX = 0;
                newGate->_ports[i]._offY = 36;
            }
            in++;
            break;
            case OUT:
            if (out == 0)
            {
                newGate->_ports[i]._offX = 94;
                newGate->_ports[i]._offY = 22;
            }
            out++;
            break;

            default: break;
        } 
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
