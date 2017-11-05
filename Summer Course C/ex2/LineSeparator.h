/**
 * @file LineSeperator.h
 * @author  jjherskow <jherskow@cs.huji.ac.il>
 * @date 13 Aug 2017
 *
 * @brief //todo
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>

// -------------------------- const definitions -------------------------

#define M_N_BUFFER 128
#define VECTOR_BUFFER 128

#define IO_ERROR 1
#define FILE_FORMAT_ERROR  2

const double RESOLUTION = 0.00001;

// -------------------------- global definitions ------------------------
int g_n, g_m;

// ------------------------- function definitions -----------------------


/**
 * @brief Uses linear separation to classify a list of vectors,
 *        based on an pre-classified input list.
 * @return 0 upon success, error code otherwise
 */
int main(int argc, char *argv[]);
