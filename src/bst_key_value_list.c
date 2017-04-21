

/************************************************************************************
    Implementation of Binary Search Tree Key:Value List Generation Algorithms
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bst.h"
#include <list.h>
#include <queue.h>







int bst_listKeys(const BisTree *pTree, List *lstKeys) {
    
    BNode *pNode;
    Queue qNodes;
    ListElem *pLstElem;
    
    if (pTree == 0 || lstKeys == 0)
        return -1;
    if (bst_size(pTree) == 0)
        return -2;
    
    
    /* Initialize the Queue */
    /* Use Inorder algorithm to get a Sorted Key sequence (might be convenient) */
    queue_init(&qNodes, 0);
    bst_inOrder(bst_root((BisTree *) pTree), &qNodes);
    
    pLstElem = list_tail(lstKeys);
    while (queue_size(&qNodes) > 0) {
        queue_dequeue(&qNodes, (void **) &pNode);
        if (bst_isInternal(pNode) == 1) {
            list_ins_next(lstKeys, pLstElem, (const void *) pNode->pKey);
            pLstElem = list_tail(lstKeys);
        }
    }
    
    queue_destroy(&qNodes);
    return 0;
}




int bst_listElements(const BisTree *pTree, List *lstElements) {
    
    BNode *pNode;
    Queue qNodes;
    ListElem *pLstElem;
    
    if (pTree == 0 || lstElements == 0)
        return -1;
    if (bst_size(pTree) == 0)
        return -2;
    
    
    /* Initialize the Queue */
    /* Use Inorder algorithm to get a Sorted Element sequence */
    queue_init(&qNodes, 0);
    bst_inOrder(bst_root((BisTree *) pTree), &qNodes);
    
    pLstElem = list_tail(lstElements);
    while (queue_size(&qNodes) > 0) {
        queue_dequeue(&qNodes, (void **) &pNode);
        if (bst_isInternal(pNode) == 1) {
            list_ins_next(lstElements, pLstElem, (const void *) pNode->pElement);
            pLstElem = list_tail(lstElements);
        }
    }
    
    queue_destroy(&qNodes);
    return 0;
}



int bst_listKeysElements(const BisTree *pTree, List *lstKeys, List *lstElements) {
    
    BNode *pNode;
    Queue qNodes;
    ListElem *pLstElem1;
    ListElem *pLstElem2;
    
    if (pTree == 0 || lstKeys == 0 || lstElements == 0)
        return -1;
    if (bst_size(pTree) == 0)
        return -2;
    
    
    /* Initialize the Queue */
    /* Use Inorder algorithm to get a Sorted sequence */
    queue_init(&qNodes, 0);
    bst_inOrder(bst_root((BisTree *) pTree), &qNodes);
    
    pLstElem1 = list_tail(lstKeys);
    pLstElem2 = list_tail(lstElements);
    
    while (queue_size(&qNodes) > 0) {
        queue_dequeue(&qNodes, (void **) &pNode);
        if (bst_isInternal(pNode) == 1) {
            list_ins_next(lstKeys, pLstElem1, (const void *) pNode->pKey);
            list_ins_next(lstElements, pLstElem2, (const void *) pNode->pElement);
            pLstElem1 = list_tail(lstKeys);
            pLstElem2 = list_tail(lstElements);
        }
    }
    
    queue_destroy(&qNodes);
    return 0;
}

