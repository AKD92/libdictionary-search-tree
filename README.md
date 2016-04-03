# Tree Based Dictionary ADT

<img align="right" src="https://github.com/AKD92/Tree-Based-Dictionary-ADT/raw/master/bst.png">

Dictionary or Map is an Abstract Data Type that stores a collection of two cohesive elements: <i>a key and a value</i>. The key must be unique and camparable on its own domain, and the value that is being mapped can be anything: a sting, a block of memory, an integer, an array, or even user-defined data structures containing thousands of other data structures.

The primary application of Dictionary ADT is to facilitate a fast and efficient <b>look-up (search)</b> operation for a specific key among the others. Generally this look-up operation relys on the comparability and uniqueness of the key.

The design of good Dictionary data structure means good algorithmic performance in 3 general areas:
  * <b>Insertion</b> : Insert a key and a value to Dictionary
  * <b>Deletion</b>  : Delete a key and its corresponding value from Dictionary
  * <b>Look-up</b>   : Efficiently search for a given key in Dictionary, and if found, return its corresponding value object to the caller.

### About This Implementation
This Dictionary ADT is implemented using <b>Binary Search Tree (BST).</b> This data structure allows very efficient look-up through using <i>Binary Search algorithm</i>. The implementation begins by creating and using structures of Nodes and Links (pointers). Because of using C language, memory allocation and clean-up is necessary. A typical starting point of using this dictionary is to create an instance of BST as a variable and initialize it by calling <b>bst_init()</b> function while passing some function pointers on it as arguments. After we are done with our BST, we should destroy it with <b>bst_destroy()</b> function.

The key and the value objects are stored in BST as <b>generic pointers (void *)</b> of actual objects. User should take care about <i>allocation and destruction</i> of key and value objects, and while a dictionary is being used (not destroyed yet), the actual key and value data must not be changed by other means. More information related to program interfaces can be found in <b>bst.h</b> header file.

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
  * All the algorithms implemented so far are all Iterative. Traditional recursive algorithms are converted to iterative algorithms by using Stack and Queue.
  * This project is built as a 32-bit Static C library, so that any C application program can use this data structure very easily.
  * To build from the source, linking to dependent libraries is necessary. Link order for GCC is: -lstq -llinkedlist

### Reference Book:
Implementation techniques follow the principles from the book <a href="http://ww3.algorithmdesign.net/">Algorithm Design</a> by Michael T. Goodrich and Roberto Tamassia.

### License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.
