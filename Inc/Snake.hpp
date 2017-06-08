#ifndef SNAKE_CLASS
#define SNAKE_CLASS

#include <iostream>

class Snake
{
public:
		Snake( void );
        Snake( Snake &src);
        ~Snake( void );
private:
        int							speed;
        unsigned int				length;
        unsigned int				headpos[2];
        unsigned int				tailpos[2];

};

#endif
