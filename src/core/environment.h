#ifndef ENVIRONMENT_H__
#define ENVIRONMENT_H__

#include "gates/gate.h"

struct Wire
{
    struct Pin* _sink;
    struct Pin* _drain;
};

struct WireArray
{
    struct Wire* _wires;
    int _curwire;
    int _size;
};

struct GateArray
{
    struct Gate* _gates;
    int _curgate;
    int _size;
};

struct EnvironmentState
{
    struct Gate* _lastGateClicked;
    struct Wire* _lastWireClicked;
};

struct Environment
{
    struct EnvironmentState _state;

    struct GateArray _gateArr;
    struct WireArray _wireArr;
    
    struct Wire _wire;
};

void init_environment(struct Environment* env);
void update_environment(struct Environment* env);
void render_environment(struct Environment* env);
void destroy_environment(struct Environment* env);

void propogate_event(struct Environment* env);

void add_gate(struct Environment* env, struct Gate newGate);
void add_wire(struct Environment* env, struct Pin* lhs, struct Pin* rhs);

#endif 