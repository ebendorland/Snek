#include "sdl2.hpp"

extern "C" dynamic_libs *create()
{
    return (new sdl);
}

extern "C" void destroy(dynamic_libs *obj)
{
    delete obj;
}

sdl::sdl()
{
    this->max_x = 0;
    this->max_y = 0;
    this->rand = 0;

    //window
    this->window = NULL;
    this->renderer = NULL;

    //display score (create a texture using ttf)
    this->score = NULL;
    this->textSurface = NULL;

    this->col.r = 23;
    this->col.g = 45;
    this->col.b = 34;
    this->col.a = 255;

    this->text = NULL;
}

sdl::sdl(unsigned int tmp_x, unsigned int tmp_y)
{
    this->max_x = tmp_x;
    this->max_y = tmp_y;
}

sdl::sdl(sdl const &obj)
{
    *this = obj;
}

sdl::~sdl()
{
    SDL_DestroyRenderer(this->renderer);
    this->renderer = NULL;

	SDL_DestroyWindow(this->window);
    this->window = NULL;

    SDL_DestroyTexture(this->text);
    this->text = NULL;

	SDL_Quit();
}

sdl &sdl::operator=(sdl const &obj)
{
    this->max_x = obj.GetX();
    this->max_y = obj.GetY();

    return (*this);
}

bool sdl::init(unsigned int &maxX,unsigned int &maxY)
{
     this->max_x = maxX;
     this->max_y = maxY;

     if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
     {
        std::cout << "SDL Error: \"SDL_Init() failed.\"" << std::endl;
        return (true);
     }

     if (TTF_Init() < 0)
     {
         std::cout << "SDL Error: \"TTF_Init() failed.\"" << std::endl;
         return (true);
     }

     SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

     this->window = SDL_CreateWindow( "Snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (maxX + 2) * SCALE, (maxY + 2) * SCALE, SDL_WINDOW_SHOWN );
     if (this->window == NULL)
     {
         std::cout << "SDL Error: \"SDL_CreateWindow() failed.\"" << std::endl;
         return (true);
     }

     this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_ACCELERATED );
     if (this->renderer == NULL)
     {
         std::cout << "SDL Error: \"SDL_CreateRenderer() failed.\"" << std::endl;
         return (true);
     }

     SDL_RenderSetLogicalSize( this->renderer, (this->max_x + 2) * SCALE, (this->max_y + 2) * SCALE );
     SDL_SetRenderDrawColor( this->renderer, 0, 0, 0, 255 );

     this->score = TTF_OpenFont("LemonMilk.otf", 29);
     if (this->score == NULL)
     {
         std::cout << "SDL Error: \"TTF_OpenFont() failed.\"" << std::endl;
         return (true);
     }

     return (false);
}

int sdl::create_score_texture(unsigned int &score)
{
    std::string tmp = "Score: ";
    std::ostringstream stm ;
    stm << score ;

    tmp += stm.str();
    this->textSurface = TTF_RenderText_Solid(this->score, tmp.c_str(), this->col);
    this->text = SDL_CreateTextureFromSurface(this->renderer, this->textSurface);

    SDL_FreeSurface(this->textSurface);
    this->textSurface = NULL;

    return ((tmp.length() / 2) - 1);
}

void sdl::render(char **map, unsigned int &score, bool &pause)
{
    pause = false;
    this->rand = create_score_texture(score);
	SDL_SetRenderDrawColor(this->renderer, 100, 102, 200, 255);
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
                    SDL_SetRenderDrawColor(this->renderer, 138, 3, 98, 255);
                    break;
                case '*':
                    SDL_SetRenderDrawColor(this->renderer, 3, 30, 138, 255);
                    break;
                case '@':
                    SDL_SetRenderDrawColor(this->renderer, 129, 42, 23, 255);
                    break;
                case 'o':
                    SDL_SetRenderDrawColor(this->renderer, 235, 98, 10, 255);
                    break;
                case '!':
                    SDL_SetRenderDrawColor(this->renderer, 6, 99, 34, 255);
                    break;
                default:
                    SDL_SetRenderDrawColor(this->renderer, 100, 102, 200, 255);
                    break;
			}

            rectangle.x = tmp_x * SCALE;
            rectangle.y = tmp_y * (SCALE - 3);
            rectangle.w = SCALE;
            rectangle.h = SCALE;

            SDL_RenderFillRect(this->renderer, &rectangle);
		}
	}

    sco.x = ((this->max_x / 2) - this->rand) * SCALE;
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

void sdl::SetX(int tmp) { this->max_x = tmp; }
void sdl::SetY(int tmp) { this->max_y = tmp; }

int sdl::GetY() const { return (this->max_x); }
int sdl::GetX() const { return (this->max_y); }
