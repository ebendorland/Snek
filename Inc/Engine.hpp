#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <dlfcn.h>
//#include <conio.h>
#include <curses.h>
#include <stdlib.h>
#include <term.h>
#include "Snek.hpp"
#include "libs.hpp"

#define DEFAULT_WIN_X 60
#define DEFAULT_WIN_Y 30

class Engine
{
    private:
        dynamic_libs *lib;
        void *handle;
        bool game_state;
        unsigned int Froot[2];
        unsigned int s_Froot[2];
        std::vector < Snek * > snek;
        unsigned int win_x;
        unsigned int win_y;
        bool froot;
        bool s_froot;
        char **map;
        int steps;
        //unsigned int snek_len;
        int snek_dir;

    public:
        Engine();
        Engine(unsigned int win_X, unsigned int win_Y);
        Engine(Engine const &obj);
        ~Engine();

        Engine &operator=(Engine const &obj);

        void user_input(int argc, char **argv);
        void init(int argc, char **argv);
        void game_loop();
        int check_digit(char *str);
        void init_map();
        void add_placeholders();
        void create_snek();
        void move_snek();
        void check_colision();
        void spawn_froot();
        void ClearScreen();
        //int mygetch();
        void load_lib(std::string const &lib_path);
        void close_lib();
};
