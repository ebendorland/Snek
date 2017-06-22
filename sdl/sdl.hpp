#pragma once

#include <SDL.h>
//#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include <SDL_mixer.h>
#include <iostream>
#include <sstream>
#include "../Inc/libs.hpp"

#define SCALE 20.0f

class sdl : public dynamic_libs
{
    private:
        int max_x;
        int max_y;

        //window
        SDL_Window *window;
        SDL_Renderer *renderer;

        //event (key input)
        SDL_Event event;

        //display score (create a texture using ttf)
        TTF_Font *score;
        SDL_Surface *textSurface;
        SDL_Colour col = { 23, 45, 34, 255};
        SDL_Texture *text;

    public:
        ~sdl();
        void init(unsigned int &maxX, unsigned int &maxY);
        void render(char **map, unsigned int &score);
        int input(int &dir, int &lib);
        void create_score_texture(unsigned int &score);
};
