#pragma once

#include <iostream>
#include <vector>

class Snek
{
    private:
        unsigned int snek_x;
        unsigned int snek_y;

    public:
        Snek();
        Snek(unsigned int x, unsigned int y);
        Snek(Snek const &obj);
        ~Snek();

        Snek &operator=(Snek const &obj);

        void SetX( unsigned int x);
        void SetY( unsigned int y);

        unsigned int GetX() const;
        unsigned int GetY() const;
};
