

/************************************************************************************
    Implementation of Binary Search Tree Look-Up (Search) Algorithms
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bst.h"
#include "bst_internal.h"








BNode * bst_search_node(const BisTree *pTree, const void *key, BNode *pStartNode) {
    
    register int opCompareKey;
    register BNode *pNode;
    
    pNode = pStartNode;
    while (bst_is_external(pNode) != 1) {
        
        opCompareKey = pTree->fpCompareKey((const void *) key, (const void *) pNode->pKey);
        if (opCompareKey == 0) {
            break;
        }
        else if (opCompareKey < 0) {
            pNode = bst_leftchild(pNode);
        }
        else if (opCompareKey > 0) {
            pNode = bst_rightchild(pNode);
        }
    }
    
    return pNode;
}





int bst_lookup(const BisTree *pTree, const void *pKey, void **pElem) {
    
    int iRetVal;
    BNode *pTarget;
    
    if (pTree == 0 || pKey == 0)
        return -1;
    
    
    /*  Search for the key in the specified BisTree dictionary */
    pTarget = bst_search_node(pTree, pKey, bst_root((BisTree *) pTree));
    
    
    /*  The key has been found.
        So now we update pElem pointer with the value associated
        with the key
    */
    if (bst_is_internal(pTarget) == 1) {
        
        if (pElem != 0) {
            *pElem = pTarget->pElement;
        }
        iRetVal = 1;
    }
    
    /*  The key does not exist. */
    else if (bst_is_external(pTarget) == 1) {
        iRetVal = 0;
    }
    
    return iRetVal;
}





int bst_exists(const BisTree *pTree, const void *pKey) {
    
    int iRetVal, iSearchVal;
    
    iSearchVal = bst_lookup(pTree, pKey, 0);
    
    iRetVal = (iSearchVal == 1) ? 1 : 0;
    return iRetVal;
}

