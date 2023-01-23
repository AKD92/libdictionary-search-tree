
#ifndef HTABLE_H_INCLUDED
#define HTABLE_H_INCLUDED

#define HTABLE_INITIAL_CAPACITY                 101
#define HTABLE_LOAD_FACTOR                      0.70

#include <list.h>
#include <dlist.h>

struct KeyValuePair_ {
    
    const void *key;
    const void *value;
};
typedef struct KeyValuePair_ KeyValuePair;

struct HTable_ {
    
    unsigned int size;                      // number of keys in the hash table
    unsigned int bucket_size;               // number of buckets in use by the hash table
    unsigned int capacity;                  // total number of buckets
    DList *buckets;
    int (*hashcode)(const void *key);
    int (*equals)(const void *key1, const void *key2);
    void (*destroy_key)(void *key);
    void (*destroy_value)(void *value);
};
typedef struct HTable_ HTable;


/*
 *  Compute a hash code as an integer for any arbitrary object.
 *  The uses should provide the hash code for their key objects
 *  through using this function.
 *  If the object is NULL, the outcome of this function is undefined.
 *
 *  Parameters:
 *      object              : Pointer to the object whose hash code is being computed
 *      length              : The size of the object in bytes (use sizeof operator)
 *
 *  Returns (int):
 *      the computed hash code as an integer
 */
int htable_hash(const void *object, unsigned int length);


/*
 *  Initialized the given hash table.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table which is being initialized
 *      hashcode            : Hash function which will provide hash code for
 *                            the keys.
 *                            The keys which are considered "equal" should also have
 *                            exactly same hash codes.
 *      equals              : Function which will check for equality of keys
 *                            This function should return positive integer for equal keys
 *                            and 0 (zero) for non-equal keys.
 *                            It is absolutely necessary that the hash code for the "equal"
 *                            keys should exactly be same.
 *      destroy_key         : Clean up function which will de-allocate keys from the memory.
 *                            This function will be called upon the destruction of the hash table.
 *                            (can be null).
 *      destroy_value       : Clean up function which will de-allocate associated value to the key
 *                            from the memory. This function will be called upon the destruction of
 *                            the hash table.
 *                            (can be null).
 *
 *  Returns (int):
 *      0 if the hash table is initialized successfully
 *      -1 for error (parameters are null or could not allocate memory)
 */
int htable_init
(
    HTable *dictionary,
    int (*hashcode)(const void *key),
    int (*equals)(const void *key1, const void *key2),
    void (*destroy_key)(void *key),
    void (*destroy_value)(void *value)
);


/*
 *  De-allocates the given hash table from the memory.
 *  Upon calling this function, internal memory of the hash table will be released.
 *  If the "destroy_key" and/or "destroy_value" functions are provided,
 *  they will be called to release the contained keys and associated value objects.
 *  The specified hash table can be used again through initialization.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table which is being destroyed
 *
 *  Returns (void):
 *      Nothing
 */
void htable_destroy(HTable *dictionary);


/*
 *  Query the current number of entries (key-value pairs) in the given hash table.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table
 *
 *  Returns (unsigned int):
 *      The number of key-value pais in the hash table
 */
#define htable_size(dictionary) ((dictionary)->size)


/*
 *  Query for the given key in the given hash table to retreive its value.
 *  If the key exists, the "value" pointer will receive the value object associated
 *  with that key in the hash table.
 *  If the key does not exist, the "value" pointer won't be touched and
 *  it will retain its original value.
 *
 *  Parameters:
 *      dictionary          : The hash table where the lookup is being done
 *      key                 : Pointer to the search key
 *      value               : Pointer to the "value" pointer which will point to
 *                            the associated value object (if the key exists)
 *                            (can be null)
 *
 *  Returns (int):
 *      1 if the key exists
 *      0 if the key does not exist
 *      -1 for error (parameters are null)
 */
int htable_lookup(const HTable *dictionary, const void *key, void **value);


/*
 *  Check to see if the specified key exists into the given hash table.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table where to look into
 *      key                 : Pointer to the key which we are looking for
 *
 *  Returns (int):
 *      1 if the key exists into the hash table
 *      0 if the key does not exist into the hash table
 *      -1 for error (parameters are null)
 */
int htable_exists(const HTable *dictionary, const void *key);


/*
 *  Inserts the given key and associated value object into the specified hash table.
 *  It is expected that the given key does not exist in the hash table.
 *  If the key exist, it won't update the "value" and return immediately.
 *  To update associated value object for an existing key, please use the
 *  "htable_reassign" function instead.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table dictionary where the key
 *                            and its associated value is being added
 *      key                 : Pointer to they key
 *      value               : Pointer to the associated value object
 *                            (can be null).
 *
 *  Returns (int):
 *      0 if the key and the value is added successfully
 *      -1 for error (parameters are null or the key already exists)
 */
int htable_insert(HTable *dictionary, const void *key, const void *value);


/*
 *  Replaces the value object associated with the given key in the given hash table.
 *  It is expected that the given key already exists into the dictionary.
 *  If the key does not exist, it will return immediately.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table where some value is being replaced
 *      key                 : Pointer to the key whose value is being replaced
 *      value               : Pointer to the new value object whill will replace existing
 *                            value object associated with the given key
 *                            (can be null)
 *
 *  Returns (int):
 *      0 if the value is replaced successfully
 *      -1 for error (parameters are null or the key does not exist)
 */
int htable_reassign(HTable *dictionary, const void *key, const void *value);


/*
 *  Removes the given key and associated value object from the hash table dictionary.
 *  Please note that no clean-up will be done for the removed key and associated value object.
 *  If the clean-up or de-allocation is needed for the key and value,
 *  it must be done separatetly after the removal.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table dictionary from where
 *                            the key and associated value is being removed.
 *      key                 : Pointer to the key which will be used for searching
 *      removed_key         : Pointer to the void pointer which will point to the
 *                            ponter to actual key removed from the dictionary.
 *                            (can be null).
 *      removed_value       : Pointer to the void pointer which will point to the
 *                            pointer to the associated value object removed.
 *                            (can be null).
 *
 *  Returns (int):
 *      0 if the key is removed successfully
 *      -1 for error (the key does not exist or parameters are null)
 */
int htable_remove(HTable *dictionary, const void *key, void **removed_key, void **removed_value);


/*
 *  Fills up the given singly linked list with all the keys in the
 *  specified hash table dictionary.
 *  The given list must be initialized before calling this function.
 *  If the linked list is not initialized, the behavior of this function
 *  is undetermined or unknown.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table where the keys are stored.
 *      keys                : Pointer to the singly linked list which will receive
 *                            all the pointers to the keys present in the hash table.
 *
 *  Returns (int):
 *      0 if all the keys are loaded into the linked list
 *      -1 for error (parameters are null)
 *      -2 if the hash table is empty
 */
int htable_keys(const HTable *dictionary, List *keys);


/*
 *  Fills up the given singly linked list with all the value objects in the
 *  specified hash table dictionay.
 *  The given list must be initialized before calling this function.
 *  If the linked list is not initialized, the behavior of this function
 *  is undetermined or unknown.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table where the value objects are stored.
 *      value               : Pointer to the singly linked list which will receive
 *                            all the pointers to the value objects exist in the hash table.
 *
 *  Returns (int):
 *      0 if all the value objects are loaded into the linked list
 *      -1 for error (parameters are null)
 *      -2 if the hash table is empty
 */
int htable_values(const HTable *dictionary, List *values);


#endif // HTABLE_H_INCLUDED
