/**
 * @file MyString.c
 * @author  jjherskow <jherskow@cs.huji.ac.il>
 * @date 12 Aug 2017
 *
 * @brief
 */


// ------------------------------ includes ------------------------------
#include <stdio.h>
#include "MyString.h"

// ------------------------------ functions -----------------------------

/**
 * @brief returns the length of a string
 */
int strLen(const char *str)
{
    if (*str == '\0')
    {
        return 0;
    }
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

/**
 * @brief perfoms a cyclic search
 */
int cyclicSearch(const char *str1, const char *str2)
{
    int textLength = strLen(str1);
    int needleLength = strLen(str2);
    int maxSearch = 0;
    int needleCounter = 0;
    int result = 0;

    // if search term is shorter
    if (needleLength <= textLength)
    {
        // make search counter equal to the distance needed to check , including a possible wraparound.
        maxSearch = (textLength + needleLength - 1);
    }
    // if needle is longer,
    if (needleLength > textLength)
    {
        // make counter equal to the first multiple of text that is greater than needle
        maxSearch = textLength;
        for (int i = 1; maxSearch < needleLength; i++)
        {
            maxSearch = i * textLength;
        }
    }


    // iterate, looking at [i (mod) text length]
    for (int i = 0; i < maxSearch; ++i)
    {
        // if letters match
        if (str1[i % textLength] == str2[needleCounter])
        {
            //if finished match
            if (needleCounter == needleLength - 1)
            {
                needleCounter = 0;
                result++;
                i = i - needleLength + 1;
            }
                //if during match
            else
            {
                needleCounter++;
            }
        }
            // if letters don't match
        else
        {
            // return to letter after start of match
            i -= needleCounter;
            needleCounter = 0;
        }
    }
    return result;
}

/**
 * @brief perfoms a non-cyclic search
 */
int acyclicSearch(const char *str1, const char *str2)
{
    int textLength = strLen(str1);
    int needleLength = strLen(str2);
    int maxSearch = 0;
    int needleCounter = 0;
    int result = 0;

    // if needle is longer, return 0
    if (needleLength > textLength)
    {
        return 0;
    }

    // set Max counter to length of text
    // (if i passes this point, then no match can fit in remaining space)
    maxSearch = textLength;

    // check each start point
    for (int i = 0; i < maxSearch; ++i)
    {
        // if letters match
        if (str1[i] == str2[needleCounter])
        {
            //if finished match
            if (needleCounter == needleLength - 1)
            {
                needleCounter = 0;
                result++;
                i = i - needleLength + 1;
            }
                //if during match
            else
            {
                needleCounter++;
            }
        }
            // if letters don't match
        else
        {
            // return to letter after start of match
            i -= needleCounter;
            needleCounter = 0;
        }
    }
    return result;
}


/**
 * Counts the amount of str1 substrings that are equal to str2.
 * In case one (or two) of the strings is empty- returns 0.
 * @str1 - the string
 * @str2 -  the substring
 * @isCycic != 0 - search also for cyclic appearnce
 * @return number appearance of str2 as substring of str1
 */
unsigned int countSubStr(const char *str1, const char *str2, int isCyclic)
{
    // if either is empty string or NULL, return zero.
    if (str1 == NULL || str2 == NULL || *str1 == '\0' || *str2 == '\0')
    {
        return 0;
    }

    int result = 0;

    if (!isCyclic)
    {
        result = acyclicSearch(str1, str2);
    } else
    {
        result = cyclicSearch(str1, str2);
    }

    return (unsigned int) result;
}
