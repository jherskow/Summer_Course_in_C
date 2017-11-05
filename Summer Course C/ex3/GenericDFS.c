
/**
 * @file GenericDFS.c
 * @author  jjherskow <jherskow@cs.huji.ac.il>
 * @date //todo
 *
 * @brief //todo
 */


// ------------------------------ includes ------------------------------
#include <stdio.h>
#include "GenericDFS.h"

// -------------------------- global definitions ------------------------

// ------------------------------ functions -----------------------------

/**
 * @brief getBest This function returns the best valued node in a tree using
 * DFS algorithm.
 * @param head The head of the tree
 * @param getChildren A function that gets a node and a pointer to array of nodes.
 * the function allocates memory for an array of all the children of the node, and
 * returns the number of the children.
 * (the array might be initialized, but the function can't know how many children
 * the node has)
 * @param getVal A function that gets a node and returns its value, as int
 * @param freeNode A function that frees node from memory.
 * this function will be called for each Node returns by getChilds.
 * @param best The best available value for a node, when the function encounters
 * a node with that value it stops looking and returns it.
 * If the best value can't be determined, pass UINT_MAX (defined in limits.h)
 * for that param.
 * @param copy A function that do deep copy of Node.
 * @return The best valued node in the tree
 * In case of an error, or when all the nodes in the tree valued zero the returns
 * Node is NULL.
 * If some nodes shares the best valued, the function returns the first one it encounters.
 */
pNode getBest(pNode head, getNodeChildrenFunc getChildren,
             getNodeValFunc getVal, freeNodeFunc freeNode, copyNodeFunc copy, unsigned int best)
{
    if (getVal(head) == best)
    {
        return copy(head);
    }

    pNode *bestSoFar;
    pNode bestSubSearch;

    bestSoFar = &head;

    pNode *childList;
    pNode *subChildList;

    int numChildren = getChildren(head, &childList);

    int subChildren;

    for (int i = 0; i <numChildren ; ++i)
    {
        if (getVal(childList[i]) == best)
        {
            return copy(childList[i]);
        }

        if (getVal(bestSoFar) < getVal(childList[i]))
        {
            bestSoFar = copy(childList[i]);
        }

        subChildren = getChildren(childList[i],&subChildList );

        if (subChildren != 0)
        {
            bestSubSearch = getBest(childList[i], getChildren, getVal, freeNode, copy, best);

            if (getVal(bestSoFar) < getVal(bestSubSearch))
            {
                bestSoFar = copy(bestSubSearch);
            }
        }
    }

    if (getVal(bestSoFar) == 0)
    {
        return NULL;
    }

    return copy(bestSoFar);

}
