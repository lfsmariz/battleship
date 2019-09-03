using namespace std;
#include<stdlib.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<ctime>
#include<vector>

//!< impressão da mensagem de erro
static void show_Usage(std::string name)
{
    //Use name on the print in case we need to point out exactly on what entrance the error was.
    std::cerr << "Usage:  [<options>] <number_of_puzzles>\n"
              << "  Program options are:\n"
              << "    --rows <num>\tSpecify the number of rows for the matrix, with `<num>` in the range [7, 16 ]. The default value is 10.\n"
              << "    --cols <num>\tSpecify the number of columns for the matrix, with `<num>` in the range [7,16]. The default value is 10.\n"
              << "  Requested input is:\n"
              << "    number_of_puzzles\tThe number of puzzles to be generated, in the range [1,100]."
              << std::endl;
}
//!< struct para registro de cards
struct card_pos
{
    int eixo_x;
    int eixo_y;
};
//!< struct om informações relevantes dos barcos
struct boat
{
    int head_x;
    int head_y;
    int orientation;
};
//!< struct para variável das casas do tabuleiro
struct table
{
    bool available = true;
    std::string content = "·";
};

//!< classe puzzle e seus respectivos parâmetros
class puzzle
{
//!< variáveis privadas da classe
private:
    int dimension_x = 10;
    int dimension_y = 10;
    table **board;
    card_pos *shuffle_insert;
    boat submarine[4];
    boat cruiser[3];
    boat destroyer[2];
    boat battleship[1];
//!<métodos públicos da classe
public:
    //!< cosntrutor defaut da classe
    puzzle()
    {
        board = new table *[dimension_x];

        for(int n = 0; n < dimension_x; n++)
        {
            board[n] = new table[dimension_y];
        }

        for (int i = 0 ; i < dimension_x ; i++)
        {   
            for (int j = 0; j < dimension_y; j++)
            {
                shuffle_insert[i*j +j].eixo_x = i;
                shuffle_insert[i*j +j].eixo_y = j;
            }       
            
        }

        int total_dimension = dimension_x * dimension_y;     
        
        for (int k = 0 ; k < dimension_x * dimension_y; k++)
        {
            int position_rand = rand() % total_dimension;
            card_pos aux;
            aux = shuffle_insert[k];
            shuffle_insert[k] = shuffle_insert[position_rand];
            shuffle_insert[position_rand] = aux; 
        }       
    }
    
    puzzle(int rows, int cols)
    {
        dimension_x = rows;
        dimension_y = cols;
        
        board = new table *[dimension_x];

        for(int n = 0; n < dimension_x; n++)
        {
            board[n] = new table[dimension_y];
        }

        shuffle_insert = new card_pos[dimension_x * dimension_y];
        
        int contador=0;
        for (int i = 0; i < dimension_x; i++){
            for (int j = 0 ; j < dimension_y; j++){
                shuffle_insert[contador].eixo_x = i;
                shuffle_insert[contador].eixo_y = j;
                contador++;
            }
        }

        int total_dimension = dimension_x * dimension_y;     
        
        for (int k = 0 ; k < dimension_x * dimension_y; k++)
        {
            int position_rand = rand() % total_dimension;
            card_pos aux;
            aux = shuffle_insert[k];
            shuffle_insert[k] = shuffle_insert[position_rand];
            shuffle_insert[position_rand] = aux; 
        }       
    }
    //!< destrutor defaut da classe
    ~puzzle()
    {
        for (int n = 0; n < dimension_x; n++)
        {
            delete[] board[n];
        }
    }
    //!< função para definição das dimensões da classe
    void set_dimension(int rows, int cols)
    {
        dimension_x = rows;
        dimension_y = cols;
    }

    
    //!< função para impressão do tabuleiro
    void print_puzzle()
    {
        for (int i = 0; i < dimension_x; i++)
        {
            for (int j = 0; j < dimension_y ; j++)
            {
                std::cout << board[i][j].content << " ";
            }
            std::cout<< " " <<std::endl;
        }

       //for(int a = 0; a < 3; a++)
        //{
        //    std::cout << cruiser[a].head_x << "/" << cruiser[a].head_y << " --"<<cruiser[a].orientation <<" C\n";
        //}

        for(int a = 0; a < 4; a++)
        {
            std::cout << submarine[a].head_x << "/" << submarine[a].head_y << " -- S \n";
        }

        for(int a = 0; a < 2; a++)
        {
            std::cout << destroyer[a].head_x << "/" << destroyer[a].head_y << " --"<<destroyer[a].orientation <<" D\n";
        }
       

    }
    //!< set battleship no tabuleiro
    void set_battleship()
    {
        int k = 0;
        int j = 0;
        while (k<1)
        {
            int axisx = shuffle_insert[j].eixo_x;
            int axisy = shuffle_insert[j].eixo_y;
            int try_insert_v = 0;
            int try_insert_h = 0;

            for (int d = axisx ; d < axisx + 4; d++)
            {
                if (d < dimension_x and board[d][axisy].available == true)
                {
                    try_insert_v++;
                }              
                
            }

            if (try_insert_v < 4)
            {
                try_insert_v = 0;
            }
            
            for (int d = axisy ; d < axisy + 4; d++)
            {
                if (d < dimension_y and board[axisx][d].available == true and try_insert_v == 0)
                {
                    try_insert_h++;
                }

                else
                {
                    break;
                }                    
                
            }

            if (try_insert_v == 4)
            {   
                battleship[k].orientation = 1;
                battleship[k].head_x = axisx + 1;
                battleship[k].head_y = axisy + 1;
                for (int i = 0; i < try_insert_v; i++)
                {
                    if(i==0){
                        board[axisx+i][axisy].content = "▲";
                    }else{
                        if(i<try_insert_v-1){
                            board[axisx+i][axisy].content = "◼︎";
                        }
                        else{
                            if(i==try_insert_v-1){
                                board[axisx+i][axisy].content = "▼︎";
                            }
                        }
                    }
                    board[axisx+i][axisy].available = false;
                }
                
                for (int x = axisx -1 ; x < axisx + 5; x++)
                {
                    for (int y = axisy - 1; y < axisy + 2 ; y++)
                    {
                        if (x >= 0 && x < dimension_x && y >= 0 && y < dimension_y)
                        {
                           board[x][y].available = false;
                        }
                       
                    }
                }
                k++;
            }

            if (try_insert_h == 4)
            {   
                battleship[k].orientation = 0;
                battleship[k].head_x = axisx + 1;
                battleship[k].head_y = axisy + 1;
                for (int i = 0; i < try_insert_h; i++)
                {
                    if(i==0){
                        board[axisx][axisy+i].content = "◀︎";
                    }else{
                        if(i<try_insert_h-1){
                            board[axisx][axisy+i].content = "◼︎";
                        }
                        else{
                            if(i==try_insert_h-1){
                                board[axisx][axisy+i].content = "▶︎︎";
                            }
                        }
                    }
                    board[axisx][axisy].available = false;
                }
                

                for (int x = axisx -1 ; x < axisx + 4; x++)
                {
                    for (int y = axisy - 1; y < axisy + 5 ; y++)
                    {
                        if (x >= 0 && x < dimension_x && y >= 0 && y < dimension_y)
                        {
                           board[x][y].available = false;
                        }
                       
                    }
                }
                k++;
            }
            j++;
        }  

    }
     //!< set cruiser no tabuleiro
    void set_cruiser()
    {
        int k = 0;
        int j = 0;
        while (k<3)
        {
            int axisx = shuffle_insert[j].eixo_x;
            int axisy = shuffle_insert[j].eixo_y;
            int try_insert_v = 0;
            int try_insert_h = 0;

            for (int d = axisx ; d < axisx + 2; d++)
            {
                if (d < dimension_x and board[d][axisy].available == true)
                {
                    try_insert_v++;
                }                
                
            }

            if (try_insert_v < 2)
            {
                try_insert_v = 0;
            }
            
            for (int d = axisy ; d < axisy + 2; d++)
            {
                if (d < dimension_y and board[axisx][d].available == true and try_insert_v == 0)
                {
                    try_insert_h++;
                }

                else
                {
                    break;
                }                    
                
            }

            if (try_insert_v == 2)
            {   
                cruiser[k].orientation = 1;
                cruiser[k].head_x = axisx + 1;
                cruiser[k].head_y = axisy + 1;
                for (int i = 0; i < try_insert_v; i++)
                {
                    if(i==0){
                        board[axisx+i][axisy].content = "▲";
                    }else{
                        board[axisx+i][axisy].content = "▼";
                        
                    }
                    board[axisx+i][axisy].available = false;
                }
                
                for (int x = axisx -1 ; x < axisx + 3; x++)
                {
                    for (int y = axisy - 1; y < axisy + 2 ; y++)
                    {
                        if (x >= 0 && x < dimension_x && y >= 0 && y < dimension_y)
                        {
                           board[x][y].available = false;
                        }
                       
                    }
                }
                k++;
            }

            if (try_insert_h == 2)
            {   
                destroyer[k].orientation = 0;
                destroyer[k].head_x = axisx + 1;
                destroyer[k].head_y = axisy + 1;
                for (int i = 0; i < try_insert_h; i++)
                {
                    if(i==0){
                        board[axisx][axisy + i].content = "◀";
                    }else{
                        board[axisx][axisy + i].content = "▶︎";
                    }
                    board[axisx][axisy+i].available = false;
                }
                

                for (int x = axisx -1 ; x < axisx + 2; x++)
                {
                    for (int y = axisy - 1; y < axisy + 3 ; y++)
                    {
                        if (x >= 0 && x < dimension_x && y >= 0 && y < dimension_y)
                        {
                           board[x][y].available = false;
                        }
                       
                    }
                }
                k++;
            }
            j++;
        }  

    }
     //!< set destroyer no tabuleiro
    void set_destroyer()
    {
        int k = 0;
        int j = 0;
        while (k<2)
        {
            int axisx = shuffle_insert[j].eixo_x;
            int axisy = shuffle_insert[j].eixo_y;
            int try_insert_v = 0;
            int try_insert_h = 0;

            for (int d = axisx ; d < axisx + 3; d++)
            {
                if (d < dimension_x and board[d][axisy].available == true)
                {
                    try_insert_v++;
                }              
                
            }

            if (try_insert_v < 3)
            {
                try_insert_v = 0;
            }
            
            for (int d = axisy ; d < axisy + 3; d++)
            {
                if (d < dimension_y and board[axisx][d].available == true and try_insert_v == 0)
                {
                    try_insert_h++;
                }

                else
                {
                    break;
                }                    
                
            }

            if (try_insert_v == 3)
            {   
                destroyer[k].orientation = 1;
                destroyer[k].head_x = axisx + 1;
                destroyer[k].head_y = axisy + 1;
                for (int i = 0; i < try_insert_v; i++)
                {
                    if(i==0){
                        board[axisx+i][axisy].content = "▲";
                    }else{
                        if(i<try_insert_v-1){
                            board[axisx+i][axisy].content = "◼︎";
                        }
                        else{
                            if(i==try_insert_v-1){
                                board[axisx+i][axisy].content = "▼︎";
                            }
                        }
                    }
                    board[axisx+i][axisy].available = false;
                }
                
                for (int x = axisx -1 ; x < axisx + 4; x++)
                {
                    for (int y = axisy - 1; y < axisy + 2 ; y++)
                    {
                        if (x >= 0 && x < dimension_x && y >= 0 && y < dimension_y)
                        {
                           board[x][y].available = false;
                        }
                       
                    }
                }
                k++;
            }

            if (try_insert_h == 3)
            {   
                destroyer[k].orientation = 0;
                destroyer[k].head_x = axisx + 1;
                destroyer[k].head_y = axisy + 1;
                for (int i = 0; i < try_insert_h; i++)
                {
                    if(i==0){
                        board[axisx][axisy+i].content = "◀︎";
                    }else{
                        if(i<try_insert_h-1){
                            board[axisx][axisy+i].content = "◼︎";
                        }
                        else{
                            if(i==try_insert_h-1){
                                board[axisx][axisy+i].content = "▶︎︎";
                            }
                        }
                    }
                    board[axisx][axisy].available = false;
                }
                

                for (int x = axisx -1 ; x < axisx + 2; x++)
                {
                    for (int y = axisy - 1; y < axisy + 4 ; y++)
                    {
                        if (x >= 0 && x < dimension_x && y >= 0 && y < dimension_y)
                        {
                           board[x][y].available = false;
                        }
                       
                    }
                }
                k++;
            }
            j++;
        }  

    }

     //!< set submarine no tabuleiro
    void set_submarine()
    {
        int k = 0;
        int j = 0;
        while (k<4)
        {            
            int axis_x = shuffle_insert[j].eixo_x;
            int axis_y = shuffle_insert[j].eixo_y;
            
            if (board[axis_x][axis_y].available == true)
            {
                board[axis_x][axis_y].content = "●";
                submarine[k].head_x = axis_x + 1;
                submarine[k].head_y = axis_y + 1;
                
                for (int x = axis_x -1 ; x <= axis_x + 1; x++)
                {
                    for (int y = axis_y - 1; y <= axis_y + 1; y++)
                    {
                        if (x >= 0 && x < dimension_x && y >= 0 && y < dimension_y)
                        {
                           board[x][y].available = false;
                        }
                       
                    }
                }
                k++;
            }
            j++;
        }
        
    }

     //!<impressão do conteúdo da posição do tabuleiro
    std::string save_board(int x , int y)
    {
      return board[x][y].content;
    }

    //!<impressão do conteúdo de head do submarino
    std::string save_submarine(int k)
   {   
       int axix = submarine[k].head_x;
       int axiy = submarine[k].head_y;
       std::string concatenatedata;
       concatenatedata = "S " + std::to_string(axix) +" / "+ std::to_string(axiy);
       return concatenatedata;
   }
    //!<impressão do conteúdo de head e orientação do cruiser
   std::string save_cruiser(int k)
   {   
       int axix = cruiser[k].head_x;
       int axiy = cruiser[k].head_y;
       std::string concatenatedata;
       if (cruiser[k].orientation == 1)
       {
            concatenatedata = "C " + std::to_string(axix) +" / "+ std::to_string(axiy) + "- V" ;
       }
       else{concatenatedata = "C " + std::to_string(axix) +" / "+ std::to_string(axiy) + "- H";}
       
       return concatenatedata;
   }

    //!<impressão do conteúdo de head e orientação do destroyer
   std::string save_destroyer(int k)
   {   
       int axix = destroyer[k].head_x;
       int axiy = destroyer[k].head_y;
       
       std::string concatenatedata;
       if (destroyer[k].orientation == 1)
       {
            concatenatedata = "D " + std::to_string(axix) +" / "+ std::to_string(axiy) + "- V" ;
       }
       else{concatenatedata = "D " + std::to_string(axix) +" / "+ std::to_string(axiy) + "- H";}
       
       return concatenatedata;
   }
    //!<impressão do conteúdo de head e orientação do battleship
   std::string save_battleship(int k)
   {   
       int axix = battleship[k].head_x;
       int axiy = battleship[k].head_y;
       
       std::string concatenatedata;
       if (battleship[k].orientation == 1)
       {
            concatenatedata = "B " + std::to_string(axix) +" / "+ std::to_string(axiy) + "- V" ;
       }
       else{concatenatedata = "B " + std::to_string(axix) +" / "+ std::to_string(axiy) + "- H";}
       
       return concatenatedata;
   }


};

//!<função main
int main(int argc, char* argv[])
{  
    if (argc < 1){
        show_Usage(argv[0]);
        return 1;
    }
    
    std::vector <std::string> sources;
    std::string destination;
    int rows = 10;
    int cols = 10;
    int nBoards = 0;
    bool setNBoard = false;
     for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--rows"){
            std::string numeroRow(argv[i+1]);
            if(numeroRow==std::to_string((int)atoi(argv[i+1])) && atoi(argv[i+1])>=7 && atoi(argv[i+1])<=16){
                rows = atoi(argv[i+1]);
                i=i+1;
            }
            else{
                std::cout << "bpg ERROR: ``invalid number of rows!``\n" << std::endl;
                show_Usage(argv[i]);
                return 1;
            }
        }else{
            if(arg == "--cols"){
                std::string numeroCol(argv[i+1]);
                if(numeroCol==std::to_string((int)atoi(argv[i+1])) && atoi(argv[i+1])>=7 && atoi(argv[i+1])<=16){
                    cols = atoi(argv[i+1]);
                    i=i+1;
                }
                else{
                    std::cout << "bpg ERROR: ``invalid number of columns!``\n" << std::endl;
                    show_Usage(argv[i]);
                    return 1;
                }
            }else{
                if(setNBoard == false){
                    std::string numeroBoards(argv[i]);
                    if(numeroBoards==std::to_string((int)atoi(argv[i])) && atoi(argv[i])>=1 && atoi(argv[i])<=100){
                        nBoards = atoi(argv[i]);
                        setNBoard = true;
                    }else{
                        std::cout << "bpg ERROR: ``invalid number of boards!``\n" << std::endl;
                        show_Usage(argv[i]);
                        return 1;
                    }
                }else{
                    show_Usage(argv[i]);
                    return 1;
                }
            }
        }
    }
    if(setNBoard == false){
        std::cout << "bpg ERROR: ``invalid number of boards!``\n" << std::endl;
        show_Usage(argv[0]);
        return 1;
    }
    
    srand((int)time(0));
    //using parameters = unsigned int;
    

    puzzle *active_board[nBoards];
    for (int i=0;i<=nBoards-1;i++){
        active_board[i] = new puzzle(rows,cols);
        active_board[i]->set_battleship();
        active_board[i]->set_destroyer();
        active_board[i]->set_cruiser();
        active_board[i]->set_submarine();
        //active_board[i]->print_puzzle();
    }


    ofstream outdata;
    outdata.open("boards.bs");
    if( !outdata ) 
    {
      cerr << "Error: file could not be opened" << endl;
      exit(1);
    }
    int number_tabs = 0;
    while (number_tabs < nBoards)
    {
        outdata << "tabuleiro: " << number_tabs << "\n" << rows << "/" << cols << "\n";
        for (int i = 1; i <= cols; i++)
        {
            outdata << i/10;
        }
        outdata << "\n";
        for (int i = 1; i <= cols; i++)
        {
            outdata << i%10;
        }
        
        outdata << "\n";
        
        for (int i = 0 ; i < rows; i++)
        {
            outdata << i+1;
            for (int j = 0; j < cols; j++)
            {
                outdata << active_board[number_tabs]->save_board(i,j);
            }
            outdata << "\n"; 
        }
        outdata << "--------------------\n\n";

        number_tabs++;
    }

    outdata.close();

    ofstream outdata_pos;
    outdata_pos.open("boat.bs");
    if( !outdata_pos ) 
    {
      cerr << "Error: file could not be opened" << endl;
      exit(1);
    }

    number_tabs = 0;
    while (number_tabs < nBoards)
    {
        outdata_pos << "tabuleiro: " << number_tabs << "\n" << rows << "/" << cols << "\n";
        outdata_pos << active_board[number_tabs]->save_battleship(0) << "\n";

        for (int i = 0 ; i < 2; i++)
        {
            outdata_pos << active_board[number_tabs]->save_destroyer(i) << "\n";
        }
        for (int i = 0 ; i < 3; i++)
        {
            outdata_pos << active_board[number_tabs]->save_cruiser(i) << "\n";
        }
        for (int i = 0 ; i < 4; i++)
        {
            outdata_pos << active_board[number_tabs]->save_submarine(i) << "\n";
        }

        outdata_pos << "--------------------\n\n";

        number_tabs++;
    }
         outdata_pos.close();



    return 0;

}