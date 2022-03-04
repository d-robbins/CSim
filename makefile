SRC := src/main.c src/csim.c src/gates.c src/gate_menu.c
INCLUDE := -D_THREAD_SAFE -I/opt/homebrew/include/SDL2
LIBS := -L/opt/homebrew/lib
FLAGS := -lSDL2_image -lSDL2
EXC_NAME = csim

all:
	gcc $(SRC) $(INCLUDE) $(LIBS) $(FLAGS) -o $(EXC_NAME)
	
clean:
	rm $(EXC_NAME)