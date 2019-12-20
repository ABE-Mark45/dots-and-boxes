#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_
 // FILE_SYSTEM_H_
#include <string.h>
#include "structs.h"
#include <stdbool.h>
#include <stdio.h>
#define max(a, b) a > b?a:b

void load_game ();

bool compare_str(char input_str[], char option_str[]);
void save_game(Game *game);

int input_file_number();

void compare_two_players(Player a, Player b);

void sort_players(Player* players, int num_of_players);

void print_ten_players(Player* players, int num_of_players);


void update_player_score(Players_File *players_file, char player_name[], int new_score);

void update_player_score_to_files(char name[], int new_score);

void get_top_10_players(Players_File *players_file);

#endif
