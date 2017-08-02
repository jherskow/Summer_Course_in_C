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

// ------------------------------ functions -----------------------------
/**
 * @brief
 * @return
 */
long double calculateD1(long double x, long double x)
{
    long double term = powl((x-BETA), 2) + powl(y,2);
    return powl(term, 1.5);
}

/**
 * @brief
 * @return
 */
long double calculateD2(long double x, long double* y)
{
    long double term = powl((x+ALPHA), 2) + powl(y,2);
    return powl(term, 1.5);
}

/**
 * @brief
 * @return
 */
long double calculateAlphaX(long double x, long double vY, long double d1, long double d2)
{
    return x + 2*vY - BETA*((x+ALPHA)/d1) - ALPHA*((x-BETA)/d2);
}

/**
 * @brief
 * @return
 */
long double calculateAlphaY(long double y, long double vX, long double d1, long double d2)
{
    return y + 2*vX - BETA*(y/d1) - ALPHA*(y/d2);
}

long double calculateInitialVelocity(long double x, long double y,  long double vX,  long double vY,  long double time,
                      long double steps, long double stepsToPrint)
{
    // todo
    return 0;
}

long double calculateSingleStep(long double* x, long double* y,  long double* velX,  long double* velY,
                                long double differenceTime)
{
    long double d1 = calculateD1(x, y);
    long double d2 = calculateD2(x, y);

    long double alphaX = calculateAlphaX(x, velX, d1, d2);
    long double alphaY = calculateAlphaY(x, velY, d1, d2);

    forwardZ(x, velX, alphaX, differenceTime );
    forwardZ(y, velY, alphaY, differenceTime );
}

long double forwardZ(long double* z, long double* velZ, long double alphaZ, long double differenceTime)
{
    *z = (*z) + (*velZ)*(differenceTime);
    *velZ = (*velZ) + (alphaZ)*(differenceTime);
    return 0;
}

int main()
{
    // todo
    return 0;
}

