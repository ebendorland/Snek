#include "sfml.hpp"

extern "C" dynamic_libs *create()
{
    return (new SFML);
}

extern "C" void destroy(dynamic_libs *obj)
{
    delete obj;
}

SFML::SFML()
{
    this->rwindow = NULL;
    this->max_x = 0;
    this->max_y = 0;
}

SFML::SFML(unsigned int tmp_x, unsigned int tmp_y)
{
    this->max_x = tmp_x;
    this->max_y = tmp_y;
}

SFML::~SFML()
{
    std::cout << "kill";
}

bool SFML::init(unsigned int &maxX, unsigned int &maxY)
{
    rwindow = new sf::RenderWindow;

    rwindow->create(sf::VideoMode(maxX, maxY), "Snek");
    rwindow->setFramerateLimit(60);
    rwindow->setVerticalSyncEnabled(true);
    rwindow->isOpen();

    return (false);
}

int SFML::input(int &dir, int &lib)
{
    if (dir != 3 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
        return (1);
    else if (dir != 4 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
        return (2);
    else if (dir != 1 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
        return (3);
    else if (dir != 2 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
        return (4);
    else if (lib != 5 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)))
        return (5);
    else if (lib != 6 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)))
        return (6);
    else if (lib != 7 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)))
        return (7);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return (8);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return (9);

    return (dir);
}

void SFML::render(char **map, unsigned int &score, bool &pause)
{
    std::cout << score;
    pause = false;
    rwindow->clear();
    sf::RectangleShape rmap(sf::Vector2f(20, 20));
    for (unsigned int tmp_y = 0; tmp_y < this->max_y + 2; tmp_y++)
    {
	    for (unsigned int tmp_x = 0; tmp_x < this->max_x + 2; tmp_x++)
        {
			switch (map[tmp_y][tmp_x])
            {
                case '/':
                    rmap.setSize(sf::Vector2f(20, 20));
	                rmap.setFillColor(sf::Color::Magenta);
                    break;
                case '*':
                    rmap.setSize(sf::Vector2f(20, 20));
	                rmap.setFillColor(sf::Color::Cyan);
                    break;
                case '@':
                    rmap.setSize(sf::Vector2f(20, 20));
	                rmap.setFillColor(sf::Color::Yellow);
                    break;
                case 'o':
                    rmap.setSize(sf::Vector2f(20, 20));
	                rmap.setFillColor(sf::Color::Yellow);
                    break;
                case '!':
                    rmap.setSize(sf::Vector2f(20, 20));
	                rmap.setFillColor(sf::Color::Red);
                    break;
                default:
                    rmap.setSize(sf::Vector2f(20, 20));
	                rmap.setFillColor(sf::Color::Black);
                    break;
			}
            rmap.setPosition(tmp_y * 20, tmp_x * 20);
            rwindow->draw(rmap);
		}
	}
    rwindow->display();
}

void SFML::SetX(int tmp) { this->max_x = tmp; }
void SFML::SetY(int tmp) { this->max_y = tmp; }

int SFML::GetY() const { return (this->max_x); }
int SFML::GetX() const { return (this->max_y); }
