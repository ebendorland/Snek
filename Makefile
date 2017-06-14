NAME=Nibbler

CLANG=clang++

CFLAGS=

RM=rm -f

PATH_SRC= ./Src/

PATH_HD= -I Inc/

SRC = $(PATH_SRC)main.cpp $(PATH_SRC)Engine.cpp $(PATH_SRC)Snek.cpp

OBJ = main.o Engine.o Snek.o

$(NAME):
	@echo "Compiling binaries..."
	@$(CLANG) -std=c++11 $(CFLAGS) $(PATH_HD) -c $(SRC)
	@$(CLANG) -std=c++11 -o $(NAME) $(OBJ) -lncurses
	@echo "Compilation was successful!"

all: $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
