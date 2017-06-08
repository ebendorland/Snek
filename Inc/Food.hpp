#ifndef FOOD_CLASS
#define FOOD_CLASS

#include <iostream>

class Food
{
public:
        Food( void );
        Food( Food &src);
        ~Food( void );
private:
        int             pos[2];
        unsigned int    points;
};

#endif
