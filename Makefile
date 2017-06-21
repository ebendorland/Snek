NAME =Nibbler

CLANG =clang++

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

PATH_SRC = ./Src/

PATH_HD = -I Inc/

SRC = $(PATH_SRC)main.cpp $(PATH_SRC)Engine.cpp $(PATH_SRC)Snek.cpp $(PATH_SRC)food.cpp

OBJ = main.o Engine.o Snek.o food.o

$(NAME):
	@echo "Compiling binaries..."
	make -C ./ncurses/
	make -C ./sdl/
	@$(CLANG) -std=c++11 $(CFLAGS) $(PATH_HD) -c $(SRC)
	@$(CLANG) -std=c++11 -o $(NAME) $(OBJ) -ldl -lncurses
	@echo "Compilation was successful!"

all: $(NAME)

clean:
	@rm -rf $(OBJ)
	@make -C ./ncurses/ clean
	@make -C ./sdl/ clean

fclean: clean
	@rm -rf $(NAME)
	@make -C ./ncurses/ fclean
	@make -C ./sdl/ fclean

re: fclean all
