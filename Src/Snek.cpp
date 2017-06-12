#include "../Inc/Snek.hpp"

Snek::Snek()
{
    this->snek_x = 0;
    this->snek_y = 0;
}

Snek::Snek(unsigned int x, unsigned int y)
{
    this->snek_x = x;
    this->snke_y = y;
}

Snek::Snek(Snek const &obj)
{
    *this = obj;
}

Snek::~Snek()
{
    std::cout << "Snek Part Destroyed" << std::endl;
}

Snek &Snek::operator=(Snek const &obj)
{
    this->snek_x = obj.GetX();
    this->snek_y = obj.GetY();

    return (*this);
}

void Snek::SetX( unsigned int x)
{
    this->snek_x = x;
}

void Snek::SetY( unsigned int y)
{
    this->snek_y = y;
}

unsigned int Snek::GetX()
{
    return (this->snek_x);
}

unsigned int Snek::GetY()
{
    return (this->snek_y);
}
