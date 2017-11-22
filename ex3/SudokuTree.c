/**
 * @file SudokuTree.c
 * @author  jjherskow <jherskow@cs.huji.ac.il>
 * @date //todo
 *
 * @brief //todo
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "SudokuTree.h"


// -------------------------- global definitions ------------------------
static int g_n;


// ------------------------------ typedefs -----------------------------

/**
 * @brief //todo
 */
typedef int Board[MAX_N][MAX_N];

/**
 * @brief //todo
 */
typedef struct Node
{
    Board board;
    struct Node *nextSibling;
    struct Node *child;
} Node;


// ------------------------------ functions -----------------------------

void getNextEmptyCell(Node node, int *i, int *j/*for the result*/) //todo make func
{
    //todo
}

void returnLegalValuesList(Node node, int *i, int *j, int *valArray, int *numVals/*for the result*/)
{
    //todo make func
}

int getNodeChildren(Node parent, Node** children/*for the result*/) //todo make func
{
    // go to child & add it
    Node *nextChild = (parent.child);
    int i=0;
    // while nextSibling exists, add it as well
    for (; nextChild != NULL ; ++i)
    {
        children[i] = nextChild;
        nextChild = (children[i]->nextSibling);
    }
    assert(i<g_n); //todo??
    assert(i>=0); //todo??

    //todo only legal children
    //todo is legal number checker (iterates over row, col and square , if one of == X return 0, else 1)
    //todo legal values finder  runs legal number checker for all 0-N, returns linked list and length.
    // todo return a child for each, in linked list form, place head as child.

    return (unsigned int) i;
}

unsigned int getBoardVal(Board aBoard)
{
    //todo 1 IFF board full, zero otherwise
    for (int i = 0; i < g_n ; ++i)
    {
        for (int j = 0; j < g_n ; ++j)
        {
            if (aBoard[i][j] == 0 )
            {
                return 0;
            }
        }
    }
    return 1;

}

Node copyBoard(Board source, Board dest)
{
    for (int i = 0; i < g_n ; ++i)
    {
        for (int j = 0; j < g_n ; ++j)
        {
            dest[i][j] = source[i][j];
        }
    }

}

Node *boardToRoot(Board aBoard)
{
    Node *root = malloc(sizeof(Node)); //todo take care of allocation

    copyBoard(aBoard, root.board);

    return root;

}

unsigned int getNodeVal(Node aNode)
{
    return getBoardVal(Node.board); //todo make func
}

//todo check board - iterate over board, and mark x as # of zeroes.
// todo return value is filled spaces -  N minus X. Stop for value of N

void freeNode(Node aNode)  //todo make func takes Node, returns nothing
{
    Node *childList[MAX_N];
    getNodeChildren(aNode, childList);
    for (int i = 0; childList[i] != NULL ; ++i)
    {
        freeNode(*(childList[i]));
        childList[i] = NULL;
    }
    free(&aNode);
}

Node copyNode(Node node)
{
    //todo make func - takes *Node, returns Node
}

