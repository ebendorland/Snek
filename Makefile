CLANG =	clang++

NAME = Nibbler

CFLAGS = -Wall -Werror -Wextra

C++_TYPE = -std=c++11

HEADER = ./Inc/

SRC_PATH = ./Src/

SRC = $(SRC_PATH)main.cpp $(SRC_PATH)Engine.cpp $(SRC_PATH)food.cpp $(SRC_PATH)Snek.cpp

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CLANG) -c $(CFLAGS) $(C++_TYPE) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C ./ncurses/
	make -C ./sdl/
	$(CLANG) $(CFLAGS) $(C++_TYPE) -Qunused-arguments -o $(NAME) $(OBJ) -ldl

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

lib:
	make -C ./ncurses/
	make -C ./sdl/

lib_clean:
	make -C ./ncurses/ fclean
	make -C ./sdl/ fclean

c_everything: fclean lib_clean
