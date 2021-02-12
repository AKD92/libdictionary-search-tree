

/************************************************************************************
    Program Interface for AVL Tree based Dictionary ADT
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef AVL_TREE_DATA_STRUCTURE_H
#define AVL_TREE_DATA_STRUCTURE_H






#define AVL_INSERTION               1
#define AVL_REMOVAL                 2




#include "bst.h"
#include "bst_internal.h"






/**********************************************************************************************/
/***********************************                       ************************************/
/***********************************    DATA STRUCTURES    ************************************/
/***********************************                       ************************************/
/**********************************************************************************************/


typedef BisTree AvlTree;







/**********************************************************************************************/
/***********************************                       ************************************/
/***********************************   PUBLIC INTERFACES   ************************************/
/***********************************                       ************************************/
/**********************************************************************************************/



#define     avl_init                bst_init

#define     avl_destroy             bst_destroy

#define     avl_size                bst_size

#define     avl_lookup              bst_lookup

#define     avl_exists              bst_exists



int avl_insert(AvlTree *pTree, const void *pKey, const void *pElem);


int avl_remove(AvlTree *pTree, const void *pKey, void **pRemovedKey, void **pRemovedElem);



#define     avl_reassign            bst_reassign


#define     avl_keys                bst_keys

#define     avl_elements            bst_elements

#define     avl_keys_elements       bst_keys_elements







/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************     SORTING ALGORITHMS    **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



/*
 *  Sorts the specified singly linked list in ascending order.
 *  This function is actually an alias of 'avl_treesort_asc'.
 *  The sorting algorithm is TreeSort.
 *  This algorithm is stable, means for equal elements this algorithm
 *  will retain the order in which those elements were found on the List.
 *  Time complexity is O(nlogn).
 *  This algorithm is out of place.
 *
 *  Parameter:
 *      list                :   Pointer to a singly linked list
 *      compare             :   Pointer to a function which will be used to compare
 *                              between the objects of the linked list
 *
 *  Returns
 *      0 for successful sorting
 *      -1 if parameters are invalid
*/
int avl_treesort(List *list, int (*compare) (const void *arg1, const void *arg2));





/*
 *  Sorts the specified doubly linked list in ascending order.
 *  This function is actually an alias of 'avl_treesort_asc_dl'.
 *  The sorting algorithm is TreeSort.
 *  This algorithm is stable, means for equal elements this algorithm
 *  will retain the order in which those elements were found on the List.
 *  Time complexity is O(nlogn).
 *  This algorithm is out of place.
 *
 *  Parameter:
 *      list                :   Pointer to a doubly linked list
 *      compare             :   Pointer to a function which will be used to compare
 *                              between the objects of the linked list
 *
 *  Returns
 *      0 for successful sorting
 *      -1 if parameters are invalid
*/
int avl_treesort_dl(DList *dlist, int (*compare) (const void *arg1, const void *arg2));





/*
 *  Sorts the specified singly linked list in ascending order.
 *  The sorting algorithm is TreeSort.
 *  This algorithm is stable, means for equal elements this algorithm
 *  will retain the order in which those elements were found on the List.
 *  Time complexity is O(nlogn).
 *  This algorithm is out of place.
 *
 *  Parameter:
 *      list                :   Pointer to a singly linked list
 *      compare             :   Pointer to a function which will be used to compare
 *                              between the objects of the linked list
 *
 *  Returns
 *      0 for successful sorting
 *      -1 if parameters are invalid
*/
int avl_treesort_asc(List *list, int (*compare) (const void *arg1, const void *arg2));





/*
 *  Sorts the specified singly linked list in descending order.
 *  The sorting algorithm is TreeSort.
 *  This algorithm is stable, means for equal elements this algorithm
 *  will retain the order in which those elements were found on the List.
 *  Time complexity is O(nlogn).
 *  This algorithm is out of place.
 *
 *  Parameter:
 *      list                :   Pointer to a singly linked list
 *      compare             :   Pointer to a function which will be used to compare
 *                              between the objects of the linked list
 *
 *  Returns
 *      0 for successful sorting
 *      -1 if parameters are invalid
*/
int avl_treesort_desc(List *list, int (*compare) (const void *arg1, const void *arg2));





/*
 *  Sorts the specified doubly linked list in ascending order.
 *  The sorting algorithm is TreeSort.
 *  This algorithm is stable, means for equal elements this algorithm
 *  will retain the order in which those elements were found on the List.
 *  Time complexity is O(nlogn).
 *  This algorithm is out of place.
 *
 *  Parameter:
 *      list                :   Pointer to a doubly linked list
 *      compare             :   Pointer to a function which will be used to compare
 *                              between the objects of the linked list
 *
 *  Returns
 *      0 for successful sorting
 *      -1 if parameters are invalid
*/
int avl_treesort_asc_dl(DList *dlist, int (*compare) (const void *arg1, const void *arg2));





/*
 *  Sorts the specified doubly linked list in descending order.
 *  The sorting algorithm is TreeSort.
 *  This algorithm is stable, means for equal elements this algorithm
 *  will retain the order in which those elements were found on the List.
 *  Time complexity is O(nlogn).
 *  This algorithm is out of place.
 *
 *  Parameter:
 *      list                :   Pointer to a doubly linked list
 *      compare             :   Pointer to a function which will be used to compare
 *                              between the objects of the linked list
 *
 *  Returns
 *      0 for successful sorting
 *      -1 if parameters are invalid
*/
int avl_treesort_desc_dl(DList *dlist, int (*compare) (const void *arg1, const void *arg2));






#endif


