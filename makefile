OBJS := src/main.o src/core/window.o src/core/core.o src/core/gates/gate.o src/core/gates/and_gate.o src/core/util/util.o src/core/util/pin_layout.o src/core/environment.o src/core/gates/or_gate.o src/core/ui/ui.o src/core/ui/and_button.o src/core/ui/ipin_button.o src/core/ui/or_button.o
INCLUDE := -D_THREAD_SAFE -I/opt/homebrew/include/SDL2
LIBS := -L/opt/homebrew/lib
LIB_FLAGS := -lSDL2 -lSDL2_image
CFLAGS := -Wall
EXC_NAME = csim

all: $(OBJS)
	clang $(CFLAGS) $(shell pwd)/objs/*.o -o $(EXC_NAME) $(LIBS) $(LIB_FLAGS)
	
run: all
	./$(EXC_NAME)
	
%.o: %.c
	clang $(CFLAGS) -c $< -o $@ $(INCLUDE)
	mv $@ $(shell pwd)/objs/

clean:
	rm objs/*.o
	rm $(EXC_NAME)