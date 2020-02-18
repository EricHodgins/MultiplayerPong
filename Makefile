OBJS = main.cpp
CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = Renderer.cpp Game.cpp -lSDL2 -lSDL2_image -lSDL2_ttf
OBJ_NAME = multiplayerPong 
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)	
