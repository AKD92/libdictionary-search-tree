

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





/*
 *  Query for the root BNode object of the BisTree
 *
 *  Parameter:
 *      pTree               :   The binary search tree being initialized
 *
 *  Returns
 *      Pointer to a BNode structure which is the root of the tree
 *      0 if pTree is 0
*/
BNode * bst_root(const BisTree *pTree);





/*
 *  Query for the parent BNode object of the BisTree
 *
 *  Parameter:
 *      pNode               :   The child BNode object
 *
 *  Returns
 *      Pointer to a BNode structure which is the parent
 *      0 if pNode is 0
*/
BNode * bst_parent(const BNode *pNode);





/*
 *  Query for the left child of the specified BNode object
 *
 *  Parameter:
 *      pNode               :   The parent BNode object
 *
 *  Returns
 *      Pointer to a BNode structure which is the left child
 *      0 if pNode is 0
*/
BNode * bst_leftChild(const BNode *pNode);





/*
 *  Query for the right child of the specified BNode object
 *
 *  Parameter:
 *      pNode               :   The parent BNode object
 *
 *  Returns
 *      Pointer to a BNode structure which is the right child
 *      0 if pNode is 0
*/
BNode * bst_rightChild(const BNode *pNode);





/*
 *  Query for the sibling BNode of the specified BNode object
 *
 *  Parameter:
 *      pNode               :   Pointer to a BNode object which has a sibling
 *
 *  Returns
 *      Pointer to a BNode structure which is the sibling
 *      0 if pNode has no sibling
*/
BNode * bst_sibling(const BNode *pNode);





/*
 *  Query to know the specified BNode object is an External node or not
 *
 *  Parameter:
 *      pNode               :   Pointer to a BNode object
 *
 *  Returns
 *      1 if the specified BNode is an external node
 *      0 otherwise
*/
int bst_isExternal(const BNode *pNode);





/*
 *  Query to know the specified BNode object is an Internal node or not
 *
 *  Parameter:
 *      pNode               :   Pointer to a BNode object
 *
 *  Returns
 *      1 if the specified BNode is an internal node
 *      0 otherwise
*/
int bst_isInternal(const BNode *pNode);





/*
 *  Query to know the specified BNode object is the root BNode object
 *  Of the specified BisTree
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      pNode               :   Pointer to a BNode object
 *
 *  Returns
 *      1 if the specified pNode is the root node of pTree
 *      0 otherwise
*/
int bst_isRoot(const BisTree *pTree, const BNode *pNode);





/*
 *  Query to know the depth of the specified BNode object
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      pNode               :   Pointer to a BNode object
 *
 *  Returns
 *      an unsigned integer representing the depth of the specified pNode
 *      0 if pTree or pNode is 0 (NULL)
*/
unsigned int bst_depth(const BisTree *pTree, const BNode *pNode);





/*
 *  Query to know the height value of the specified BNode object
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      pNode               :   Pointer to a BNode object
 *
 *  Returns
 *      an unsigned integer representing the height value of the specified BNode
 *      0 if pTree or pNode is not valid objects
*/
unsigned int bst_height(const BisTree *pTree, const BNode *pNode);





/*
 *  Query to know the specified pParent BNode is an ancestor
 *  Of the specified pChild BNode in the specified pTree BisTree
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      pParent             :   Pointer to a BNode object which might be an ancestor of pChild
 *      pChild              :   Pointer to a BNode object
 *
 *  Returns
 *      1 if pParent is an ancestor of pChild
 *      0 otherwise
*/
int bst_isAncestor(const BisTree *pTree, const BNode *pParent, const BNode *pChild);







/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************    TRAVERSAL FUNCTIONS    **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



/*
 *  Enqueues pointers of each BNode object to the queue "qPreorder"
 *  On "pre-order" fashion
 *  BNodes enqueued in the "qPreorder" includes all nodes (external + internal)
 *
 *  Parameter:
 *      pStartNode          :   Pointer to a BNode from which the algorithm
 *                              will start traversing
 *      qPreorder           :   Pointer to a Queue which will receive pointers of
 *                              all the traversed BNode objects
 *
 *  Returns
 *      0 for successful traversal
 *      -1 otherwise
*/
int bst_preOrder(BNode *pStartNode, Queue *qPreorder);





/*
 *  Enqueues pointers of each BNode object to the queue "qInorder"
 *  On "in-order" fashion
 *  BNodes enqueued in the "qInorder" includes all nodes (external + internal)
 *
 *  Parameter:
 *      pStartNode          :   Pointer to a BNode from which the algorithm
 *                              will start traversing
 *      qInorder            :   Pointer to a Queue which will receive pointers of
 *                              all the traversed BNode objects
 *
 *  Returns
 *      0 for successful traversal
 *      -1 otherwise
*/
int bst_inOrder(BNode *pStartNode, Queue *qInorder);




/*
 *  Enqueues pointers of each BNode object to the queue "qPostorder"
 *  On "post-order" fashion
 *  BNodes enqueued in the "qPostorder" includes all nodes (external + internal)
 *
 *  Parameter:
 *      pStartNode          :   Pointer to a BNode from which the algorithm
 *                              will start traversing
 *      qPostorder          :   Pointer to a Queue which will receive pointers of
 *                              all the traversed BNode objects
 *
 *  Returns
 *      0 for successful traversal
 *      -1 otherwise
*/
int bst_postOrder(BNode *pStartNode, Queue *qPostorder);





/*
 *  Enqueues pointers of each BNode object to the queue "qLRorder"
 *  On "level-order Left to Right" fashion
 *  BNodes enqueued in the "qLRorder" includes all nodes (external + internal)
 *
 *  Parameter:
 *      pStartNode          :   Pointer to a BNode from which the algorithm
 *                              will start traversing
 *      qLRorder            :   Pointer to a Queue which will receive pointers of
 *                              all the traversed BNode objects
 *
 *  Returns
 *      0 for successful traversal
 *      -1 otherwise
*/
int bst_levelOrderLR(BNode *pStartNode, Queue *qLRorder);





/*
 *  Enqueues pointers of each BNode object to the queue "qRLorder"
 *  On "level-order Right to Left" fashion
 *  BNodes enqueued in the "qRLorder" includes all nodes (external + internal)
 *
 *  Parameter:
 *      pStartNode          :   Pointer to a BNode from which the algorithm
 *                              will start traversing
 *      qRLorder            :   Pointer to a Queue which will receive pointers of
 *                              all the traversed BNode objects
 *
 *  Returns
 *      0 for successful traversal
 *      -1 otherwise
*/
int bst_levelOrderRL(BNode *pStartNode, Queue *qRLorder);





/*
 *  Removes pointer to the BNode objects which are not internal (external)
 *  From the specified Queue
 *  This function only removes pointer to external BNode objects from the queue
 *  It does not de-allocate or free those BNode object from memory
 *
 *  Parameter:
 *      qNodes          :   Pointer to a Queue
 *
 *  Returns
 *      0 for successful
 *      -1 otherwise
*/
int bst_eraseExternalLinks(Queue *qNodes);







/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************    SEARCHING FUNCTIONS    **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



/*
 *  Search for a specific pKey entry in the specific BisTree dictionary
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      pKey                :   Pointer to a key object for which the search will take place
 *      pStartNode          :   Pointer to a BNode object from which the algorithm
 *                              will start searching for the pKey entry
 *
 *  Returns
 *      Pointer to an Internal BNode object which contains a pKey
 *      which is compared equally to the specified key object
 *      Pointer to an External BNode object if the specific key object does not exist
*/
BNode * bst_binarySearch(const BisTree *pTree, const void *pKey, BNode *pStartNode);





/*
 *  Search for a specific pKey entry in the specific BisTree dictionary
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      pKey                :   Pointer to a key object for which the search will take place
 *      pRealKey            :   Pointer to a pointer which will receive the pointer
 *                              to the real key object (optional)
 *      pElem               :   Pointer to a pointer which will receive the pointer
 *                              to the data element (optional)
 *
 *  Returns
 *      0 if the specified pKey is found
 *      -1 of pKey does not exist on the pTree
*/
int bst_search(const BisTree *pTree, const void *pKey, void **pRealKey, void **pElem);







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
 *  Replaces the associated value data pointer to a new data pointer
 *  For a specified pKey
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      pKey                :   Pointer to a key object which value data is being changed
 *      pElem               :   Pointer to the data object which is the new value object of pKey
 *      pOlde               :   Pointer to the pointer which will receive the pointer
 *                              to the old value data object (optional)
 *
 *  Returns
 *      0 for successful replacement
 *      -1 otherwise
*/
int bst_changeElement(BisTree *pTree, const void *pKey, const void *pElem, void **pOldelem);





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
 *  Fill ups the specified linked list with all the key pointers
 *
 *  Parameter:
 *      pTree               :   Pointer to a BisTree
 *      lstKeys             :   Pointer to a singly linked list which will receive
 *                              all the pointers to the key objects available in the dictionary
 *
 *  Returns
 *      0 for successful
 *      -1 if pTree or lstKeys pointers are invalid
 *      -2 if pTree is empty
*/
int bst_listKeys(const BisTree *pTree, List *lstKeys);





/*
 *  Fill ups the specified linked list with all the value data pointers
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
int bst_listElements(const BisTree *pTree, List *lstElements);





/*
 *  Fill ups the specified linked list with all the keys
 *  And their associated value data pointers
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
int bst_listKeysElements(const BisTree *pTree, List *lstKeys, List *lstElements);







/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************     SORTING ALGORITHMS    **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



/*
 *  Sorts the specified singly linked list in ascending order
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
int bst_sort(List *list, int (*compare) (const void *arg1, const void *arg2));





/*
 *  Sorts the specified doubly linked list in ascending order
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
int bst_sortDList(DList *dlist, int (*compare) (const void *arg1, const void *arg2));





/*
 *  Sorts the specified singly linked list in ascending order
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
int bst_sortAscending(List *list, int (*compare) (const void *arg1, const void *arg2));





/*
 *  Sorts the specified singly linked list in descending order
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
int bst_sortDescending(List *list, int (*compare) (const void *arg1, const void *arg2));





/*
 *  Sorts the specified doubly linked list in ascending order
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
int bst_sortAscendingDList(DList *dlist, int (*compare) (const void *arg1, const void *arg2));





/*
 *  Sorts the specified doubly linked list in descending order
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
int bst_sortDescendingDList(DList *dlist, int (*compare) (const void *arg1, const void *arg2));







#endif



