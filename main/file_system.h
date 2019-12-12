Game load_game (int file_num){
    FILE *save_file;
    char file_name[] = "save_X.dat";
    printf("Enter save file number: \n");
    scanf("%d",&file_num);
    file_name[5] = file_num + 48;
    printf("file name = %s\n",file_name);
    save_file = fopen(file_name,"rb");

    Game game; //saves the read game here
    fread(&game,sizeof(Game),1,save_file);
    fclose(save_file);

    print_game_struct_values(&game);
    print_grid(&game);
}

bool is_save(char input_str[1000]){

    char save[] = {'s','a','v','e','\0'};
    //checking if input_str = "save". I love C
    for (int i = 0;input_str[i] != '\n';i++){
        if (input_str[i] != save[i]  || i > 4){
            return false;
        }
    }
    return true;
}

void save_menu(Game *game){
    FILE *save_file;
    char file_name[] = "save_X.dat";
    printf("Enter save file number: \n");

    //Remains to be validated TODO
    int file_num;
    scanf("%d",&file_num);
    file_name[5] = file_num + 48;
    printf("file name = %s\n",file_name);
    save_file = fopen(file_name,"wb");

    fwrite(game,sizeof(Game),1,save_file);
    if (fwrite != 0)
        printf("Success\n");
    else printf("Fail\n");
    fclose(save_file);
}

