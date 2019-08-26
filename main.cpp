#include<iostream>
#include<iomanip>
#include<fstream>

class table
{
private:
    int dimension_x = 10;
    int dimension_y = 10;
    int **board;
    bool available = true;
    char content;

public:
    char ocean = 'o';

    table()
    {
        board = new int[dimension_x]
        for(n= 0; n<dimension_x; n++)
        {
            board[n] = new int [dimension_y]
        }        
    }

    ~table()
    {
        for (n = 0; n < dimension_x; n++)
        {
            delete[] board[n];
        }
    }

    set_dimension(int rows, int cols)
    {
        dimension_x = rows;
        dimension_y = cols;
    }
};

struct boat
{
    int head_x;
    int head_y;
    char orientation;
};

set_boat(table active, )
{
    boat submarine[4];
    boat cruiser[3];
    boat destroyer[2];
    boat battleship;
}


int main()
{  
    using unsigned int = parameters;

    table active_board[boards];
    
    parameters dimension_max = 16;
    parameters dimension_min = 7; 
    parameters min_puzzles_bs = 1;
    parameters max_puzzles_bs = 100;
    parameters boards = min_puzzles_bs;

    table active_board[boards];

    std::cout << min_puzzles_bs << std::endl;
    std::cout << max_puzzles_bs << std::endl;
    
    parameters height;
    parameters width;
    parameters puzzles;
    parameters puzzle_number;


    create_puzzles(height, width, puzzles);

    print_table(puzzle_number);
    
    return 0;

}