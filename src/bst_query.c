

/************************************************************************************
	Implementation of BST Query Functions
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
*************************************************************************************/






#include "bst.h"







unsigned int bst_size(const BST *tree) {
	
	return tree->size;
}



BNode * bst_root(const BST *tree) {
	
	return tree == 0 ? 0 : tree->root;
}



BNode * bst_parent(const BNode *v) {
	
	return v == 0 ? 0 : v->parent;
}



BNode * bst_leftChild(const BNode *v) {
	
	return v == 0 ? 0 : v->leftChild;
}



BNode * bst_rightChild(const BNode *v) {
	
	return v == 0 ? 0 : v->rightChild;
}



BNode * bst_sibling(const BNode *v) {
	
	BNode *sibling;
	BNode *parent;
	
	parent = bst_parent(v);
	if (parent == 0) sibling = 0;
	
	else {
		
		if (v == bst_leftChild(parent)) {
			sibling = bst_rightChild(parent);
		}
		else if (v == bst_rightChild(parent)) {
			sibling = bst_leftChild(parent);
		}
	}
	
	return sibling;
}



int bst_isExternal(const BNode *v) {
	
	BNode *left, *right;
	
	left = bst_leftChild(v);
	right = bst_rightChild(v);
	
	if (((int)left | (int)right) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}



int bst_isInternal(const BNode *v) {
	
	BNode *left, *right;
	
	left = bst_leftChild(v);
	right = bst_rightChild(v);
	
	if (((int)left | (int)right) != 0) {
		return 1;
	}
	else {
		return 0;
	}
}



int bst_isRoot(const BST *tree, const BNode *v) {
	
	if (v == bst_root(tree)) {
		return 1;
	}
	else {
		return 0;
	}
}
