#pragma once

#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <SDL_mixer.h>
#include <iostream>
#include "../Inc/libs.hpp"

#define SCALE 20.0f

class sdl : public dynamic_libs
{
    private:
        int max_x;
        int max_y;

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
    	//TTF_Font *font;

    public:
        ~sdl();
        void init(unsigned int &maxX, unsigned int &maxY);
        void render(char **map);
        int input(int &dir);
        int change_lib();
};
