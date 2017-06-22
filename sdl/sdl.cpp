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
     TTF_Init();
     SDL_Init( SDL_INIT_EVERYTHING );
     SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
     this->window = SDL_CreateWindow( "Snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (maxX + 2) * SCALE, (maxY + 2) * SCALE, SDL_WINDOW_SHOWN );
     this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_ACCELERATED );
     SDL_RenderSetLogicalSize( this->renderer, (this->max_x + 2) * SCALE, (this->max_y + 2) * SCALE );
     //SDL_SetRenderDrawColor( this->renderer, 0, 0, 0, 255 );

     this->score = TTF_OpenFont("LemonMilk.otf", 29);
     this->textSurface = TTF_RenderText_Solid(this->score, "TESTING YOU CUNT !!!", this->col);
     this->text = SDL_CreateTextureFromSurface(this->renderer, this->textSurface);
}

void sdl::render(char **map)
{
	SDL_SetRenderDrawColor(this->renderer, 23, 23, 23, 255);
	SDL_RenderClear( this->renderer );
    SDL_Rect rectangle;
    SDL_Rect sco;

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
                    SDL_SetRenderDrawColor(this->renderer, 23, 23, 23, 255);
                    break;
			}


            rectangle.x = tmp_x * SCALE;
            rectangle.y = tmp_y * (SCALE - 3);
            rectangle.w = SCALE;
            rectangle.h = SCALE;

            SDL_RenderFillRect(this->renderer, &rectangle);
		}
	}


    sco.x = ((this->max_x / 2) - 6) * SCALE;
    sco.y = (this->max_y - 1) * SCALE;
    sco.w = SCALE;
    sco.h = SCALE;

    SDL_QueryTexture(this->text, NULL, NULL, &sco.w, &sco.h);

    SDL_RenderCopy(this->renderer, this->text, NULL, &sco);

	SDL_RenderPresent( this->renderer );
}

int sdl::input(int &dir, int &lib)
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
                case SDLK_1:
                    if (lib != 5)
                        return (5);
                    break ;
                case SDLK_2:
                    if (lib != 6)
                        return (6);
                    break ;
                case SDLK_3:
                    if (lib != 7)
                        return (7);
                    break ;
                case SDLK_ESCAPE:
                    return (8);
                case SDLK_SPACE:
                    return (9);
            }
        }
    }
    return(dir);
}
