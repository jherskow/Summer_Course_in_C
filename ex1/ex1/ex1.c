/**
 * @file CodingStyleExampleC.c
 * @author  John Doe <jdoe@example.com>
 * @version 1.0
 * @date 9 Sep 2014
 *
 * @brief System to keep track of the cooking times.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The system keeps track of the cooking times.
 * Input  : Times to be measured.
 * Process: Summing times if needed, waiting for the correct time and
 *          notifying the user.
 * Output : Notification.
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
// ... rest of includes from the system
// ... all my includes

// -------------------------- const definitions -------------------------
/**
 * @def MAX_TEMPERATURE_CS 300
 * @brief A macro that sets the maximal temperature.
 */
#define MAX_TEMPERATURE_CS 300

/**
 * @var int NUM_HEAT_LEVELS
 * @brief Sets the number of heat levels.
 */
const int NUM_HEAT_LEVELS = 5;

// ------------------------------ functions -----------------------------
/**
 * @brief The main function. Actually, does nothing here.
 * @return 0, to tell the system the execution ended without errors.
 */
int main()
{
    return 0;
}

/**
 * @brief Perform time measurement.
 */
void performMeasurement()
{
    // Variable definition

    // Code section
}

/**
 * @brief Calculate sum of times and return it.
 * @param time1 First time
 * @param time2 Second time
 * @return Addition of the two times
 */
int addTwoTimes(const int time1, const int time2)
{
    // Local variables:
    double localVariable1; // In real programs there should be
    // a meaningful name for the variable.

    return (time1 + time2);
}

/**
 * @brief Just a long parameter list example.
 * @param a First arg.
 * @param b Second arg.
 * ...
 * @param j Last arg.
 */
void functionA(int a, int b, int c, int d, int e, double f, double g,
               double h, double i, double j)
{
    int aA = (2 + 3); // OK. It's ok not to provide spaces around [, (, {
    int bB = -2; // OK. Minus can be used to indicate minus value.
    for (a; b; c); // OK
    hello(a, b, c); // OK
    tt[c++]; // OK. Unary operator is used in the [ ( [
}