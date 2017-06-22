CLANG =	clang++

NAME = ncurses.so

CFLAGS = -Wall -Werror -Wextra

NCURSES = -lncurses

HEADER = ncurses.hpp

SRC_PATH = ../Src/

SRC = $(SRC_PATH)libs.cpp ncurses.cpp

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CLANG) -c $(CFLAGS) -fpic $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CLANG) $(CFLAGS) $(NCURSES) -shared -Qunused-arguments -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
