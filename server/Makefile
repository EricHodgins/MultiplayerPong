OBJS = main.cpp 
CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = ../shared/LTexture.cpp Ball.cpp ../shared/Renderer.cpp Game.cpp udp_server.cpp udp_socket.cpp Paddle.cpp -pthread -lSDL2 -lSDL2_image -lSDL2_ttf
OBJ_NAME = multiplayerPong 
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)	
