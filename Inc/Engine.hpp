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

#define PATH_SDL "./sdl/sdl.so"
#define PATH_NCURSES "./ncurses/ncurses.so"
#define PATH_SFML "./sdl2/sdl2.so"

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
        int steps;
        int snek_dir;
        int current_lib;
        bool pause;
        unsigned int score;
        bool lib_closed;

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
        void change_lib(int &ret_tmp);
        void check_colision();
        void spawn_froot();
        void spawn_special_froot();
        void load_lib(std::string const &lib_path);
        void close_lib();

        void SetSteps(int tmp);
        void SetSnekDir(int tmp);
        void SetCurrentLib(int tmp);
        void SetPause(bool tmp);
        void SetScore(unsigned int tmp);
        void SetWinX(unsigned int tmp);
        void SetWinY(unsigned int tmp);

        int GetSteps() const;
        int GetSnekDir() const;
        int GetCurrentLib() const;
        bool GetPause() const;
        unsigned int GetScore() const;
        unsigned int GetWinX() const;
        unsigned int GetWinY() const;
};
