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
    for (int count = 0; count < this->snake_len; count++)
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

    while (str[count] != NULL)
    {
        if (!(isdigit(str[count])))
            return (0);
        count++;
    }
    return (1);
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
    for (int count = 0; count < 4; count++)
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
        this->snake_len += 1;
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
    this->snake_len = 0;
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

int Engine::kbhit(void)
{
  struct timeval tv;
  fd_set read_fd;

  /* Do not wait at all, not even a microsecond */
  tv.tv_sec=0;
  tv.tv_usec=0;

  /* Must be done first to initialize read_fd */
  FD_ZERO(&read_fd);

  /* Makes select() ask if input is ready:
   * 0 is the file descriptor for stdin    */
  FD_SET(0,&read_fd);

  /* The first parameter is the number of the
   * largest file descriptor to check + 1. */
  if(select(1, &read_fd,NULL, /*No writes*/NULL, /*No exceptions*/&tv) == -1)
    return 0;  /* An error occured */

  /*  read_fd now holds a bit map of files that are
   * readable. We test the entry for the standard
   * input (file 0). */

if(FD_ISSET(0,&read_fd))
    /* Character pending on stdin */
    return 1;

  /* no characters were pending */
  return 0;
}

void Engine::move_snek()
{
    int move_x = 0;
    int move_y = 0;

    char input = getch();
    /*switch (input)
    {
        case KEY_UP:

    }*/
}

void Engine::game_loop()
{
    this->game_state = true;

	srand(time(NULL));
	while (this->game_state)
    {
		move_snek();
        add_placeholders();
		//render_scene();
		usleep(10000);
	}
}

void Engine::render()
{

}
