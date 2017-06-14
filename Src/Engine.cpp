#include "../Inc/Engine.hpp"

Engine::Engine()
{

}

Engine::Engine(unsigned int win_X, unsigned int win_Y)
{

}

Engine::Engine(Engine const &obj)
{

}

Engine::~Engine()
{
    for (unsigned int count = 0; count < this->snek.size(); count++)
    {
        delete this->snek[count];
    }
}

Engine &Engine::operator=(Engine const &obj)
{
    return (*this);
}

int Engine::check_digit(char *str)
{
    int count = 0;

    while (str[count] != '\0')
    {
        if (!(isdigit(str[count])))
            return (0);
        count++;
    }
    return (1);
}

void Engine::check_colision()
{

}

void Engine::add_placeholders()
{
    for (int tmp_y = 0; tmp_y < (this->win_y + 2); tmp_y++)
	{
        for (int tmp_x = 0; tmp_x < this->win_x + 2; tmp_x++)
        {
            if (tmp_y == 0)
                this->map[tmp_y][tmp_x] = '/';
            else if (tmp_y == (this->win_y + 2) - 1)
                this->map[tmp_y][tmp_x] = '/';
        }
        this->map[tmp_y][0] = '/';
        this->map[tmp_y][(this->win_x + 2) - 1] = '/';
	}


    int tmp_x = 0;
    int tmp_y = 0;
    for (int count = 0; count < this->snek.size(); count++)
    {
        tmp_x = this->snek[count]->GetX();
        tmp_y = this->snek[count]->GetY();

        if (this->snek[count]->GetIsHed())
            this->map[tmp_y][tmp_x] = '^';
        else
            this->map[tmp_y][tmp_x] = '!';
    }
}

void Engine::user_input(int argc, char **argv)
{
    if (argc >= 3)
    {
        for (int count = 1; count < argc; count++)
        {
            if (check_digit(argv[count]))
            {
                std::cout << "VALID" << std::endl;
                if (count == 1)
                    this->win_x = atoi(argv[count]);

                if (count == 2)
                    this->win_y = atoi(argv[count]);

                std::cout << "x " << this->win_x << " y " << this->win_y << std::endl;
            }
            else
            {
                std::cerr << "Invalid Arguments" << std::endl;
            }
        }
    }
    else
    {
        std::cerr << "Invalid Arguments" << std::endl;
    }
}

void Engine::init_map()
{
    this->map = new char * [this->win_y + 2];

    if (this->map == NULL)
    {
        std::cerr << "Map Not allocated" << std::endl;
        return ;
    }

	for (int tmp_y = 0; tmp_y < (this->win_y + 2); tmp_y++)
	{
		this->map[tmp_y] = new char[this->win_x + 2];
        if (this->map[tmp_y] != NULL)
        {
            for (int tmp_x = 0; tmp_x < this->win_x + 2; tmp_x++)
            {
                this->map[tmp_y][tmp_x] = ' ';
            }
        }
        else
        {
            std::cerr << "Map Not allocated" << std::endl;
            return ;
        }
	}

    add_placeholders();

    for (int tmp_y = 0; tmp_y < (this->win_y + 2); tmp_y++)
	{
        for (int tmp_x = 0; tmp_x < this->win_x + 2; tmp_x++)
        {
            std::cout << this->map[tmp_y][tmp_x];
        }
        std::cout << std::endl;
	}
}

void Engine::create_snek()
{
    for (int count = 0; count < 4; count++)
    {
        this->snek.push_back(new Snek((this->win_x / 2), ((this->win_y / 2) + count), false));
        if (count == 0)
            this->snek[count]->SetIsHed(true);
        //this->snek_len += 1;
    }

    for (int count = 0; count < 4; count++)
    {
        std::cout << "x " << snek[count]->GetX() << " y " << snek[count]->GetY() << " head " << snek[count]->GetIsHed() << std::endl;
    }
}

void Engine::init(int argc, char **argv)
{
    std::cout << argc << " " << argv[1] << std::endl;
    this->game_state = false;
    this->Froot[0] = 0;
    //this->snek_len = 0;
    this->snek_dir = 1;
    this->Froot[1] = 0;
    this->s_Froot[0] = 0;
    this->s_Froot[1] = 0;
    this->win_x = DEFAULT_WIN_X;
    this->win_y = DEFAULT_WIN_Y;
    this->froot = false;
    this->s_froot = false;
    user_input(argc, argv);
    create_snek();
    init_map();
}

void Engine::move_snek()
{

    //char input = getch();
    /*switch (input)
    {
        case KEY_UP:

    }*/

    for (int count = 0; count < this->snek.size(); count++)
    {
        int tmp_x = this->snek[count]->GetX();
        int tmp_y = this->snek[count]->GetY();
        this->map[tmp_y][tmp_x] = ' ';

        if (1 == this->snek_dir) // UP
            this->snek[count]->SetY(tmp_y - 1);
        else if (2 == this->snek_dir) // RIGHT
            this->snek[count]->SetX(tmp_x + 1);
        else if (3 == this->snek_dir) // DOWN
            this->snek[count]->SetY(tmp_y + 1);
        else if (4 == this->snek_dir) // LEFT
            this->snek[count]->SetX(tmp_x - 1);
    }

}

void Engine::game_loop()
{
    this->game_state = true;

	srand(time(NULL));
	while (this->game_state)
    {
		move_snek();
        add_placeholders();
		render();
		usleep(10000);
	}
}

void Engine::render()
{
    for (int tmp_y = 0; tmp_y < (this->win_y + 2); tmp_y++)
	{
        for (int tmp_x = 0; tmp_x < this->win_x + 2; tmp_x++)
        {
            std::cout << this->map[tmp_y][tmp_x];
        }
        std::cout << std::endl;
	}
}
