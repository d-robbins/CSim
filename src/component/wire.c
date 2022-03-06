#include "wire.h"

#include "gates.h"

/**
 * @brief create a wire from one gate to another
 * 
 * @param g1 the gate whos output port will have wire attached
 * @param g2 the gate whos input port will have wire attached
 * @return wire_t* created wire
 */
wire_t* createWire(port_t* g1, port_t* g2)
{
    wire_t* newWire = (wire_t*)malloc(sizeof(wire_t));
    
    newWire->_power = 0.0;
    
    // allow ability for no output to wire
    // for input pins
    if (g1->_type != OUT)
    {
        printf("wrong end out\n");
    }

    if (g2->_type != IN)
    {
        printf("wrong end in\n");
    }

    g1->_wire = newWire;
    g2->_wire = newWire;

    newWire->_drainport = g2;
    newWire->_sinkport = g1;

    return newWire;
}

/**
 * @brief recursively send power through wires/gates
 * 
 * @param wire current wire receiving power
 * @param power power to send
 */
void sendPower(wire_t* wire, float power)
{
    // if (wire == NULL)
    //     return;

    // if (wire->_sinkgate == NULL)
    // {
    //     printf("No sink port connection");
    // }
    
    // if (wire->_draingate == NULL)
    // {
    //     printf("No drain port connection");
    //     return;
    // }

    // gate_t* draingate = wire->_draingate;

    // // if wire is powered, set the port power on next gate
    // wire->_power = power;

    // // propogate power if gates condition met
    // float propPower = draingate->_propogate(draingate);

    // int i;
    // for (i = 0; i < draingate->_drainsize; i++)
    // {
    //     // sendPower propogated to all the gates drains
    //     sendPower(draingate->_drains[i], propPower);
    // }
}

void freeWire(wire_t* wire)
{
    free(wire);
}