#include "../Inc/Engine.hpp"

Engine::Engine()
{
    this->win_x = 0;
    this->win_y = 0;
    this->steps = 0;
    this->snek_dir = 0;
    this->current_lib = 0;
    this->pause = false;
    this->score = 0;
    this->lib_closed = true;
    this->map = nullptr;
    this->handle = NULL;
    this->game_state = false;
}

Engine::Engine(unsigned int win_X, unsigned int win_Y)
{
    this->win_x = win_X;
    this->win_y = win_Y;
}

Engine::Engine(Engine const &obj)
{
    *this = obj;
}

Engine::~Engine()
{
    delete this->froot;
    delete this->s_froot;

    if (this->map != nullptr)
    {
        for (unsigned int y = 0; y < this->win_y + 2; y++)
        {
            if (this->map[y] != NULL)
                delete this->map[y];
        }
        delete[ ] this->map;
    }

    if (this->snek.size() > 0)
    {
        for (unsigned int count = 0; count < this->snek.size(); count++)
        {
            delete this->snek[count];
        }
    }
}

Engine &Engine::operator=(Engine const &obj)
{
    this->win_x = obj.GetWinX();
    this->win_y = obj.GetWinY();
    this->steps = obj.GetSteps();
    this->snek_dir = obj.GetSnekDir();
    this->current_lib = obj.GetCurrentLib();
    this->pause = obj.GetPause();
    this->score = obj.GetScore();

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

        this->score += (rand() % 5 + 1);
    }

    if (this->s_froot->comp_x(hed_x) && this->s_froot->comp_y(hed_y))
    {
        this->map[this->s_froot->GetY()][this->s_froot->GetX()] = ' ';
        this->s_froot->SetIsFood(false);
        this->score += 10;
    }
}

void Engine::spawn_special_froot()
{
    if (this->steps % 20000)
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
        this->map[this->froot->GetY()][this->froot->GetX()] = '*';

    if (this->s_froot->GetIsFood() == true)
        this->map[this->s_froot->GetY()][this->s_froot->GetX()] = '!';

    for (unsigned int count = 0; count < this->snek.size(); count++)
    {
        tmp_x = this->snek[count]->GetX();
        tmp_y = this->snek[count]->GetY();

        if (this->snek[count]->GetIsHed())
            this->map[tmp_y][tmp_x] = '@';
        else
            this->map[tmp_y][tmp_x] = 'o';
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
                throw ("Input Error: \"Invalid Arguments\"");
        }
    }
    else
        throw ("Input Error: \"No Arguments\"");

    if ((this->win_y < 30 || this->win_y > 45) || (this->win_x < 30 || this->win_x > 45))
        throw ("Input Error: \"Invalid map size (30 - 45).\"");
}

void Engine::init_map()
{
    this->map = new char * [this->win_y + 2];

    if (this->map == nullptr)
        throw ("Memory Not Allocated: Bad Alloc.");

	for (unsigned int tmp_y = 0; tmp_y < (this->win_y + 2); tmp_y++)
	{
		this->map[tmp_y] = new char[this->win_x + 2];
        if (this->map[tmp_y] != nullptr)
        {
            for (unsigned int tmp_x = 0; tmp_x < this->win_x + 2; tmp_x++)
            {
                this->map[tmp_y][tmp_x] = ' ';
            }
        }
        else
            throw ("Memory Not Allocated: Bad Alloc.");
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
        if (this->snek[count] == nullptr)
            throw ("Memory Not Allocated: Bad Alloc.");
        if (count == 0)
            this->snek[count]->SetIsHed(true);
    }
}

void Engine::init(int argc, char **argv)
{
    this->froot = new food(0, 0, false);
    this->s_froot = new food(0, 0, false);
    if (this->froot == nullptr || this->s_froot == nullptr)
        throw ("Memory Not Allocated: Bad Alloc.");
    this->snek_dir = 1;
    this->current_lib = 5;
    user_input(argc, argv);
    load_lib(PATH_NCURSES);
    create_snek();
    init_map();
}

void Engine::move_snek()
{
    int tmp_dir = this->snek[0]->GetPartDir();
    int tmp_x = this->snek[0]->GetX();
    int tmp_y = this->snek[0]->GetY();
    int ret_tmp = 0;

    ret_tmp = this->lib->input(this->snek_dir, this->current_lib);

    if (ret_tmp > 4)
        change_lib(ret_tmp);
    else if (this->pause == false)
    {
        this->snek_dir = ret_tmp;

        switch (this->snek_dir)
        {
            case 1: // UP
                this->snek[0]->SetY(tmp_y - 1);
                break ;
            case 2: // RIGHT
                this->snek[0]->SetX(tmp_x + 1);
                break ;
            case 3: // DOWN
                this->snek[0]->SetY(tmp_y + 1);
                break ;
            case 4: // LEFT
                this->snek[0]->SetX(tmp_x - 1);
                break ;
        }

        int tmpx = 0;
        int tmpy = 0;
        int tmpdir = 0;

        if (this->snek_dir != tmp_dir)
            this->snek[0]->SetPartDir(this->snek_dir);

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
}

void Engine::change_lib(int &ret_tmp)
{
    if (ret_tmp == 9)
    {
        this->pause = !this->pause;
        return ;
    }
    else
        this->current_lib = ret_tmp;

    close_lib();
    switch (this->current_lib)
    {
        case 5:
            load_lib(PATH_NCURSES);
            break ;
        case 6:
            load_lib(PATH_SDL);
            break ;
        case 7:
            load_lib(PATH_SFML);
            break ;
        case 8:
            this->game_state = false;
            break ;
    }

    this->pause = true;
}

void Engine::game_loop()
{
    this->game_state = true;

	srand(time(0));
	while (this->game_state)
    {
    	move_snek();
        if (this->pause == false)
        {
            if (rand() % 100 == 9 && this->s_froot->GetIsFood() == false)
                spawn_special_froot();
            if (this->froot->GetIsFood() == false)
                spawn_froot();
            add_placeholders();
            this->steps += 1;
        }
        if (this->game_state == true)
            this->lib->render(this->map, this->score, this->pause);
    	usleep(70000);
	}

    if(!this->lib_closed)
        close_lib();
}

void Engine::load_lib(std::string const &lib_path)
{
    std::cout << lib_path << std::endl;
    this->handle = dlopen(lib_path.c_str(), RTLD_LAZY);

    if (this->handle == NULL)
        throw ("Load Error: \"Dynamic library cannot be opened\"");

    // load the symbols
    create_t* create_lib = (create_t *) dlsym(this->handle, "create");

    const char* dlsym_error = dlerror();
    if (dlsym_error)
        throw (dlsym_error);

    // create an instance of the class
    this->lib = create_lib();

    if (this->lib->init(this->win_x, this->win_y))
        throw ("library initialization Error: \"failed.\"");

    this->lib_closed = false;

}

void Engine::close_lib()
{
    destroy_t* destroy_lib = (destroy_t*) dlsym(this->handle, "destroy");

    const char* dlsym_error = dlerror();
    if (dlsym_error)
        throw (dlsym_error);

    destroy_lib(this->lib);

    // unload the library
    dlclose(this->handle);

    this->lib_closed = true;
}

//Dear Marker: Please excuse this mess.
void Engine::SetSteps(int tmp) { this->steps = tmp; }
void Engine::SetSnekDir(int tmp) { this->snek_dir = tmp; }
void Engine::SetCurrentLib(int tmp) { this->current_lib = tmp; }
void Engine::SetPause(bool tmp) { this->pause = tmp; }
void Engine::SetScore(unsigned int tmp) { this->score = tmp; }
void Engine::SetWinX(unsigned int tmp) { this->win_x = tmp; }
void Engine::SetWinY(unsigned int tmp) { this->win_y = tmp; }

int Engine::GetSteps() const { return (this->steps); }
int Engine::GetSnekDir() const { return (this->snek_dir); }
int Engine::GetCurrentLib() const { return (this->current_lib); }
bool Engine::GetPause() const { return (this->pause); }
unsigned int Engine::GetScore() const { return (this->score); }
unsigned int Engine::GetWinX() const { return (this->win_x); }
unsigned int Engine::GetWinY() const { return (this->win_y); }
