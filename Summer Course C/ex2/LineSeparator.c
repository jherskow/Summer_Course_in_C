/**
 * @file Lineseperator.c
 * @author  jjherskow <jherskow@cs.huji.ac.il>
 * @date 12 Aug 2017
 *
 * @brief Sorts vectors using a linear separation algorithm
 */


// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <stdlib.h>
#include "LineSeparator.h"

// -------------------------- global definitions ------------------------
int g_n, g_m;

// ------------------------------ functions -----------------------------

/**
 * @brief Represents a vector of 0 < dim <= 400
 */
typedef struct
{
    double cord[400];
} vector;

/**
 * @return the scalar product of u and v
 */
double dotProduct(vector *u, vector *v)
{
    double result = 0;

    for (int i = 0; i < g_n; ++i)
    {
        result += u->cord[i] * v->cord[i];
    }

    return result;
}

/**
 * @return 1 iff <u*v> > 0, -1 otherwise
 */
int calculateTag(vector *u, vector *v)
{
    double dotP = dotProduct(u, v);
    if (dotP < RESOLUTION)
    {
        return -1;
    }
    return 1;
}

/**
 * @brief multiplies a vector by a scalar
 */
void scalarize(vector *u, double scalar)
{
    for (int i = 0; i < g_n; ++i)
    {
        u->cord[i] = u->cord[i] * scalar;
    }
}

/**
 * @return adds vector v to u
 */
void addVtoU(vector *u, vector *v)
{
    for (int i = 0; i < g_n; ++i)
    {
        u->cord[i] += v->cord[i];
    }
}

/**
 * @brief initializes a vector's coordinates to zero
 */
void zeroize(vector *u)
{
    for (int i = 0; i < g_n; ++i)
    {
        u->cord[i] = 0;
    }
}

/**
 * @brief Attempt to read a double from a string to the value of the given pointer.
 * @return 0 upon success, error code otherwise
 */
int makeDouble(double *doublePtr, char *strPtr)
{
    char *emptyString = "";

    // conversion
    char *checkBadIo = 0;
    *doublePtr = strtod(strPtr, &checkBadIo);

    // error check
    if (*checkBadIo != *emptyString)
    {
        return FILE_FORMAT_ERROR;
    }
    return 0;
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
 * @brief gets a n-dimension vector, and a 1/-1 tag
 * @return 0 upon success, error code otherwise
 */
int getPractiseVector(vector *v, int *givenTag, char *buffer)
{
    char *delim = ",\n";

    if (makeDouble(&v->cord[0], strtok(buffer, delim)))
    {
        return IO_ERROR;
    }

    // scan each coordinate
    for (int j = 1; j < g_n; ++j)
    {
        if (makeDouble(&v->cord[j], strtok(NULL, delim)))
        {
            return IO_ERROR;
        }
    }

    // scan the tag
    if (makeInt(givenTag, strtok(NULL, delim)))
    {
        return IO_ERROR;
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
 * @brief gets a n-dimension vector
 * @return 0 upon success, error code otherwise
 */
int getRegularVector(vector *v, char *buffer)
{
    char *delim = ",\n";

    if (makeDouble(&v->cord[0], strtok(buffer, delim)))
    {
        return IO_ERROR;
    }

    // scan each coordinate
    for (int j = 1; j < g_n; ++j)
    {
        if (makeDouble(&v->cord[j], strtok(NULL, delim)))
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
 * @brief // reads the dimension, and # of practise inputs
 * @return 0 upon success, error code otherwise
 */
int readMN(FILE *inPtr)
{
    // read input
    char buffer[M_N_BUFFER];

    // get n
    fgets(buffer, M_N_BUFFER, inPtr);
    makeInt(&g_n, buffer);
    assert(g_n > 0);

    // get m
    fgets(buffer, M_N_BUFFER, inPtr);
    makeInt(&g_m, buffer);
    assert(g_m > 0);

    return 0;
}

/**
 * @brief creates te vector wBar - an orthogonal vector to the separator hyperplane.
 * @return 0 upon success, error code otherwise
 */
int makeSeparator(vector *wBar, FILE *inPtr)
{
    //initialise wBar to zero
    zeroize(wBar);

    // read input
    char buffer[VECTOR_BUFFER];
    int givenTag;
    vector v;

    // for each practise vector (line)
    for (int i = 0; i < g_m; ++i)
    {

        //read the line into buffer
        fgets(buffer, VECTOR_BUFFER, inPtr);

        // get a practise vector, and tag, from the line
        getPractiseVector(&v, &givenTag, buffer);

        // adjust W-bar as per the formula
        if (calculateTag(wBar, &v) != givenTag)
        {
            scalarize(&v, givenTag);
            addVtoU(wBar, &v);
        }

    }
    return 0;
}

/**
 * @brief reads an arbitrary number of vecots from the input file, and prints their classification.
 * @return 0 upon success, error code otherwise
 */
int classifyVectors(vector *v, vector *wBar, FILE *inPtr)
{
    // read input
    char buffer[VECTOR_BUFFER];
    //int tag;

    // for each vector (line)
    while (fgets(buffer, VECTOR_BUFFER, inPtr) != NULL)
    {
        getRegularVector(v, buffer);

        // compute classification and print
        printf("%d\n", calculateTag(wBar, v));
    }
    return 0;
}


/**
 * @brief Uses linear separation to classify a list of vectors,
 *        based on an pre-classified input list.
 * @return 0 upon success, error code otherwise
 */
int main(int argc, char *argv[])
{
    int wasError = 0;

    if (argc != 2)
    {
        printf("Usage: LineSeparator inputFilename\n");
        return 0;
    }

    //open file
    FILE *inPtr = fopen(argv[1], "r");

    if (inPtr == NULL)
    {
        wasError = IO_ERROR;
    }

    if (!wasError)
    {
        //get dimension and practise input size
        wasError = readMN(inPtr);
    }

    vector wBar;

    //iterate over test input and create wBar (the separator)
    if (!wasError)
    {
        wasError = makeSeparator(&wBar, inPtr);
    }

    vector v;

    //iterate over rest input, and (give / print?) correct result
    if (!wasError)
    {
        wasError = classifyVectors(&v, &wBar, inPtr);
    }

    //close file
    fclose(inPtr);

    // We're done here.
    return wasError;
}
// shockingly, this took me half as many lines as ex1 :)