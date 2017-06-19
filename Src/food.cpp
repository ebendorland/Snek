#include "../Inc/food.hpp"

food::food() : x(0), y(0), is_food(false)
{

}

food::food(unsigned int tmp_x, unsigned int tmp_y, bool tmp)
{
    this->x = tmp_x;
    this->y = tmp_y;
    this->is_food = tmp;
}

food::~food()
{
    std::cout << "Food Expired" << std::endl;
}

void food::SetX( unsigned int tmp_x)
{
    this->x = tmp_x;
}

void food::SetY( unsigned int tmp_y)
{
    this->y = tmp_y;
}

void food::SetIsFood( bool tmp)
{
    this->is_food = tmp;
}

int food::GetX() const
{
    return (this->x);
}

int food::GetY() const
{
    return (this->y);
}

bool food::GetIsFood() const
{
    return (this->is_food);
}

void food::make_food(unsigned int &win_x, unsigned int &win_y)
{
    this->x = rand() % (int)win_x + 1;
    this->y = rand() % (int)win_y + 1;
}

bool food::comp_x(unsigned int const &tmp_x)
{
    return this->x == tmp_x ? true : false ;
}

bool food::comp_y(unsigned int const &tmp_y)
{
    return this->y == tmp_y ? true : false ;
}
