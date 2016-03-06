


#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H




#include <queue.h>
#include <list.h>





/* Data Structures for Binary Search Tree (BST) */

struct BNode_ {
	
	void *key;
	void *element;
	
	struct BNode_ *parent;
	struct BNode_ *leftChild;
	struct BNode_ *rightChild;
	
};
typedef struct BNode_ BNode;


struct BST_ {
	
	unsigned int size;
	BNode *root;
	
	int (*compare_key) (const void *key1, const void *key2);
	void (*destroy_key) (void *key);
	void (*destroy_data) (void *data);
	
};
typedef struct BST_ BST;








/* Function Prototypes */


int bst_init (BST *tree, int (*compare_key) (const void *k1, const void *k2));

void bst_destroy(BST *tree);


/*********	Accessor methods ****************/

unsigned int bst_size(const BST *tree);

BNode * bst_root(const BST *tree);

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


/*	IsRoot(v)
	Returns 1 if true, v is the root node
	Else return 0, v is not the root node
*/

int bst_isRoot(const BST *tree, const BNode *v);


/*******************************************************************************/
/***************************** TRAVERSAL FUNCTIONS *****************************/
/*******************************************************************************/

/*	In Order traversal
	Enqueues each BNode v to the queue "out", on "in-order" fashion
	BNodes enqueued in the "out" includes all nodes (external + internal)
	returns: 0 for successful
*/

int bst_inorder(BST *tree, BNode *v, Queue *out);


/*	Pre Order traversal
	Calls visit with each node w traversed
	if visit return -1, this algorithms haults immediately & terminate
*/

int bst_preorder(BST *tree, BNode *v, Queue *out);


/*	Post Order traversal
	Calls visit with each node w traversed
	if visit return -1, this algorithms haults immediately & terminate
*/

int bst_postorder(BST *tree, BNode *v, Queue *out);



/*******************************************************************************/
/**************************** BST SPECIFIC FUNCTONS ****************************/
/*******************************************************************************/


BNode * bst_treeSearch(BST *tree, void *key, BNode *startNode);


/*	Searches for a given key in the BST
	Return 0 if successful, -1 otherwise
*/

int bst_findElement(BST *tree, void *key, void **elem);

int bst_insert(BST *tree, void *key, void *elem);

int bst_changeElement(BST *tree, void *key, void *elem);

int bst_remove(BST *tree, void *key, void **elem);


int bst_keys(BST *tree, List *keyList);

int bst_elements(BST *tree, List *elementList);



#endif
