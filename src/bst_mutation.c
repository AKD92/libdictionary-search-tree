


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







int bst_expandExternal(BNode *nodeExternal) {
	
	BNode *leftChild, *rightChild;
	
	if (bst_isExternal(nodeExternal) == 0) return -1;
	
	leftChild = (BNode*) malloc(sizeof(BNode));
	rightChild = (BNode*) malloc(sizeof(BNode));
	
	memset((void *) leftChild, 0, sizeof(BNode));
	memset((void *) rightChild, 0, sizeof(BNode));
	
	/* Actually, nodeExternal bocomes an Internal by executing the following codes */
	nodeExternal->leftChild = leftChild;
	nodeExternal->rightChild = rightChild;
	
	leftChild->parent = nodeExternal;
	rightChild->parent = nodeExternal;
	
	return 0;
}


int bst_removeAboveExternal(BST *tree, BNode *nodeExternal) {
	
	int isLeftChild;
	BNode *nodeParent, *nodeHigherParent;			/* v = parent(w), u = parent(v) */
	BNode *nodeSibling;								/* z = sibling(w)				*/
	
	if (bst_isExternal(nodeExternal) == 0) return -1;
	if (bst_parent(nodeExternal) == 0) return -1;
	
	nodeParent = bst_parent(nodeExternal);			/* Parent BNode of specified external BNode */
	nodeHigherParent = bst_parent(nodeParent);		/* Grand parent BNode of specified BNode */
	nodeSibling = bst_sibling(nodeExternal);		/* Sibling or Brother BNode of specified BNode */
	
	
	/* Determine if nodeParent is the Left Child of its parent (nodeHigherParent) */
	isLeftChild = bst_leftChild(nodeHigherParent) == nodeParent ? 1 : 0;
	
	if (tree->destroy_key != 0) {
		tree->destroy_key((void *) nodeParent->key);
	}
	
	/* Destroy parent BNode and specifed external BNode */
	free((void *) nodeParent);
	free((void *) nodeExternal);
	nodeParent = nodeExternal = 0;
	
	nodeSibling->parent = nodeHigherParent;
	
	/* If grand parent exist, adjust its left and right children appropriately */
	if (nodeHigherParent != 0) {
		switch (isLeftChild) {
		case 1:					/* nodeParent is Left Child of nodeHigherParent (Grand parent) */
			nodeHigherParent->leftChild = nodeSibling;
			break;
		case 0:					/* nodeParent is Right Child of nodeHigherParent (Grand parent) */
			nodeHigherParent->rightChild = nodeSibling;
			break;
		default:
			break;
		}
	}
	/* If Grand parent does not exist, make the sibling BNode as tree's Root BNode */
	else {
		tree->root = nodeSibling;
	}
	
	return 0;
}



int bst_changeElement(BST *tree, const void *key, void *elem, void **old_elem) {
	
	int res;
	BNode *v;
	
	v = bst_treeSearch((const BST *) tree, key, bst_root(tree));
	
	if (bst_isExternal((const BNode *) v) == 1) {
		
		res = -1;
	}
	else {
		
		if (old_elem != 0) *old_elem = v->element;
		v->element = elem;
		res = 0;
	}
	
	return res;
}



int bst_insert(BST *tree, const void *key, void *elem) {
	
	int res;
	BNode *targetNode;
	
	/* Search for the key in our BST */
	targetNode = bst_treeSearch(tree, key, bst_root(tree));
	
	/* Key not found, we have got an External BNode */
	/* So make it Internal and assing this Key and Elem to it */
	if (bst_isExternal(targetNode) == 1) {
		
		bst_expandExternal(targetNode);
		targetNode->key = (void *) key;
		targetNode->element = elem;
		tree->size++;
		
		res = 0;
	}
	else {
		
		/* We have got an Internal BNode, it means Key already exist */
		/* In this situation we cannot insert the given Key into our BST */
		res = -1;
	}
	
	return res;
}



int bst_remove(BST *tree, void *key, void **elem) {
	
	int res;
	int left_external, right_external;
	int both_internal;
	
	BNode *targetNode;
	BNode *leftChild, *rightChild;
	BNode *z, *y, *x;
	
	Queue order;
	
	z = 0;
	queue_init(&order, 0);
	targetNode = bst_treeSearch(tree, key, bst_root(tree));
	
	if (bst_isExternal(targetNode) == 1) {
		
		res = -1;
	}
	else if (bst_isInternal(targetNode) == 1) {
		
		leftChild = bst_leftChild(targetNode);
		rightChild = bst_rightChild(targetNode);
		
		left_external = bst_isExternal(leftChild);
		right_external = bst_isExternal(rightChild);
		
		/* Both childs are internal if Left And Right childs are NOT External */
		both_internal = !(left_external | right_external);
		
		if (both_internal == 0) {
			
			/* Find the External child of targetNode and z will be the External one */
			if (left_external == 1) z = leftChild;
			if (right_external == 1) z = rightChild;
			
			if (elem != 0) *elem = targetNode->element;
			bst_removeAboveExternal(tree, z);
			
		}
		else if (both_internal == 1) {
			
			if (elem != 0) *elem = targetNode->element;
			bst_inorder(tree, rightChild, &order);
			
			/* Find two External Node from Inorder sequence */
			/* More information about this operation on the Book */
			queue_dequeue(&order, (void **) &x);
			queue_dequeue(&order, (void **) &y);
			
			targetNode->element = y->element;
			y->element = 0;
			
			bst_removeAboveExternal(tree, x);			
		}
		
		tree->size--;
		res = 0;
	}
	
	queue_destroy(&order);
	
	return res;
}

