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
 
/*
 * _XOPEN_SOURCE tells compiler to include some extra functions that exist in 
 * //most recent UNIX/BSD/Linux systems, the 500 specifically referrs to 
 * X/Open 5, incorporating POSIX 1995
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9


//variables
int rslxn = 0; //stores row index of selected tile
int cslxn = 0; //stores column index of selected tile
int rblank = 0; //stores row index of blank space
int cblank = 0; //stores column index of blank space

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
bool won(void);
bool findtile (int tile);
int checkmove (void);
void tileswap (void);

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
void init(void)
{
        //figure out how many tiles are needed, subtract one for blank space
    int tiles = (d * d) - 1;
    
    //iterate over rows and columns to fill with tile values
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            board [r] [c] = tiles;
            tiles--;
        }
    }
        
    //check  if d is even. if yes, 2 and 1 need to be switched so game can be won
    if (d % 2 == 0)
    {
        //initialize temporary "swapper" tile, assign it value 2
        int swapper = board[d - 1] [d - 3];
        //assign value 1 to 2's position in board
        
        board[d - 1] [d - 3] = board[d - 1] [d - 2];
        //assign "swapper" value 2 to 1's position
        
        //assign swapper temp
        board[d - 1] [d - 2] = swapper;
    }

    //mark position of 0 value tile (blank)
    rblank = d - 1;
    cblank = d - 1;
}




/**
 * Prints the board in its current state.
 */
void draw(void)
{
        //iterate over rows first
     for (int r = 0; r < d; r++)
    {
        //iterate over columns, print value of board
        for (int c = 0; c < d; c++)
        {
            //check if space is 0, print underscores for blank
            if (board [r][c] == 0)
            {
                printf ("___ ");
            }
            //otherwise print tile's value (%2i used in place of %i to ensure single digit tiles match up to double digit tiles)
            else
            printf ("%2i ", board [r] [c]);
        }
        printf("\n");
    }
}




/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    findtile(tile);
    checkmove();
    
    if (checkmove() == 0)
    {
        tileswap ();
        return true;
    }
    else
        return false;
    
}




/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
        //starting at board index 00, we make sure it's value is 1 and 
    //increment variable checking against
    int woncheck = 1;
    
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            if (board[r][c] == woncheck)
            {
                woncheck++;
            }
        }
    }
    
    if (woncheck == d*d && board[d - 1][d - 1] == 0)
    {
        return true;
    }
    else
        return false;
}



/**********************************************************************
*/



void tileswap (void)
{
int tswap = board[rslxn][cslxn];
    board[rslxn][cslxn] = board[rblank][cblank];
    board[rblank][cblank] = tswap;
    
//update indices of blank tile
    rblank = rslxn;
    cblank = cslxn;
}


/**********************************************************************
*/



int checkmove (void)
{
    /*four cases, if any are true, move is legal. selection out of bounds check done in findtile; 
    no legal selections should have out of bounds idicies*/
    if (    (rslxn == (rblank + 1) && cslxn == cblank) 
         || (rslxn == (rblank - 1) && cslxn == cblank) 
         || (cslxn == (cblank + 1) && rslxn == rblank) 
         || (cslxn == (cblank - 1) && rslxn == rblank))
        {
            return 0;
        }
    else
    {
        return 1;
    }
}



/**********************************************************************
*/



//find tile function
bool findtile (int tile)
{
    //check for tile selection validity
    if (tile < 0 || tile > d*d) //case is tile selection is invalid
    {
       
    return false;
    }
    
    //iterate over rows first
    for (int r = 0; r < d; r++)
    {
        //iterate over columns
        for (int c = 0; c < d; c++)
        {
            //when tile value is found
            if (board[r][c] == tile)
            {
                rslxn = r;
                cslxn = c;
            }
        }
    }
    return true;
}