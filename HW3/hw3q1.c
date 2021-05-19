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

void get_move(int player, int coords[2], int board_size, int board_arr[N][N]);
int make_move(int board_arr[N][N], int *p_move, int coords[2], int size);
void conclude_game(int winner);
int check_board(int board_arr[N][N], int *p_winner, int board_size, int move);

int check_for_straight(int board_arr[N][N], int board_size);
int check_cols(int board_arr[N][N], int board_size);
int check_for_diag(int board_arr[N][N], int board_size);
void revert_moves(int board_arr[N][N], int revert_by, int *p_move, int size);

int get_size();

void print_welcome();
void print_enter_board_size();
void print_board(int board[N][N], int n);
void print_player_turn(int player_index);
void print_error();
void print_winner(int player_index);
void print_tie();

/*-------------------------------------------------------------------------
    Implementation
-------------------------------------------------------------------------*/

int main()
{
    int board_arr[N][N] = {{0}}, board_size;
    int move = 1, winner = 0;
    int coords[2] = {0};
    
    print_welcome();
    board_size = get_size();
    while (move <= board_size * board_size)
    {
        print_board(board_arr, board_size);
        if (move >= 2 * board_size && check_board(board_arr, &winner, board_size, move))
            break;
        get_move(2 - (move % 2), coords, board_size, board_arr);
        make_move(board_arr, &move, coords, board_size);
    }
    conclude_game(winner);
    return 0;
}

// 5 lines
int get_size()
{
    int size = 0;
    print_enter_board_size();

    if (scanf("%d", &size) == 1)
        return size;
    return 0;
}

// 15 lines (REFACTOR!!!)
void get_move(int player, int coords[2], int board_size, int board_arr[N][N])
{
    print_player_turn(player);
    do
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

    } while (1);

    return;
}

// 6 lines
int make_move(int board_arr[N][N], int *p_move, int coords[2], int size)
{
    if (coords[X] < 0)
        revert_moves(board_arr, coords[X], p_move, size);
    else
    {
        board_arr[coords[X] - 1][coords[Y] - 1] = *p_move;
        (*p_move)++;
    }
    return 0;
}

// 6 lines
void revert_moves(int board_arr[N][N], int revert_by, int *p_move, int size)
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (board_arr[row][col] >= *p_move + revert_by)
                board_arr[row][col] = 0;
        }
    }
    *p_move += revert_by;

    return;
}

// 8 lines
int check_board(int board_arr[N][N], int *p_winner, int board_size, int move)
{
    // last move was played == no winner
    if ((move - 1) == board_size * board_size)
    {
        *p_winner = 0;
        return 1;
    }

    if (check_for_straight(board_arr, board_size) ||
        check_for_diag(board_arr, board_size))
    {
        *p_winner = 2 - (move % 2);
        return 1;
    }

    return 0;
}

int valid_product(int product, int count)
{
    if (product == 0 || product == count)
        return 1;
    return 0;
}

int check_for_straight(int board_arr[N][N], int board_size)
{
    int rows_prodct = 0, cols_prodct = 0;
    int row_has_empty, col_has_empty;
    for (int i = 0; i < board_size; i++)
    {
        row_has_empty = col_has_empty = 0;
        rows_prodct = cols_prodct = 0;
        for (int j = 0; j < board_size; j++)
        {
            cols_prodct += board_arr[j][i] % 2;
            col_has_empty += board_arr[j][i] == 0;
            rows_prodct += board_arr[i][j] % 2;
            row_has_empty += board_arr[i][j] == 0;
        }
        if ((!col_has_empty && (cols_prodct == 0 || cols_prodct == board_size)) ||
            (!row_has_empty && (rows_prodct == 0 || rows_prodct == board_size)))
            return 1;
    }
    return 0;
}

int check_for_diag(int board_arr[N][N], int board_size)
{
    int top_product = 0, bottom_product = 0;
    int top_has_empty = 0, bottom_has_empty = 0;
    for (int i = 0; i < board_size; i++)
    {
        top_has_empty += board_arr[i][i] == 0;
        top_product += board_arr[i][i] % 2;
        bottom_has_empty += board_arr[board_size - i - 1][i] == 0;
        bottom_product += board_arr[board_size - i - 1][i] % 2;
    }

    return (!top_has_empty && (top_product == 0 || top_product == board_size)) ||
           (!bottom_has_empty && (bottom_product == 0 || bottom_product == board_size));
}

int check_for_loss(int arr[N], int size)
{
}

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