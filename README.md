# Dictionary ADT

Dictionary or Map is an Abstract Data Type where we store a list of 2 cohesive data: a key and a value. The key must be unique and camparable on their domain, and the value they maps can be anything, a sting, a block of memory, an integer or even a long list of various customized data.

The design of a good Dictionary data structure means good algorithmic performance in 3 general applications:
  * Insertion : Insert a key and a value to Dictionary
  * Deletion  : Delegte a key and its corresponding value from Dictionary
  * Search    : Efficiently search for a given key in Dictionary, and if found, return its corresponding value to the caller.

Here is an implementation of dictionary data structure using Binary Search Tree (BST).

### Performance Analysis
  * Insertion : O(n)            [Worst Case]
  * Deletion  : O(n)            [Worst Case]
  * Search    : O(logn)         [Average Case]


### Reference Book:
Implementation follows the principles from the book <a href="http://ww3.algorithmdesign.net/">Algorithm Design" by Michael T. Goodrich and Roberto Tamassia</a>

