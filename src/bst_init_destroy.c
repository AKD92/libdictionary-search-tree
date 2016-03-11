


#include "bst.h"
#include <queue.h>
#include <stdlib.h>
#include <string.h>






int bst_destroy_node(BST *tree, BNode *node);





int bst_destroy_node(BST *tree, BNode *node) {
	/*	int ext;*/
	/*	ext = bst_isExternal(node);*/
	if (tree->destroy_data != 0) {
		tree->destroy_data((void *) node->element);
		/*		printf("Value destroyed\n");*/
	}
	if (tree->destroy_key != 0) {
		tree->destroy_key((void *) node->key);
		/*		printf("Key destroyed\n");*/
	}
	free((void *) node);
	/*	printf("Node destroyed, external? %d\n\n", ext);*/
	
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
	
	Queue nodes;										/* Queue for holding all BNode objects */
	BNode *node;
	
	queue_init(&nodes, 0);								/* Initialize queue with no destructor function */
	bst_postorder(tree, bst_root(tree), &nodes);		/* Collect all BNodes on the Queue in Postorder */
	
	while (queue_size(&nodes) > 0) {
		
		queue_dequeue(&nodes, (void **) &node);			/* Acquire pointer of each BNode */
		bst_destroy_node(tree, node);					/* Destroy the acquired BNode */
	}
	
	queue_destroy(&nodes);								/* Destroy temporary queue */
	memset((void *) tree, 0, sizeof(BST));				/* Clear the memory of BST object */
	
	return;
}
