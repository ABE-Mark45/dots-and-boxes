
typedef struct{
    int row1,row2,col1,col2;
} Move;

typedef struct{
    int up,right,down,left;
    int covered_by_player;
} Square;

typedef struct{
    char name[1000];
    int best_score;
    int id;
} Player;

typedef struct{
    Player players[1000];
    int num_of_players;
} Players_File;

typedef struct {
    bool expert;
    bool PVP;
    int grid_length;
    int player1_points;
    int player2_points;
    int number_of_moves;
    int player_turn;
    bool can_redo;
    int max_redo;
    Move moves[1000];
    Square grid[20][20];
    char winner_name[1000];

} Game;

typedef struct{
    int row1,row2,col1,col2;
    int save;
} Input;
