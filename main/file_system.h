#include <string.h>

void load_game (){
    FILE *save_file;
    char file_name[] = "save_X.bin";
    int file_num;
    do{
        printf("Enter file numbers:\n");
        file_num = input_file_number();
    }while (file_num == -1);

    file_name[5] = file_num + 48;
    //printf("file name = %s\n",file_name);
    save_file = fopen(file_name,"rb");

    Game game; //saves the read game here
    fread(&game,sizeof(Game),1,save_file);
    if(fread != 0){
        fclose(save_file);
        play_game(&game);
    }
}


bool compare_str(char input_str[], char option_str[]){
    // adds an enter character to match the input_str
    if (strcmp(option_str, input_str) == 0)
        return true;
    return false;
}

void save_game(Game *game){
    FILE *save_file;
    char file_name[] = "save_X.bin";
    printf("Enter save file number: \n");
    int file_num;
    do{
        file_num = input_file_number();
    }while(file_num == -1);
    file_name[5] = file_num + 48;
    save_file = fopen(file_name,"wb");

    fwrite(game,sizeof(Game),1,save_file);
    fclose(save_file);
}


int input_file_number(){
    char input_str[1000] = "";
    fgets(input_str, 1000, stdin);

    if (input_str[0] == '\0' || input_str[1] != 10)
        return -1;


    // only 3 files are allowed to be saved
    if (input_str[0] >= 49 && input_str[0] <= 51){
        int x = input_str[0] - 48;
        return x;
    }
    return -1;
}



void compare_two_players(Player a, Player b){
    return a.best_score > b.best_score;
}

void sort_players(Player* players, int num_of_players){
    int y,x;
    for (y = num_of_players-1; y > 0; y--)
    {
        for (x = 0; x < y; x++)
        {
            if (players[x].best_score > players[x + 1].best_score)
            {
                Player temp = players[x];
                players[x] = players[x + 1];
                players[x + 1] =  temp;
            }
        }
    }
}

void print_ten_players(Player* players, int num_of_players){
    printf("Players TOP Scores:\n\n");

    for(int i=num_of_players-1; i>=max(num_of_players-10,0); i--){
        printf("%s - %d\n", players[i].name, players[i].best_score);
    }
}


void update_player_score(Players_File *players_file, char player_name[], int new_score){
    int size = players_file->num_of_players;
    //printf("size: %d\n", size);

    char player_name_lowercase[1000];
    strcpy(player_name_lowercase,player_name);
    string_to_lower(player_name_lowercase);

    bool player_found = 0;
    for(int i=0; i<size; i++){

        char index_name_lowercase[1000];
        strcpy(index_name_lowercase, players_file->players[i].name);
        string_to_lower(index_name_lowercase);

        if(compare_str( index_name_lowercase, player_name_lowercase)){
            players_file->players[i].best_score = max( players_file->players[i].best_score , new_score);
            strcpy(players_file->players[i].name, player_name);
            player_found = 1;
            break;
        }
    }
    if(!player_found){
         players_file->players[size].best_score = new_score;
         memcpy(players_file->players[size].name, player_name, 1000);
         players_file->num_of_players++;
    }
}

void update_player_score_to_files(char name[], int new_score){
    FILE *save_file;
    Players_File players_file;

    players_file.num_of_players=0;// for empty files;
    char file_name[] = "player_scores.bin";

    save_file = fopen(file_name,"rb+");
    fread(&players_file,sizeof(players_file),1,save_file);
    fclose(save_file);

    update_player_score(&players_file, name, new_score);
    save_file = fopen(file_name,"wb");
    fwrite(&players_file,sizeof(players_file),1,save_file);
    fclose(save_file);

}

void get_top_10_players(Players_File *players_file){

    FILE *save_file;

    players_file->num_of_players=0; // for empty case

    char file_name[] = "player_scores.bin";
    save_file = fopen(file_name,"rb");

    fread(players_file, sizeof(Players_File),1, save_file);
    sort_players(&(players_file->players), players_file->num_of_players);
    print_ten_players(&(players_file->players), players_file->num_of_players);
    fclose(save_file);
}
