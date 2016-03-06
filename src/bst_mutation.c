


#include "bst.h"
#include <queue.h>
#include <stdlib.h>
#include <string.h>






/*	bst_expandExternal(BNode *w)
	Returns 0 if successful, -1 if fails
*/

int bst_expandExternal(BNode *w);


/*	bst_removeAboveExternal(BST *tree, BNode *w)
	Returns 0 if successful, -1 if fails
*/

int bst_removeAboveExternal(BST *tree, BNode *w);







int bst_expandExternal(BNode *w) {
	
	BNode *leftChild, *rightChild;
	
	if (bst_isExternal(w) == 0) return -1;
	
	leftChild = (BNode*) malloc(sizeof(BNode));
	rightChild = (BNode*) malloc(sizeof(BNode));
	
	memset(leftChild, 0, sizeof(BNode));
	memset(rightChild, 0, sizeof(BNode));
	
	w->leftChild = leftChild;
	w->rightChild = rightChild;
	
	leftChild->parent = w;
	rightChild->parent = w;
	
	return 0;
}


int bst_removeAboveExternal(BST *tree, BNode *nodeExternal) {
	
	int isLeftChild;
	BNode *nodeParent, *nodeHigherParent;			/* v = parent(w), u = parent(v) */
	BNode *nodeSibling;								/* z = sibling(w)				*/
	
	if (bst_isExternal(nodeExternal) == 0) return -1;
	if (bst_parent(nodeExternal) == 0) return -1;
	
	nodeParent = bst_parent(nodeExternal);
	nodeHigherParent = bst_parent(nodeParent);
	nodeSibling = bst_sibling(nodeExternal);
	
	isLeftChild = bst_leftChild(nodeHigherParent) == nodeParent ? 1 : 0;
	
	if (tree->destroy_key != 0) {
		tree->destroy_key(nodeParent->key);
	}
	free(nodeParent);
	free(nodeExternal);
	nodeParent = nodeExternal = 0;
	
	nodeSibling->parent = nodeHigherParent;
	
	if (nodeHigherParent != 0) {
		switch (isLeftChild) {
		case 1:
			nodeHigherParent->leftChild = nodeSibling;
			break;
		case 0:
			nodeHigherParent->rightChild = nodeSibling;
			break;
		default:
			break;
		}
	}
	else {
		tree->root = nodeSibling;
	}
	
	return 0;
}



int bst_changeElement(BST *tree, void *key, void *elem){
	
	int res;
	BNode *v;
	
	v = bst_treeSearch(tree, key, bst_root(tree));
	
	if (bst_isExternal(v) == 1) {
		
		res = -1;
	}
	else {
		
		v->element = elem;
		res = 0;
	}
	
	return res;
}



int bst_insert(BST *tree, void *key, void *elem) {
	
	int res;
	BNode *v;
	
	v = bst_treeSearch(tree, key, bst_root(tree));
	
	if (bst_isExternal(v) == 1) {
		
		bst_expandExternal(v);
		v->key = key;
		v->element = elem;
		tree->size++;
		
		res = 0;
	}
	else {
		
		res = -1;
	}
	
	return res;
}



int bst_remove(BST *tree, void *key, void **elem) {
	
	int res;
	int left_external, right_external;
	int both_internal;
	
	BNode *w;
	BNode *leftChild, *rightChild;
	BNode *z, *y, *x;
	
	Queue order;
	
	z = 0;
	queue_init(&order, 0);
	w = bst_treeSearch(tree, key, bst_root(tree));
	
	if (bst_isExternal(w) == 1) {
		
		res = -1;
	}
	else if (bst_isInternal(w) == 1) {
		
		leftChild = bst_leftChild(w);
		rightChild = bst_rightChild(w);
		
		left_external = bst_isExternal(leftChild);
		right_external = bst_isExternal(rightChild);
		
		both_internal = !(left_external || right_external);
		
		if (both_internal == 0) {
			
			if (left_external == 1) z = leftChild;
			if (right_external == 1) z = rightChild;
			
			*elem = w->element;
			bst_removeAboveExternal(tree, z);
			
		}
		else if (both_internal == 1) {
			
			*elem = w->element;
			bst_inorder(tree, rightChild, &order);
			
			queue_dequeue(&order, (void**)&x);
			queue_dequeue(&order, (void**)&y);
			
			w->element = y->element;
			y->element = 0;
			
			bst_removeAboveExternal(tree, x);			
		}
		
		tree->size--;
		res = 0;
	}
	queue_destroy(&order);
	
	return res;
}

