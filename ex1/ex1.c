/**
 * @file ex1.c
 * @author  jjherskow <jdoe@example.com>
 * @date 9 Sep 2014
 *
 * @brief
 *
 *
 * @section DESCRIPTION
 * //todo
 * Input  : hththththt
 * Process: hthththth
 * Output : hhthth
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// -------------------------- const definitions -------------------------

/**
 * @var long double
 * @brief
 */
const long double ALPHA =  0.012299;

/**
 * @var long double
 * @brief
 */
const long double BETA =  1 - 0.012299;

const long double ZERO =  0;

const int IO_ERROR =  2;
const int NM_ERROR =  3;
const int TIME_ERROR =  4;


// -------------------------- global definitions ------------------------

long double x, y , velX, velY, time, differenceTime;
int n, m;

// ------------------------------ functions -----------------------------
/**
 * @brief
 * @return
 */
long double calculateD1()
{
    long double term = powl((x-BETA), 2) + powl(y,2);
    return powl(term, 1.5);
}

/**
 * @brief
 * @return
 */
long double calculateD2()
{
    long double term = powl((x+ALPHA), 2) + powl(y,2);
    return powl(term, 1.5);
}

/**
 * @brief
 * @return
 */
long double calculateAx(long double d1, long double d2)
{
    return x + 2*velY - BETA*((x+ALPHA)/d1) - ALPHA*((x-BETA)/d2);
}

/**
 * @brief
 * @return
 */
long double calculateAy(long double d1, long double d2)
{
    return y - 2*velX - BETA*(y/d1) - ALPHA*(y/d2);
}

//long double calculateInitialVelocity(long double x, long double y,  long double vX,  long double vY,  long double time,
//                      long double steps, long double stepsToPrint)
//{
//    // todo
//    return 0;
//}

/**
 * @brief
 * @return
 */
long double forwardZ(long double* z, long double* velZ, long double alphaZ)
{
    *z = (*z) + (*velZ)*(differenceTime);
    *velZ = (*velZ) + (alphaZ)*(differenceTime);
    return 0;
}

/**
 * @brief
 */
void eulerSingleStep()
{
    long double d1 = calculateD1();
    long double d2 = calculateD2();

    long double alphaX = calculateAx(d1, d2);
    long double alphaY = calculateAy(d1, d2);

    forwardZ(&x, &velX, alphaX);
    forwardZ(&y, &velY, alphaY);
}
/**
 * @brief
 */
void calculatePath()
{
    long double differenceTime = time/n;
    for (int i = 1; i <= n; i++)
    {
        eulerSingleStep();
        if(i%(n/m))
        {
            //todo correct format?
            printf("<%Lf>,<%Lf>,", x, y);
        }
    }
}

long double getLongDouble()
{
    // todo get long double
    int length = sizeof(long double)/sizeof(char);

    // todo long double x = sscanf(,)

    // if error
    sprintf(stderr,"Input Error:\nInvalid input for _long double_");
    exit(IO_ERROR);

}
int getInt()
{
    // todo get int

   //todo long double x = str;

    // if error
    sprintf(stderr,"Input Error:\nInvalid input for _int_");
    exit(IO_ERROR);
}

int getInputFromUser()
{
    printf("Enter initial pos x:\n");
    x = getLongDouble();
    printf("Enter initial pos y:\n");
    y = getLongDouble();

    printf("Enter initial vel x:\n");
    velX = getLongDouble();
    printf("Enter initial vel y:\n");
    velY = getLongDouble();

    printf("Enter num of steps to save:\n");
    n = getInt();
    printf("Enter num of steps:\n");
    m = getInt();

    printf("Enter total time T:\n");
    time = getLongDouble();
}

int getInputFromFile()
{
    //todo
}

void checkNM()
{
    if(n%m != 0)
    {
        sprintf(stderr,"Input Error:\nn must divide m!");
        exit(NM_ERROR);
    }
}

void checkTime()
{
    if(time <= 0)
    {
        sprintf(stderr,"Input Error:\nTime must be positive!");
        exit(TIME_ERROR);
    }
}

int checkInputs()
{
    checkNM();
    checkTime();
}

