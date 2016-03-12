

/************************************************************************************
	Implementation of BST Initialization and Destruction Functions
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
*************************************************************************************/






#include "bst.h"
#include <queue.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>






int bst_freeNode(BST *tree, BNode *node);





int bst_freeNode(BST *tree, BNode *node) {
	
	if (tree->destroy_data != 0) {
		tree->destroy_data((void *) node->element);
	}
	if (tree->destroy_key != 0) {
		tree->destroy_key((void *) node->key);
	}
	free((void *) node);
	
	return 0;
	
}




int bst_init(BST *tree, int (*compare_key) (const void *k1, const void *k2)) {
	
	tree->size = 0;										/* Initially size must be Zero */
	tree->destroy_key = 0;								/* No destructor function for Keys */
	tree->destroy_data = 0;								/* No destructor function for User Data */
	tree->compare_key = compare_key;					/* Use User-defined comparing function */
	tree->root = (BNode*) malloc(sizeof(BNode));		/* Create an empty BNode object as Root */
	memset((void *) tree->root, 0, sizeof(BNode));		/* Root BNode object is zerowed */
	
	return 0;
}


void bst_destroy(BST *tree) {
	
	BNode *node;
	Queue nodeList;													/* Queue for holding all BNode objects */
	
	queue_init(&nodeList, 0);										/* Initialize queue with no destructor function */
	bst_postorder((const BST *) tree, bst_root(tree), &nodeList);	/* Collect all BNodes on the Queue in Postorder */
	
	if (bst_size((const BST *) tree) != queue_size(&nodeList)) {
		fputs("At bst_destroy(): Post-order list size NOT EQUAL to bst_size()", stderr);
	}
	
	while (queue_size(&nodeList) > 0) {
		
		queue_dequeue(&nodeList, (void **) &node);					/* Acquire pointer of each BNode */
		bst_freeNode(tree, node);									/* Destroy the acquired BNode */
	}
	
	queue_destroy(&nodeList);										/* Destroy temporary queue */
	memset((void *) tree, 0, sizeof(BST));							/* Clear the memory of BST object */
	
	return;
}
