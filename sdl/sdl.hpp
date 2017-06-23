#pragma once

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include "../Inc/libs.hpp"

#define SCALE 20.0f

class sdl : public dynamic_libs
{
    private:
        int max_x;
        int max_y;
        int rand;

        //window
        SDL_Window *window;
        SDL_Renderer *renderer;

        //event (key input)
        SDL_Event event;

        //display score (create a texture using ttf)
        TTF_Font *score;
        SDL_Surface *textSurface;
        SDL_Colour col;
        SDL_Texture *text;

    public:
        sdl();
        sdl(unsigned int tmp_x, unsigned int tmp_y);
        sdl(sdl const &obj);
        ~sdl();

        sdl &operator=(sdl const &obj);

        bool init(unsigned int &maxX, unsigned int &maxY);
        void render(char **map, unsigned int &score, bool &pause);
        int input(int &dir, int &lib);
        int create_score_texture(unsigned int &score);

        void SetX(int tmp);
        void SetY(int tmp);

        int GetY() const;
        int GetX() const;
};
