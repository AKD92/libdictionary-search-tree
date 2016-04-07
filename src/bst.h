

/************************************************************************************
	Program Interface of Binary Search Tree Dictionary ADT
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H




#include <list.h>
#include <dlist.h>
#include <queue.h>





/* Data Structures for Binary Search Tree (BisTree) */

struct BNode_ {
	
	void *key;
	void *element;
	
	struct BNode_ *parent;
	struct BNode_ *leftChild;
	struct BNode_ *rightChild;
	
};
typedef struct BNode_ BNode;


struct BisTree_ {
	
	BNode *root;
	unsigned int size;
	
	int (*fpCompareKey) (const void *key1, const void *key2);
	void (*fpDestroyKey) (void *key);
	void (*fpDestroyData) (void *data);
	
};
typedef struct BisTree_ BisTree;











/* Function Prototypes */


int bst_init (BisTree *pTree, int (*fpCompareKey) (const void *k1, const void *k2),
					void (*fpDestroyKey) (void *key), void (*fpDestroyData) (void *data));


void bst_destroy(BisTree *pTree);











/*********	Accessor methods ****************/

unsigned int bst_size(const BisTree *pTree);


BNode * bst_root(const BisTree *pTree);


BNode * bst_parent(const BNode *v);




/*	bst_leftChild(BNode *v)
	Returns the address (pointer) of the left child of v, if it exist
	Else return 0, if v does not have a left child (v is external)
*/
BNode * bst_leftChild(const BNode *v);





/*	bst_rightChild(BNode *v)
	Returns the address (pointer) of the right child of v, if it exist
	Else return 0, if v does not have a right child (v is external)
*/
BNode * bst_rightChild(const BNode *v);





/*	bst_sibling(BNode *v)
	Returns the address (pointer) of the sibling of v, if it exist
*/
BNode * bst_sibling(const BNode *v);





/*	IsExternal(v)
	Returns 1 if true, v is an external node
	Else return 0, v is not an external node
*/
int bst_isExternal(const BNode *v);





/*	IsInternal(v)
	Returns 1 if true, v is an internal node
	Else return 0, v is not an internal node
*/
int bst_isInternal(const BNode *v);





/*	isRoot(v)
	Returns 1 if true, v is the root node
	Else return 0, v is not the r
	oot node
*/
int bst_isRoot(const BisTree *pTree, const BNode *v);





/*	bst_depth(v)
	Returns 1 if true, v is the root node
	Else return 0, v is not the root node
*/
unsigned int bst_depth(const BisTree *pTree, const BNode *v);





/*	bst_height(v)
	Returns 1 if true, v is the root node
	Else return 0, v is not the root node
*/
unsigned int bst_height(const BisTree *pTree, const BNode *v);







/*******************************************************************************/
/***************************** TRAVERSAL FUNCTIONS *****************************/
/*******************************************************************************/




/*	Pre Order traversal
	Enqueues each BNode v to the queue "out", on "pre-order" fashion
	BNodes enqueued in the "out" includes all nodes (external + internal)
	returns: 0 for successful
*/
int bst_preOrder(const BisTree *pTree, BNode *pStartNode, Queue *qPreorder);




/*	In Order traversal
	Enqueues each BNode v to the queue "out", on "in-order" fashion
	BNodes enqueued in the "out" includes all nodes (external + internal)
	returns: 0 for successful
*/
int bst_inOrder(const BisTree *pTree, BNode *pStartNode, Queue *qInorder);




/*	Post Order traversal
	Enqueues each BNode v to the queue "out", on "post-order" fashion
	BNodes enqueued in the "out" includes all nodes (external + internal)
	returns: 0 for successful
*/
int bst_postOrder(const BisTree *pTree, BNode *pStartNode, Queue *qPostorder);

int bst_levelOrderLR(const BisTree *pTree, BNode *pStartNode, Queue *qLRorder);

int bst_levelOrderRL(const BisTree *pTree, BNode *pStartNode, Queue *qRLorder);

int bst_eraseExternalLinks(Queue *qNodes);











/*******************************************************************************/
/*************************** BisTree SPECIFIC FUNCTONS *************************/
/*******************************************************************************/



BNode * bst_binarySearch(const BisTree *pTree, const void *key, BNode *pStartNode);


/*	Searches for a given key in the BisTree
	Return 0 if successful, -1 otherwise
*/

int bst_findElement(const BisTree *pTree, const void *key, void **elem);

int bst_insert(BisTree *pTree, const void *key, const void *elem);

int bst_changeElement(BisTree *pTree, const void *key, const void *elem, void **old_elem);

int bst_remove(BisTree *pTree, const void *key, void **removedKey, void **removedElem);




int bst_keys(const BisTree *pTree, List *keyList);

int bst_elements(const BisTree *pTree, List *elementList);




int bst_sort(List *list, int (*compare) (const void *arg1, const void *arg2));

int bst_sortDList(DList *dlist, int (*compare) (const void *arg1, const void *arg2));


int bst_sortAscending(List *list, int (*compare) (const void *arg1, const void *arg2));

int bst_sortDescending(List *list, int (*compare) (const void *arg1, const void *arg2));


int bst_sortAscendingDList(DList *dlist, int (*compare) (const void *arg1, const void *arg2));

int bst_sortDescendingDList(DList *dlist, int (*compare) (const void *arg1, const void *arg2));



#endif
