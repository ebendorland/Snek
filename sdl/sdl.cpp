#include "sdl.hpp"

extern "C" dynamic_libs *create()
{
    return (new sdl);
}

extern "C" void destroy(dynamic_libs *obj)
{
    SDL_Quit();
    delete obj;
}

void sdl::init(unsigned int &maxX,unsigned int &maxY)
{
     this->max_x = maxX;
     this->max_y = maxY;
     SDL_Init( SDL_INIT_EVERYTHING );
     SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
     this->window = SDL_CreateWindow( "Snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, maxX, maxY, SDL_WINDOW_SHOWN );
     this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_ACCELERATED );
     SDL_SetRenderDrawColor( this->renderer, 0, 0, 0, 255 );
}

int sdl::change_lib()
{
    return (0);
}

void sdl::render(char **map)
{

}

int sdl::input(int &dir)
{
    switch(SDL_PollEvent( &this->event ))
    {
        case SDLK_UP:
            if (dir != 3)
                return (1);
            break ;
        case SDLK_RIGHT:
            if (dir != 4)
                return (2);
            break ;
        case SDLK_DOWN:
            if (dir != 1)
                return (3);
            break ;
        case SDLK_LEFT:
            if (dir != 2)
                return (4);
            break ;
    }

    return(dir);
}
