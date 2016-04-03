

/************************************************************************************
	Implementation of BST Tree Traversal Algorithms
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:				https://github.com/AKD92
*************************************************************************************/






#include "bst.h"
#include <stack.h>
#include <queue.h>






#define CMP_KEY_POINTER(k1, k2) ((k1) == (k2) ? 0 : 1)








static int cmpKeyPointer(const void *key1, const void *key2);





static int cmpKeyPointer(const void *key1, const void *key2) {
	
	if (key1 == key2) return 0;
	else return 1;
}




int bst_preOrder(const BST *tree, BNode *startNode, Queue *out) {
	
	Stack tmpStack;
	int isInternal;
	const BNode *pNode;
	const BNode *leftChild, *rightChild;
	
	if (startNode == 0 || out == 0)
		return -1;
	
	stack_init(&tmpStack, 0);
	stack_push(&tmpStack, (const void *) startNode);
	
	while (stack_size(&tmpStack) > 0) {
		
		stack_pop(&tmpStack, (void **) &pNode);
		queue_enqueue(out, (const void *) pNode);
		
		isInternal = bst_isInternal(pNode);
		if (isInternal == 1) {
			rightChild = bst_rightChild(pNode);
			leftChild = bst_leftChild(pNode);
			stack_push(&tmpStack, (const void *) rightChild);
			stack_push(&tmpStack, (const void *) leftChild);
		}
	}
	
	stack_destroy(&tmpStack);
	return 0;
}



int bst_postOrder(const BST *tree, BNode *startNode, Queue *out) {
	
	BNode *node;
	BNode *nodeLeftChild, *nodeRightChild;
	Stack st1, st2;
	
	if (startNode == 0 || out == 0)
		return -1;
	
	stack_init(&st1, 0);
	stack_init(&st2, 0);
	stack_push(&st1, (const void *) startNode);
	
	while (stack_size(&st1) > 0) {
		
		stack_pop(&st1, (void **) &node);
		stack_push(&st2, (const void *) node);
		
		nodeLeftChild = bst_leftChild((const BNode *) node);
		nodeRightChild = bst_rightChild((const BNode *) node);
		
		if (nodeLeftChild != 0) {
			stack_push(&st1, (const void *) nodeLeftChild);
		}
		if (nodeRightChild != 0) {
			stack_push(&st1, (const void *) nodeRightChild);
		}
	}
	
	while (stack_size(&st2) > 0) {
		stack_pop(&st2, (void **) &node);
		queue_enqueue(out, (const void *) node);
	}
	
	stack_destroy(&st1);
	stack_destroy(&st2);
	return 0;
}




int bst_inOrder(const BST *tree, BNode *startNode, Queue *out) {
	
	BNode *node;
	BNode *nodeLeftChild, *nodeRightChild;
	int opCompare;
	Stack st;
	
	if (startNode == 0 || out == 0)
		return -1;
	
	stack_init(&st, 0);
	stack_push(&st, (const void *) startNode);
	
	while (stack_size(&st) > 0) {
		
		stack_pop(&st, (void **) &node);
		
		nodeLeftChild = bst_leftChild((const BNode *) node);
		nodeRightChild = bst_rightChild((const BNode *) node);
		
		opCompare = queue_linearSearch(out, (void*) nodeLeftChild, cmpKeyPointer);
		
		if (nodeLeftChild != 0 && opCompare == 0) {
			stack_push(&st, (const void *) node);
			stack_push(&st, (const void *) nodeLeftChild);
		}
		else {
			queue_enqueue(out, (const void *) node);
			if (nodeRightChild != 0) {
				stack_push(&st, (const void *) nodeRightChild);
			}
		}
	}
	
	stack_destroy(&st);
	return 0;
}



int bst_levelOrderLR(const BST *tree, BNode *startNode, Queue *out) {
	
	Queue tmpQueue;
	int isInternal;
	const BNode *pNode;
	const BNode *leftChild, *rightChild;
	
	if (startNode == 0 || out == 0)
		return -1;
	
	queue_init(&tmpQueue, 0);
	queue_enqueue(&tmpQueue, (const void *) startNode);
	
	while (queue_size(&tmpQueue) > 0) {
		
		queue_dequeue(&tmpQueue, (void **) &pNode);
		queue_enqueue(out, (const void *) pNode);
		
		isInternal = bst_isInternal(pNode);
		if (isInternal == 1) {
			leftChild = bst_leftChild(pNode);
			rightChild = bst_rightChild(pNode);
			queue_enqueue(&tmpQueue, (const void *) leftChild);
			queue_enqueue(&tmpQueue, (const void *) rightChild);
		}
	}
	
	queue_destroy(&tmpQueue);
	return 0;
}




int bst_levelOrderRL(const BST *tree, BNode *startNode, Queue *out) {
	
	Queue tmpQueue;
	int isInternal;
	const BNode *pNode;
	const BNode *leftChild, *rightChild;
	
	if (startNode == 0 || out == 0)
		return -1;
	
	queue_init(&tmpQueue, 0);
	queue_enqueue(&tmpQueue, (const void *) startNode);
	
	while (queue_size(&tmpQueue) > 0) {
		
		queue_dequeue(&tmpQueue, (void **) &pNode);
		queue_enqueue(out, (const void *) pNode);
		
		isInternal = bst_isInternal(pNode);
		if (isInternal == 1) {
			rightChild = bst_rightChild(pNode);
			leftChild = bst_leftChild(pNode);
			queue_enqueue(&tmpQueue, (const void *) rightChild);
			queue_enqueue(&tmpQueue, (const void *) leftChild);
		}
	}
	
	queue_destroy(&tmpQueue);
	return 0;
}




int bst_eraseExternalLinks(Queue *nodeQueue) {
	
	int isInternal;
	const BNode *pNode;
	unsigned int size;
	register unsigned int index;
	
	if (nodeQueue == 0)
		return -1;
	
	index = 0;
	size = queue_size(nodeQueue);
	while (index < size) {
		
		queue_dequeue(nodeQueue, (void **) &pNode);
		
		isInternal = bst_isInternal(pNode);
		if (isInternal == 1) {
			queue_enqueue(nodeQueue, (const void *) pNode);
		}
		index = index + 1;
	}
	
	return 0;
}

