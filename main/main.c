#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"



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
            game->grid[i][j].left=  false;
            game->grid[i][j].up=  false;
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

bool enter_options (Game *game){
    printf("Pick a menu number:\n\
           1. Beginner (2 by 2 grid)\n\
           2. Expert (5 by 5 grid)\n");

    char input[100000];
    bool invalid_input = 0;
    do{
        if(invalid_input)
            printf("Enter A Valid Input:\n");
        fgets(input,1000,stdin);
        invalid_input = (input[0] != '1' && input[0] != '2') || strlen(input) != 2;
    }while( invalid_input );

            // terminate program ??
    system("@cls||clear");
    printf("Pick a menu number: \n \
           1. Players vs Player\n \
           2. Player vs Computer\n");

    invalid_input = 0;
    do{
        if(invalid_input)
            printf("Enter A Valid Input:\n");
        fgets(input,1000,stdin);
        invalid_input = (input[0] != '1' && input[0] != '2') || strlen(input) != 2;
    }while( invalid_input );

        // terminate program

    //print_game(game);
    return ;
}

void print_grid(Game *game){
    system("@cls||clear");
    int grid_length = 4;
    int scale = 3;
//    Sqaure *grid = game->grid;
    char full_side[scale+1], empty_side[scale+1];
    fill_string(full_side,'-',scale);
    fill_string(empty_side,' ',scale);
    char in_between_line[(scale+1)*grid_length+10];

    /*
        IF the Square of size 3 (scale=2):

        main_line               *---*---*---*
        in_between_line         |---|   |
        main_line               *---*


    */
    initialize_grid(game);
    /*game->grid[1][1].up =  1;
    game->grid[0][1].left = 1;*/

    printf("\n");
    for(int i=0; i<grid_length; i++){
        fill_string(in_between_line,' ',(scale+1)*grid_length+3);
        for(int j=0; j<grid_length; j++){
            // main_line
            if(j<grid_length-1){
                printf("+");
                if(game->grid[i][j].up==1 )
                    printf("%s",full_side);
                else
                    printf("%s",empty_side);
            }
            // in_between_line
            if(game->grid[i][j].left == 1)
                in_between_line[(scale+1)*j]='|';

        }
        printf("+\n");
        if(i != grid_length-1){
            for(int k=0; k<scale/3; k++)
                printf("%s\n",in_between_line);
        }
    }

}

bool in_grid(int point, int grid_length){
    if(point >= 0 && point < grid_length)
        return 1;

    return 0;
}

bool validate_points(int row1, int row2, int col1, int col2, Game *game){
    int grid_length = game->grid_length;
    if(!(in_grid(row1,grid_length) && in_grid(row2,grid_length) && in_grid(col1,grid_length) && in_grid(col2,grid_length))){
        return false;
    }

    bool adjacent = (row1 == row2 || col1 == col2)
    && (abs(row1 - row2) == 1 || abs(col1 - col2) == 1) ;
    if(! adjacent)
        return false;

    return 1;

}
// 1 1 3 2 >> 1,1

void play_game(Game *game){
    int row1,row2,col1,col2;
    for(int i=0; i<10; i++){

        bool valid_input = 1;
        do{
            if(!valid_input)
                printf("Enter Valid numbers\n");
            int num_of_inputs = scanf("%d %d %d %d",&row1,&row2,&col1,&col2);
            printf("n = %d\nvalidate = %d", num_of_inputs,validate_points(row1,row2,col1,col2,game));
            valid_input = num_of_inputs == 4 && validate_points(row1,row2,col1,col2,game);
        } while (!valid_input);

        game->grid[row1][col1].up = 1;
        print_grid(&game);
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

    //play_main_menu(&game);
//    print_grid(&game);
    //printf("%d", validate_points(1,1,3,));

     // int row1,row2,col1,col2;
    // printf("%d\n" ,scanf("%d %d %d %d",&row1,&row2,&col1,&col2));
    // printf("%d\n", col1);

    play_game(&game);
    return 0;
}
