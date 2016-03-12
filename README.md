# Dictionary ADT

Dictionary or Map is an Abstract Data Type where we store a collection of two cohesive data: a key and a value. The key must be unique and camparable on their domain, and the value they maps can be anything, a sting, a block of memory, an integer or even a long list of various customized data.

The main application of a Dictionary is to look-up (search) for a specific key stored on it <b>efficiently.</b> Generally the look-up is conducted via the key, and thats why key must be unique and comparable.

The design of good Dictionary data structure means good algorithmic performance in 3 general areas:
  * Insertion : Insert a key and a value to Dictionary
  * Deletion  : Delete a key and its corresponding value from Dictionary
  * Search    : Efficiently search for a given key in Dictionary, and if found, return its corresponding value object to the caller.

### About This Implementation
This Dictionary ADT is implemented using <b>Binary Search Tree</b> (BST). BST is implemented internally using Nodes and Links. Because of using C language, memory allocation and clran-up is necessary. We should typically create an instance of BST Dictionary by calling <b>bst_init()</b> function while passing a function pointer on it as an argument. After we are done with our BST, we should destroy it with <b>bst_destroy()</b> function.

The key and the value objects are stored in BST by supplying <b>generic void * pointers</b> of those objects. User should take care about allocation and destruction of key and value objects. More information related to interfaces can be found in <b>bst.h</b> header file.

### Signatures of some function pointers:
  * int (*compare_key) (const void *key1, const void *key2) : For comparing two keys, which are stored on this BST.
  * void (*destroy_key) (void *key) : For destroying keys on the time of destruction of the BST itself.
  * void (*destroy_data) (void *data) : For destroying user data objects on the time of destruction of the BST itself.

### Performance Analysis
  * Insertion : O(log n)         [Average Case]
  * Deletion  : O(log n)         [Average Case]
  * Search    : O(log n)         [Average Case]


### Reference Book:
Implementation follows from the principles of the book <a href="http://ww3.algorithmdesign.net/">"Algorithm Design" by Michael T. Goodrich and Roberto Tamassia</a>

