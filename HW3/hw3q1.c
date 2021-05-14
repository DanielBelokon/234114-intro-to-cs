/*-------------------------------------------------------------------------
    Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>

/*-------------------------------------------------------------------------
    Constants and definitions:
-------------------------------------------------------------------------*/
#define N 11
#define PLAYERS 2

/*-------------------------------------------------------------------------
    Function declaration
-------------------------------------------------------------------------*/

int get_move(int player, int *row, int *col);
int revert_moves(/* amount of moves, history? */);
int update_board(/* status */);
int conclude_game(/* status */);
int check_for_win(int board_arr[N][N], int *p_winner);

int get_size();

void print_welcome();
void print_enter_board_size();
void print_board(char board[N][N], int n);
void print_player_turn(int player_index);
void print_error();
void print_winner(int player_index);
void print_tie();

/*-------------------------------------------------------------------------
    Implementation
-------------------------------------------------------------------------*/

int main()
{
    int board_arr[N][N] = {{0}};

    int board_size, move = 1;
    int winner, endgame = 0;
    board_size = get_size();

    while (!endgame)
    {
        print_board(board_arr, board_size);
        update_board(board_arr, move);
        endgame = check_for_win(board_arr, &winner);
    }
    conclude_game(winner);
    return 0;
}

/*-------------------------------------------------------------------------
    Course Provided Functions
-------------------------------------------------------------------------*/
//print welcome message
//1 lines
void print_welcome()
{
    printf("*** Welcome to AVOIDANCE TIC-TAC-TOE game ***\n\n");
}

//print message to enter board size
//1 lines
void print_enter_board_size()
{
    printf("Please enter board size (1 to %d):\n", N);
}

//print the board
//7 lines
void print_board(char board[N][N], int n)
{
    printf("\nCurrent board:\n");
    for (int i = 0; i < n; i++)
    {
        printf("|");
        for (int j = 0; j < n; j++)
        {
            printf("%c|", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//print a request for player with index "player_index" to move
//1 lines
void print_player_turn(int player_index)
{
    printf("\nPlayer ** %d **, enter next move:\n", player_index);
}

//print error message
//1 lines
void print_error()
{
    printf("Illegal move!!!, please try again:\n");
}

//print the winner
//1 lines
void print_winner(int player_index)
{
    printf("Player %d Wins! Hooray!\n", player_index);
}

//print message to announce there is a tie (no one wins)
//1 lines
void print_tie()
{
    printf("It's a tie!\n");
}