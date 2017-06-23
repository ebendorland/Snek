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
        ncurses();
        ncurses(unsigned int tmp_x, unsigned int tmp_y);
        ncurses(ncurses const &obj);
        ~ncurses();

        ncurses &operator=(ncurses const &obj);

        bool init(unsigned int &maxX, unsigned int &maxY);
        void render(char **map, unsigned int &score, bool &pause);
        int input(int &dir, int &lib);

        void SetX(int tmp);
        void SetY(int tmp);

        int GetY() const;
        int GetX() const;
};
