

/************************************************************************************
    Internal Program Interface for Binary Search Tree based Dictionary ADT
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef BST_INTERNAL_H_INCLUDED
#define BST_INTERNAL_H_INCLUDED




#include "bst.h"
#include <queue.h>





#define BNODE_ALLOW_EXTERNAL       0x01
#define BNODE_ALLOW_INTERNAL       0x02










/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************      QUERY FUNCTIONS      **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/




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
#define bst_root(pTree) ((pTree)->pRootNode)





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
#define bst_parent(pNode) ((pNode) == 0 ? 0 : (pNode)->pParentNode)





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
#define bst_leftchild(pNode) ((pNode) == 0 ? 0 : (pNode)->pLeftNode)





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
#define bst_rightchild(pNode) ((pNode) == 0 ? 0 : (pNode)->pRightNode)





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
#define bst_is_external(pNode) ((bst_leftchild(pNode) || bst_rightchild(pNode)) == 0 ? 1 : 0)





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
#define bst_is_internal(pNode) ((bst_leftchild(pNode) || bst_rightchild(pNode)) != 0 ? 1 : 0)





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
#define bst_is_root(pTree, pNode) (bst_root(pTree) == (pNode) ? 1 : 0)





/*
 *  Query to know the depth of the specified BNode object
 *
 *  Parameter:
 *      pNode               :   Pointer to a BNode object
 *      pDepth              :   Pointer to an unsigned integer which will receive
 *                              the depth value of the specified BNode object
 *
 *  Returns
 *      0 if successful
 *      -1 otherwise
*/
int bst_depth(const BNode *pNode, unsigned int *pDepth);





/*
 *  Query to know the height value of the specified BNode object
 *
 *  Parameter:
 *      pNode               :   Pointer to a BNode object
 *      pHeight             :   Pointer to an unsigned integer which will receive
 *                              the height value of the specified BNode object
 *
 *  Returns
 *      0 if successful
 *      -1 otherwise
*/
int bst_height(const BNode *pNode, unsigned int *pHeight);





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
int bst_is_ancestor(const BisTree *pTree, const BNode *pParent, const BNode *pChild);






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
BNode * bst_search_node(const BisTree *pTree, const void *pKey, BNode *pStartNode);






/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************    TRAVERSAL FUNCTIONS    **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



/*
 *  Traverses a binary search tree with "pre-order" fashion.
 *  Traversal starts from the specified node of the tree.
 *  Retrives pointers to the traversed node objects into the specified queue.
 *
 *  Parameter:
 *      pStartNode          :   Pointer to a BNode from which the algorithm
 *                              will start traversing
 *      nodeType            :   Specify what kind of nodes this algorithm will
 *                              store on the output queue. It can be only internal
 *                              nodes, only external nodes or both type of nodes
 *                              For internal nodes only, set it to BNODE_ALLOW_INTERNAL
 *                              For external nodes only, set it to BNODE_ALLOW_EXTERNAL
 *                              For all nodes, set it to the 'bitwise-or' of the constants above
 *      qPreorder           :   Pointer to a Queue which will receive pointers of
 *                              all the traversed BNode objects
 *
 *  Returns
 *      0 for successful traversal
 *      -1 otherwise
*/
int bst_preorder(BNode *pStartNode, int nodeType, Queue *qPreorder);





/*
 *  Traverses a binary search tree with "in-order" fashion.
 *  Traversal starts from the specified node of the tree.
 *  Retrives pointers to the traversed node objects into the specified queue.
 *
 *  Parameter:
 *      pStartNode          :   Pointer to a BNode from which the algorithm
 *                              will start traversing
 *      nodeType            :   Specify what kind of nodes this algorithm will
 *                              store on the output queue. It can be only internal
 *                              nodes, only external nodes or both type of nodes
 *                              For internal nodes only, set it to BNODE_ALLOW_INTERNAL
 *                              For external nodes only, set it to BNODE_ALLOW_EXTERNAL
 *                              For all nodes, set it to the 'bitwise-or' of the constants above
 *      qInorder            :   Pointer to a Queue which will receive pointers of
 *                              all the traversed BNode objects
 *
 *  Returns
 *      0 for successful traversal
 *      -1 otherwise
*/
int bst_inorder(BNode *pStartNode, int nodeType, Queue *qInorder);





/*
 *  Traverses a binary search tree in the reverse of "in-order" fashion.
 *  Traversal starts from the specified node of the tree.
 *  Retrives pointers to the traversed node objects into the specified queue.
 *
 *  Parameter:
 *      pStartNode          :   Pointer to a BNode from which the algorithm
 *                              will start traversing
 *      nodeType            :   Specify what kind of nodes this algorithm will
 *                              store on the output queue. It can be only internal
 *                              nodes, only external nodes or both type of nodes
 *                              For internal nodes only, set it to BNODE_ALLOW_INTERNAL
 *                              For external nodes only, set it to BNODE_ALLOW_EXTERNAL
 *                              For all nodes, set it to the 'bitwise-or' of the constants above
 *      qInorder            :   Pointer to a Queue which will receive pointers of
 *                              all the traversed BNode objects
 *
 *  Returns
 *      0 for successful traversal
 *      -1 otherwise
*/
int bst_reverse_inorder(BNode *pStartNode, int nodeType, Queue *qInorder);





/*
 *  Traverses a binary search tree with "post-order" fashion.
 *  Traversal starts from the specified node of the tree.
 *  Retrives pointers to the traversed node objects into the specified queue.
 *
 *  Parameter:
 *      pStartNode          :   Pointer to a BNode from which the algorithm
 *                              will start traversing
 *      nodeType            :   Specify what kind of nodes this algorithm will
 *                              store on the output queue. It can be only internal
 *                              nodes, only external nodes or both type of nodes
 *                              For internal nodes only, set it to BNODE_ALLOW_INTERNAL
 *                              For external nodes only, set it to BNODE_ALLOW_EXTERNAL
 *                              For all nodes, set it to the 'bitwise-or' of the constants above
 *      qPostorder          :   Pointer to a Queue which will receive pointers of
 *                              all the traversed BNode objects
 *
 *  Returns
 *      0 for successful traversal
 *      -1 otherwise
*/
int bst_postorder(BNode *pStartNode, int nodeType, Queue *qPostorder);





/*
 *  Traverses a binary search tree with "level-order Left to Right" fashion.
 *  Traversal starts from the specified node of the tree.
 *  Retrives pointers to the traversed node objects into the specified queue.
 *
 *  Parameter:
 *      pStartNode          :   Pointer to a BNode from which the algorithm
 *                              will start traversing
 *      nodeType            :   Specify what kind of nodes this algorithm will
 *                              store on the output queue. It can be only internal
 *                              nodes, only external nodes or both type of nodes
 *                              For internal nodes only, set it to BNODE_ALLOW_INTERNAL
 *                              For external nodes only, set it to BNODE_ALLOW_EXTERNAL
 *                              For all nodes, set it to the 'bitwise-or' of the constants above
 *      qLRorder            :   Pointer to a Queue which will receive pointers of
 *                              all the traversed BNode objects
 *
 *  Returns
 *      0 for successful traversal
 *      -1 otherwise
*/
int bst_levelorder_lr(BNode *pStartNode, int nodeType, Queue *qLRorder);





/*
 *  Traverses a binary search tree with "level-order Right to Left" fashion.
 *  Traversal starts from the specified node of the tree.
 *  Retrives pointers to the traversed node objects into the specified queue.
 *
 *  Parameter:
 *      pStartNode          :   Pointer to a BNode from which the algorithm
 *                              will start traversing
 *      nodeType            :   Specify what kind of nodes this algorithm will
 *                              store on the output queue. It can be only internal
 *                              nodes, only external nodes or both type of nodes
 *                              For internal nodes only, set it to BNODE_ALLOW_INTERNAL
 *                              For external nodes only, set it to BNODE_ALLOW_EXTERNAL
 *                              For all nodes, set it to the 'bitwise-or' of the constants above
 *      qRLorder            :   Pointer to a Queue which will receive pointers of
 *                              all the traversed BNode objects
 *
 *  Returns
 *      0 for successful traversal
 *      -1 otherwise
*/
int bst_levelorder_rl(BNode *pStartNode, int nodeType, Queue *qRLorder);






/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************     MUTATION FUNCTIONS    **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



/*  bst_expandExternal(BNode *w)
    Returns 0 if successful, -1 if fails
*/

int bst_expandExternal(BNode *pExternal);



/*  bst_removeAboveExternal(BisTree *pTree, BNode *w)
    Returns 0 if successful, -1 if fails
*/

int bst_removeAboveExternal(BisTree *pTree, BNode *pExternal, BNode **pGrandParent);




#endif

