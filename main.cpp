#include<iostream>
#include<iomanip>
#include<fstream>

struct card_pos
{
    int eixo_x;
    int eixo_y;
};

struct boat
{
    int head_x;
    int head_y;
    char orientation;
};

class table
{
private:
    int dimension_x = 10;
    int dimension_y = 10;
    int **board;
    bool available = true;
    char content;
    card_pos shuffle_insert = [dimension_x * dimension_y];
    boat submarine[4];
    boat cruiser[3];
    boat destroyer[2];
    boat battleship[1];

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

    set_shuffle(shuffle_insert[])
    {
        for (int i = 0 ; i < dimension_x ; i++)
        {
            for(int j = 0 ; j < dimension_y ; j++)
            {
                shuffle_insert.eixo_x = i;
                shuffle_insert.eixo_y = j;
            }
        }

        int total_dimension = dimension_x * dimension_y;     
        for (int k = 0 ; k < dimension_x * dimension_y; k++);
        {
            int position_rand = rand() % total_dimension;
            card_pos aux;
            aux = shuffle_insert[k];
            shuffle_insert[k] = shuffle_insert[position_rand];
            shuffle_insert[position_rand] = aux;

        }
    }

    
};


int main()
{  
    using unsigned int = parameters;
    
    parameters dimension_max = 16;
    parameters dimension_min = 7; 
    parameters min_puzzles_bs = 1;
    parameters max_puzzles_bs = 100;
    parameters boards = min_puzzles_bs;

    table active_board[boards];

    std::cout << min_puzzles_bs << std::endl;
    std::cout << max_puzzles_bs << std::endl;
    
    parameters height = 10;
    parameters width = 10;
    parameters puzzle_number = 0;

    shuffle_insert(height, width)

    print_table(puzzle_number);
    
    return 0;

}