

/************************************************************************************
    Program Interface for Binary Search Tree based Dictionary ADT
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H




#include <list.h>
#include <dlist.h>
#include <queue.h>







/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************      DATA STRUCTURES      **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



struct BNode_ {
    
    void *pKey;
    void *pElement;
    
    struct BNode_ *pParentNode;
    struct BNode_ *pLeftNode;
    struct BNode_ *pRightNode;
    
};
typedef struct BNode_ BNode;



struct BisTree_ {
    
    BNode *pRootNode;
    unsigned int size;
    
    int (*fpCompareKey) (const void *pKey1, const void *pKey2);
    void (*fpDestroyKey) (void *pKey);
    void (*fpDestroyData) (void *pData);
    
};
typedef struct BisTree_ BisTree;







/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************   INIT & DEST FUNCTIONS   **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



/*
 *  Initializes a BisTree
 *  Destruction functions are called only when the tree is being destroyed
 *
 *  Parameter:
 *      pTree               :   The binary search tree being initialized
 *      fpCompareKey        :   Comparison function for key objects
 *      fpDestroyKey        :   Destruction function for key objects
 *      fpDestroyData       :   Destruction function for optional data objects
 *
 *  Returns
 *      0 for successful initialization
 *      -1 for error
*/
int bst_init (BisTree *pTree, int (*fpCompareKey) (const void *k1, const void *k2),
                    void (*fpDestroyKey) (void *pKey), void (*fpDestroyData) (void *pData));




/*
 *  Destroyes a BisTree
 *  Destruction functions are called only when the tree is being destroyed
 *
 *  Parameter:
 *      pTree               :   The binary search tree being initialized
 *
 *  Returns
 *      Nothing
*/                  
void bst_destroy(BisTree *pTree);







/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************      QUERY FUNCTIONS      **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/




/*
 *  Query for the current number of entries (keys) on the BisTree
 *
 *  Parameter:
 *      pTree               :   The binary search tree being initialized
 *
 *  Returns
 *      an unsigned integer representing the current number of entries
*/
#define bst_size(pTree) ((pTree)->size)






/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************    SEARCHING FUNCTIONS    **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/




/*
 *  Search for a specific pKey entry in the specific BisTree dictionary.
 *  If the specified key is found, then the pElem will receive the pointer
 *  to the value element associated with the key.
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      pKey                :   Pointer to a key object for which the search will take place
 *      pElem               :   Pointer to a pointer which will receive the pointer
 *                              to the data element (optional)
 *
 *  Returns
 *      1 if the specified pKey is found
 *      0 if pKey does not exist on the pTree
 *      -1 if pTree or pKey is NULL
*/
int bst_lookup(const BisTree *pTree, const void *pKey, void **pElem);





/*
 *  Check to see if the specified key exists into the BisTree dictionary.
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      pKey                :   Pointer to a key object for which the search will take place
 *
 *  Returns
 *      1 if the specified pKey is found
 *      0 if pKey does not exist on the pTree
 *      -1 if pTree or pKey is NULL
*/
int bst_exists(const BisTree *pTree, const void *pKey);







/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************     MUTATION FUNCTIONS    **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



/*
 *  Inserts a pointer to a key and a pointer to its associated value data
 *  Into the specified BisTree dictionary
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      pKey                :   Pointer to a key object which is being inserted
 *      pElem               :   Pointer to the data object which is value object of pKey
 *
 *  Returns
 *      0 for successful insertion
 *      -1 if insertion was not successful
*/
int bst_insert(BisTree *pTree, const void *pKey, const void *pElem);





/*
 *  Replaces the associated value element for the specified key element.
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      pKey                :   Pointer to a key object which value data is being changed
 *      pElem               :   Pointer to the value element which is the new value for the key
 *
 *  Returns
 *      0 for successful replacement
 *      -1 otherwise
*/
int bst_reassign(BisTree *pTree, const void *pKey, const void *pElem);





/*
 *  Removes a key and its associated value data pointer from the specific BisTree
 *  Removed key and data objects are not de-allocated (freed) from memory
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      pKey                :   Pointer to a key object which will be used to search for the key
 *      pRemovedKey         :   Pointer to a pointer which will receive the pointer
 *                              to the removed key object if found (optional)
 *      pRemovedElem        :   Pointer to a pointer which will receive the pointer
 *                              to the removed value data object if found (optional)
 *
 *  Returns
 *      0 for successful removal
 *      -1 otherwise
*/
int bst_remove(BisTree *pTree, const void *pKey, void **pRemovedKey, void **pRemovedElem);







/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************     LISTING FUNCTIONS     **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



/*
 *  Fills up the specified linked list with all the key pointers
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      lstKeys             :   Pointer to a singly linked list which will receive
 *                              all the pointers to the key elements available
 *                              in the dictionary
 *
 *  Returns
 *      0 for successful
 *      -1 if pTree or lstKeys pointers are invalid
 *      -2 if pTree is empty
*/
int bst_keys(const BisTree *pTree, List *lstKeys);





/*
 *  Fills up the specified linked list with all the value data pointers.
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      lstElements         :   Pointer to a singly linked list which will receive
 *                              all the pointers to the value data objects available
 *                              in the dictionary
 *
 *  Returns
 *      0 for successful
 *      -1 if pTree or lstKeys pointers are invalid
 *      -2 if pTree is empty
*/
int bst_elements(const BisTree *pTree, List *lstElements);





/*
 *  Fills up the specified linked list with all the keys
 *  and their associated value data pointers.
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      lstKeys             :   Pointer to a singly linked list which will receive
 *                              all the pointers to the key objects available in the dictionary
 *      lstElements         :   Pointer to a singly linked list which will receive
 *                              all the pointers to the value data objects available
 *                              in the dictionary
 *
 *  Returns
 *      0 for successful
 *      -1 if pTree or lstKeys pointers are invalid
 *      -2 if pTree is empty
*/
int bst_keys_elements(const BisTree *pTree, List *lstKeys, List *lstElements);





#endif



