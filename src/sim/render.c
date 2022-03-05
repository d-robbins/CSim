#include "render.h"

#include "csim.h"

void renderGates(struct CSim* sim)
{
    int i;
    for (i = 0; i < MAX_GATES; i++)
    {
        if (sim->_components._gates[i] != NULL)
        {
            SDL_Texture * gateTex = NULL;
            switch(sim->_components._gates[i]->_type)
            {
                case OR:
                    gateTex = sim->_textures._ortexture;
                    break;
                case AND:
                    gateTex = sim->_textures._andtexture;
                    break;
                default: break;
            }
            
             if (gateTex != NULL)
             {
                SDL_RenderCopy(sim->_renderer, gateTex, NULL, &sim->_components._gates[i]->_sdlgate);
             }
             else
             {             
                GATE_COLOR
                printf("could not load gate texture for gate type: %d\n", sim->_components._gates[i]->_type);
                SDL_RenderFillRect(sim->_renderer, &sim->_components._gates[i]->_sdlgate);
             }
        }
    }
}

void renderWires(struct CSim* sim)
{
    int i;
    for (i = 0; i < MAX_WIRES; i++)
    {
        if (sim->_components._wires[i] != NULL)
        {
            WIRE_COLOR
            gate_t* wire_sink_gate = sim->_components._wires[i]->_sinkgate;
            gate_t* wire_drain_gate = sim->_components._wires[i]->_draingate;
            
            int x1 = wire_drain_gate->_sdlgate.x - 30;
            int y1 = wire_drain_gate->_sdlgate.y + wire_drain_gate->_sdlgate.w / 2;
            
            if (wire_sink_gate != NULL)
            {
                float sink_interval = wire_sink_gate->_sdlgate.w / (wire_sink_gate->_sinksize);
                x1 = wire_sink_gate->_sdlgate.x + wire_sink_gate->_sdlgate.w;
                y1 = wire_sink_gate->_sdlgate.y + sink_interval + sink_interval * sim->_components._wires[i]->_sinkport;
            }
            
            int x2 = wire_drain_gate->_sdlgate.x;
            
            float drain_interval = (float)wire_drain_gate->_sdlgate.w / (float)(wire_drain_gate->_sinksize);
            
            int y2 = wire_drain_gate->_sdlgate.y + drain_interval + drain_interval * sim->_components._wires[i]->_drainport;
            
            SDL_RenderDrawLine(sim->_renderer, x1, y1, x2, y2);
        }
    }
}

void renderMenu(struct CSim* sim)
{
    for (int i = 0; i < sim->_menu->_numButtons; i++)
    {
        BUTTON_COLOR
        SDL_RenderFillRect(sim->_renderer, &sim->_menu->_buttons[i]._button);
    }
}
