/**
 * @file ex1.c
 * @author  jjherskow <jherskow@cs.huji.ac.il>
 * @date 6 Aug 2017
 *
 * @brief
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>

// -------------------------- const definitions -------------------------

#define LONG_DOUBLE_BUFFER 255
#define INT_BUFFER 16

const long double ALPHA =  0.012299;
const long double BETA =  1 - 0.012299;

const int IO_ERROR = 2;
const int NM_ERROR = 3;
const int TIME_ERROR = 4;
const int ARG_ERROR = 5;
const int FLOAT_ERROR = 6;


// -------------------------- global definitions ------------------------

long double time, differenceTime;
long int n, m;

// ------------------------------ functions -----------------------------
/**
 * @brief
 * @return
 */
long double calculateD1(long double x, long double y)
{
    long double term = powl((x-BETA), 2) + powl(y,2);
    return powl(term, 1.5);
}

/**
 * @brief
 * @return
 */
long double calculateD2(long double x, long double y)
{
    long double term = powl((x+ALPHA), 2) + powl(y,2);
    return powl(term, 1.5);
}

/**
 * @brief
 * @return
 */
long double calculateAx(long double d1, long double d2, long double x, long double velY)
{
    return x + 2*velY - BETA*((x+ALPHA)/d1) - ALPHA*((x-BETA)/d2);
}

/**
 * @brief
 * @return
 */
long double calculateAy(long double d1, long double d2, long double y, long double velX)
{
    return y - 2*velX - BETA*(y/d1) - ALPHA*(y/d2);
}

/**
 * @brief
 * @return
 */
long double forwardZ(long double *const z, long double *const velZ, long double alphaZ)
{
    *z = (*z) + (*velZ)*(differenceTime);
    *velZ = (*velZ) + (alphaZ)*(differenceTime);
    return 0;
}

/**
 * @brief
 */
void eulerSingleStep(long double *const x, long double *const y,
                     long double *const velX,long double *const velY)
{
    long double d1 = calculateD1(*x,*y);
    long double d2 = calculateD2(*x,*y);

    long double alphaX = calculateAx(d1, d2,*x,*y);
    long double alphaY = calculateAy(d1, d2,*x,*y);

    forwardZ(x, velX, alphaX);
    forwardZ(y, velY, alphaY);
}
/**
 * @brief
 */
void calculatePath(long double *const x, long double *const y,
                   long double *const velX,long double *const velY)
{
    long double differenceTime = time/n;
    for (int i = 1; i <= n; i++)
    {
        eulerSingleStep(x,y,velX,velY);
        if(i%(n/m) == 0) //todo check
        {
            //todo correct format?  change to file print
            printf("<%Lf>,<%Lf>,", *x, *y);
        }
    }
}

long double getLongDouble()
{
    long double num;

    // read input
    char buffer[LONG_DOUBLE_BUFFER];
    fgets(buffer, sizeof(buffer), stdin);

    // conversion
    char *checkBadIo = NULL;
    num = strtold(buffer, &checkBadIo);

    // error check
    if (checkBadIo != NULL)
    {
        sprintf(stderr,"Input Error:\nInvalid input for _long double_\n");
        exit(IO_ERROR);
    }
    return num;

}
long int getLongInt()
{
    long int num;

    // read input
    char buffer[INT_BUFFER];
    fgets(buffer, sizeof(buffer), stdin);

    // conversion
    char *checkBadIo = NULL;
    num = strtol(buffer, &checkBadIo, 10);

    // error check
    if (checkBadIo != NULL)
    {
        sprintf(stderr, "Input Error:\nInvalid input for _int_\n");
        exit(IO_ERROR);
    }

    return num;
}

int getInputFromUser(long double *const x, long double *const y,
                     long double *const velX,long double *const velY)
{
    printf("Enter initial pos x:\n");
    *x = getLongDouble();
    printf("Enter initial pos y:\n");
    *y = getLongDouble();

    printf("Enter initial vel x:\n");
    *velX = getLongDouble();
    printf("Enter initial vel y:\n");
    *velY = getLongDouble();

    printf("Enter num of steps to save:\n");
    n = getLongInt();
    printf("Enter num of steps:\n");
    m = getLongInt();

    printf("Enter total time T:\n");
    time = getLongDouble();
}

int getInputFromFile(long double *const x, long double *const y,
                     long double *const velX,long double *const velY,
                     char *filename)
{
    //todo check all (lengths and whatever) (split \n then comma) (check # of args)
    FILE* filePtr = fopen(filename, "r");

    char buffer[7 * LONG_DOUBLE_BUFFER];
    fgets(buffer, sizeof(buffer), filePtr);

    // todo fix this voodoo shit
    char *lineSplit[2] = strtok(buffer, "\n");
    char *longDoubles[4] = strtok(lineSplit[0], ",");
    char *ints[3] = strtok(lineSplit[1], ",");


}

void checkNM()
{
    if(n%m != 0)
    {
        sprintf(stderr,"Input Error:\nn must divide m!\n");
        exit(NM_ERROR);
    }
}

void checkTime()
{
    if(time <= 0)
    {
        sprintf(stderr,"Input Error:\nTime must be positive!\n");\
        exit(TIME_ERROR);
    }
}



void checkLongDouble(long double *const z)
{
    if(*z == INFINITY || *z == NAN)
    {
        sprintf(stderr,"Invalid number for coordinate / velocity\n");
        exit(FLOAT_ERROR);
    }
}

void checkLongDoubles(long double *const x, long double *const y,
                      long double *const velX,long double *const velY)
{
    checkLongDouble(x);
    checkLongDouble(y);
    checkLongDouble(velX);
    checkLongDouble(velY);
}



void checkInputs(long double *const x, long double *const y,
                 long double *const velX,long double *const velY)
{
    checkNM();
    checkTime();
    checkLongDoubles(x,y,velX,velY);
}

/**
 * @brief
 */
void main(int argc, char *argv[] )
{
    // allocate memory
    long double *const x = malloc(sizeof(long double));
    long double *const y = malloc(sizeof(long double));
    long double *const velX = malloc(sizeof(long double));
    long double *const velY = malloc(sizeof(long double));

    if(argc == 2)
    {
       getInputFromUser(x,y,velX,velY);
    }
    else if(argc == 3)
    {
        getInputFromFile(x,y,velX,velY, argv[1]);
    }
    else
    {
        sprintf(stderr,"Usage: ex1 [ [input file] output file ]\n");
        exit(ARG_ERROR);
    }

    //todo set output file

    // check number legality
    checkInputs(x,y,velX,velY);

    //run program
    calculatePath(x,y,velX,velY);

    //free memory
    free(x);
    free(y);
    free(velX);
    free(velY);

    // We're done here
    exit(0);
}

