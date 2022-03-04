#ifndef RENDER_SIM_H
#define RENDER_SIM_H

struct CSim;

void render_wires(struct CSim* sim);
void render_gates(struct CSim* sim);
void render_menu(struct CSim* sim);

#endif // RENDER_SIM_H