#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct{
    int row1,row2,col1,col2;
} Move;

typedef struct{
    bool up,right,down,left;
} Square;

typedef struct {
    bool expert;
    bool PVP;
    int player1_points;
    int player2_points;
    Square grid[20][20];

} Game;


void fill_string(char str[], char value, int size){
    for(int i=0; i<size; i++)
        str[i]=value;

    str[size] = NULL;
}

void initialize_grid(Game *game){
    int grid_length = 4;
    for(int i=0; i<grid_length; i++){
        for(int j=0; j<grid_length; j++){
            game->grid[i][j].right=  false;
            game->grid[i][j].down = false;
            printf("%d%d ",game->grid[i][j].right,game->grid[i][j].down);
        }
        printf("\n");
    }

}

void print_game_struct_values(Game *game){
    printf("%d %d\n", game->expert, game->PVP);
}

void display_top_10_players(){
}

void enter_options (Game *game){
    printf("Pick a menu number:\n\
           1. Beginner (2 by 2 grid)\n\
           2. Expert (5 by 5 grid)\n");

    char input[10];
    fgets(input,5,stdin);
    if(strlen(input) != 2)
        exit(0);

    if(input[0] == '1')
        game->expert = 0;

    else if(input[0] == '2')
        game->expert = 1;

    else
        exit(0);
        // terminate program ??
    system("@cls||clear");
    printf("Pick a menu number: \n \
           1. Players vs Player\n \
           2. Player vs Computer\n");

    fgets(input,4,stdin);
    if(strlen(input) != 2)
        exit(0);

    if(input[0] == '1')
        game->PVP = 1;

    else if(input[0] == '2')
        game->PVP = 0;

    else
        exit(0);
        // terminate program

    //print_game(game);
    return ;
}

void print_grid(Game *game){
    system("@cls||clear");
    int grid_length = 4;
    int scale = 3;
//    Sqaure *grid = game->grid;
    char full_side[3+1]= "---";
    char empty_side[3+1]= "   ";
    char in_between_line[(scale+1)*grid_length+10];

    /*
        IF the Square of size 3 (scale=2):

        main_line               *---*---*---*
        in_between_line         |   |   |
        main_line               *---*


    */
    initialize_grid(game);
    game->grid[2][0].right=  1;
    game->grid[1][3].down = 1;

    printf("\n");
    for(int i=0; i<grid_length; i++){
        fill_string(in_between_line,' ',(scale+1)*grid_length+3);
        for(int j=0; j<grid_length; j++){
            // main_line
            if(j<grid_length-1){
                printf("+");
                if(game->grid[i][j].right==1 )
                    printf("%s",full_side);
                else
                    printf("%s",empty_side);
            }
            // in_between_line
            if(game->grid[i][j].down == 1)
                in_between_line[(scale+1)*j]='|';

        }
        printf("+\n");
        if(i != grid_length-1){
            for(int k=0; k<scale; k++)
                printf("%s\n",in_between_line);
        }
    }

}

void play_game(Game *game){
    int row1,row2,col1,col2;
    for(int i=0; i<10; i++){
        scanf("%d %d %d %d",&row1,&row2,&col1,&col2);


    }
}


void play_main_menu(Game *game){
    printf("1.Start a New Game\n"
            "2.Load a Game\n"
            "3.Top 10 Players\n"
            "4.exit\n");

    printf("Enter the desired option's number:\n");

    //
    char input[10];
    fgets(input,5,stdin);
    system("@cls||clear");


    if(strlen(input) != 2) // input != 1 character
        exit(0); // terminate?

    switch(input[0]){
    case '1':
        enter_options(game);
        system("@cls||clear");
        play_game(game);
        break;
    case '2':
    case '3':

    case '4':
        display_top_10_players();
    default:
        exit(0);
    break;
    }



}

int main()
{
    // tab = 8 spaces
    //char arr[4];
  //  fgets(arr,3,stdin);
//    printf("%d",strlen(arr));

    Game game;
    print_grid(&game);

    //play_main_menu(&game);
    return 0;
}
