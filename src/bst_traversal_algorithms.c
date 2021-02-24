

/************************************************************************************
    Implementation of Binary Search Tree Traversal Algorithms
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bst.h"
#include "bst_internal.h"
#include <stack.h>
#include <queue.h>









int bst_preorder(BNode *pStartNode, int nodeType, Queue *qPreorder) {
    
    Stack stNodes;
    int isInternal;
    int allowInternal, allowExternal;
    BNode *pNode;
    BNode *pLeftChild, *pRightChild;
    
    if (pStartNode == 0 || qPreorder == 0)
        return -1;
    
    pNode = 0;
    pLeftChild = pRightChild = 0;
    allowInternal = nodeType & BNODE_ALLOW_INTERNAL;
    allowExternal = nodeType & BNODE_ALLOW_EXTERNAL;
    stack_init(&stNodes, 0);
    stack_push(&stNodes, (const void *) pStartNode);
    
    while (stack_size(&stNodes) > 0) {
        
        stack_pop(&stNodes, (void **) &pNode);
        isInternal = bst_is_internal(pNode);
        
        if ((isInternal == 1 && allowInternal != 0) ||
            (isInternal == 0 && allowExternal != 0))
            queue_enqueue(qPreorder, (const void *) pNode);
        
        if (isInternal == 1) {
            pRightChild = bst_rightchild(pNode);
            pLeftChild = bst_leftchild(pNode);
            stack_push(&stNodes, (const void *) pRightChild);
            stack_push(&stNodes, (const void *) pLeftChild);
        }
    }
    
    stack_destroy(&stNodes);
    return 0;
}



int bst_inorder(BNode *pStartNode, int nodeType, Queue *qInorder) {
    
    Stack stNodes;
    BNode *pNode;
    int allowInternal, allowExternal;
    int isInternal;
    
    if (pStartNode == 0 || qInorder == 0)
        return -1;
    
    allowInternal = nodeType & BNODE_ALLOW_INTERNAL;
    allowExternal = nodeType & BNODE_ALLOW_EXTERNAL;
    pNode = pStartNode;
    stack_init(&stNodes, 0);
    
    REPEAT:
    while (pNode != 0) {
        stack_push(&stNodes, (const void *) pNode);
        pNode = bst_leftchild(pNode);
    }
    
    if (stack_size(&stNodes) > 0) {
        stack_pop(&stNodes, (void **) &pNode);
        isInternal = bst_is_internal(pNode);
        
        if ((isInternal == 1 && allowInternal != 0) ||
            (isInternal == 0 && allowExternal != 0))
            queue_enqueue(qInorder, (const void *) pNode);
        
        pNode = bst_rightchild(pNode);
        goto REPEAT;
    }
    
    stack_destroy(&stNodes);
    return 0;
}



int bst_reverse_inorder(BNode *pStartNode, int nodeType, Queue *qInorder) {
    
    Stack stNodes;
    BNode *pNode;
    int allowInternal, allowExternal;
    int isInternal;
    
    if (pStartNode == 0 || qInorder == 0)
        return -1;
    
    allowInternal = nodeType & BNODE_ALLOW_INTERNAL;
    allowExternal = nodeType & BNODE_ALLOW_EXTERNAL;
    pNode = pStartNode;
    stack_init(&stNodes, 0);
    
    REPEAT:
    while (pNode != 0) {
        stack_push(&stNodes, (const void *) pNode);
        pNode = bst_rightchild(pNode);
    }
    
    if (stack_size(&stNodes) > 0) {
        stack_pop(&stNodes, (void **) &pNode);
        isInternal = bst_is_internal(pNode);
        
        if ((isInternal == 1 && allowInternal != 0) ||
            (isInternal == 0 && allowExternal != 0))
            queue_enqueue(qInorder, (const void *) pNode);
        
        pNode = bst_leftchild(pNode);
        goto REPEAT;
    }
    
    stack_destroy(&stNodes);
    return 0;
}



int bst_postorder(BNode *pStartNode, int nodeType, Queue *qPostorder) {
    
    BNode *pNode;
    BNode *pLeftChild, *pRightChild;
    int allowInternal, allowExternal;
    int isExternal;
    Stack stNodesA, stNodesB;
    
    if (pStartNode == 0 || qPostorder == 0)
        return -1;
    
    allowInternal = nodeType & BNODE_ALLOW_INTERNAL;
    allowExternal = nodeType & BNODE_ALLOW_EXTERNAL;
    pNode = 0;
    pLeftChild = pRightChild = 0;
    stack_init(&stNodesA, 0);
    stack_init(&stNodesB, 0);
    stack_push(&stNodesA, (const void *) pStartNode);
    
    while (stack_size(&stNodesA) > 0) {
        
        stack_pop(&stNodesA, (void **) &pNode);
        stack_push(&stNodesB, (const void *) pNode);
        
        pLeftChild = bst_leftchild(pNode);
        pRightChild = bst_rightchild(pNode);
        
        if (pLeftChild != 0) {
            stack_push(&stNodesA, (const void *) pLeftChild);
        }
        if (pRightChild != 0) {
            stack_push(&stNodesA, (const void *) pRightChild);
        }
    }
    
    while (stack_size(&stNodesB) > 0) {
        stack_pop(&stNodesB, (void **) &pNode);
        isExternal = bst_is_external(pNode);
        
        if ((isExternal == 0 && allowInternal != 0) ||
            (isExternal == 1 && allowExternal != 0))
            queue_enqueue(qPostorder, (const void *) pNode);
    }
    
    stack_destroy(&stNodesA);
    stack_destroy(&stNodesB);
    return 0;
}



int bst_levelorder_lr(BNode *pStartNode, int nodeType, Queue *qLRorder) {
    
    Queue qNodes;
    int isInternal;
    int allowInternal, allowExternal;
    BNode *pNode;
    BNode *pLeftChild, *pRightChild;
    
    if (pStartNode == 0 || qLRorder == 0)
        return -1;
    
    allowInternal = nodeType & BNODE_ALLOW_INTERNAL;
    allowExternal = nodeType & BNODE_ALLOW_EXTERNAL;
    pNode = 0;
    pLeftChild = pRightChild = 0;
    queue_init(&qNodes, 0);
    queue_enqueue(&qNodes, (const void *) pStartNode);
    
    while (queue_size(&qNodes) > 0) {
        
        queue_dequeue(&qNodes, (void **) &pNode);
        isInternal = bst_is_internal(pNode);
        
        if ((isInternal == 1 && allowInternal != 0) ||
            (isInternal == 0 && allowExternal != 0))
            queue_enqueue(qLRorder, (const void *) pNode);
        
        if (isInternal == 1) {
            pLeftChild = bst_leftchild(pNode);
            pRightChild = bst_rightchild(pNode);
            queue_enqueue(&qNodes, (const void *) pLeftChild);
            queue_enqueue(&qNodes, (const void *) pRightChild);
        }
    }
    
    queue_destroy(&qNodes);
    return 0;
}




int bst_levelorder_rl(BNode *pStartNode, int nodeType, Queue *qRLorder) {
    
    Queue qNodes;
    int isInternal;
    int allowInternal, allowExternal;
    BNode *pNode;
    BNode *pLeftChild, *pRightChild;
    
    if (pStartNode == 0 || qRLorder == 0)
        return -1;
    
    allowInternal = nodeType & BNODE_ALLOW_INTERNAL;
    allowExternal = nodeType & BNODE_ALLOW_EXTERNAL;
    queue_init(&qNodes, 0);
    queue_enqueue(&qNodes, (const void *) pStartNode);
    
    while (queue_size(&qNodes) > 0) {
        
        queue_dequeue(&qNodes, (void **) &pNode);
        isInternal = bst_is_internal(pNode);
        
        if ((isInternal == 1 && allowInternal != 0) ||
            (isInternal == 0 && allowExternal != 0))
            queue_enqueue(qRLorder, (const void *) pNode);
        
        if (isInternal == 1) {
            pRightChild = bst_rightchild(pNode);
            pLeftChild = bst_leftchild(pNode);
            queue_enqueue(&qNodes, (const void *) pRightChild);
            queue_enqueue(&qNodes, (const void *) pLeftChild);
        }
    }
    
    queue_destroy(&qNodes);
    return 0;
}




