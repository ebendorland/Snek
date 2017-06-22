CLANG =	clang++

NAME = sdl.so

CFLAGS = -Wall -Wextra -Werror

SFML_lIBS = -lsfml-graphics -lsfml-window -lsfml-system

SFML_CFLAGS =

HEADER = sfml.hpp

SRC_PATH = ../Src/

SRC = $(SRC_PATH)libs.cpp sdl.cpp

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CLANG) -c $(CFLAGS) $(SFML_CFLAGS)  -fpic $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CLANG) $(CFLAGS) $(SFML_lIBS)  -shared -Qunused-arguments -o $(NAME) $(OBJ)

sdl2:
	brew install sfml

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
