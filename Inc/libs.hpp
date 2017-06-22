#pragma once

class dynamic_libs
{
    public:
        dynamic_libs() {};
        virtual ~dynamic_libs() {};

        virtual void init(unsigned int &maxX,unsigned int &maxY) = 0;
        virtual void render(char **map, unsigned int &score) = 0;
        virtual int input(int &dir, int &lib) = 0;
};

typedef dynamic_libs* create_t();
typedef void destroy_t(dynamic_libs*);
