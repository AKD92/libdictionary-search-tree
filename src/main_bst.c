


#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <queue.h>



int cmpInt(const void *k1, const void *k2);

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(void) {
    
    BisTree btree;
    Queue nodes;
    int *pKey, *pRemovedKey;
    List *list;
    ListElem *elem;
    BNode *pNode;
    int keys[12] = {44, 17, 88, 28, 65, 97, 29, 54, 82, 76, 80, 78};
    int i = 0;
    unsigned int depth, height;
    
    bst_init(&btree, cmpInt, 0, 0);
    queue_init(&nodes, 0);
    
    printf("\nInserting 12 auto-allocated key\n");
    while (i < 12) {
        bst_insert(&btree, (const void *) &keys[i], 0);
        i++;
    }
    pKey = (int *) malloc(sizeof(int));
    *pKey = 77;
    bst_insert(&btree, pKey, 0);
    printf("\nInserted a manually allocated key, addr: %p, val: %d\n\n",
                    pKey, *pKey);
    pKey = 0;
    
    bst_levelOrderLR(bst_root(&btree), &nodes);
    printf("Printing after insertion (Level LR Order) (Internal+External = %u)\n",
                            queue_size(&nodes));
    bst_eraseExternalLinks(&nodes);
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    
    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    bst_preOrder(bst_root(&btree), &nodes);
    printf("Printing after insertion (Pre Order) (Internal+External = %u)\n",
                            queue_size(&nodes));
    bst_eraseExternalLinks(&nodes);
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    

    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    bst_postOrder(bst_root(&btree), &nodes);
    printf("Printing after insertion (Post Order) (Internal+External = %u)\n",
                            queue_size(&nodes));
    bst_eraseExternalLinks(&nodes);
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    
    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    bst_inOrder(bst_root(&btree), &nodes);
    printf("Printing after insertion (In Order) (Internal+External = %u)\n",
                            queue_size(&nodes));
    bst_eraseExternalLinks(&nodes);
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    
    pKey = (int *) malloc(sizeof(int));
    *pKey = 88;
    pNode = bst_binarySearch(&btree, (const void *) pKey, bst_root(&btree));
    
    depth = bst_depth(&btree, pNode);
    height = bst_height(&btree, pNode);
    printf("Depth of %d: %u, Height of %d: %u\n\n", *pKey, depth, *pKey, height);
    free(pKey);
    
    height = bst_height(&btree, bst_root(&btree));
    printf("Height of Root: %u\n\n", height);
    
    pKey = (int *) malloc(sizeof(int));
    *pKey = 77;
    bst_remove(&btree, pKey, (void **) &pRemovedKey, 0);
    free(pKey);
    printf("Removed Key addr: %p, Value: %d\n", pRemovedKey, *pRemovedKey);
    free(pRemovedKey);
    printf("Again Removed Key addr: %p, Value: %d\n\n", pRemovedKey, *pRemovedKey);
    
    pKey = (int *) malloc(sizeof(int));
    *pKey = 44;
    bst_remove(&btree, pKey, (void **) &pRemovedKey, 0);
    free(pKey);
    printf("Removed Key addr: %p, Value: %d\n", pRemovedKey, *pRemovedKey);
    printf("Again Removed Key addr: %p, Value: %d\n\n", pRemovedKey, *pRemovedKey);
    
    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    bst_levelOrderLR(bst_root(&btree), &nodes);
    printf("Printing after removal (Level LR Order) (Internal+External = %u)\n",
                            queue_size(&nodes));
    bst_eraseExternalLinks(&nodes);
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    
    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    bst_preOrder(bst_root(&btree), &nodes);
    printf("Printing after removal (Pre Order) (Internal+External = %u)\n",
                            queue_size(&nodes));
    bst_eraseExternalLinks(&nodes);
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    
    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    bst_postOrder(bst_root(&btree), &nodes);
    printf("Printing after insertion (Post Order) (Internal+External = %u)\n",
                            queue_size(&nodes));
    bst_eraseExternalLinks(&nodes);
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    
    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    bst_inOrder(bst_root(&btree), &nodes);
    printf("Printing after removal (In Order) (Internal+External = %u)\n",
                            queue_size(&nodes));
    bst_eraseExternalLinks(&nodes);
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    
    height = bst_height(&btree, bst_root(&btree));
    printf("Height of Root: %u\n\n", height);
    
    queue_destroy(&nodes);
    printf("Queue destroyed\n");
    bst_destroy(&btree);
    printf("BST destroyed\n");
    
    return 0;
}


int cmpInt(const void *k1, const void *k2) {
    int *i1 = (int *) k1;
    int *i2 = (int *) k2;
    
    return (*i1 - *i2);
}
