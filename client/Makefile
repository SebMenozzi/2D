.PHONY : clean, fclean, re
.SUFFIXES :

NAME = client
SRC =	src/main.cpp src/game.cpp src/scene.cpp src/player.cpp src/map.cpp src/iniFile.cpp src/clock.cpp src/udpClient.cpp

CC = g++

OBJ = $(SRC:.cpp=.o)

OS = $(shell uname)
ifeq ($(OS), Darwin)
	LINKER_FLAGS = -framework OpenGL -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_TTF

  IFLAGS = -I/Library/Frameworks/SDL2.framework/Headers/ -I/Library/Frameworks/SDL2_image.framework/Headers/ -I/Library/Frameworks/SDL2_TTF.framework/Headers/
else
  LINKER_FLAGS = -lGL -lGLU -lSDL2 -lSDL2_image -lSDL2_ttf
endif

COMPILER_FLAGS = -w

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

%.o : %.cpp
	$(CC) -c $^ $(COMPILER_FLAGS) $(IFLAGS) -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f  $(NAME)

re : fclean all
