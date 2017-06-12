#pragma once

#include <iostream>
#include <vector>
#include "Snek.hpp"

class Engine
{
    private:
        bool game_state;
        unsigned int Froot[2];
        unsigned int s_Froot[2];
        vector <Snek> *snek;
        unsigned int win_x;
        unsigned int win_y;
        bool froot;
        bool s_froot;
        int **map;

    public:
        Engine();
        Engine(unsigned int win_X, unsigned int win_Y);
        Engine(Engine const &obj);
        ~Engine();

        Engine &operator=(Engine const &obj);

        void user_input(argc, argv);
        void init(int argc, char **argc);
        void game_loop();
        void render();
};
