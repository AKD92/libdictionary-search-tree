


#include "bst.h"
#include <queue.h>
#include <stdlib.h>
#include <string.h>






int bst_destroy_node(BST *tree, BNode *node);





int bst_destroy_node(BST *tree, BNode *node) {
	/*	int ext;*/
	/*	ext = bst_isExternal(node);*/
	if (tree->destroy_data != 0) {
		tree->destroy_data(node->element);
		/*		printf("Value destroyed\n");*/
	}
	if (tree->destroy_key != 0) {
		tree->destroy_key(node->key);
		/*		printf("Key destroyed\n");*/
	}
	free(node);
	/*	printf("Node destroyed, external? %d\n\n", ext);*/
	
	return 0;
	
}




int bst_init(BST *tree, int (*compare_key) (const void *k1, const void *k2)) {
	
	tree->size = 0;
	tree->compare_key = compare_key;
	tree->root = (BNode*) malloc(sizeof(BNode));
	memset(tree->root, 0, sizeof(BNode));
	
	return 0;
}


void bst_destroy(BST *tree) {
	
	Queue nodes;
	BNode *node;
	
	queue_init(&nodes, 0);
	bst_postorder(tree, bst_root(tree), &nodes);
	
	while (queue_size(&nodes) > 0) {
		
		queue_dequeue(&nodes, (void **) &node);
		bst_destroy_node(tree, node);
	}
	
	queue_destroy(&nodes);
	memset(tree, 0, sizeof(BST));
	
	return;
}
