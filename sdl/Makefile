COMPILER = clang++ -o
NAME = sdl.so
SRCS = sdl.cpp ../Src/libs.cpp
LIBS = $(shell sdl2-config --cflags --libs)
FLAGS = -Wall -Werror -Wextra

$(NAME):
	$(COMPILER) $(NAME) $(SRCS) $(LIBS) $(FLAGS) -shared -fpic

clean:
	rm -f $(NAME)
re: clean $(NAME)
