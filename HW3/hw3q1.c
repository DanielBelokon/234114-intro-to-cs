/*-------------------------------------------------------------------------
    Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>

/*-------------------------------------------------------------------------
    Constants and definitions:
-------------------------------------------------------------------------*/
#define N 11
#define PLAYERS 2
#define DIM 2
#define X 0
#define Y 1

/*-------------------------------------------------------------------------
    Function declaration
-------------------------------------------------------------------------*/

int check_board(int board_arr[N][N], int *p_winner, int board_size, int move);
int make_move(int board_arr[N][N], int board_size, int *p_move, int coords[2]);
int play_game(int board_arr[][N], int board_size);
int get_size();

void get_move(int board_arr[N][N], int board_size, int player, int coords[2]);
void conclude_game(int winner);

int is_line_loss(int board_arr[N][N], int board_size);
int is_diag_loss(int board_arr[N][N], int board_size);
int is_loss(int arr[], int size);
void undo(int board_arr[N][N], int board_size, int *p_move, int undo_by);

void print_welcome();
void print_enter_board_size();
void print_board(int board[N][N], int n);
void print_player_turn(int player_index);
void print_error();
void print_winner(int player_index);
void print_tie();

/*-------------------------------------------------------------------------
    Implementation
    Avoidance tic tac toe - play until someone loses by placing n moves in a 
    straight or diagnal line

    X := odd numbers in the board arr
    O := even numbers in the board arr

    The arr stores when the move was made rather than who made it, 
    thus we are able to revert when needed and easily deduce who it was made
    by (first player always on odd moves, second always on even moves)
-------------------------------------------------------------------------*/

// Initialize the variables, start the game
// 7 lines
int main()
{
    int board_arr[N][N] = {{0}}, board_size;
    int winner;

    print_welcome();

    board_size = get_size();
    winner = play_game(board_arr, board_size);
    conclude_game(winner);
    return 0;
}

// get the board size from the the players
// 5 lines
int get_size()
{
    int size = 0;
    print_enter_board_size();

    if (scanf("%d", &size) == 1)
        return size;
    return 0;
}

// actual game logic, initialize variables, start the game loop and make moves
// 12 lines
int play_game(int board_arr[][N], int board_size)
{
    int coords[2] = {0}, winner = 0;
    int move = 1, player = 0;

    // play as long as board isn't full (save one to print the final board)
    while (move - 1 <= board_size * board_size)
    {
        player = 2 - (move % 2);
        print_board(board_arr, board_size);

        // when enough moves for a loss, check
        if (move >= 2 * board_size &&
            check_board(board_arr, &winner, board_size, move))
            return winner;
            
        print_player_turn(player);
        get_move(board_arr, board_size, player, coords);
        make_move(board_arr, board_size, &move, coords);
    }
    return 0;
}

// get the next move from the cur player
// 13 lines
void get_move(int board_arr[N][N], int board_size, int player, int coords[2])
{
    while (1)
    {
        if (scanf(" %d", &coords[X]) == 1)
        {
            if (coords[X] > 0)
            {
                if (scanf(" %d", &coords[Y]) == 1 &&
                    coords[Y] > 0 &&
                    coords[Y] <= board_size &&
                    coords[X] <= board_size &&
                    board_arr[coords[X] - 1][coords[Y] - 1] == 0)
                    break;
            }
            else if (coords[X] % 2 == -1)
                break;
        }

        print_error();
    }

    return;
}

// apply the current move to the board and update the move counter accordingly
// 6 lines
int make_move(int board_arr[][N], int board_size, int *p_move, int coords[])
{
    if (coords[X] < 0)
        undo(board_arr, board_size, p_move, coords[X]);
    else
    {
        board_arr[coords[X] - 1][coords[Y] - 1] = *p_move;
        (*p_move)++;
    }
    return 0;
}

// revert the board by 'undo_by' moves and reverse move counter
// 6 lines
void undo(int board_arr[N][N], int board_size, int *p_move, int undo_by)
{
    for (int row = 0; row < board_size; row++)
    {
        for (int col = 0; col < board_size; col++)
        {
            if (board_arr[row][col] >= *p_move + undo_by)
                board_arr[row][col] = 0;
        }
    }
    *p_move += undo_by;

    return;
}

// check the board for full X or O in a diag/vert/horiz line or no loser
// 8 lines
int check_board(int board_arr[N][N], int *p_winner, int board_size, int move)
{
    // no more space == no winner
    if ((move - 1) == board_size * board_size)
    {
        *p_winner = 0;
        return 1;
    }

    if (is_line_loss(board_arr, board_size) ||
        is_diag_loss(board_arr, board_size))
    {
        // loss happened on prev move, so curr player is the winner
        *p_winner = 2 - (move % 2);
        return 1;
    }

    return 0;
}

// Check the rows & columns for X or O in a row (odd vs even)
// 8 lines
int is_line_loss(int board_arr[N][N], int board_size)
{
    int col_arr[N];
    int loss_cnt = 0;
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            col_arr[j] = board_arr[j][i];
        }

        loss_cnt += is_loss(col_arr, board_size) ||
                    is_loss(board_arr[i], board_size);
    }

    return loss_cnt;
}

// Check both diagnals for full X or O (odd vs even)
int is_diag_loss(int board_arr[N][N], int board_size)
{
    int diag_arr_ltr[N], diag_arr_rtl[N];

    for (int i = 0; i < board_size; i++)
    {
        diag_arr_ltr[i] = board_arr[i][i];
        diag_arr_rtl[i] = board_arr[board_size - i - 1][i];
    }

    return is_loss(diag_arr_ltr, board_size) ||
           is_loss(diag_arr_rtl, board_size);
}

// Check a given arr of numbers if all entries are odd or all are even (X - O)
// 6 lines
int is_loss(int arr[], int size)
{
    int odd_count = 0;

    // count all occurences of odd numbers, if a square is empty (0) - stop
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == 0)
            return 0;
        odd_count += arr[i] % 2;
    }

    // when all of the numbers are either odd or even, it's a loss.
    return (odd_count == size || odd_count == 0);
}

// print conclusion based on winner/tie
// 5 lines
void conclude_game(int winner)
{
    if (winner == 0)
        print_tie();
    else
        print_winner(winner);

    return;
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
//9 lines
void print_board(int board[N][N], int n)
{
    printf("\nCurrent board:\n");
    for (int i = 0; i < n; i++)
    {
        printf("|");
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == 0)
                printf("_|");
            else
                printf("%c|", board[i][j] % 2 ? 'X' : 'O');
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