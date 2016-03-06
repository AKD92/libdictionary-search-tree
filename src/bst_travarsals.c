


#include "bst.h"
#include <stack.h>
#include <queue.h>







int bst_cmp_byNode(const void *key1, const void *key2);



int bst_cmp_byNode(const void *key1, const void *key2) {
	
	if (key1 == key2) return 0;
	else return 1;
	
}




int bst_postorder(BST *tree, BNode *v, Queue *out) {
	
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




int bst_inorder(BST *tree, BNode *v, Queue *out) {
	
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
