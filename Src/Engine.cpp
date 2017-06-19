#include "../Inc/Engine.hpp"

Engine::Engine()
{

}

Engine::Engine(unsigned int win_X, unsigned int win_Y)
{
    this->win_x = win_X;
    this->win_y = win_Y;
}

/*Engine::Engine(Engine const &obj)
{

}*/

Engine::~Engine()
{
    delete this->froot;
    delete this->s_froot;
    for (unsigned int y = 0; y < this->win_y + 2; y++)
    {
        delete this->map[y];
    }

    delete[ ] this->map;

    for (unsigned int count = 0; count < this->snek.size(); count++)
    {
        delete this->snek[count];
    }
}

/*Engine &Engine::operator=(Engine const &obj)
{
    return (*this);
}*/

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
    unsigned int hed_x = this->snek[0]->GetX();
    unsigned int hed_y = this->snek[0]->GetY();

    if (this->snek[0]->comp_xy(0, 0) || this->snek[0]->comp_xy(this->win_x + 1 , this->win_y + 1))
    {
        std::cout << "Colided With a Wall" << std::endl;
        this->game_state = false;
    }

    for (unsigned int count = 1; count < this->snek.size(); count++)
    {
        if (this->snek[count]->GetY() == hed_y && this->snek[count]->GetX() == hed_x)
            this->game_state = false;
    }

    if (this->froot->comp_x(hed_x) && this->froot->comp_y(hed_y))
    {
        this->map[this->froot->GetY()][this->froot->GetX()] = ' ';

        int size = this->snek.size() - 1;

        int tmp_x = this->snek[size]->GetX();
        int tmp_y = this->snek[size]->GetY();
        int tmp_dir = this->snek[size]->GetPartDir();

        if (1 == this->snek_dir) // UP
            tmp_y -= 1;
        else if (2 == this->snek_dir) // RIGHT
            tmp_x += 1;
        else if (3 == this->snek_dir) // DOWN
            tmp_y += 1;
        else if (4 == this->snek_dir) // LEFT
            tmp_x -= 1;

        this->snek.push_back(new Snek(tmp_x, tmp_y, false, tmp_dir));
        this->froot->SetIsFood(false);
    }

    if (this->s_froot->comp_x(hed_x) && this->s_froot->comp_y(hed_y))
    {
        this->map[this->s_froot->GetY()][this->s_froot->GetX()] = ' ';
        this->s_froot->SetIsFood(false);
    }
}

void Engine::spawn_special_froot()
{
    if (this->steps % 14000)
    {
        this->s_froot->make_food(this->win_x, this->win_y);
        for (unsigned int count = 0; count < this->snek.size(); count++)
        {
            if (this->s_froot->comp_x(this->snek[count]->GetY()) && this->s_froot->comp_y(this->snek[count]->GetY()))
            {
                this->s_froot->make_food(this->win_x, this->win_y);
                count = 0;
            }
        }
        this->steps = 0;
        this->s_froot->SetIsFood(true);
    }
}

void Engine::spawn_froot()
{
    this->froot->make_food(this->win_x, this->win_y);
    for (unsigned int count = 0; count < this->snek.size(); count++)
    {
        if (this->froot->comp_x(this->snek[count]->GetY()) && this->froot->comp_y(this->snek[count]->GetY()))
        {
            this->froot->make_food(this->win_x, this->win_y);
            count = 0;
        }
    }

    this->froot->SetIsFood(true);
}

void Engine::add_placeholders()
{
    int tmp_x = 0;
    int tmp_y = 0;

    if (this->froot->GetIsFood() == true)
        this->map[this->froot->GetY()][this->froot->GetX()] = 'p';

    if (this->s_froot->GetIsFood() == true)
        this->map[this->s_froot->GetY()][this->s_froot->GetX()] = 'j';

    for (unsigned int count = 0; count < this->snek.size(); count++)
    {
        tmp_x = this->snek[count]->GetX();
        tmp_y = this->snek[count]->GetY();

        if (this->snek[count]->GetIsHed())
            this->map[tmp_y][tmp_x] = '@';
        else
            this->map[tmp_y][tmp_x] = '*';
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
                if (count == 1)
                    this->win_x = atoi(argv[count]);

                if (count == 2)
                    this->win_y = atoi(argv[count]);
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

	for (unsigned int tmp_y = 0; tmp_y < (this->win_y + 2); tmp_y++)
	{
		this->map[tmp_y] = new char[this->win_x + 2];
        if (this->map[tmp_y] != NULL)
        {
            for (unsigned int tmp_x = 0; tmp_x < this->win_x + 2; tmp_x++)
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

    for (unsigned int tmp_y = 0; tmp_y < (this->win_y + 2); tmp_y++)
	{
        for (unsigned int tmp_x = 0; tmp_x < this->win_x + 2; tmp_x++)
        {
            if (tmp_y == 0)
                this->map[tmp_y][tmp_x] = '/';
            else if (tmp_y == (this->win_y + 2) - 1)
                this->map[tmp_y][tmp_x] = '/';
        }
        this->map[tmp_y][0] = '/';
        this->map[tmp_y][(this->win_x + 2) - 1] = '/';
	}

    add_placeholders();
}

void Engine::create_snek()
{
    for (unsigned int count = 0; count < 4; count++)
    {
        this->snek.push_back(new Snek((this->win_x / 2), ((this->win_y / 2) + count), false, 1));
        if (count == 0)
            this->snek[count]->SetIsHed(true);
    }
}

void Engine::init(int argc, char **argv)
{
    this->froot = new food(0, 0, false);
    this->s_froot = new food(0, 0, false);
    this->game_state = false;
    this->steps = 0;
    this->snek_dir = 1;
    this->win_x = DEFAULT_WIN_X;
    this->win_y = DEFAULT_WIN_Y;
    this->current_lib = 1;
    user_input(argc, argv);
    load_lib("./sdl/sdl.so");
    create_snek();
    init_map();
    this->lib->init(this->win_x, this->win_y);
}

void Engine::move_snek()
{

    this->snek_dir = this->lib->input(this->snek_dir);

    int tmp_dir = this->snek[0]->GetPartDir();
    int tmp_x = this->snek[0]->GetX();
    int tmp_y = this->snek[0]->GetY();

    this->snek[0]->SetPartDir(this->snek_dir);
    if (1 == this->snek_dir) // UP
        this->snek[0]->SetY(tmp_y - 1);
    else if (2 == this->snek_dir) // RIGHT
        this->snek[0]->SetX(tmp_x + 1);
    else if (3 == this->snek_dir) // DOWN
        this->snek[0]->SetY(tmp_y + 1);
    else if (4 == this->snek_dir) // LEFT
        this->snek[0]->SetX(tmp_x - 1);

    int tmpx = 0;
    int tmpy = 0;
    int tmpdir = 0;
    for (unsigned int count = 1; count < this->snek.size(); count++)
    {
        tmpx = this->snek[count]->GetX();
        tmpy = this->snek[count]->GetY();
        tmpdir = this->snek[count]->GetPartDir();

        this->snek[count]->SetY(tmp_y);
        this->snek[count]->SetX(tmp_x);
        this->snek[count]->SetPartDir(tmp_dir);

        tmp_x = tmpx;
        tmp_y = tmpy;
        tmp_dir = tmpdir;
    }

    this->map[tmp_y][tmp_x] = ' ';
    check_colision();
}

void Engine::game_loop()
{
    this->game_state = true;

	srand(time(0));
	while (this->game_state)
    {
		move_snek();
        /*if (this->current_lib != this->lib->change_lib())
        {
            //close_lib();
            switch (this->current_lib)
            {
                case 1:
                    load_lib("./ncurses/ncurses.so");
                    break ;
                case 2:
                    this->game_state = false;
                    break ;
                case 3:
                    break ;
            }
        }*/
        if (rand() % 100 == 9 && this->s_froot->GetIsFood() == false)
            spawn_special_froot();
        if (this->froot->GetIsFood() == false)
            spawn_froot();
        add_placeholders();
        if (this->game_state == true)
		      this->lib->render(this->map);
        this->steps += 1;
		usleep(100000);
	}

    close_lib();
}

void Engine::load_lib(std::string const &lib_path)
{
    this->handle = dlopen(lib_path.c_str(), RTLD_LAZY);

    if (this->handle == NULL)
    {
        std::cout << "ITS NULL" << std::endl;
        return ;
    }
    // load the symbols
    create_t* create_lib = (create_t *) dlsym(this->handle, "create");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
        return ;
    }

    // create an instance of the class
    this->lib = create_lib();

}

void Engine::close_lib()
{
    destroy_t* destroy_lib = (destroy_t*) dlsym(this->handle, "destroy");
    const char* dlsym_error = dlerror();
    dlsym_error = dlerror();
    if (dlsym_error)
    {
        std::cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
        return ;
    }

    destroy_lib(this->lib);

    // unload the triangle library
    dlclose(this->handle);
}
