
void SFML::init(unsigned int &maxX, unsigned int &maxY)
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

int SFML::checkKey(int &dir)
{
    if (dir != 3 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
        return(1);
    else if (dir != 4 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
        return(2);
    else if (dir != 1 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
        return(3);
    else if (dir != 2 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
        return(4);
    else if (lib != 5 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)))
        return(5);
    else if (lib != 6 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)))
        return(6);
    else if (lib != 7 && (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)))
        return(7);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return(8);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return(9);
}
