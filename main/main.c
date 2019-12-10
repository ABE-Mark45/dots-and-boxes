#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "structs.h"

/*
1 1 1 2
3 3 2 3
0 0 1 2
2 2 2 3
0 1 1 1
2 3 2 2
0 1 2 2
2 3 3 3
1 1 1 2
2 2 2 3



*/

void print_moves(Game *game){
    int num_of_moves = game->number_of_moves;
    for(int i=0; i<num_of_moves; i++){
        printf("%d %d %d %d", game->moves[i].row1, game->moves[i].row2,
               game->moves[i].col1,game->moves[i].col2);
    }
}



void make_move_struct(Move *move, int row1, int row2, int col1,int col2){
    move->row1 = row1;
    move->row2 = row2;
    move->col1 = col1;
    move->col2 = col2;
}

bool is_move_previously_played(Game *game,int row1, int row2, int col1, int col2){
     Square *square1,*square2;
    // check that the line isn't previously picked

    // Horizontal Line
    if(row1 == row2){
        Square *square1 = &(game->grid[row1-1][min(col1,col2)]);
        Square *square2 = &(game->grid[row1][min(col1,col2)]);
        if(square1->down !=0 || square2->up !=0)
            return true;

    }

    // Vertical Line
    if(col1 == col2){
        Square *square1 = &(game->grid[min(row1,row1)][col1]);
        Square *square2 = &(game->grid[min(row1,row2)][col1-1]);
         if(square1->left !=0 || square2->right !=0)
            return true;
    }
    return false;
}

void fill_string(char str[], char value, int size){
    for(int i=0; i<size; i++)
        str[i]=value;

    str[size] = NULL;
}

void initialize_game(Game *game){
    int grid_length = game->grid_length;
    for(int i=0; i<grid_length+2; i++){
        for(int j=0; j<grid_length+2; j++){
            game->grid[i][j].right=  0;
            game->grid[i][j].down = 0;
            game->grid[i][j].left=  0;
            game->grid[i][j].up=  0;
            game->grid[i][j].covered_by_player=0;
        }
    }

    game->number_of_moves=0;
    game->player1_points=0;
    game->player2_points=0;

}


void print_grid_values(Game *game){
    int grid_length = game->grid_length;
    for(int i=0; i<grid_length; i++){
        for(int j=0; j<grid_length; j++){
            printf("%d%d%d%d-%d ",game->grid[i][j].up,
                   game->grid[i][j].right,
                   game->grid[i][j].down,
                   game->grid[i][j].left,
                   game->grid[i][j].covered_by_player);
        }
        printf("\n");
    }

}

void print_game_struct_values(Game *game){
    printf("%d %d\n", game->expert, game->PVP);
}

bool is_point_in_grid(int point, int grid_length){
    if(point >= 0 && point < grid_length)
        return 1;

    return 0;
}

bool validate_points(int row1, int row2, int col1, int col2, Game *game){
    int grid_length = game->grid_length;
    if(!(is_point_in_grid(row1,grid_length) && is_point_in_grid(row2,grid_length) &&
          is_point_in_grid(col1,grid_length) && is_point_in_grid(col2,grid_length))){
        return false;
    }

    bool adjacent = (row1 == row2 || col1 == col2)
    && (abs(row1 - row2) == 1 || abs(col1 - col2) == 1) ;
    if(! adjacent)
        return false;

    return 1;

}

void display_top_10_players(){
}


void print_grid(Game *game){
    system("@cls||clear");
    int grid_length = game->grid_length;
    int scale = 6; // number of '-'

//    Sqaure *grid = game->grid;
    char full_side[scale+1], empty_side[scale+1];
    fill_string(full_side,'-',scale);
    fill_string(empty_side,' ',scale);
    char in_between_line[(scale+1)*grid_length+10];

    /*
        IF the Square of size (4) (scale=2):

        main_line               *---*---*---*
        in_between_line         |---|   |
        main_line               *---*


    */

    for(int i=0; i<grid_length; i++){
        fill_string(in_between_line,' ',(scale+1)*grid_length+3);
        for(int j=0; j<grid_length; j++){
            // main_line
            if(j<grid_length-1){
                printf("+");
                if(game->grid[i][j].up!= 0 )
                    printf("%s",full_side);
                else
                    printf("%s",empty_side);
            }
            // in_between_line
            if(game->grid[i][j].left != 0)
                in_between_line[(scale+1)*j]='|';

        }
        printf("+\n");
        if(i != grid_length-1){
            for(int k=0; k<scale/3; k++)
                printf("%s\n",in_between_line);
        }
    }

}
// 1 1 3 2 >> 1,1


bool enter_options (Game *game){
    printf("Pick a menu number:\n\
           1. Beginner (2 by 2 grid)\n\
           2. Expert (5 by 5 grid) \n\
           3. Choose a grid length\n");


    // input & validation
    char input[100000];
    bool invalid_input = 0;
    do{
        if(invalid_input)
            printf("Enter A Valid Input:\n");
        fgets(input,1000,stdin);
        invalid_input = (input[0] != '1' && input[0] != '2') || strlen(input) != 2;
    }while( invalid_input );

    if(input[0] == '1')
        game->grid_length = 2+1;
    else
        game->grid_length = 5+1;


    // terminate program ??
    //system("@cls||clear");
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

    if(input[0] == '1')
        game->PVP = 1;
    else
        game->PVP = 0;
    //print_game(game);

    initialize_game(game);

    return ;
}

//
bool is_colored_square(Square *square){
    if(square->right != 0
       && square->left != 0
       && square->down != 0
       && square->up != 0)
        return 1;
    return 0;
}

void color_square(Square *square, int num_of_moves){
    int color = (num_of_moves%2)+1;
    square->covered_by_player = color;
}

void play_game(Game *game){
    int row1,row2,col1,col2;
    int player_turn = 1;
    while(game->number_of_moves < (game->grid_length*(game->grid_length+1))*2 ){
        //printf("%d", game->grid_length);
        print_grid(game);
        printf("player1 Points: %d - player2 points: %d\n", game->player1_points,
           game->player2_points);
        print_moves(game);
        bool valid_input = 1;
        do{
            if(!valid_input)
                printf("Enter Valid numbers\n");
            int num_of_inputs = scanf("%d %d %d %d",&row1,&row2,&col1,&col2);
            make_move_struct(&(game->moves[game->number_of_moves]),row1,row2,col1,col2);
            valid_input = num_of_inputs == 4 && validate_points(row1,row2,col1,col2,game);
            if(valid_input)
                if(is_move_previously_played(game, row1,row2,col1,col2) == true)
                    valid_input = false;


        } while (!valid_input);


        Square *square1,*square2;
        // check that the line isn't previously picked


        // Horizontal Line
        if(row1 == row2){
            square1 = &(game->grid[row1-1][min(col1,col2)]);
            square2 = &(game->grid[row1][min(col1,col2)]);
            square1->down = player_turn;
            square2->up= player_turn;

        }

        // Vertical Line
        else if(col1 == col2){
            square1 = &(game->grid[min(row1,row1)][col1]);
            square2 = &(game->grid[min(row1,row2)][col1-1]);
            square1->left = player_turn;
            square2->right = player_turn;


        }
        //printf("%d %d %d\n", square1->left, square1->up, square1->down);
        if( is_colored_square(square1) ){
            color_square(square1, game->number_of_moves );
            if(player_turn == 1)game->player1_points++;
            else game->player2_points++;
        }
        if( is_colored_square(square2) ){
            color_square(square2, game->number_of_moves );
            if(player_turn == 1)game->player1_points++;
            else game->player2_points++;

        }
        //print_grid_values(game);
        player_turn = (3 - player_turn); // change player
        game->number_of_moves++;
      //  print_grid_values(game);

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

    // THIS CODE EXPLAINS HOW TO COLOR THE CONSOLE USE IT
/*
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  // you can loop k higher to see more color choices
  for(int k = 1; k < 255; k++)
  {
    SetConsoleTextAttribute(hConsole, k);
    printf("%3d  %s\n", k, "I want to be nice today!");
  }

  getchar();  // wait
*/

    Game game;

    //play_main_menu(&game);
//    print_grid(&game);
    //printf("%d", validate_points(1,1,3,));

     // int row1,row2,col1,col2;
    // printf("%d\n" ,scanf("%d %d %d %d",&row1,&row2,&col1,&col2));
    // printf("%d\n", col1);
    play_main_menu(&game);
    return 0;
}
