OBJS = main.cpp
CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = ../shared/LTexture.cpp Ball.cpp ../shared/Renderer.cpp udp_socket.cpp udp_client.cpp Game.cpp Paddle.cpp controller.cpp HUD.cpp -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf
OBJ_NAME = multiplayerPong 
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)	
