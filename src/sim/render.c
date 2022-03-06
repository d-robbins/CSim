#include "render.h"

#include "csim.h"

void renderGates(struct CSim* sim)
{
    int i;
    for (i = 0; i < MAX_GATES; i++)
    {
        gate_t* gate = sim->_components._gates[i];
        if (gate != NULL)
        {
            SDL_Texture * gateTex = NULL;
            switch(gate->_type)
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
                SDL_RenderCopy(sim->_renderer, gateTex, NULL, &gate->_sdlgate);
             }
             else
             {             
                GATE_COLOR
                printf("could not load gate texture for gate type: %d\n", sim->_components._gates[i]->_type);
                SDL_RenderFillRect(sim->_renderer, &sim->_components._gates[i]->_sdlgate);
             }


            if (gate->_ports != NULL)
            {
                for (int j = 0; j < gate->_portsize; j++)
                {
                    WIRE_COLOR
                    SDL_RenderFillRect(sim->_renderer, &gate->_ports[j]._portRect);
                }
            } 
        }
    }
}

void renderWires(struct CSim* sim)
{
    int i;
    for (i = 0; i < MAX_WIRES; i++)
    {
        wire_t* wire = sim->_components._wires[i];
        if (wire != NULL)
        {
            WIRE_COLOR
            SDL_RenderDrawLine(sim->_renderer, wire->_sinkport->_portRect.x, wire->_sinkport->_portRect.y
            , wire->_drainport->_portRect.x, wire->_drainport->_portRect.y);
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
