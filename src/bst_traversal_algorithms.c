

/************************************************************************************
	Implementation of Binary Search Tree Traversal Algorithms
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bst.h"
#include <stack.h>
#include <queue.h>









int bst_preOrder(const BisTree *pTree, BNode *pStartNode, Queue *qPreorder) {
	
	Stack stNodes;
	int isInternal;
	const BNode *pNode;
	const BNode *pLeftChild, *pRightChild;
	
	if (pStartNode == 0 || qPreorder == 0)
		return -1;
	
	pNode = 0;
	pLeftChild = pRightChild = 0;
	stack_init(&stNodes, 0);
	stack_push(&stNodes, (const void *) pStartNode);
	
	while (stack_size(&stNodes) > 0) {
		
		stack_pop(&stNodes, (void **) &pNode);
		queue_enqueue(qPreorder, (const void *) pNode);
		
		isInternal = bst_isInternal(pNode);
		if (isInternal == 1) {
			pRightChild = bst_rightChild(pNode);
			pLeftChild = bst_leftChild(pNode);
			stack_push(&stNodes, (const void *) pRightChild);
			stack_push(&stNodes, (const void *) pLeftChild);
		}
	}
	
	stack_destroy(&stNodes);
	return 0;
}



int bst_inOrder(const BisTree *pTree, BNode *pStartNode, Queue *qInorder) {
	
	Stack stNodes;
	BNode *pNode;
	
	if (pStartNode == 0 || qInorder == 0)
		return -1;
	
	pNode = pStartNode;
	stack_init(&stNodes, 0);
	
	REPEAT:
	while (pNode != 0) {
		stack_push(&stNodes, (const void *) pNode);
		pNode = bst_leftChild((const BNode *) pNode);
	}
	
	if (stack_size(&stNodes) > 0) {
		stack_pop(&stNodes, (void **) &pNode);
		queue_enqueue(qInorder, (const void *) pNode);
		pNode = bst_rightChild((const BNode *) pNode);
		goto REPEAT;
	}
	
	stack_destroy(&stNodes);
	return 0;
}



int bst_postOrder(const BisTree *pTree, BNode *pStartNode, Queue *qPostorder) {
	
	BNode *pNode;
	BNode *pLeftChild, *pRightChild;
	Stack stNodes1, stNodes2;
	
	if (pStartNode == 0 || qPostorder == 0)
		return -1;
	
	pNode = 0;
	pLeftChild = pRightChild = 0;
	stack_init(&stNodes1, 0);
	stack_init(&stNodes2, 0);
	stack_push(&stNodes1, (const void *) pStartNode);
	
	while (stack_size(&stNodes1) > 0) {
		
		stack_pop(&stNodes1, (void **) &pNode);
		stack_push(&stNodes2, (const void *) pNode);
		
		pLeftChild = bst_leftChild((const BNode *) pNode);
		pRightChild = bst_rightChild((const BNode *) pNode);
		
		if (pLeftChild != 0) {
			stack_push(&stNodes1, (const void *) pLeftChild);
		}
		if (pRightChild != 0) {
			stack_push(&stNodes1, (const void *) pRightChild);
		}
	}
	
	while (stack_size(&stNodes2) > 0) {
		stack_pop(&stNodes2, (void **) &pNode);
		queue_enqueue(qPostorder, (const void *) pNode);
	}
	
	stack_destroy(&stNodes1);
	stack_destroy(&stNodes2);
	return 0;
}



int bst_levelOrderLR(const BisTree *pTree, BNode *pStartNode, Queue *qLRorder) {
	
	Queue qNodes;
	int isInternal;
	const BNode *pNode;
	const BNode *pLeftChild, *pRightChild;
	
	if (pStartNode == 0 || qLRorder == 0)
		return -1;
	
	pNode = 0;
	pLeftChild = pRightChild = 0;
	queue_init(&qNodes, 0);
	queue_enqueue(&qNodes, (const void *) pStartNode);
	
	while (queue_size(&qNodes) > 0) {
		
		queue_dequeue(&qNodes, (void **) &pNode);
		queue_enqueue(qLRorder, (const void *) pNode);
		
		isInternal = bst_isInternal(pNode);
		if (isInternal == 1) {
			pLeftChild = bst_leftChild(pNode);
			pRightChild = bst_rightChild(pNode);
			queue_enqueue(&qNodes, (const void *) pLeftChild);
			queue_enqueue(&qNodes, (const void *) pRightChild);
		}
	}
	
	queue_destroy(&qNodes);
	return 0;
}




int bst_levelOrderRL(const BisTree *pTree, BNode *pStartNode, Queue *qRLorder) {
	
	Queue qNodes;
	int isInternal;
	const BNode *pNode;
	const BNode *pLeftChild, *pRightChild;
	
	if (pStartNode == 0 || qRLorder == 0)
		return -1;
	
	queue_init(&qNodes, 0);
	queue_enqueue(&qNodes, (const void *) pStartNode);
	
	while (queue_size(&qNodes) > 0) {
		
		queue_dequeue(&qNodes, (void **) &pNode);
		queue_enqueue(qRLorder, (const void *) pNode);
		
		isInternal = bst_isInternal(pNode);
		if (isInternal == 1) {
			pRightChild = bst_rightChild(pNode);
			pLeftChild = bst_leftChild(pNode);
			queue_enqueue(&qNodes, (const void *) pRightChild);
			queue_enqueue(&qNodes, (const void *) pLeftChild);
		}
	}
	
	queue_destroy(&qNodes);
	return 0;
}




int bst_eraseExternalLinks(Queue *qNodes) {
	
	int isInternal;
	const BNode *pNode;
	unsigned int qSize;
	register unsigned int index;
	
	if (qNodes == 0)
		return -1;
	
	index = 0;
	qSize = queue_size(qNodes);
	
	while (index < qSize) {
		queue_dequeue(qNodes, (void **) &pNode);
		isInternal = bst_isInternal(pNode);
		if (isInternal == 1) {
			queue_enqueue(qNodes, (const void *) pNode);
		}
		index = index + 1;
	}
	
	return 0;
}

