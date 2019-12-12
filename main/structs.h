
typedef struct{
    int row1,row2,col1,col2;
} Move;

typedef struct{
    int up,right,down,left;
    int covered_by_player;
} Square;

typedef struct {
    bool expert;
    bool PVP;
    int grid_length;
    int player1_points;
    int player2_points;
    int number_of_moves;
    int player_turn;
    Move moves[100];
    Square grid[20][20];

} Game;

typedef struct{
    int row1,row2,col1,col2;
    int save;
} Input;
