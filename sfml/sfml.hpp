#pragma once

#include <../Inc.libs.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Keyboard.hpp>

class SFML : public dynamic_libs
{
private:
    unsigned int     max_x;
    unsigned int     max_y;

    sf::RenderWindow    *rwindow;

public:
    ~sfml();
    int input(int &dir, int &lib);
    void init(unsigned int &maxX, unsigned int &maxY);
    void render(char **map, unsigned int &score);
}
