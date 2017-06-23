#include "ncurses.hpp"

extern "C" dynamic_libs *create()
{
    return (new ncurses);
}

extern "C" void destroy(dynamic_libs *obj)
{
    delete obj;
}

ncurses::ncurses()
{
    this->max_x = 0;
    this->max_y = 0;
    this->stdscr_x = 0;
    this->stdscr_y = 0;
}

ncurses::ncurses(unsigned int tmp_x, unsigned int tmp_y)
{
    this->max_x = tmp_x;
    this->max_y = tmp_y;
}

ncurses::ncurses(ncurses const &obj)
{
    *this = obj;
}

ncurses::~ncurses()
{
    endwin();
}

ncurses &ncurses::operator=(ncurses const &obj)
{
    this->max_x = obj.GetX();
    this->max_y = obj.GetY();

    return (*this);
}


bool ncurses::init(unsigned int &maxX,unsigned int &maxY)
{
    initscr();

    getmaxyx(stdscr, this->max_y, this->max_x);
    if (this->stdscr_y < 50 || this->stdscr_x < 50)
        mvprintw(this->stdscr_y / 2, (this->stdscr_x / 2) - 15,"Please enlarge terminal window");

    this->max_y = maxY;
    this->max_x = maxX;

	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	raw();
	noecho();
    nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
    curs_set(FALSE);

    return (false);
}

void ncurses::render(char **map, unsigned int &score, bool &pause)
{
    clear();

    getmaxyx(stdscr, this->stdscr_y, this->stdscr_x);
    if (this->stdscr_y < 50 || this->stdscr_x < 50)
    {
        mvprintw(this->stdscr_y / 2, (this->stdscr_x / 2) - 15,"Please enlarge terminal window");
        pause = true;
        return ;
    }

    for (int tmp_y = 0; tmp_y < (this->max_y + 2); tmp_y++)
    {
        for (int tmp_x = 0; tmp_x < this->max_x + 2; tmp_x++)
        {
            printw("%c", map[tmp_y][tmp_x]);
        }
        printw("\n");
    }
    mvprintw(this->max_y + 3, 0, "Score: %d", score);
    refresh();
}

int ncurses::input(int &dir, int &lib)
{
    switch (getch())
    {
        case KEY_UP:
            if (dir != 3)
                return (1);
            break ;
        case KEY_RIGHT:
            if (dir != 4)
                return (2);
            break ;
        case KEY_DOWN:
            if (dir != 1)
                return (3);
            break ;
        case KEY_LEFT:
            if (dir != 2)
                return (4);
            break ;
        case 49:
            if (lib != 5)
                return (5);
            break ;
        case 50:
            if (lib != 6)
                return (6);
            break ;
        case 51:
            if (lib != 7)
                return (7);
            break ;
        case 27:
            return (8);
        case 32:
            return (9);
    }
    return (dir);
}

void ncurses::SetX(int tmp) { this->max_x = tmp; }
void ncurses::SetY(int tmp) { this->max_y = tmp; }

int ncurses::GetY() const { return (this->max_x); }
int ncurses::GetX() const { return (this->max_y); }
