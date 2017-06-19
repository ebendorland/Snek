#pragma once

#include <iostream>
#include <vector>

class Snek
{
    private:
        unsigned int snek_x;
        unsigned int snek_y;
        bool is_hed;
        unsigned int part_dir;

    public:
        Snek();
        Snek(unsigned int x, unsigned int y, bool tmp, unsigned int dir);
        Snek(Snek const &obj);
        ~Snek();

        Snek &operator=(Snek const &obj);

        void SetX( unsigned int x);
        void SetY( unsigned int y);
        void SetIsHed( bool tmp );
        void SetPartDir( unsigned int dir);

        unsigned int GetX() const;
        unsigned int GetY() const;
        bool GetIsHed() const;
        unsigned int GetPartDir() const;

        bool comp_xy(unsigned int const &tmp_x, unsigned int const &tmp_y);
};
