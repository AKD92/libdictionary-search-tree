# Tree Based Dictionary ADT

<img align="right" src="https://github.com/AKD92/Tree-Based-Dictionary-ADT/raw/master/bst.png">

Dictionary or Map is an Abstract Data Type where we store a collection of two cohesive elements: <i>a key and a value</i>. The key must be unique and camparable on its own domain, and the value that is being mapped can be anything: a sting, a block of memory, an integer, an array, or even user-defined data structures containing thousands of other data structures.

The main application of a Dictionary is to <b>look-up (search)</b> for a specific key stored on it <i>efficiently.</i> Generally this look-up relys on the key, and that is why all the keys must be unique and comparable.

The design of good Dictionary data structure means good algorithmic performance in 3 general areas:
  * <b>Insertion</b> : Insert a key and a value to Dictionary
  * <b>Deletion</b>  : Delete a key and its corresponding value from Dictionary
  * <b>Look-up</b>   : Efficiently search for a given key in Dictionary, and if found, return its corresponding value object to the caller.

### About This Implementation
This Dictionary ADT is implemented using <b>Binary Search Tree (BST).</b> Internally we have implemented a Binary Search Tree through using Nodes and Links (pointers). Because of using C language, memory allocation and clean-up is necessary. We should typically create an instance of BST Dictionary by calling <b>bst_init()</b> function while passing some function pointers on it as arguments. After we are done with our BST, we should destroy it with <b>bst_destroy()</b> function.

The key and the value objects are stored in BST by supplying <b>generic pointers (void *)</b> of actual objects. User should take care about <i>allocation and destruction</i> of key and value objects. More information related to interfaces can be found in <b>bst.h</b> header file.

### Signatures of some function pointers:
  * int (*compare_key) (const void *key1, const void *key2) : For comparing two keys, which are stored on this BST.
  * void (*destroy_key) (void *key) : For destroying keys on the time of destruction of the BST itself.
  * void (*destroy_data) (void *data) : For destroying user data objects on the time of destruction of the BST itself.

<img align="right" height="400" width="310" src="https://github.com/AKD92/Tree-Based-Dictionary-ADT/raw/master/book_ds_mtrt.jpg">

### Performance Analysis
Assuming n and h as numbers, where n = Total number of keys in BST, h = Height of BST
  * Insertion : O(lg n)         [Average Case],         O(h)         [Worst Case]
  * Deletion  : O(lg n)         [Average Case],         O(h)         [Worst Case]
  * Look-up   : O(lg n)         [Average Case],         O(h)         [Worst Case]
 
Space complexity is O(2n + 1)

### Some Notes
  * An instance of this dictionary implementation is identified by a BST structure, define in bst.h
  * An instance of tree node in this implementation is identified by a BNode structure, also define in bst.h
  * After creating an instance of BST, initialize it using bst_init() function, before exit call bst_destroy() function to clear memory resources.
  * All the tree traversal algorithms are implemented, they are: PreOrder, InOrder, PostOrder and LevelOrder.
  * Algorithms for obtaining Depth and Height of a specific BNode are implemented.
  * All the algorithms implemented so far are all Iterative. Taditional Recursve algorithms are converted to iterative algorthms by using Stack and Queue.
  * This project is built as a Static C library.
  * To build from the source, linking to dependency libraries is necessary, link order is: -lstq -llinkedlist

### Reference Book:
Implementation follows from the principles of the book <a href="http://ww3.algorithmdesign.net/">"Algorithm Design" by Michael T. Goodrich and Roberto Tamassia</a>

