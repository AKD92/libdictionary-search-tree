

/************************************************************************************
    Implementation of Binary Search Tree Mutation Functions (Insertion, Deletion)
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/








#include "bst.h"
#include <queue.h>
#include <stdlib.h>
#include <string.h>






/*  bst_expandExternal(BNode *w)
    Returns 0 if successful, -1 if fails
*/

int bst_expandExternal(BNode *pExternal);


/*  bst_removeAboveExternal(BisTree *pTree, BNode *w)
    Returns 0 if successful, -1 if fails
*/

int bst_removeAboveExternal(BisTree *pTree, BNode *pExternal, BNode **pGrandParent);







int bst_expandExternal(BNode *pExternal) {
    
    BNode *pLeftChild, *pRightChild;
    
    if (bst_isInternal(pExternal) == 1)
        return -1;
    
    pLeftChild = pRightChild = 0;
    pLeftChild = (BNode *) malloc(sizeof(BNode));
    pRightChild = (BNode *) malloc(sizeof(BNode));
    
    if (pLeftChild == 0 || pRightChild == 0)
    {
        free((void *) pLeftChild);
        free((void *) pRightChild);
        return -2;
    }
    
    memset((void *) pLeftChild, 0, sizeof(BNode));
    memset((void *) pRightChild, 0, sizeof(BNode));
    
    /* Actually, pExternal bocomes an Internal by executing the following codes */
    pExternal->pLeftNode = pLeftChild;
    pExternal->pRightNode = pRightChild;
    
    pLeftChild->pParentNode = pExternal;
    pRightChild->pParentNode = pExternal;
    
    return 0;
}


int bst_removeAboveExternal(BisTree *pTree, BNode *pExternal, BNode **pGrandParent) {
    
    int isLeftChild;
    BNode *pParent, *pHigherParent;                     /* v = parent(w), u = parent(v) */
    BNode *pSibling;                                    /* z = sibling(w)               */
    
    if (bst_isInternal(pExternal) == 1)
        return -1;
    if (bst_parent(pExternal) == 0)
        return -2;
    
    pParent = bst_parent(pExternal);                    /* Parent BNode of specified external BNode */
    pHigherParent = bst_parent(pParent);                /* Grand parent BNode of specified BNode */
    pSibling = bst_sibling(pExternal);                  /* Sibling or Brother BNode of specified BNode */
    
    if (pGrandParent != 0)
        *pGrandParent = pHigherParent;
    
    
    /* If grand parent exist, adjust its left and right children appropriately */
    if (pHigherParent != 0) {
        
        pSibling->pParentNode = pHigherParent;
        
        
        /* Determine if pParent is the Left Child of pHigherParent */
        isLeftChild = (pParent == bst_leftChild(pHigherParent)) ? 1 : 0;
        
        switch (isLeftChild) {
        case 1:                 /* pParent is Left Child of pHigherParent (Grand parent) */
            pHigherParent->pLeftNode = pSibling;
            break;
            
        case 0:                 /* pParent is Right Child of pHigherParent (Grand parent) */
            pHigherParent->pRightNode = pSibling;
            break;
            
        default:
            break;
        }
    }
    
    /* If Grand Parent does not exist, make the sibling BNode as pTree's Root BNode */
    else {
        pSibling->pParentNode = 0;
        pTree->pRootNode = pSibling;
    }
    
    
    /* Destroy parent BNode and specifed external BNode */
    free((void *) pParent);
    free((void *) pExternal);
    
    return 0;
}



int bst_changeElement(BisTree *pTree, const void *pKey, const void *pElem, void **pOldelem) {
    
    int iRetVal;
    BNode *pTarget;
    
    if (pTree == 0 || pKey == 0)
        return -1;
    
    pTarget = bst_binarySearch((const BisTree *) pTree, pKey, bst_root(pTree));
    
    if (bst_isExternal(pTarget) == 1) {
        iRetVal = -1;
    }
    else {
        if (pOldelem != 0) *pOldelem = pTarget->pElement;
        pTarget->pElement = (void *) pElem;
        iRetVal = 0;
    }
    
    return iRetVal;
}



int bst_insert(BisTree *pTree, const void *pKey, const void *pElem) {
    
    int iRetVal;
    int opExpand;
    BNode *pTarget;
    
    if (pTree == 0 || pKey == 0)
        return -1;
    
    
    /* Search for the pKey in our BisTree */
    pTarget = bst_binarySearch((const BisTree *) pTree, pKey, bst_root(pTree));
    
    
    /* Key not found, we have got an External BNode */
    /* So make it Internal and assing this Key and Elem to it */
    if (bst_isExternal(pTarget) == 1) {
        
        opExpand = bst_expandExternal(pTarget);
        if (opExpand != 0)
            return -1;
        
        pTarget->pKey = (void *) pKey;
        pTarget->pElement = (void *) pElem;
        pTree->size = pTree->size + 1;
        iRetVal = 0;
    }
    else {
        
        
        /* We have got an Internal BNode, it means Key already exist */
        /* In this situation we cannot insert the given Key into our BisTree */
        iRetVal = -1;
    }
    
    return iRetVal;
}



int bst_remove(BisTree *pTree, const void *pKey, void **pRemovedKey, void **pRemovedElem) {
    
    int iRetVal;
    int isRemNodeExternal;
    int isLeftExternal, isRightExternal;
    int isBothInternal;
    BNode *pRemNode;
    BNode *pLeftChild, *pRightChild;
    BNode *pChildExternal, *pInorderInternal, *pInorderExternal;
    BNode *pExternal;
    
    if (pTree == 0 || pKey == 0)
        return -1;
    
    pChildExternal = 0;
    pRemNode = bst_binarySearch((const BisTree *) pTree, pKey, bst_root(pTree));
    isRemNodeExternal = bst_isExternal(pRemNode);
    
    if (isRemNodeExternal == 1) {
        iRetVal = -1;
    }
    else {
        
        if (pRemovedKey != 0)
            *pRemovedKey = pRemNode->pKey;
        if (pRemovedElem != 0)
            *pRemovedElem = pRemNode->pElement;
        
        pLeftChild = bst_leftChild(pRemNode);
        pRightChild = bst_rightChild(pRemNode);
        
        isLeftExternal = bst_isExternal(pLeftChild);
        isRightExternal = bst_isExternal(pRightChild);
        
        
        /* Both childs are internal if Left And Right childs are NOT External */
        isBothInternal = !(isLeftExternal | isRightExternal);
        
        if (isBothInternal == 0) {
            
            
            /* Find the External child of pRemNode and pChildExternal will be the External one */
            if (isLeftExternal == 1)
                pChildExternal = pLeftChild;
            if (isRightExternal == 1)
                pChildExternal = pRightChild;
            
            pExternal = pChildExternal;
        }
        else if (isBothInternal == 1) {
            
            
            /* Find next Internal BNode in the "InOrder" serial */
            /* Next Internal BNode = pInorderInternal */
            pInorderExternal = pRightChild;
            while (bst_isExternal(pInorderExternal) != 1) {
                pInorderExternal = bst_leftChild(pInorderExternal);
            }
            pInorderInternal = bst_parent(pInorderExternal);
            
            
            /* Copy pKey and pElement pointers to pRemNode */
            pRemNode->pKey = pInorderInternal->pKey;
            pRemNode->pElement = pInorderInternal->pElement;
            pInorderInternal->pKey = 0;
            pInorderInternal->pElement = 0;
            
            pExternal = pInorderExternal;
        }
        
        
        /* Remove internal node pInorderInternal */
        bst_removeAboveExternal(pTree, pExternal, 0);
        
        pTree->size = pTree->size - 1;
        iRetVal = 0;
    }
    
    return iRetVal;
}

