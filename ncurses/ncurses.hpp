#pragma once

#include <ncurses.h>
#include <iostream>
#include "../Inc/libs.hpp"

class ncurses : public dynamic_libs
{
    private:
        int max_x;
        int max_y;
        //window *game_area;

    public:
        void init(unsigned int &maxX, unsigned int &maxY);
        void render(char **map);
        int input(int &dir);
        int change_lib();
};
