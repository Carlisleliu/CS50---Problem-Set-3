```
/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool switch_tile(int tile, int tile_row, int tile_col, int empty_tile_row, int empty_tile_col);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
 
 
 // fill the baord with numbers in a decreasing order
void init(void)
{
    int largest_num = d * d - 1;
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            board[i][j] = largest_num;
            largest_num--;
            if (largest_num == 0)
            {
                break;
            }
        }
    }
    
    // switch the last two tiles in the beginning set if the board size is a even number
    if (d % 2 == 0)
    {
        int r_last = d - 1;
        int c_2ndlast = d - 2;
        int c_3rdlast = d - 3;
        
        int hold = board[r_last][c_2ndlast];
        board[r_last][c_2ndlast] = board[r_last][c_3rdlast];
        board[r_last][c_3rdlast] = hold;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // print the board value as 2-digit integer
            printf("| %2d ", board[i][j]);
        }
        // set the row space as 2
        printf("|\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    bool existence = false;
    int tile_i, tile_j;
    
    // confirm whether the target tile exists or not
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                tile_i = i;
                tile_j = j;
                existence = true;
                break;
            }
        }
    }
    
    if (!existence)
    {
        return false;
    }
    
    // if the target tile exists, determine whether the empty tile is adjacent to the tartget tile, if yes then switch them.
    int left_tile_i = tile_i - 1;
    int left_tile_j = tile_j;
    if (switch_tile(tile, tile_i, tile_j, left_tile_i, left_tile_j))
    {
        return true;
    };
    
    int right_tile_i = tile_i + 1;
    int right_tile_j = tile_j;
    if (switch_tile(tile, tile_i, tile_j, right_tile_i, right_tile_j))
    {
        return true;
    }
    
    int top_tile_i = tile_i;
    int top_tile_j = tile_j - 1;
    if (switch_tile(tile, tile_i, tile_j, top_tile_i, top_tile_j))
    {
        return true;
    }
    
    int bot_tile_i = tile_i;
    int bot_tile_j = tile_j + 1;
    if (switch_tile(tile, tile_i, tile_j, bot_tile_i, bot_tile_j))
    {
        return true;
    }
    
    return false;
}


// switch the target tile with the adjacent empty tile
bool switch_tile(int tile, int tile_row, int tile_col, int empty_tile_row, int empty_tile_col)
{
    if (empty_tile_row >= 0 && empty_tile_row < d && empty_tile_col >= 0 && empty_tile_col < d)
    {
        int empty_tile = board[empty_tile_row][empty_tile_col];
        if (empty_tile == 0)
        {
            int hold = empty_tile;
            board[empty_tile_row][empty_tile_col] = board[tile_row][tile_col];
            board[tile_row][tile_col] = hold;
            return true;
        }
    }
    else
    {
        return false;
    }
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
 
// determine whether the board is in the winning order
bool won(void)
{
    int target = 1;
    int last_tile_i = d - 1;
    int last_tile_j = d - 1;
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] != board[last_tile_i][last_tile_j])
            {
                if (board[i][j] == target)
                {
                    target++;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return true;
            }
        }
    }
    
    return true;
}
```
