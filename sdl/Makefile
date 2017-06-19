CLANG =	clang++

NAME = sdl.so

CFLAGS = -Wall -Werror -Wextra

SDL = -w -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

HEADER = ncurses.hpp

SRC = ../Src/libs.cpp sdl.cpp

OBJ =	$(SRC:.cpp=.cpp.o)

%.cpp.o: %.cpp
	$(CLANG) -c $(CFLAGS) -fpic $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CLANG) $(CFLAGS) $(SDL) -shared -Qunused-arguments -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
