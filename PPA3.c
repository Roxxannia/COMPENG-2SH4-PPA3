#include <stdio.h>
#include "MacUILib.h"
#include "myStringLib.h" // This is your first custom C library

// [TODO] Import the required library for rand() and srand()
// [TODO] Import the required library for accessing the current time - for seeding random number generation

#include <stdlib.h>
#include <time.h>

// PREPROCESSOR DIRECTIVE CONSTANTS
// ================================
// For program-wide constants, define them here using #define.  Add as seen needed.

// [COPY AND PASTE FROM PPA2] Copy your additional preprocessor constants from PPA2 and paste them below
#define dimX 20
#define dimY 10
#define strLen 18

// EngPhys-iBioMed-25

// [TODO] Then, define more constants here as seen needed.
// GLOBAL VARIABLES
// ================================

int exitFlag; // Program Exiting Flag

// [COPY AND PASTE FROM PPA2] Copy your additional global from PPA2 and paste them below
char input;
int i, j;
int moveCnt = 0;
int win =0;
const char goalStr[strLen] = "EngPhys-iBioMed25";
char *mysteryStr;

struct objPos
{
    int x;
    int y;
    char symbol;
};

struct objPos player = {10, 5, '@'};

struct objPos *itemBin;

char gameBoard[dimY][dimX];

enum direction
{
    STOP,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
enum direction dirMode;

// [TODO] Declare More Global Variables as seen needed

// [TODO] Declare Global Pointers as seen needed / instructed in the manual.

// FUNCTION PROTOTYPES
// ================================
// Declare function prototypes here, so that we can organize the function implementation after the main function for code readability.

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// [TODO] In PPA3, you will need to implement this function to generate random items on the game board
//        to set the stage for the Scavenger Hunter game.
// list[]       The pointer to the Item Bin
// listSize     The size of the Item Bin (5 by default)
// playerPos    The pointer to the Player Object, read only.
// xRange       The maximum range for x-coordinate generation (probably the x-dimension of the gameboard?)
// yRange       The maximum range for y-coordinate generation (probably the y-dimension of the gameboard?)
// str          The pointer to the start of the Goal String (to choose the random characters from)
void GenerateItems(struct objPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char *str);

// MAIN PROGRAM
// ===============================
int main(void)
{

    Initialize();

    while (!exitFlag)
    {
        GetInput();

        RunLogic();

        DrawScreen();

        LoopDelay();
    }

    CleanUp();
}

// INITIALIZATION ROUTINE
// ===============================
void Initialize(void)
{
    MacUILib_init();

    MacUILib_clearScreen();

    // [COPY AND PASTE FROM PPA2] Copy your initialization routine from PPA2 and paste them below
    input = 0;
    dirMode = STOP;
    // [TODO] Initialize any global variables as required.
    exitFlag = 0; // 0 - do not exit, non-zero - exit the program

    // [TODO] Allocated heap memory for on-demand variables as required.  Initialize them as required.
    mysteryStr = (char *)malloc(strLen * sizeof(char));
    itemBin = (struct objPos*)malloc(5 * sizeof(struct objPos));

    // [TODO] Seed the random integer generation function with current time.
    srand(time(NULL));

    // [TODO] Generate the initial random items on the game board at the start of the game.
    // gameStart
    GenerateItems(itemBin, 5, &player, dimX, dimY, goalStr);

    for(i = 0; i<strLen-1; i++)
    {
        mysteryStr[i] = '?';
    }
    mysteryStr[i] = '\0';
}

// INPUT COLLECTION ROUTINE
// ===============================
void GetInput(void)
{

    // Asynchronous Input - non blocking character read-in

    // [COPY AND PASTE FROM PPA2] Copy your input collection routine from PPA2 and paste them below
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }

    // [TODO] Though optional for PPA3, you may insert any additional logic for input processing.
}

// MAIN LOGIC ROUTINE
// ===============================
void RunLogic(void)
{
    // [COPY AND PASTE FROM PPA2] Copy your main logic routine from PPA2 and paste them below

    if (input != 0) // if not null character
    {

        switch (dirMode)
        {
            case STOP:
                if (input == ' ')
                    exitFlag = 1;
                else if (input == 'W' || input == 'w')
                    dirMode = UP;                      
                else if (input == 'S' || input == 's')
                    dirMode = DOWN;
                else if (input == 'A' || input == 'a')
                    dirMode = LEFT;
                else if (input == 'D' || input == 'd')
                    dirMode = RIGHT;
                break;

            case UP:
                if (input == 'A' || input == 'a')
                    dirMode = LEFT;
                else if (input == 'D' || input == 'd')
                    dirMode = RIGHT;
                else if (input == ' ')
                    exitFlag = 1;
                    // break;
                break;

            case DOWN:
                if (input == 'A' || input == 'a')
                    dirMode = LEFT;
                else if (input == 'D' || input == 'd')
                    dirMode = RIGHT;
                else if (input == ' ')
                    exitFlag = 1;
                    // break;
                break;

            case LEFT:
                if (input == 'w' || input == 'W')
                    dirMode = UP;
                else if (input == 'S' || input == 's')
                    dirMode = DOWN;
                else if (input == ' ')
                    exitFlag = 1;
                    // break;
                    
                break;

            case RIGHT:
                if (input == 'w' || input == 'W')
                    dirMode = UP;
                else if (input == 'S' || input == 's')
                    dirMode = DOWN;
                else if (input == ' ')
                    exitFlag = 1;
                    // break;

                break;

            default:
                break;
        }
        input = 0;
    }
    else 
    {
        switch (dirMode)
        {        
            case UP:

                if (player.y <= 1)
                {
                    player.y = dimY - 1;
                }
                player.y--;

                break;

            case DOWN:

                if (player.y >= dimY - 2)
                {
                    player.y = 0;
                }
                player.y++;

                break;

            case LEFT:
                    
                if (player.x <= 1)
                {
                    player.x = dimX - 1;
                }
                player.x--;

                break;

            case RIGHT:

                if (player.x >= dimX - 2)
                {
                    player.x = 0;
                }
                player.x++;

                break;

            default:
                break;
        }
    }

    if (dirMode != STOP)
    {
        moveCnt++;
    }

    // [TODO]   Implement the Object Collision logic here
    //
    //      Simple Collision Algorithm
    //      1. Go through all items on board and check their (x,y) against the player object x and y.
    //      2. If a match is found, use the ASCII symbol of the collided character, and
    //         find all the occurrences of this ASCII symbol in the Goal String
    //      3. For every occurrence, reveal its ASCII character at the corresponding location in the
    //         Collected String
    //      4. Then, determine whether the game winning condition is met.
    
    for (i = 0; i<5; i++)
    {
        
        if (player.x == itemBin[i].x && player.y == itemBin[i].y)
        {
            for(j = 0; j<strLen-1; j++)
            {
                if(goalStr[j] == itemBin[i].symbol)
                {
                    mysteryStr[j] = goalStr[j];
                }
            }


            mysteryStr[j] ='\0';
            //need to update mystery string
            //update corresponding index
            
            //and then do game winning logic
            GenerateItems(itemBin, 5, &player, dimX, dimY, goalStr);
            break;
        }
        
    }
    
    //Game winning logic

    if(my_strcmp(goalStr, mysteryStr) == 1)
    {
        dirMode = STOP;
        exitFlag = 1;
        win = 1;
    }
    

    // [TODO]   Implement Game Winning Check logic here
    //
    //      Game Winning Check Algorithm
    //      1. Check if the contents of the Collected String exactly matches that of the Goal String.
    //         YOU MUST USE YOUR OWN my_strcmp() function from Lab 3.
    //      2. If matched, end the game.
    //      3. Otherwise, discard the current items on the game board, and
    //         generate a new set of random items on the board.  Game continues.

}

// DRAW ROUTINE
// ===============================
void DrawScreen(void)
{

    // [COPY AND PASTE FROM PPA2] Copy your draw logic routine from PPA2 and paste them below
    MacUILib_clearScreen();

    // dimy is rows; dimx is columns
    for (i = 0; i < dimY; i++) // rows
    {
        for (j = 0; j < dimX; j++) // columns
        {
            if (i == player.y && j == player.x)
            {
                gameBoard[i][j] = player.symbol;
            }
            else if (i == 0 || i == dimY - 1 ||j == 0 || j == dimX - 1)
            {
                gameBoard[i][j] = '#';
            }
            else if (i == itemBin[0].y && j == itemBin[0].x)
            {
                gameBoard[i][j] = itemBin[0].symbol;
            }
            else if (i == itemBin[1].y && j == itemBin[1].x)
            {
                gameBoard[i][j] = itemBin[1].symbol;
            }
            else if (i == itemBin[2].y && j == itemBin[2].x)
            {
                gameBoard[i][j] = itemBin[2].symbol;
            }
            else if (i == itemBin[3].y && j == itemBin[3].x)
            {
                gameBoard[i][j] = itemBin[3].symbol;
            }
            else if (i == itemBin[4].y && j == itemBin[4].x)
            {
                gameBoard[i][j] = itemBin[4].symbol;
            }
            else
            {
                gameBoard[i][j] = ' ';
            }
            MacUILib_printf("%c", gameBoard[i][j]);
        }
        MacUILib_printf("\n");
    }

    // [TODO]   Insert somewhere in the draw routine to draw the randomly generated items on the board.

    // [TODO]   Display the "Mystery String" contents at the bottom of the game board
    //          To help players keep track of their game progress.
    MacUILib_printf("Mystery String: %s\n", mysteryStr);
    // MacUILib_printf("%s\n", goalStr);

    // MacUILib_printf("Myster String: %s\n", *mysteryStr);
    MacUILib_printf("Player Move Count %d\n", moveCnt);
    MacUILib_printf("Press spacebar to exit the game!\n");
}

// DELAY ROUTINE
// ===============================
void LoopDelay(void)
{
    MacUILib_Delay(100000); // 0.1s delay
}

// TEAR-DOWN ROUTINE
// ===============================
void CleanUp(void)
{
    // [TODO]   To prevent memory leak, free() any allocated heap memory here
    //          Based on the PPA3 requirements, you need to at least deallocate one heap variable here.
    free(mysteryStr);
    free(itemBin);

    // Insert any additional end-game actions here.
    if(win == 1)
    {
        MacUILib_clearScreen();
        MacUILib_printf("Congratulations, you completed the scavenger hunt!\n");
        MacUILib_printf("The mystery string is: %s", goalStr);
        MacUILib_uninit();
    }
    else 
    {
        MacUILib_uninit();
    }

    
}

// The Item Generation Routine
////////////////////////////////////
void GenerateItems(struct objPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char *str)
{
    // This is possibly one of the most conceptually challenging function in all PPAs
    // Once you've mastered this one, you are ready to take on the 2SH4 course project!

    // Random Non-Repeating Item Generation Algorithm
    ////////////////////////////////////////////////////

    // Use random number generator function, rand(), to generate a random x-y coordinate and a random choice of character from the Goal String as the ASCII character symbol.
    //      The x and y coordinate range should fall within the xRange and yRange limits, which should be the x- and y-dimension of the board size.
    // This will then be a candidate of the randomly generated Item to be placed on the game board.

    // In order to make sure this candidate is validated, it needs to meet both criteria below:
    //  1. Its coordinate and symbol has not been previously generated (no repeating item)
    //  2. Its coordinate does not overlap the Player's position
    // Thus, for every generated item candidate, check whether its x-y coordinate and symbol has previously generated.
    //  Also, check if it overlaps the player position
    //      If yes, discard this candidate and regenerate a new one
    //      If no, this candidate is validated.  Add it to the input list[]

    // There are many efficient ways to do this question
    //  We will take a deep dive into some methods in 2SI.

    int tempx, tempy;
    char tempc;
    int flag;

    i = 0;

    while(i<listSize)
    {
        // num = (rand() % (upper – lower + 1)) + lower 
        // [1,19], [1,9]
        if (i <2)
        {
            tempx  = rand() % ((xRange-2) - 1+1) + 1;
            tempy = rand() % ((yRange-2) - 1+1) + 1;
            tempc = str[rand() % (my_strlen(str))];

            for (j = 0; j <i; j++)
            {
                if ((itemBin[j].x == tempx && itemBin[j].y == tempy) )
                {
                    flag = 1;
                    break;
                }
                else if (playerPos->x == tempx && playerPos->y == tempy)
                {
                    flag = 1;
                    break;
                }
                else 
                {
                    if (itemBin[j].symbol == tempc)
                    {
                        flag = 1;
                        break;
                    }
                    flag = 0;
                }
                
            }

            if (flag != 1)
            {
                itemBin[i].x = tempx;
                itemBin[i].y = tempy;
                itemBin[i].symbol = tempc;
                i++;
            }
        }

        else 
        {
            tempx  = rand() % ((xRange-2) - 1+1) + 1;
            tempy = rand() % ((yRange-2) - 1+1) + 1;
            //ASCII table [33,126] (int val of ascii characters)
            //Excluded space character
            tempc = rand() % (126-33+1) + 33;

            for (j = 0; j <i; j++)
            {
                if ((itemBin[j].x == tempx && itemBin[j].y == tempy) )
                {
                    flag = 1;
                    break;
                }
                else if (playerPos->x == tempx && playerPos->y == tempy)
                {
                    flag = 1;
                    break;
                }
                else 
                {
                    //35 --> #
                    if (itemBin[j].symbol == tempc || playerPos->symbol == tempc || tempc == 35)
                    {
                        flag = 1;
                        break;
                    }
                    flag = 0;
                }
                
            }

            if (flag != 1)
            {
                itemBin[i].x = tempx;
                itemBin[i].y = tempy;
                itemBin[i].symbol = tempc;
                i++;
            }
        }
        
    }
}






    // itemBin[0].x =  rand() % (xRange - 1) + 1;
    // itemBin[0].y = rand() % (yRange - 1) + 1;
    // itemBin[0].symbol = str[rand() % (my_strlen(str)-1)];


    // for (i = 1; i< listSize;i++)
    // {
        
    //     do 
    //     {
    //         tempx  = rand() % (xRange - 1) + 1;
    //         tempy = rand() % (yRange - 1) + 1;
    //     }while ((tempx == playerPos->x && tempy == playerPos->y) || (tempx == itemBin[i-1].x && tempy == itemBin[i-1].y));

    //     itemBin[i].x = tempx;
    //     itemBin[i].y = tempy;

    //     do{
    //         tempc = str[rand() % (my_strlen(str)-1)];
    //     }while (tempc == itemBin[i-1].symbol);

    //     itemBin[i].symbol = tempc;
               
    // }



// GenerateItems(itemBin, 5, &player, dimX, dimY, goalStr);