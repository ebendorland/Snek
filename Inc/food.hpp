#pragma once

#include <iostream>

class food
{
    private:
        unsigned int x;
        unsigned int y;
        bool is_food;

    public:
        food();
        food(unsigned int tmp_x, unsigned int tmp_y, bool tmp);
        ~food();

        void SetX( unsigned int tmp_x);
        void SetY( unsigned int tmp_y);
        void SetIsFood( bool tmp);

        int GetX() const;
        int GetY() const;
        bool GetIsFood() const;

        void make_food(unsigned int &win_x, unsigned int &win_y);
        bool comp_x(unsigned int const &tmp_x);
        bool comp_y(unsigned int const &tmp_y);
};
