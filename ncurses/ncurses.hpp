#pragma once

#include <ncurses.h>
#include <iostream>
#include "../Inc/libs.hpp"

class ncurses : public dynamic_libs
{
    private:
        int max_x;
        int max_y;
        int stdscr_x;
        int stdscr_y;

    public:
        void init(unsigned int &maxX, unsigned int &maxY);
        void render(char **map, unsigned int &score);
        int input(int &dir, int &lib);
};
