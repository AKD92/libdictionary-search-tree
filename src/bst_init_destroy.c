

/************************************************************************************
	Implementation of BST Initialization and Destruction Functions
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bst.h"
#include <queue.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>









int bst_init (
			BST *tree,
			int (*compare_key) (const void *k1, const void *k2),
			void (*destroy_key) (void *key),
			void (*destroy_data) (void *data)
			)
{
	
	tree->size = 0;										/* Initially size must be Zero */
	tree->compare_key = compare_key;					/* Use User-defined comparing function */
	tree->destroy_key = destroy_key;					/* No destructor function for Keys */
	tree->destroy_data = destroy_data;					/* No destructor function for User Data */
	tree->root = 0;
	tree->root = (BNode *) malloc(sizeof(BNode));		/* Create an empty BNode object as Root */
	if (tree->root == 0)
		return -1;
	memset((void *) tree->root, 0, sizeof(BNode));		/* Initialize Root BNode object */
	
	return 0;
}



void bst_destroy(BST *tree) {
	
	BNode *pNode;
	Queue allNodes;													/* Queue for holding all BNode objects */
	unsigned int calculatedNodeCount;								/* Number of BNode objects to be */
	
	queue_init(&allNodes, 0);										/* Initialize Queue with no destructor function */
	bst_preOrder((const BST *) tree, bst_root(tree), &allNodes);	/* Collect all BNode objects on the Queue */
	calculatedNodeCount = 2 * bst_size((const BST *) tree) + 1;		/* Node Count = 2 X (Internals) + 1 */
	
	if (calculatedNodeCount != queue_size(&allNodes)) {
		printf("bst_destroy() : Post-order queue_size() NOT EQUAL to bst_size()\n");
		printf("bst_destroy() : bst_size(): %u, queue_size(): %u\n",
						bst_size((const BST *) tree), queue_size(&allNodes));
	}
	
	while (queue_size(&allNodes) > 0) {
		queue_dequeue(&allNodes, (void **) &pNode);					/* Acquire pointer of each BNode */
		
		if (tree->destroy_key != 0) {
			tree->destroy_key((void *) pNode->key);
		}
		if (tree->destroy_data != 0) {
			tree->destroy_data((void *) pNode->element);
		}
		free((void *) pNode);
	}
	
	queue_destroy(&allNodes);										/* Destroy temporary queue */
	memset((void *) tree, 0, sizeof(BST));							/* Clear the memory of BST object */
	return;
}

