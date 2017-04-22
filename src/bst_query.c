

/************************************************************************************
    Implementation of Binary Search Tree Query Functions
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bst.h"
#include <stack.h>
#include <queue.h>




#define maxu(a, b) ((a) > (b) ? (a) : (b))







/*
BNode * bst_root(const BisTree *pTree) {
    
    return (pTree == 0 ? 0 : pTree->pRootNode);
}



BNode * bst_parent(const BNode *pNode) {
    
    return (pNode == 0 ? 0 : pNode->pParentNode);
}



BNode * bst_leftChild(const BNode *pNode) {
    
    return (pNode == 0 ? 0 : pNode->pLeftNode);
}



BNode * bst_rightChild(const BNode *pNode) {
    
    return (pNode == 0 ? 0 : pNode->pRightNode);
}
*/


BNode * bst_sibling(const BNode *pNode) {
    
    BNode *sibling;
    BNode *parent;
    
    parent = bst_parent(pNode);
    if (parent == 0) {
        sibling = 0;
    }
    else {
        if (pNode == bst_leftChild(parent)) {
            sibling = bst_rightChild(parent);
        }
        else if (pNode == bst_rightChild(parent)) {
            sibling = bst_leftChild(parent);
        }
    }
    
    return sibling;
}


/*
int bst_isExternal(const BNode *pNode) {
    
    unsigned int left, right;
    
    left = (unsigned int) bst_leftChild(pNode);
    right = (unsigned int) bst_rightChild(pNode);
    
    if ((left | right) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}
*/


/*
int bst_isInternal(const BNode *pNode) {
    
    unsigned int left, right;
    
    left = (unsigned int) bst_leftChild(pNode);
    right = (unsigned int) bst_rightChild(pNode);
    
    if ((left | right) != 0) {
        return 1;
    }
    else {
        return 0;
    }
}



int bst_isRoot(const BisTree *pTree, const BNode *pNode) {
    
    int retVal;
    
    retVal = bst_root(pTree) == pNode ? 1 : 0;
    return retVal;
}
*/



int bst_depth(const BNode *pNode, unsigned int *pDepth) {
    
    register unsigned int iDepth;
    register const BNode *pCurrent;
    
    if (pNode == 0 || pDepth == 0)
        return -1;
    
    iDepth = 0;
    pCurrent = pNode;
    
    while (pCurrent != 0) {
        pCurrent = bst_parent(pCurrent);
        iDepth = iDepth + 1;
    }
    *pDepth = iDepth - 1;
    return 0;
}



int bst_height(const BNode *pNode, unsigned int *pHeight) {
    
    int isExternal;
    Queue qPostorder;
    register unsigned int iCount;
    unsigned int nExternal;
    unsigned int heightR, heightL, heightN;
    const BNode *pCurrent;
    unsigned int *pTmpHeight;
    int opRes;
    
    if (pNode == 0 || pHeight == 0)
        return -1;
    
    iCount = 0;
    pCurrent = 0;
    pTmpHeight = 0;
    
    /* Initialize the Queue and store PostOrder nodes on it */
    queue_init(&qPostorder, 0);
    bst_postOrder((BNode *) pNode, &qPostorder);
    
    /* Total nodes in queue: 2n + 1 (internal + external) */
    /* Therefore number of external nodes = ((2n + 1) - 1)/2 + 1 */
    nExternal = ((queue_size(&qPostorder) - 1) / 2) + 1;
    pTmpHeight = (unsigned int *) malloc(sizeof(unsigned int) * nExternal);
    if (pTmpHeight == 0) {
        opRes = -1;
        goto END;
    }
    
    while (queue_size(&qPostorder) > 0) {
        
        queue_dequeue(&qPostorder, (void **) &pCurrent);
        isExternal = bst_isExternal(pCurrent);
        
        if (isExternal == 1) {
            *(pTmpHeight + iCount) = 0;
            iCount = iCount + 1;
        }
        else {
            iCount = iCount - 1;
            heightR = *(pTmpHeight + iCount);
            
            iCount = iCount - 1;
            heightL = *(pTmpHeight + iCount);
            
            heightN = 1 + maxu(heightL, heightR);
            *(pTmpHeight + iCount) = heightN;
            iCount = iCount + 1;
        }
    }
    
    heightN = *(pTmpHeight + iCount - 1);
    *pHeight = heightN;
    opRes = 0;
    
    END:
    queue_destroy(&qPostorder);
    free((void *) pTmpHeight);
    return opRes;
}



int bst_isAncestor(const BisTree *pTree, const BNode *pParent, const BNode *pChild){
    
    int opRes;
    register const BNode *pN;
    
    opRes = 0;
    pN = pChild;
    
    REPEAT:
        if (pN == pParent) {
            opRes = 1;
            goto END;
        }
        else if (pN == 0) {
            goto END;
        }
        pN = bst_parent(pN);
    goto REPEAT;
    
    END:
        return opRes;
}


