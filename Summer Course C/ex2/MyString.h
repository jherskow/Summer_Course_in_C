/**
 * The header file for the countSubStr function.
 */


#ifndef COUNT_SUB_STR_H
#define COUNT_SUB_STR_H

#include <stdio.h>


/**
 * Counts the amount of str1 substrings that are equal to str2.
 * In case one (or two) of the strings is empty- returns 0.
 * @str1 - the string
 * @str2 -  the substring
 * @isCycic != 0 - search also for cyclic appearnce 
 * @return number appearance of str2 as substring of str1
 */
unsigned int countSubStr(const char *str1, const char *str2, int isCyclic);

#endif

