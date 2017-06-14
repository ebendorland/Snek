#include "../Inc/Snek.hpp"

Snek::Snek()
{
    this->snek_x = 0;
    this->snek_y = 0;
    this->is_hed = false;
}

Snek::Snek(unsigned int x, unsigned int y, bool tmp)
{
    this->snek_x = x;
    this->snek_y = y;
    this->is_hed = tmp;
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

void Snek::SetIsHed( bool tmp )
{
    this->is_hed = tmp;
}

void Snek::SetX( unsigned int x)
{
    this->snek_x = x;
}

void Snek::SetY( unsigned int y)
{
    this->snek_y = y;
}

bool Snek::GetIsHed() const
{
    return (this->is_hed);
}

unsigned int Snek::GetX() const
{
    return (this->snek_x);
}

unsigned int Snek::GetY() const
{
    return (this->snek_y);
}
