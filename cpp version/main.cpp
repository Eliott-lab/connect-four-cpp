#include <iostream>
#include <vector>
#include <stdlib.h>
#include <array>
#include <Windows.h>
#include <cstdio>

struct Player // this struct is which info we should have about a player
{
    int sign ; //this value will be 1 or 2 and it's used to know which symbol will be print between "X" and "0"
    std::string name; //the name of player
    int score = 0; // the score of the player

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
    number_line = "   ";
    arrow = "   ";
    equal = "||";
    for (int column_number = 1 ;column_number <= y_axis ;column_number++) // for every column of the grid
    {
        if (column_number < 10) //if the number is lower than 10 we add a small space before it because 9 is one spac sized and 10 is two
            {
                number_line += " ";
            }
        number_line += std::to_string(column_number) + " "; // we add the number and a space to our string

        arrow += " ↓ "; // we add an arrow for the arrow string

        equal += column_number == 1 ? "=====" : "==="; // if the column number we add a smaller equal for estetethic purpose 
    }
    std::cout << number_line << std::endl; // print the number string
    std::cout << arrow << std::endl;       // print the arrow string

    for (int grid_height = 0; grid_height < x_axis; grid_height++) // for every lin of the grid
    {
        line = "|| ";
        for (int column_number = 0; column_number < y_axis; column_number++) // for every column of the grid
        {
                std::string sign = grid[grid_height * y_axis + column_number] != 0 ? grid[grid_height * y_axis + column_number] == 2 ? "X" : "O" : "-";
                /*
                our grid is a 1d vector so for example a grid of [6;7] is 42 items long and every 7 items we go one line down
                if the item is a 1 we add a "O" if it's a 2 we add a "X" otherwise we add a "-"
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
    std::vector<int> logo { 0,2,2,0,2,2,0,2,0,0,2,0,0,2,2,0,0,0,0,0,2,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0 };// just the heart array for estethic purpose

    while (true)
    {
        system("cls"); //clear the terminal
        print_grid(6,7,logo); //print the logo
        std::cout<<"combien de piece vous devez aligner pour gagner \nnous devons aligner : ";
        std::cin >> win_condition ; 
        if ((win_condition > 2) && (win_condition <40))// verify if the grid is not to big for the screen
        {
            break ;
        }
    }

    system("cls");
    print_grid(6,7,logo);
    std::cout << "quelle est le nom du joueur numéro 1 ,il auras le signe 'O'?\nil s'appelle : ";
    std::cin >> name1;

    system("cls");
    print_grid(6, 7, logo);
    std::cout << "quelle est le nom du joueur numéro 2 ,il auras le signe 'X'?\nil s'appelle : ";
    std::cin >> name2;
    system("cls");
}

bool play(std::vector<int>& grid,const int& symbol,const int& y_axis,const int& x_axis,const int& column_played) // add the play make by a player on the grid
{
    int smallest_empty_cell  =-1;//the smallest row with a piece
    for (int line_number = 0; line_number < x_axis; line_number++)
    {
        if (grid[line_number * y_axis + column_played - 1] == 0) //if this row is empty
        {
            smallest_empty_cell = line_number; //we register this row to be the smallest raw empty
        }
        else
        {
            break;
        }
    }
    if (smallest_empty_cell<0) // if the column is already full we return false and do nothing
    {
        return false;
    }
    grid[smallest_empty_cell * y_axis + column_played - 1] = symbol; // we apply the changement on the grid
    return true;
}

bool check_for_victory(const int &symbol, const int& win_condition, const std::vector<int>& grid,const int& x_axis,const int& y_axis) // this function check for a victory in the grid
    {
    for (int line_number = 0; line_number < x_axis; line_number++)
        {
        for (int column_number = 0; column_number < y_axis;column_number++)
            {
            if (grid[line_number * y_axis + column_number] == symbol ) // if the cell we are looking is the value of the player who played
            {
                int right_row = 1; // this is for a vertical combination
                int right_down_row = 1; // this is for a diagonal down right combination
                int down_row = 1;       // this is for a horizontal combination
                int left_down_row = 1;  // this is for a diagonal down left combination

                for (int index = 1; index < win_condition; index++) 
                {
                    if (y_axis - column_number >= win_condition) // if we have enough space between the cell and the end of the wall to have a win
                    {
                        if (grid[line_number * y_axis + column_number + index] == symbol)
                            {
                                right_row++; // we add one to that value to say "yes that cell is also the good symbol"
                            }
                            if (x_axis - line_number >= win_condition) // if we have enough space between the cell and the end of the ground to have a win
                            {
                                if (grid[(line_number + index) * y_axis + column_number + index] == symbol)
                                {
                                    right_down_row++;
                                }
                        }
                    }
                    if (x_axis - line_number >= win_condition)
                    {
                        if (grid[(line_number+index) * y_axis + column_number] == symbol)
                        {
                            down_row++;
                        }
                        if (column_number>=win_condition-1)
                        {
                           if (grid[(line_number + index) * y_axis + column_number - index] == symbol)
                            {
                                left_down_row++;
                            }
                        }
                    }
                }
                if ((right_row == win_condition) || (right_down_row == win_condition) ||(down_row == win_condition )||(left_down_row == win_condition)) 
                {
                    return true ; // return true if one those value is equal to the win requierment number
                }
            }
        }
    }
    return false; // otherwise it's not end already so we return false
}

void switch_current_player (int& current_player) //change the value for the list index 
{
    current_player = current_player == 1 ? 0 : 1 ; // if 1 switch to 0 if 0 switch to 1
}

int main()
{
    // Set console code page to UTF-8 so console known how to interpret string data
    SetConsoleOutputCP(CP_UTF8);

    int current_player = 0;
    int column_played;
    int win_condition ;

    std::string name1 , name2;

    bool game_loop = true ;
    bool play_again = true;

    std::string ask_for_play_again ;

    ask_info(win_condition, name1, name2);// ask how much in row is required to win  and the name of the two player

    Player player_1(1, name1) ;// create our two player
    Player player_2(2, name2);


    std::array <Player,2> list_of_player {player_1 ,player_2} ; // we stock our player in an array

    const int x_axis = win_condition + 2; 
    const int y_axis = win_condition * 2 - 1;

    std::vector<int> grid; //create the 2d aray in a 1d array
    for (int cell = 0; cell < y_axis * x_axis; cell++)
        grid.push_back(0) ;
    
    while (play_again) // while the users want to play
    {
        while (game_loop) // if the game is on a play statement
        {
            system("cls") ;
            print_grid(x_axis ,y_axis ,grid); // print the grid
            std::cout << list_of_player[current_player].name + " à ton tour de jouer !!\nJe jou sur la colone : " ; // ask the user to play
            std::cin >> column_played ;
            if (play(grid, list_of_player[current_player].sign ,y_axis,x_axis ,column_played)) // if the play is allowed and place on the grid
            {
                if (check_for_victory(list_of_player[current_player].sign, win_condition, grid, x_axis, y_axis)) // we look for a victory
                {
                    game_loop = false ;
                    list_of_player[current_player].score++; // add one to the total score of the player who won
                }
                else 
                {
                    switch_current_player(current_player) ; // we switch the player
                }
            }
        }
        system("cls") ;
        print_grid(x_axis, y_axis, grid); 
        std::cout << list_of_player[current_player].name + " à gagner !!:\nLe joueur " + list_of_player[current_player].name + " a " + std::to_string(list_of_player[current_player].score) + " points" << std::endl;
        std::cout << "Le joueur " + list_of_player[current_player + 1].name + " a " + std::to_string(list_of_player[current_player + 1].score) + " points" << std::endl;
        std::cout << "voulez vous rejouer ? \nY/N : " ;
        std::cin >> ask_for_play_again;

        if (!((ask_for_play_again == "Y")||(ask_for_play_again == "Yes")||(ask_for_play_again == "oui"))) // if the users don't want to play again
        {
            play_again = false ;
        }
        else //otherwise
        {
            game_loop = true ; // start a new game
            for (int cell = 0; cell < y_axis * x_axis; cell++)
                grid[cell] = 0; // reinitialize the grid 
        }
    }
}