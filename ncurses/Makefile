CLANG =	clang++

NAME = ncurses.so

CFLAGS = -Wall -Werror -Wextra

NCURSES = -lncurses

HEADER = ncurses.hpp

SRC = ../Src/libs.cpp ncurses.cpp

OBJ =	$(SRC:.cpp=.cpp.o)

%.cpp.o: %.cpp
	$(CLANG) -c $(CFLAGS) -fpic $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CLANG) $(CFLAGS) $(NCURSES) -shared -Qunused-arguments -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
