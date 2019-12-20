#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>
#include "structs.h"
#include "file_system.h"
#include <time.h>
#define blue 9
#define green 10
#define white 15
#define test1 printf("working1\n");
#define test2 printf("working2\n");
#define test3 printf("working3\n");


/*
Expert Game:
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
1 1 2 3
0 1 3 3
0 1 0 0
0 0 2 3
0 0 0 1


Beginner Game:
PVP:
0 0 1 2
0 0 0 1
1 1 0 1
1 2 1 1
1 2 2 2
0 1 2 2
1 2 0 0
2 2 0 1
1 2 1 1
0 1 0 0
0 1 1 1
1 1 1 2


PVC:
0 0 0 1
1 2 0 0
1 1 1 0
0 0 1 2
0 1 2 2
2 2 1 2

*/

/*          Debugging Utilities       */



bool exit_game;

void delay(float number_of_seconds)
{
    float milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}

void print_all_played_moves(Game *game){
    int num_of_moves = game->number_of_moves;
    for(int i=0; i<num_of_moves; i++){
        printf("%d %d %d %d", game->moves[i].row1, game->moves[i].row2,
               game->moves[i].col1,game->moves[i].col2);
    }
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


// helping functions

void string_to_lower(char str[]){
    for(int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);

}
void fill_string(char str[], char value, int size){
    for(int i=0; i<size; i++)
        str[i]=value;

    str[size] = NULL;
}


void record_move(Move *move, int row1, int row2, int col1,int col2){
    move->row1 = row1;
    move->row2 = row2;
    move->col1 = col1;
    move->col2 = col2;
}

bool is_move_previously_played(Game *game,int row1, int row2, int col1, int col2){
     Square *square1,*square2;
    // Horizontal Line
    if(row1 == row2){
        Square *square2 = &(game->grid[row1][min(col1,col2)]);
        if(square2->up !=0) // square previously filled
            return true;

    }

    // Vertical Line
    if(col1 == col2){
        Square *square1 = &(game->grid[min(row1,row1)][col1]);
         if(square1->left !=0)
            return true;
    }
    return false;
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
    game->player_turn = 1;
    game->can_redo = 0;
    exit_game = false;
    game->max_redo =0;

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


void print_grid(Game *game){
    system("@cls||clear");
    int grid_length = game->grid_length;
    int scale;
    if(grid_length == 3)
        scale = 20;

    else
        scale = 8;
        // number of '-'

//    Sqaure *grid = game->grid;
    char full_side[scale+1], empty_side[scale+1],
    in_between_line[(scale+1)*grid_length+10],
    full_box[scale+1];

    fill_string(full_side,'-',scale);
    fill_string(empty_side,' ',scale);
    fill_string(full_box,219,scale);
    /*
        IF the Square of size (3) (scale=3):

        main_line               *---*---*---*
        in_between_line         |---|   |
        main_line               *---*


    */
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int color1= 9;
    int color2= 10;
    // you can loop k higher to see more color choices
   /* for(int k = 1; k < 255; k++)
    {
        SetConsoleTextAttribute(hConsole, k);
        printf("%3d  %s\n", k, "I want to be nice today!");
    }*/

    for(int i=0; i<grid_length; i++){
        fill_string(in_between_line,' ',(scale+1)*grid_length+3);
        for(int j=0; j<grid_length; j++){
            // main_line

            if(j<grid_length-1){
                printf("+");
                if(game->grid[i][j].up!= 0 ){
                    if(game->grid[i][j].up == 1)
                        SetConsoleTextAttribute(hConsole, blue);
                    else // == 2
                        SetConsoleTextAttribute(hConsole, green);


                    printf("%s",full_side);
                    SetConsoleTextAttribute(hConsole, white);
                }
                else
                    printf("%s",empty_side);
            }
            // in_between_line
            if(game->grid[i][j].left != 0)
                in_between_line[(scale+1)*j]='|';

        }
        printf("+\n");
        if(i != grid_length-1){
            for(int k=0; k<scale/3; k++){
                for(int j=0; j<grid_length; j++){
                    if(game->grid[i][j].left!= 0 ){
                        if(game->grid[i][j].left == 1)
                            SetConsoleTextAttribute(hConsole, blue);
                        else // == 2
                            SetConsoleTextAttribute(hConsole, green);


                        printf("|");
                        SetConsoleTextAttribute(hConsole, white);
                    }
                    else
                        printf(" ");

                    if(game->grid[i][j].covered_by_player == 1){
                        SetConsoleTextAttribute(hConsole, blue);
                        printf("%s", full_box);
                        SetConsoleTextAttribute(hConsole, white);
                    }

                    else if(game->grid[i][j].covered_by_player == 2){
                        SetConsoleTextAttribute(hConsole, green);
                        printf("%s", full_box);
                        SetConsoleTextAttribute(hConsole, white);
                    }
                    else
                        printf("%s",empty_side);
                }
                printf("\n");

            }
                //

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

    if(input[0] == '1')
        game->PVP = 1;
    else
        game->PVP = 0;

    initialize_game(game);

    return ;
}

bool is_colored_square(Square *square){
    if(square->right != 0
       && square->left != 0
       && square->down != 0
       && square->up != 0)
        return 1;
    return 0;
}


void display_top_10_players(){
    system("@cls||clear");
    Players_File *players_file,mem;
    players_file = &mem;
    get_top_10_players(players_file);
    //print_ten_players(&(players_file->players), players_file->num_of_players);

    printf("\n");
    printf("Enter anything to get back\n");

    char input[100];
    fgets(input,100,stdin);

}


void after_game(Game *game){

    system("@cls||clear");
    int score_to_update;
    char name_to_update[1000];
    // print the winner's name
    if(game->PVP == 1){
        if(game->player1_points > game->player2_points)
            printf("Player1 Won .. Congrats :D \n");

        else if(game->player1_points < game->player2_points){
                printf("Player2 Won .. Congrats :D \n");
        }
        else {
            printf("DRAW !!");
            return ;
        }
        printf("Winner, Enter Your Name, please :) .\n");

        do{
            fgets(name_to_update, 50, stdin);
        }while(strlen(name_to_update) == 1);

        name_to_update[ strlen(name_to_update) - 1 ] = '\0';
        score_to_update = max(game->player1_points, game->player2_points);
    }
    else{
        if(game->player1_points > game->player2_points)
            printf("Congrats .. You Won ^^ \n");

        else if(game->player1_points < game->player2_points)
            printf("Sorry, u lost .. try again later \n");

        else
            printf("DRAW!!");

        printf("Enter Your Name, please :) .\n");

        do{
            fgets(name_to_update, 50, stdin);
        }while(strlen(name_to_update) == 1);

        score_to_update = game->player1_points;
    }

    delay(0.5);
    name_to_update[ strlen(name_to_update)-1 ] = NULL;
    update_player_score_to_files( name_to_update , score_to_update );
    display_top_10_players();

}

void color_square(Square *square, int player_turn){

    square->covered_by_player = player_turn; // give the square to the player
}
void un_color_square(Square *square, int player_turn){
    square->covered_by_player = 0;
}

void undo(Game *game){
    // one more redo allowed
    game->max_redo++;

    game->number_of_moves--;
    int row1,row2,col1,col2;
    row1= game->moves[ game->number_of_moves ].row1;
    row2= game->moves[ game->number_of_moves ].row2;
    col1= game->moves[ game->number_of_moves ].col1;
    col2= game->moves[ game->number_of_moves ].col2;

    Square *square1, *square2;
    // Horizontal Line


    if(row1 == row2){
        square1 = &(game->grid[row1-1][min(col1,col2)]); // upper square
        square2 = &(game->grid[row1][min(col1,col2)]);
    }
    else if(col1 == col2){
        square1 = &(game->grid[min(row1,row1)][col1]); // right square
        square2 = &(game->grid[min(row1,row2)][col1-1]); // left square
    }

    bool player_marked_a_box=0;

    if( is_colored_square(square1) ){
        un_color_square(square1, game->player_turn );
        if(game->player_turn == 1)game->player1_points--;
        else game->player2_points--;
        player_marked_a_box=1; // to change player twice here and at the end of the loop
    }
    if( is_colored_square(square2) ){
        un_color_square(square2, game->player_turn );
        if(game->player_turn == 1)game->player1_points--;
        else game->player2_points--;
        player_marked_a_box=1; // to change player twice here and at the end of the loop
    }

    if(row1 == row2){
          square1->down = 0;
          square2->up= 0;
    }

    // Vertical Line
    else if(col1 == col2){
        square1->left = 0;
        square2->right = 0;
    }
    if(player_marked_a_box == false)
        game->player_turn = (3 - game->player_turn); // change player

}


void display_game(Game *game){
    print_grid(game);
    printf("\n");
    printf("player1 Points: %d - player2 points: %d\n\n", game->player1_points,
       game->player2_points);


    printf("Type \'undo\' to undo a move\n");
    printf("Type \'redo\' to save a move\n");

    printf("Type \'save\' to save the game\n");
    printf("Type \'exit\' to exit the game (Note: you might want to save it before u exit)\n\n");
}

bool three_sidded_box_exists(Game *game, int *row1, int *row2, int* col1, int *col2){
    int grid_length = game->grid_length;
    for(int i=0; i<grid_length; i++){
        for(int j=0; j<grid_length; j++){
            int num_of_sides = 0;
            if(game->grid[i][j].right != 0)num_of_sides++;
            if(game->grid[i][j].up!= 0)num_of_sides++;
            if(game->grid[i][j].left != 0)num_of_sides++;
            if(game->grid[i][j].down != 0)num_of_sides++;
            if(num_of_sides++ == 3){
                if(game->grid[i][j].up == 0){
                    *row1 = i; *row2= i;
                    *col1 = j; *col2= j+1;
                }
                if(game->grid[i][j].down == 0){
                    *row1 = i+1; *row2= i+1;
                    *col1 = j; *col2= j+1;
                }
                if(game->grid[i][j].right == 0){
                    *row1 = i; *row2= i+1;
                    *col1 = j+1; *col2= j+1;
                }
                if(game->grid[i][j].left == 0){
                    *row1 = i; *row2= i+1;
                    *col1 = j; *col2= j;
                }
                record_move( &(game->moves[game->number_of_moves]), *row1,*row2,*col1,*col2);
                return 1;
            }
        }
    }
    return false;
}

void computer_to_play(Game *game, int *row1, int *row2, int *col1, int *col2){


     game->can_redo = 0;
     game->max_redo = 0;
     if(three_sidded_box_exists(game, row1, row2, col1, col2)){
        return;
     }


     for(int i=0; i<game->grid_length; i++){ // col loop
        for(int j=0; j<game->grid_length-1; j++){
            *row1 = j; *row2 = j+1;
            *col1 = i; *col2 = i;
            if(is_move_previously_played(game, *row1, *row2, *col1, *col2) == false){
                record_move( &(game->moves[game->number_of_moves]), *row1,*row2,*col1,*col2);
                return ;
            }
        }
    }
    // play a vertical line
    for(int i=0; i<game->grid_length; i++){
        for(int j=0; j<game->grid_length-1; j++){
            *row1 = i; *row2 = i;
            *col1 = j; *col2 = j+1;
            if(is_move_previously_played(game, *row1, *row2, *col1, *col2) == false){
                record_move( &(game->moves[game->number_of_moves]), *row1,*row2,*col1,*col2);
                return ;
            }
        }
    }
}



void take_coordinates_input(Game *game, int *row1, int *row2, int *col1, int *col2){

    bool valid_input;
    do{
        char input_str[1000] = "";
        fgets(input_str,1000,stdin);

        if (compare_str(input_str, "save\n")){
            save_game(game);
            continue;
        }
        else if ( compare_str(input_str, "undo\n") && game->number_of_moves > 0){
            game->can_redo = true;

            int new_play_turn,previous_play_turn = game->player_turn;
            do{
                undo(game); // other's player turn
                new_play_turn = game->player_turn;
            }while(previous_play_turn != new_play_turn); // undo until the players gets his turn again

            display_game(game);
            continue;
         }
        else if (compare_str(input_str, "redo\n") && game->can_redo && game->max_redo > 0){
            *row1= game->moves[ game->number_of_moves ].row1;
            *row2= game->moves[ game->number_of_moves ].row2;
            *col1= game->moves[ game->number_of_moves ].col1;
            *col2= game->moves[ game->number_of_moves ].col2;
            game->max_redo--;
            return;
         }
        if (compare_str(input_str, "exit\n")){
            exit_game = true;
            return;
        }


        int num_of_inputs;

        num_of_inputs = sscanf(input_str,"%d %d %d %d",row1,row2,col1,col2);

        test3;
        delay(2);
        /*printf("\n-----------------------------------------\n");
        printf("%s",input_str);
        printf("num = %d\n",num_of_inputs);
        printf("inputs = %d %d %d %d\n",row1,row2,col1,col2);
        printf("-----------------------------------------\n\n");
*/

        valid_input = num_of_inputs == 4 && validate_points(*row1,*row2,*col1,*col2,game);

        if(valid_input){
            if(is_move_previously_played(game, *row1,*row2,*col1,*col2) == true){
                valid_input = false;
            }
            else
                record_move( &(game->moves[game->number_of_moves]), *row1,*row2,*col1,*col2);
        }
        if(!valid_input)
            printf("Enter a valid input please\n");

    } while (!valid_input);
    game->can_redo = false;
    game->max_redo = 0;
}

void play_game(Game *game){
    exit_game = 0;
    int row1,row2,col1,col2;
    float seconds = 0.0;
    clock_t start = clock();
    delay(0.5);
    while(game->number_of_moves < ((game->grid_length-1)*(game->grid_length))*2 ){
        // print game after each play

        display_game(game);
        printf("Time: %0.2f\n", seconds);
        if(game->PVP == 0 && game->player_turn == 2){
            delay(0.5);
            computer_to_play(game, &row1, &row2, &col1, &col2);
        }
        else
            take_coordinates_input(game, &row1, &row2, &col1, &col2);
        if(exit_game)
            return;


        Square *square1,*square2;

        // Horizontal Line
        if(row1 == row2){
            square1 = &(game->grid[row1-1][min(col1,col2)]); // upper square
            square2 = &(game->grid[row1][min(col1,col2)]); // lower square
            square1->down = game->player_turn;
            square2->up= game->player_turn;

        }

        // Vertical Line
        else if(col1 == col2){
            square1 = &(game->grid[min(row1,row1)][col1]); // right square
            square2 = &(game->grid[min(row1,row2)][col1-1]); // left square
            square1->left = game->player_turn;
            square2->right = game->player_turn;


        }
        bool player_marked_a_box = 0;
        if( is_colored_square(square1) ){
            color_square(square1, game->player_turn );
            if(game->player_turn == 1)game->player1_points++;
            else game->player2_points++;
            player_marked_a_box = 1; // to change player twice here and at the end of the loop
        }
        if( is_colored_square(square2) ){
            color_square(square2, game->player_turn );
            if(game->player_turn == 1)game->player1_points++;
            else game->player2_points++;
            player_marked_a_box = 1; // to change player twice here and at the end of the loop
        }

        if(player_marked_a_box == false)
            game->player_turn = (3 - game->player_turn); // change player
        game->number_of_moves++;

        clock_t end = clock();
        seconds = (float)(end - start) / 1000;



    }
    display_game(game);
    delay(1);
    after_game(game);

}


void play_main_menu(Game *game){

    system("@cls||clear");
    printf("1.Start a New Game\n"
            "2.Load a Game\n"
            "3.Top 10 Players\n"
            "4.exit\n");

    printf("Enter the desired option's number:\n");

    //
    char input[10000];
    fgets(input,10000,stdin);
    system("@cls||clear");


    if(strlen(input) != 2){ // input != 1 character
         play_main_menu(game);
         return;
    }

    switch(input[0]){
    case '1':
        enter_options(game);
        play_game(game);
        break;
    case '2':
        load_game();
        break;
    case '3':
        display_top_10_players();
        break;
    case '4':
        exit(0);
        break;
    default:
        break;;

    }



}




int main()
{

  /*   HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int color1= 9;
    int color2= 10;
    // you can loop k higher to see more color choices
    for(int k = 1; k < 255; k++)
    {

        SetConsoleTextAttribute(hConsole, k);
        printf("%3d  %s\n", k, "I want to be nice today!");
    }*/
    //print_grid(&game);
    while(true){
        Game new_game;
        play_main_menu(&new_game);
    }

    return 0;
}

