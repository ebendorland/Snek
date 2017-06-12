#include "../Inc/Engine.hpp"

Engine::Engine();
Engine::Engine(unsigned int win_X, unsigned int win_Y);
Engine::Engine(Engine const &obj);
Engine::~Engine();

Engine &Engine::operator=(Engine const &obj);

void Engine::user_input(argc, argv);

void Engine::init(int argc, char **argc)
{
    this->game_state = false;
    this->Froot[0] = 0;
    this->Froot[1] = 0;
    this->s_Froot[0] = 0;
    this->s_Froot[1] = 0;
    this->win_x = 0;
    this->win_y = 0;
    this->froot = false;
    this->s_froot = false;
    user_input(argc, argv);
}

void Engine::game_loop()
{
    while(!this->game_state)
    {

    }
}

void Engine::render();
