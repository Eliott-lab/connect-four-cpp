/* this a c++ version of the python version*/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <array>
#include <Windows.h>
#include <cstdio>

struct Player // this struct is which info we should have about a player
{
    int sign ; //this value will be 1 or 2 and it's use to know which symbol will be print between "X" and "0"
    std::string name; //the name of player

    Player(const int& sign ,const std::string &name) //the constructor of the struc it will set the variables
        : sign(sign) ,name(name)
    {
    }
};

void print_grid(const int& x_axis ,const int& y_axis ,const std::vector<int>& grid) // this will function print our vector to look nice on the terminal
{
    std::string number_line; // the string for the number
    std::string line; // the string for the X or O value
    std::string arrow; // the string for the arrow line
    std::string equal; // the string for the equal line
    number_line += "   ";
    arrow += "   ";
    equal = "||";
    for (int column_number = 1 ;column_number <= y_axis ;column_number++) // for every column of the grid
    {
        if (column_number < 10) //if the number is lower than 10 we add a small space before it because 9 is one spac sized and 10 is two
            {
                number_line += " ";
            }
        number_line += std::to_string(column_number) + " "; // we add the number and a space to our string

        arrow += " ↓ "; // we add an arrow for the arrow string

        equal += column_number == 1 ? "==" : "==="; // if the column number we add a smaller equal for estetethic purpose 
    }
    std::cout << number_line << std::endl; // print the number string
    std::cout << arrow << std::endl;       // print the arrow string

    for (int grid_height = 0; grid_height < x_axis; grid_height++) // for every lin of the grid
    {
        line = "|| ";
        for (int column_number = 0; column_number < y_axis; column_number++) // for every column of the grid
        {
                std::string sign = grid[grid_height * x_axis + column_number] == 1 ? grid[grid_height * x_axis + column_number] == 2 ? "X" : "O" : "-";
                /*
                our grid is a 1d vector so for example a grid of [6;7] is 42 items long and every 7 items we go one line down
                if the item is a 1 we add a "X" if it's a 2 we add a "O" otherwise we add a "-"
                */
                line += " " + sign + " "; 
        }
        line += " ||"; // end the line 
        std::cout << line << std::endl;//print the line
    }

    std::cout << equal + "||\n\n"<<std::endl; // the we print the "equa line" for the end of the grid
    }


void ask_info(int& win_condition, std::string& name1,std::string& name2) //ask the info of the player
{
    std::vector<int> logo { 0,1,1,0,1,1,0,1,0,0,1,0,0,1,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0 };
    
    while (true)
    {
        system("cls");
        print_grid(6,7,logo);
        std::cout<<"combien de piece vous devez aligner pour gagner \nnous devons aligner : ";
        std::cin >> win_condition ; 
        if ((win_condition > 3) && (win_condition <51))
        {
            break ;
        }
    }
    system("cls");
    print_grid(6,7,logo);
    std::cout << "quelle est le nom du joueur numéro 1 ?\n il s'appelle : ";
    std::cin >> name1;
    system("cls");
    print_grid(6, 7, logo);
    std::cout << "quelle est le nom du joueur numéro 2 ?\n il s'appelle : ";
    std::cin >> name1;
    system("cls");
}

bool play(std::vector<int>& grid,const int& symbol,const int& x_axis,const int& column_played) // add the play make by a player on the grid
{
    int smallest_empty_cell  =-1;//the sm
    for (int line_number = 0; line_number < x_axis; line_number++)
    {
        if (grid[line_number * x_axis + column_played] == 0)
        {
            smallest_empty_cell = line_number;
        }
        else
        {
            break;
        }
    }
    if (smallest_empty_cell<0)
    {
        return false;
    }
    grid[smallest_empty_cell * x_axis + column_played] = symbol;
    return true;
}

bool check_for_victory(const int &symbol, const int& win_condition, const std::vector<int>& grid,int& x_axis, int& y_axis)
    {
    for (int line_number = 0; line_number < x_axis; line_number++)
        {
        for (int column_number = 0; column_number < y_axis;column_number++)
            {
            if (grid[line_number * x_axis + column_number] == symbol )
            {
                if(y_axis - column_number >= win_condition)
                {
                    int right_symbole_row = 0;
                    if (x_axis - line_number >= win_condition)
                    {
                        int right_down_symbole_row = 0;
                    }
                }
                if (x_axis - line_number >= win_condition)
                {
                    int down_symbole_row = 0;
                    if (win_condition <=-column_number)
                    {
                        int right_down_row = 0;
                    }
                }
            }
        }
    }
    return false;
}

int main()
{
    // Set console code page to UTF-8 so console known how to interpret string data
    SetConsoleOutputCP(CP_UTF8);


    int win_condition ;
    std::string name1 , name2;

    ask_info(win_condition,name1,name2);

    Player player_1(1, name1) ;
    Player player_2(2, name2);

    std::array <Player,2> card {player_1 ,player_2} ;

    const int x_axis = win_condition + 2;
    const int y_axis = win_condition * 2 - 1;
    const int cell_length = y_axis * x_axis;

    std::vector<int> grid;
    for (int cell = 0; cell < cell_length ;cell++)
        grid.push_back(0) ;
    
    print_grid(x_axis, y_axis, grid);
}