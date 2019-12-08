
typedef struct{
    int row1,row2,col1,col2;
} Move;

typedef struct{
    bool up,right,down,left;
    int player;
} Square;

typedef struct {
    bool expert;
    bool PVP;
    int grid_length;
    int player1_points;
    int player2_points;
    Square grid[20][20];

} Game;
