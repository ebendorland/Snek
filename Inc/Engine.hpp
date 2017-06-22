#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <dlfcn.h>
#include <curses.h>
#include <stdlib.h>
#include <term.h>
#include "Snek.hpp"
#include "libs.hpp"
#include "food.hpp"

#define DEFAULT_WIN_X 60
#define DEFAULT_WIN_Y 30
#define PATH_SDL "./sdl/sdl.so"
#define PATH_NCURSES "./ncurses/ncurses.so"

class Engine
{
    private:
        dynamic_libs *lib;
        void *handle;
        bool game_state;
        food *froot;
        food *s_froot;
        std::vector < Snek * > snek;
        unsigned int win_x;
        unsigned int win_y;
        char **map;
        int last_pressed;
        int steps;
        int snek_dir;
        int current_lib;
        bool pause;
        unsigned int score;

    public:
        Engine();
        Engine(unsigned int win_X, unsigned int win_Y);
        //Engine(Engine const &obj);
        ~Engine();

        //Engine &operator=(Engine const &obj);

        void user_input(int argc, char **argv);
        void init(int argc, char **argv);
        void game_loop();
        int check_digit(char *str);
        void init_map();
        void add_placeholders();
        void create_snek();
        void move_snek();
        void change_lib(int &ret_tmp);
        void check_colision();
        void spawn_froot();
        void spawn_special_froot();
        void load_lib(std::string const &lib_path);
        void close_lib();
};
