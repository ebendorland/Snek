#include <iostream>
#include "../Inc/Engine.hpp"

int main(int argc, char **argv)
{
    Engine  Snek;

    try
    {
        Snek.init(argc, argv);
        Snek.game_loop();
    }
    catch (char const *err)
    {
        std::cout << err <<std::endl;
    }

    return (0);
}
