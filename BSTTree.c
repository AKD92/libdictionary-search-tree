
#include "BSTTree.h"
#include <stack.h>
#include <queue.h>
#include <stdlib.h>
#include <string.h>

int bst_cmp_byNode(const void *key1, const void *key2);

int bst_destroy_node(BSTTree *tree, BNode *node);


int bst_init(BSTTree *tree) {
	
	tree->size = 0;
	tree->root = (BNode*) malloc(sizeof(BNode));
	memset(tree->root, 0, sizeof(BNode));
	
	return 0;
}

void bst_destroy(BSTTree *tree) {
	
	Queue nodes;
	BNode *n;
	
	queue_init(&nodes, 0);
	bst_postorder(tree, bst_root(tree), &nodes);
	
	while (queue_size(&nodes) > 0) {
		
		queue_dequeue(&nodes, (void**)&n);
		bst_destroy_node(tree, n);
	}
	
	queue_destroy(&nodes);
	memset(tree, 0, sizeof(BSTTree));
	
	return;
}

unsigned int bst_size(const BSTTree *tree) {
	
	return tree->size;
}

BNode * bst_root(const BSTTree *tree) {
	
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
	
	if ((left || right) == 0) {
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
	
	if ((left || right) == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

int bst_isRoot(const BSTTree *tree, const BNode *v) {
	
	if (v == bst_root(tree)) {
		return 1;
	}
	else {
		return 0;
	}
}


int bst_postorder(BSTTree *tree, BNode *v, Queue *out) {
	
	BNode *n;
	BNode *n_left, *n_right;
	
	Stack st1, st2;
	
	stack_init(&st1, 0);
	stack_init(&st2, 0);
	
	stack_push(&st1, v);
	
	while (stack_size(&st1) > 0) {
		
		stack_pop(&st1, (void**)&n);
		stack_push(&st2, n);
		
		n_left = bst_leftChild(n);
		n_right = bst_rightChild(n);
		
		if (n_left != 0) {
			stack_push(&st1, bst_leftChild(n));
		}
		if (n_right != 0) {
			stack_push(&st1, bst_rightChild(n));
		}
	}
	
	while (stack_size(&st2) > 0) {
		
		stack_pop(&st2, (void**)&n);
		queue_enqueue(out, n);
	}
	
	return 0;
}

int bst_inorder(BSTTree *tree, BNode *v, Queue *out) {
	
	BNode *n;
	BNode *n_left, *n_right;
	int cmpres;
	
	Stack st;
	/*	Queue out;*/
	
	stack_init(&st, 0);
	/*	queue_init(&out, 0);*/
	
	stack_push(&st, v);
	
	while (stack_size(&st) > 0) {
		
		stack_pop(&st, (void**)&n);
		n_left = bst_leftChild(n);
		n_right = bst_rightChild(n);
		
		cmpres = queue_contains(out, (void*) n_left, bst_cmp_byNode);
		
		if (n_left != 0 && cmpres == 0) {
			stack_push(&st, n);
			stack_push(&st, n_left);
		}
		else {
			
			queue_enqueue(out, n);
			if (n_right != 0) {
				stack_push(&st, n_right);
			}
		}
		
	}
	
	/*	while (queue_size(&out) > 0) {*/
	
	/*		queue_dequeue(&out, &n);*/
	/*		cmpres = visit(n);*/
	/*		if (cmpres == -1) break;*/
	/*	}*/
	
	stack_destroy(&st);
	/*	queue_destroy(&out);*/
	
	return 0;
}


/**************************	 BST SPECIFIC FUNCTIONS  ***************************/

BNode * bst_treeSearch(BSTTree *tree, void *key, BNode *startNode) {
	
	int cmpres;
	
	/*	printf("treeSearch: Is v the root? %d\n", bst_isRoot(tree, v));*/
	/*	printf("treeSearch: Is v external? %d\n", bst_isExternal(v));*/
	
	while (bst_isExternal(startNode) != 1) {
		
		cmpres = tree->compare_key(key, startNode->key);
		
		if (cmpres == 0) {
			break;
		}
		else if (cmpres < 0) {
			startNode = bst_leftChild(startNode);
		}
		else if (cmpres > 0) {
			startNode = bst_rightChild(startNode);
		}
	}
	
	return startNode;
}

/*	Searches for a given key in the BST
Return 0 if successful, -1 otherwise
*/


int bst_findElement(BSTTree *tree, void *key, void **elem) {
	
	int res;
	BNode *v;
	v = bst_treeSearch(tree, key, bst_root(tree));
	
	if (bst_isInternal(v) == 1) {
		*elem = v->element;
		res = 0;
	}
	else if (bst_isExternal(v) == 1) {
		res = -1;
	}
	
	return res;
}


int bst_insert(BSTTree *tree, void *key, void *elem) {
	
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


int bst_changeElement(BSTTree *tree, void *key, void *elem){
	
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


int bst_remove(BSTTree *tree, void *key, void **elem) {
	
	int res;
	int left_external, right_external;
	int both_internal;
	
	BNode *w;
	BNode *leftChild, *rightChild;
	BNode *z, *y, *x;
	
	Queue order;
	
	w = bst_treeSearch(tree, key, bst_root(tree));
	z = 0;
	queue_init(&order, 0);
	
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


int bst_removeAboveExternal(BSTTree *tree, BNode *nodeExternal) {
	
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


int bst_keys(BSTTree *tree, List *keyList) {
	
	ListElem *n;
	BNode *node;
	Queue nodeQ;
	
	queue_init(&nodeQ, 0);
	list_init(keyList, 0);
	n = list_head(keyList);
	
	bst_inorder(tree, bst_root(tree), &nodeQ);
	
	while (queue_size(&nodeQ) > 0) {
		
		queue_dequeue(&nodeQ, (void**) &node);
		
		if (bst_isInternal(node)) {
			
			list_ins_next(keyList, n, node->key);
			n = list_tail(keyList);
		}
	}
	
	queue_destroy(&nodeQ);
	return 0;
}

int bst_elements(BSTTree *tree, List *elementList) {
	
	ListElem *n;
	BNode *node;
	Queue nodeQ;
	
	queue_init(&nodeQ, 0);
	list_init(elementList, 0);
	n = list_tail(elementList);
	
	bst_inorder(tree, bst_root(tree), &nodeQ);
	
	while (queue_size(&nodeQ) > 0) {
		
		queue_dequeue(&nodeQ, (void**)&node);
		
		if (bst_isInternal(node)) {
			
			list_ins_next(elementList, n, node->element);
			n = list_tail(elementList);
		}
	}
	
	queue_destroy(&nodeQ);
	return 0;
}

/****************************	INTER-MODULE FUNCTIONS *************************/

int bst_cmp_byNode(const void *key1, const void *key2) {
	
	if (key1 == key2) return 0;
	else return 1;
	
}

int bst_destroy_node(BSTTree *tree, BNode *node) {
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
