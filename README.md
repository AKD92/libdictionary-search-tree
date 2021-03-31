# libdictionary - Tree Based Dictionary ADT Library

<img align="right" src="https://github.com/AKD92/Tree-Based-Dictionary-ADT/raw/master/bst.png">

Dictionary or Associative array or Map is an Abstract Data Type that stores a collection of two cohesive elements: **_a key and a value_**. The key must be unique and camparable on its own domain, and the value that is being mapped can be anything: a sting, a block of memory, an integer, an array, or even user-defined data structures which might contain many other structures.

The primary application of Dictionary ADT is to facilitate a fast and efficient **look-up (search)** operation for a specific key among the others. Generally this look-up operation relys on the comparability and uniqueness of the key.

The design of good Dictionary data structure means good algorithmic performance in 3 general areas:
  * **Insertion** : Insert a key and a value to Dictionary
  * **Deletion**  : Delete a key and its corresponding value from Dictionary
  * **Look-up**   : Efficiently search for a given key in Dictionary, and if found, return its corresponding value object to the caller.

### About This Implementation
This library contains two implementations of Dictionay ADT, such as:

+ **AVL Tree** based Dictionary ADT (`AvlTree` from `avl.h`) [Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)
+ **Binary Search Tree** based Dictionary ADT (`BisTree` from `bst.h`) [Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree)
	
The **Binary Search Tree** based implementation is defined in `bst.h` file. It is a plain binary search tree implementation and has linear worst-case time complexity for certain algorithms. The **AVL Tree** based implementation is defined in `avl.h` file. It is a self-banalcing binary search tree implementation and has logarithmic worst-case time complexity for all dictionary operations. Both of the implementation is fully functiional and bug free, but you might consider using the _AVL Tree_ based implementation for performance reasons.
Because of using C language, memory allocation and clean-up is necessary. A typical starting point of using this dictionary is to create an instance and initialize it by calling initialization function while passing some function pointers on it as arguments. After we are done with it, we should destroy it with destruction or clean-up function.

### Documentation
Documentation for this library is given as **_detailed code comment_** in the header files `bst.h` and `avl.h`.
In those files, every declared function has an associated _comment_ section which thoroughly describes the nature of the function, the purpose of the function, description of parameters, what it does and what it does not, and all the possible return values and their meanings.
Please kindly open up `include\bst.h` or `include\avl.h` and read carefully before you use the library.

### Examples

#### Creating a dictionary
```C
#include <bst.h>		// Include this if you want plain binary search tree based dictionary
#include <avl.h>		// Include this if you want AVL tree based dictionary

	// Inside of some function
	
	BisTree bis_dict;				// This is our Binary Search Tree dictionary
	AvlTree avl_dict;				// This is out AVL tree dictionary
	
```

#### Initializing a dictionary
```C
	// We will use strings (char *) as keys and integers (int *) as associated value.
	// Here strcmp is the string comparison function for comparing keys.
	// Our string keys will be dynamically allocated, so we use 'free' from stdlib.h
	// as clean-up function for keys. This clean-up function will be called when we destroy our dictionary.
	// We also will insert dynamically allocated integers as value, so use 'free' to clean-up them
	// when we destroy this dictionary.
	
	avl_init(&avl_dict, strcmp, free, free);
	
	// OR, if you do not want your keys or values to be released automatically,
	// pass NULL as the value to the function pointer.
	
	avl_init(&avl_dict, strcmp, NULL, NULL);
	
	// OR, if you want to use the plain binary search tree based dictionary.
	
	bst_init(&bst_dict, strcmp, free, free);
```

#### Inserting a key associated with a value
```C
	// Remember, keys or values are always inserted by their pointers.
	// We insert a pointer to the key element and a pointer to the value element.
	
	char *key = (char *) malloc(...);
	int *value = (int *) malloc(...);
	
	// Put some information into the key and value, such as *value = 18 or strcpy(key, "hello").
	
	int opval = avl_insert(&avl_dict, (const void *) key, (const void *) value);
	
	// OR, if you want to use the plain binary search tree based dictionary
	
	int opval = bst_insert(&avl_dict, (const void *) key, (const void *) value);
```

#### Looking up or finding a value for some key
```C
	// We look up for a key and retrive the associated value.
	// Here, 'value' variable is declared as 'int *value'.
	// We pass the 'address of value variable' as the 3rd argument,
	// So that the 'value' variable will point to the associated value after the lookup is finished.
	
	int *value = NULL;
	char *any_key = "any string here";
	opval = avl_lookup(&avl_dict, (const void *) any_key, (void **) &value);
	
	// Use 'bst_lookup' if you use a plain binary search tree
	
	// Check if we have found the key
	if (opval == 1) {
		
		// We have found the key. 'value' variable is pointing to the associated value.
		printf("%d\n", *((int *) value));
	}
	else {
		
		// We did not find the key because it does not exist.
		printf("Key not found\n");
	}
```

#### Changing the value for some existing key
```C
	int *new_value = (int *) malloc(...);
	*new_value = 35;
	
	// 'avl_reassign' changes the associated value to a new one for an existing key.
	// Use 'bst_reassign' if you use plain binary search tree.
	
	opval = avl_reassign(&avl_dict, (const void *) key, (const void *) new_value);
```

#### Removing a key/value pair from the dictionary
```C
	char *key = "any key here";
	char *removed_key;
	int *removed_value;
	
	// Call 'avl_remove' function to remove a key and the value associated with it.
	// Call 'bst_remove' if you use a plain binary search tree based dictionary.
	// Upon removal, the pointer variable 'removed_key' and 'removed_value'
	// will point to the removed key element and removed value element respectively.
	
	int opval = avl_remove(&avl_dict, (const void *) key, (void **) &removed_key, (void **) &removed_value);
	
	if (opval == 0) {
		
		// Successfully removed. We can clean up the removed items.
		// Remember, we inserted dynamically allocated elements into the dictionary.
		// So de-allocation is necessary.
		
		printf("Removed key : %s\n", removed_key);
		printf("Removed value : %d\n", *removed_value);
		
		free((void *) removed_key);
		free((void *) removed_value);
	}
```

#### Get number of key-value pairs in the dictionary
```C
	// Use 'bst_size' instead if you use plain binary search tree
	
	int count = avl_size(&avl_dict);
```

#### Destroy the dictionary
```C
	// When you no longer need the dictionay, remove it from the memory.
	// Call 'bst_destroy' instead if you use plain binary search tree.
	// This destruction function calls the clean-up functions passed into it
	// while initialization, so that all the keys and associated value elements
	// could be de-allocated from the memory while the dictionary is destroyed.
	
	avl_destroy(&avl_dict);
	
	// 'avl_dect' destroyed. Memory allocated by this dictionary is released.
	// All the keys and values which were dynamically allocated by user,
	// those are also released (cleaned up by 'free'
	// because we provided 'free' as clean-up function).
```

### Performance Analysis
Assuming **n** and **h**, where n = _Total number of keys in dictionary_, h = _Height of internal tree_.
Here lg is the base 2 logarithm.

Plain Binary Search Tree based Dictionary (BisTree, defined in `bst.h`)
| Algorithm      | Time complexity (average case)    | Time complexity (worst case)|
|----------------|:---------------------------------:|:---------------------------:|
| Insertion	     | O (lg n)                          | O (h)                       |
| Removal	     | O (lg n)                          | O (h)                       |
| Look-up	     | O (lg n)                          | O (h)                       |

AVL Tree based Dictionary (AvlTree, defined in `avl.h`)
| Algorithm      | Time complexity (average case)    | Time complexity (worst case)|
|----------------|:---------------------------------:|:---------------------------:|
| Insertion	     | O (lg n)                          | O (lg n)                    |
| Removal	     | O (lg n)                          | O (lg n)                    |
| Look-up	     | O (lg n)                          | O (lg n)                    |

Space complexity is O(2n + 1) for both dictionaries.

### Code Examples

#### Sorting a [Linked List](https://github.com/AKD92/Linked-List-ADT) using [TreeSort Algorithm](https://en.wikipedia.org/wiki/Tree_sort)
```C
#include <avl.h>
#include <list.h>
#include <stdio.h>
#include <stdlib.h>

int main(void);
int compare_int(const void *arg1, const void *arg2);

int compare_int(const void *arg1, const void *arg2) {
	int *val1, *val2;
	
	val1 = (int *) arg1;
	val2 = (int *) arg2;
	return (*val1 - *val2);
}

int main(void) {
	List lstInt;
	ListElem *elem;
	int *pInt, index;
	
	list_init(&lstInt, free);
	
	elem = list_tail(&lstInt);
	for (index = 3; index >= -4; index--) {
		pInt = (int *) malloc(sizeof(int));
		*pInt = index;
		list_ins_next(&lstInt, elem, (const void *) pInt);
		elem = list_tail(&lstInt);
	}
	/* Current List: 3 2 1 0 -1 -2 -3 -4 */
	
	/* Sort Linked List */
	/* For more sort function, check out bst.h */
	avl_sort(&lstInt, compare_int);
	/* Sorted List: -4 -3 -2 -1 0 1 2 3 */
	
	printf("Sorted in ascending order. Printing...\n");
	elem = list_head(&lstInt);
	while (elem != 0) {
		pInt = (int *) list_data(elem);
		printf("%d ", *pInt);
		elem = list_next(elem);
	}
	
	list_destroy(&lstInt);
	return 0;
}
```
<img align="right" height="400" width="310" src="https://github.com/AKD92/Tree-Based-Dictionary-ADT/raw/master/book_ds_mtrt.jpg">

### Linking with this library
You can download pre-built packages which are available here as **Releases**. Those package contains _include_ files and gcc compiled static library files (extension .a) for both x86 and x64 architecture for Windows platform. Please check the assets page for pre-build static library packages [here.](/releases)
You also need **liblinkedlist** library which is a dependency for this library. You can find it [here.](https://github.com/AKD92/Linked-List-ADT)
While linking, provide this link order: `-ldictionary -llinkedlist`

### Compiling from source
This project is developed using the [Code::Blocks](https://www.codeblocks.org/) IDE. Do a SVN check-out or download the source and open the _Dictionary ADT.cbp_ project file with Code::Blocks IDE. Then inside the IDE you will see the build configurations and might start building from sources. Plese note that Code::Blocks may warn you about the compiler not found for this project. In this case you must choose and set the compiler from the _Project Properties_ dialog box.

### Reference Book:
Implementation follows the algorithms from the book <a href="http://ww3.algorithmdesign.net/">Algorithm Design</a> by Michael T. Goodrich and Roberto Tamassia.

### License
<a rel="license" href="http://www.gnu.org/licenses/lgpl-3.0-standalone.html"><img alt="LGPLv3 License" style="border-width:0" src="http://www.gnu.org/graphics/lgplv3-147x51.png" /></a><br />This software is licensed under <a rel="license" href="http://www.gnu.org/licenses/lgpl-3.0-standalone.html">GNU Lesser General Public License, Version 3</a>.
