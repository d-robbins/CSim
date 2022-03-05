SRC := src/main.c src/sim/csim.c src/component/gates.c src/menu/gate_menu.c src/component/wire.c src/sim/render.c src/sim/util.c
INCLUDE := -D_THREAD_SAFE -I/opt/homebrew/include/SDL2
LIBS := -L/opt/homebrew/lib
FLAGS := -lSDL2 -lSDL2_image
EXC_NAME = csim

all:
	gcc $(SRC) $(INCLUDE) $(LIBS) $(FLAGS) -o $(EXC_NAME)
	
clean:
	rm $(EXC_NAME)