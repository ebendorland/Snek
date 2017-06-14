#include <iostream>
#include "../Inc/Engine.hpp"

int main(int argc, char **argv)
{
    Engine  Snek;

    Snek.init(argc, argv);
    Snek.game_loop();

    return (0);
}
