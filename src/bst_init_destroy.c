

/************************************************************************************
	Implementation of Binary Search Tree Initialization and Destruction Functions
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bst.h"
#include <queue.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>






#define ERROR_MSG_1 "\n** bst_destroy() : Post-order queue_size() NOT EQUAL to bst_size()\n"
#define ERROR_MSG_2 "** bst_destroy() : bst_size(): %u, queue_size(): %u\n\n"






int bst_init (BisTree *pTree, int (*fpCompareKey) (const void *k1, const void *k2),
					void (*fpDestroyKey) (void *key), void (*fpDestroyData) (void *data))
{
	
	BNode *pRoot;
	
	pRoot = 0;
	pRoot = (BNode *) malloc(sizeof(BNode));
	if (pRoot == 0)
		return -1;
	
	pTree->size = 0;										/* Initially size must be Zero */
	pTree->fpCompareKey = fpCompareKey;						/* Use User-defined comparing function */
	pTree->fpDestroyKey = fpDestroyKey;						/* No destructor function for Keys */
	pTree->fpDestroyData = fpDestroyData;					/* No destructor function for User Data */
	pTree->root = pRoot;									/* Create an empty BNode object as Root */
	memset((void *) pTree->root, 0, sizeof(BNode));			/* Initialize Root BNode object */
	
	return 0;
}



void bst_destroy(BisTree *pTree) {
	
	BNode *pNode;
	Queue qNodes;											/* Queue for holding all BNode objects */
	unsigned int iNodeCount;								/* Number of BNode objects supposed to be */
	
	
	/* Initialize Queue with no destructor function */
	pNode = 0;
	queue_init(&qNodes, 0);
	
	
	/* Collect all BNode objects on the Queue */
	/* This MUST be TRUE: Node Count = 2 * (Internals) + 1 */
	bst_preOrder((const BisTree *) pTree, bst_root(pTree), &qNodes);
	iNodeCount = 2 * bst_size((const BisTree *) pTree) + 1;
	
	
	/* If our Node Count assert is FALSE, signal an error */
	if (iNodeCount != queue_size(&qNodes)) {
		printf(ERROR_MSG_1);
		printf(ERROR_MSG_2, bst_size((const BisTree *) pTree), queue_size(&qNodes));
	}
	
	
	/* Dequeue a BNode object one by one */
	/* And de-allocate its memory by freeing it */
	while (queue_size(&qNodes) > 0) {
		queue_dequeue(&qNodes, (void **) &pNode);
		
		if (pTree->fpDestroyKey != 0) {
			pTree->fpDestroyKey((void *) pNode->key);
		}
		if (pTree->fpDestroyData != 0) {
			pTree->fpDestroyData((void *) pNode->element);
		}
		free((void *) pNode);
	}
	
	
	/* Destroy temporary Queue */
	/* Clear the memory of BisTree structure */
	queue_destroy(&qNodes);
	memset((void *) pTree, 0, sizeof(BisTree));
	return;
}

