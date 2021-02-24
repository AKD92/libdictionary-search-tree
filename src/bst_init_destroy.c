

/************************************************************************************
    Implementation of Binary Search Tree Initialization and Destruction Functions
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bst.h"
#include "bst_internal.h"
#include <queue.h>
#include <stdlib.h>
#include <string.h>








int bst_init (BisTree *pTree, int (*fpCompareKey) (const void *k1, const void *k2),
                    void (*fpDestroyKey) (void *key), void (*fpDestroyData) (void *pData))
{
    
    BNode *pRoot;
    
    if (pTree == 0 || fpCompareKey == 0)
        return -1;
    
    pRoot = 0;
    pRoot = (BNode *) malloc(sizeof(BNode));
    if (pRoot == 0)
        return -1;
    
    memset((void *) pTree, 0, sizeof(BisTree));
    pTree->size = 0;                                                /* Initially size must be Zero */
    pTree->fpCompareKey = fpCompareKey;                             /* Use User-defined comparing function */
    pTree->fpDestroyKey = fpDestroyKey;                             /* No destructor function for Keys */
    pTree->fpDestroyData = fpDestroyData;                           /* No destructor function for User Data */
    pTree->pRootNode = pRoot;                                       /* Create an empty BNode object as Root */
    memset((void *) pTree->pRootNode, 0, sizeof(BNode));            /* Initialize Root BNode object */
    
    return 0;
}



void bst_destroy(BisTree *pTree) {
    
    BNode *pNode;
    Queue qNodes;                             /* Queue for holding all BNode objects */
    
    if (pTree == 0)
        return;
    
    
    /* Initialize Queue with no Destructor function */
    pNode = 0;
    queue_init(&qNodes, 0);
    
    
    /* Collect all BNode objects to the Queue */
    bst_levelorder_lr(bst_root(pTree), BNODE_ALLOW_INTERNAL | BNODE_ALLOW_EXTERNAL, &qNodes);
    
    
    /* Dequeue each BNode object one by one */
    /* And de-allocate memory by freeing each BNode dequeued */
    while (queue_size(&qNodes) > 0) {
        queue_dequeue(&qNodes, (void **) &pNode);
        if (pTree->fpDestroyKey != 0) {
            pTree->fpDestroyKey((void *) pNode->pKey);
        }
        if (pTree->fpDestroyData != 0) {
            pTree->fpDestroyData((void *) pNode->pElement);
        }
        free((void *) pNode);
    }
    
    
    /* Destroy temporary Queue */
    /* Release the memory of BisTree structure */
    queue_destroy(&qNodes);
    
    return;
}

