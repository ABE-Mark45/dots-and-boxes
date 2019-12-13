#include <string.h>
Game load_game (){
    FILE *save_file;
    char file_name[] = "save_X.dat";
    int file_num;
    do{
        printf("Enter file number:\n");
        file_num = input_file_number();
    }while (file_num == -1);

    file_name[5] = file_num + 48;
    printf("file name = %s\n",file_name);
    save_file = fopen(file_name,"rb");

    Game game; //saves the read game here
    fread(&game,sizeof(Game),1,save_file);
    fclose(save_file);

<<<<<<< HEAD
=======
    print_game_struct_values(&game);
    print_grid(&game);
>>>>>>> 01137b5242b8bbebae62d5a44b81d02506131743
    play_game(&game);
}

bool compare_str(char input_str[], char option_str[]){
    // adds an enter character to match the input_str
    if (strcmp(option_str, input_str) == 0)
        return true;
    return false;
}

void save_game(Game *game){
    FILE *save_file;
    char file_name[] = "save_X.dat";
    printf("Enter save file number: \n");
    int file_num;
    do{
        file_num = input_file_number();
    }while(file_num == -1);
    file_name[5] = file_num + 48;
    printf("file name = %s\n",file_name);
    save_file = fopen(file_name,"wb");

    fwrite(game,sizeof(Game),1,save_file);
    if (fwrite != 0)
        printf("Success\n");
    else printf("Fail\n");
    fclose(save_file);
}

int input_file_number(){
    char input_str[1000] = "";
    fgets(input_str, 1000, stdin);
    if (input_str[0] == '\0' || input_str[1] != 10)
        return -1;

    if (input_str[0] >= 49 && input_str[0] <= 51){
        int x = input_str[0] - 48;
        return x;
    }
    return -1;
}
