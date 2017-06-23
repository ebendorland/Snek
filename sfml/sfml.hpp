#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
//#include <SFML/Keyboard.hpp>
#include <vector>

#include "../Inc/libs.hpp"

class SFML : public dynamic_libs
{
    private:
        unsigned int max_x;
        unsigned int max_y;

        sf::RenderWindow *rwindow;

    public:
        SFML();
        SFML(unsigned int tmp_x, unsigned int tmp_y);
        //SFML(SFML const &obj);
        ~SFML();

        int input(int &dir, int &lib);
        bool init(unsigned int &maxX, unsigned int &maxY);
        void render(char **map, unsigned int &score, bool &pause);

        void SetX(int tmp);
        void SetY(int tmp);

        int GetY() const;
        int GetX() const;
};
