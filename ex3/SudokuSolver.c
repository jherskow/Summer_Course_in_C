/**
 * @file SudokuSolver.c
 * @author  jjherskow <jherskow@cs.huji.ac.il>
 * @date //todo
 *
 * @brief //todo
 */
// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include "SudokuTree.c"


// -------------------------- global definitions ------------------------
#define EPSILON 0.000001
#define LINE_BUFFER 0 //todo
#define FILE_FORMAT_ERROR 2
#define IO_ERROR 3

static int g_n;
static int g_sqrtN;

// ------------------------------ functions -----------------------------

//todo read file
//todo vreate board
//todo create tree
//todo find DFS

//todo - start at root. call get children to get list of children
//todo - maeke eval func - value is the location of the first zero (row*N+ col), with MAXINT if no zeroes.
//todo -


//todo func get next empty square
//todo func make array of legal numbers for a given square
//todo subfunc - remove row, remove set, remove square. - starts with 1-N and ends with legal places.
//todo func make new copy board with passed value at first empty square

/*
 * todo assumptions about squares on a board
 * Board size is N
 * Square root of N must be integer todo make func
 *
 * board is int[sqrtN][sqrtN] todo assign with dynamic? or make board sizes constant based (100)
 * row of element (x,y) is int[x][0 up to sqrtN]
 * col of element (x,y) is int[0 up to sqrtN][y]
 * box of element (x,y) is int[x floor of mod sqrtn  up to X ceil of mod sqrt n][floor of y mod sqrtn  up to ceil of x mod sqrt y]
 *
 *
 *
 *
 */



int getBoardFromFile()
{
    //todo
    return 1;
}

int initialiseSubPrograms(int n, Board board)
{
    //todo
    return 1;
}

int solve(int n, Board board)
{
    //todo
    return 1;
}



int IsNSquare()
{
    int intSqrt = (int) sqrt( (double) g_n);
    return (intSqrt*intSqrt == g_n);
}

/**
 * @brief Attempt to read an int from a string to the value of the given pointer.
 * @return 0 upon success, error code otherwise
 */
int makeInt(int *intPtr, char *strPtr)
{
    char *emptyString = "";

    // conversion
    char *checkBadIo = 0;
    *intPtr = (int) strtof(strPtr, &checkBadIo);

    // error check
    if (*checkBadIo != *emptyString)
    {
        return FILE_FORMAT_ERROR;
    }
    return 0;

}

/**
 * @brief gets a n-length Row
 * @return 0 upon success, error code otherwise
 */
int getRow(int *row[MAX_N], char *buffer)
{
    char *delim = ",\n";

    if (makeInt(row[0], strtok(buffer, delim)))
    {
        return IO_ERROR;
    }

    // scan each coordinate
    for (int j = 1; j < g_n; ++j)
    {
        if (makeInt(row[j], strtok(NULL, delim)))
        {
            return IO_ERROR;
        }
    }

    // make sure we have reached end of line
    if (strtok(NULL, delim) != NULL)
    {
        fprintf(stderr, "Format Error.\n");
        return FILE_FORMAT_ERROR;
    }
    return 0;
}

/**
 * @brief // todo
 * @return 0 upon success, error code otherwise
 */
int makeBoard(Board *board, FILE *inPtr)
{

    // read input
    char buffer[LINE_BUFFER];

    // for each practise vector (line)
    for (int i = 0; i < g_n; ++i)
    {

        //read the line into buffer
        fgets(buffer, LINE_BUFFER, inPtr);

        // read a line
        getRow((board[i]), buffer); // todo figure out

    }
    return 0;
}


/**
 * @brief todo
 * @return
 */
int main(int argc, char *argv[])
{
    //todo
}