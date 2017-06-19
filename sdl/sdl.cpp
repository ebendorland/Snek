#include "sdl.hpp"

extern "C" dynamic_libs *create()
{
    return (new sdl);
}

extern "C" void destroy(dynamic_libs *obj)
{
    delete obj;
}

sdl::~sdl()
{
    SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void sdl::init(unsigned int &maxX,unsigned int &maxY)
{
     this->max_x = maxX;
     this->max_y = maxY;
     SDL_Init( SDL_INIT_EVERYTHING );
     SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
     this->window = SDL_CreateWindow( "Snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (maxX + 2) * 20.0f, (maxY + 2) * 20.0f, SDL_WINDOW_SHOWN );
     this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_ACCELERATED );
     SDL_RenderSetLogicalSize( this->renderer, (this->max_x + 2) * 20.0f, (this->max_y + 2) * 20.0f );
     SDL_SetRenderDrawColor( this->renderer, 0, 0, 0, 255 );
}

int sdl::change_lib()
{
    return (0);
}

void sdl::render(char **map)
{
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	SDL_RenderClear( this->renderer );
	for (int tmp_y = 0; tmp_y < this->max_y + 2; tmp_y++)
    {
		for (int tmp_x = 0; tmp_x < this->max_x + 2; tmp_x++)
        {
			switch (map[tmp_y][tmp_x])
            {
                case '/':
                    SDL_SetRenderDrawColor(this->renderer, 211, 25, 125, 255);
                    break;
                case '*':
                    SDL_SetRenderDrawColor(this->renderer, 123, 123, 234, 255);
                    break;
                case '@':
                    SDL_SetRenderDrawColor(this->renderer, 0, 255, 76, 255);
                    break;
                case 'p':
                    SDL_SetRenderDrawColor(this->renderer, 20, 98, 4, 255);
                    break;
                case 'j':
                    SDL_SetRenderDrawColor(this->renderer, 45, 32, 34, 255);
                    break;
                default:
                    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
                    break;
			}
            SDL_Rect rectangle;

            rectangle.x = tmp_x * 5.0f;
            rectangle.y = tmp_y * 5.0f;
            rectangle.w = 5.0f;
            rectangle.h = 5.0f;
            SDL_RenderFillRect(this->renderer, &rectangle);
		}
	}
	SDL_RenderPresent( this->renderer );
}

int sdl::input(int &dir)
{
    while(SDL_PollEvent( &this->event ))
    {
        if (this->event.type == SDL_KEYDOWN)
        {
            switch((this->event).key.keysym.sym)
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
        }
    }
    return(dir);
}
