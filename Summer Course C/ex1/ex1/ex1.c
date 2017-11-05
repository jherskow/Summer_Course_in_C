/**
 * @file ex1.c
 * @author  jjherskow <jherskow@cs.huji.ac.il>
 * @date 6 Aug 2017
 *
 * @brief Creates an Arenstorf path based on input or a user file, and writes it to the given output file.
 */


// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>

// -------------------------- const definitions -------------------------

#define LONG_DOUBLE_BUFFER 128
#define INT_BUFFER 64

#define IO_ERROR 1;
#define FILE_FORMAT_ERROR  2;
#define NM_ERROR 3;
#define TIME_ERROR 4;
#define ARG_ERROR 5;
#define FLOAT_ERROR 6;

const long double ALPHA = 0.012299;
const long double BETA = 1 - 0.012299;


// -------------------------- global definitions ------------------------

// these variables remain unchanged
long double time, differenceTime;
long int n, m;

// ------------------------------ functions -----------------------------


/**
 * @return D1, as per the formula
 */
long double calculateD1(long double x, long double y)
{
    long double term = powl((x + ALPHA), 2l) + powl(y, 2l);
    return powl(term, 1.5l);
}

/**
 * @return D2, as per the formula
 */
long double calculateD2(long double x, long double y)
{
    long double term = powl((x - BETA), 2l) + powl(y, 2l);
    return powl(term, 1.5l);
}


/**
 * @return Ax, as per the formula
 */
long double calculateAx(long double d1, long double d2, long double x, long double velY)
{
    return x + 2.0 * velY - BETA * ((x + ALPHA) / d1) - ALPHA * ((x - BETA) / d2);
}

/**
 * @return Ay, as per the formula
 */
long double calculateAy(long double d1, long double d2, long double y, long double velX)
{
    return y - 2.0 * velX - BETA * (y / d1) - ALPHA * (y / d2);
}

/**
 * @brief Modify the coordinate to it's new location, using a forward Euler calculation.
 */
void forwardZ(long double *const z, long double *const velZ, long double alphaZ)
{
    *z = (*z) + (*velZ) * (differenceTime);
    *velZ = (*velZ) + (alphaZ) * (differenceTime);
}

/**
 * @brief Modify x and y by a single forward euler step, using the different formulae.
 */
void eulerSingleStep(long double *const x, long double *const y,
                     long double *const velX, long double *const velY)
{
    long double d1 = calculateD1(*x, *y);
    long double d2 = calculateD2(*x, *y);

    long double alphaX = calculateAx(d1, d2, *x, *velY);
    long double alphaY = calculateAy(d1, d2, *y, *velX);

    forwardZ(x, velX, alphaX);
    forwardZ(y, velY, alphaY);
}

/**
 * @brief Calculate the Arenstorf path, writing the desired steps as requested.
 *        Modify the values of the given coordinates and velocities at each step.
 */
void calculatePath(long double *const x, long double *const y,
                   long double *const velX, long double *const velY,
                   FILE *outPtr)
{
    long int stepCheck = n / m;
    eulerSingleStep(x, y, velX, velY);
    fprintf(outPtr, "%.3Le, %.3Le", *x, *y);
    for (long int i = 2; i <= n; i++)
    {
        eulerSingleStep(x, y, velX, velY);
        if (i % (stepCheck) == 0)
        {
            fprintf(outPtr, ", %.3Le, %.3Le", *x, *y);
        }
    }

    // add newline
    fprintf(outPtr, "\n");
}


/**
 * @brief Attmept to read a long double to the value of the given pointer.
 * @return 0 upon success, error code otherwise
 */
int getLongDouble(long double *ldPtr)
{
    // read input
    char buffer[LONG_DOUBLE_BUFFER];
    fgets(buffer, LONG_DOUBLE_BUFFER, stdin);

    // buffer overflow/underflow
    if (strchr(buffer, '\n') == NULL)
    {
        fprintf(stderr, "Input Error:\nBuffer over/underflow\n");
        return IO_ERROR;
    }

    // conversion
    char *checkBadIo = 0;
    *ldPtr = strtold(buffer, &checkBadIo);

    // error check
    if (*checkBadIo != '\n')
    {
        fprintf(stderr, "Input Error:\nInvalid input for _long double_\n");
        return IO_ERROR;
    }
    return 0;

}

/**
 * @brief Attmept to read a long int to the value of the given pointer.
 * @return 0 upon success, error code otherwise
 */
int getLongInt(long int *intPtr)
{

    // read input
    char buffer[INT_BUFFER];
    fgets(buffer, sizeof(buffer), stdin);

    // buffer overflow/underflow
    if (strchr(buffer, '\n') == NULL)
    {
        fprintf(stderr, "Input Error:\nBuffer over/underflow\n");
        return IO_ERROR;
    }

    // conversion
    char *checkBadIo = &buffer[0];
    *intPtr = strtol(buffer, &checkBadIo, 10);

    // error check
    if (*checkBadIo != '\n')
    {
        fprintf(stderr, "Input Error:\nInvalid input for _int_\n");
        return IO_ERROR;
    }

    return 0;
}

/**
 * @brief Prompt the user for the inputs.
 * @return 0 upon success, error code otherwise
 */
int getInputFromUser(long double *const x, long double *const y,
                     long double *const velX, long double *const velY)
{

    printf("Enter initial pos x:\n");
    if (getLongDouble(x))
    {
        return IO_ERROR;
    }

    printf("Enter initial pos y:\n");
    if (getLongDouble(y))
    {
        return IO_ERROR;
    }

    printf("Enter initial vel x:\n");
    if (getLongDouble(velX))
    {
        return IO_ERROR;
    }

    printf("Enter initial vel y:\n");
    if (getLongDouble(velY))
    {
        return IO_ERROR;
    }

    printf("Enter total time T:\n");
    if (getLongDouble(&time))
    {
        return IO_ERROR;
    }

    printf("Enter num of steps:\n");
    if (getLongInt(&n))
    {
        return IO_ERROR;
    }

    printf("Enter num of steps to save:\n");
    if (getLongInt(&m))
    {
        return IO_ERROR;
    }

    return 0;
}


/**
 * @brief Attmept to read a long double from a string to the value of the given pointer.
 * @return 0 upon success, error code otherwise
 */
int makeLongDouble(long double *ldPtr, char *tokPtr)
{
    char *emptyString = "";
    // conversion
    char *checkBadIo = 0;
    *ldPtr = strtold(tokPtr, &checkBadIo);

    // error check
    if (*checkBadIo != *emptyString)
    {
        fprintf(stderr, "Input Error:\nInvalid input for _long double_\n");
        return IO_ERROR;
    }
    return 0;
}

/**
 * @brief Attmept to read a long int from a string to the value of the given pointer.
 * @return 0 upon success, error code otherwise
 */
int makeLongInt(long int *intPtr, char *tokPtr)
{
    char *emptyString = "";

    // conversion
    char *checkBadIo = 0;
    *intPtr = (int) strtold(tokPtr, &checkBadIo);

    // error check
    if (*checkBadIo != *emptyString)
    {
        fprintf(stderr, "Input Error:\nInvalid input for _int_\n");
        return IO_ERROR;
    }
    return 0;

}


/**
 * @brief Attmept to parse an input file given in the specified format.
 * @return 0 upon success, error code otherwise
 */
int getInputFromFile(long double *const x, long double *const y,
                     long double *const velX, long double *const velY,
                     char *filename)
{
    FILE *inPtr = fopen(filename, "r");

    // read first line - 4 long doubles plus a few symbols
    char line1Buffer[5 * LONG_DOUBLE_BUFFER];
    fgets(line1Buffer, sizeof(line1Buffer), inPtr);

    // buffer overflow/underflow
    if (strchr(line1Buffer, '\n') == NULL)
    {
        fprintf(stderr, "Input Error:\nBuffer over/underflow\n");
        return IO_ERROR;
    }

    //split by commas
    char *delim = ",\n";

    // try to convert each to it's type, and place in the correct variable
    if (makeLongDouble(x, strtok(line1Buffer, delim)))
    {
        return IO_ERROR;
    }
    if (makeLongDouble(y, strtok(NULL, delim)))
    {
        return IO_ERROR;
    }
    if (makeLongDouble(velX, strtok(NULL, delim)))
    {
        return IO_ERROR;
    }
    if (makeLongDouble(velY, strtok(NULL, delim)))
    {
        return IO_ERROR;
    }

    // make sure we have reached end of line
    if (strtok(NULL, delim) != NULL)
    {
        fprintf(stderr, "Format Error:\nProblem in line 1.\n");
        return FILE_FORMAT_ERROR;
    }

    // read second line - 1 long double, 2 long ints, plus a few symbols
    char line2Buffer[3 * LONG_DOUBLE_BUFFER];
    fgets(line2Buffer, sizeof(line2Buffer), inPtr);

    // try to convert each to it's type, and place in the correct variable
    if (makeLongDouble(&time, strtok(line2Buffer, delim)))
    {
        return IO_ERROR;
    }
    if (makeLongInt(&n, strtok(NULL, delim)))
    {
        return IO_ERROR;
    }
    if (makeLongInt(&m, strtok(NULL, delim)))
    {
        return IO_ERROR;
    }

    // make sure we have reached end of line
    if (strtok(NULL, delim) != NULL)
    {
        fprintf(stderr, "Format Error:\nProblem in line 2.\n");
        return FILE_FORMAT_ERROR;
    }

    return 0;

}


/**
 * @brief Check n and m for logical input errors.
 * @return 0 upon success, error code otherwise
 */
int checkNM()
{
    if (n % m != 0)
    {
        fprintf(stderr, "Input Error:\nn must divide m!\n");
        return NM_ERROR;
    }
    if (n <= 0 || m <= 0)
    {
        fprintf(stderr, "Input Error:\nn and m must be strictly positive!\n");
        return NM_ERROR;
    }
    return 0;
}


/**
 * @brief Check time for logical input errors.
 * @return 0 upon success, error code otherwise
 */
int checkTime()
{
    if (time <= 0)
    {
        fprintf(stderr, "Input Error:\nTime must be strictly positive!\n");\
        return TIME_ERROR;
    }
    return 0;
}

/**
 * @brief Check a long double for logical input errors.
 * @return 0 upon success, error code otherwise
 */
int checkLongDouble(long double *const z)
{
    if (*z == INFINITY || *z == NAN)
    {
        fprintf(stderr, "Invalid number for coordinate / velocity\n");
        return FLOAT_ERROR;
    }
    return 0;
}


/**
 * @brief Check all coordinates and velocities for logical input errors.
 * @return 0 upon success, error code otherwise
 */
int checkLongDoubles(long double *const x, long double *const y,
                     long double *const velX, long double *const velY)
{
    int a = checkLongDouble(x);
    if (a)
    {
        return a;
    }
    a = checkLongDouble(y);
    if (a)
    {
        return a;
    }
    a = checkLongDouble(velX);
    if (a)
    {
        return a;
    }
    a = checkLongDouble(velY);
    return a;
}


/**
 * @brief Check for logical input errors.
 * @return 0 upon success, error code otherwise
 */
int checkInputs(long double *const x, long double *const y,
                long double *const velX, long double *const velY)
{
    int a = checkNM();
    if (a)
    {
        return a;
    }

    a = checkTime();
    if (a)
    {
        return a;
    }

    a = checkLongDoubles(x, y, velX, velY);

    return a;
}


/**
 * @brief Creates an Arenstorf path based on input or a user file, and writes it to the given output file.
 * @return 0 upon success, error code otherwise
 */
int main(int argc, char *argv[])
{
    // allocate memory
    long double *const x = malloc(sizeof(long double));
    long double *const y = malloc(sizeof(long double));
    long double *const velX = malloc(sizeof(long double));
    long double *const velY = malloc(sizeof(long double));

    // initialise variables
    *x = *y = *velX = *velY = 0.0;
    FILE *outPtr = NULL;
    int status = 0;
    char *filename = "output.txt";

    if (argc == 2)
    {
        status = getInputFromUser(x, y, velX, velY);
        filename = argv[1];
    }
    else if (argc == 3)
    {
        status = getInputFromFile(x, y, velX, velY, argv[1]);
        filename = argv[2];
    }
    else
    {
        fprintf(stderr, "Usage: ex1 [ [input file] output file ]\n");
        status = ARG_ERROR;
    }

    if (!status)
    {
        if ((outPtr = fopen(filename, "w")) == NULL)
        {
            fprintf(stderr, "Could not open output file.\n");
            status = IO_ERROR;
        }
    }

    if (!status)
    {
        // check number legality
        status = checkInputs(x, y, velX, velY);
        differenceTime = time / (long double) n;
    }


    if (!status)
    {
        //run program
        calculatePath(x, y, velX, velY, outPtr);
    }

    // close file
    fclose(outPtr);

    //free memory
    free(x);
    free(y);
    free(velX);
    free(velY);

    // We're done here
    return status;
}