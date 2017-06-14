#pragma once

#include <iostream>
#include <vector>

class Snek
{
    private:
        unsigned int snek_x;
        unsigned int snek_y;
        bool is_hed;

    public:
        Snek();
        Snek(unsigned int x, unsigned int y, bool tmp);
        Snek(Snek const &obj);
        ~Snek();

        Snek &operator=(Snek const &obj);

        void SetX( unsigned int x);
        void SetY( unsigned int y);
        void SetIsHed( bool tmp );

        unsigned int GetX() const;
        unsigned int GetY() const;
        bool GetIsHed() const;
};
