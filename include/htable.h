
#ifndef HTABLE_H_INCLUDED
#define HTABLE_H_INCLUDED

#include <list.h>
#include <dlist.h>

struct KeyDataPair_ {
    
    const void *key;
    const void *data;
};
typedef struct KeyDataPair_ KeyDataPair

struct HTable_ {
    
    unsigned int size;
    DList *bucket;
    int (*hashcode)(const void *key);
    int (*equals)(const void *key1, const void *key2);
    void (*destroy_key)(const void *key);
    void (*destroy_data)(const void *data);
};
typedef struct HTable_ HTable;


/*
 *  Compute a hash code as an integer for any arbitrary object.
 *  
 *
 *  Parameters:
 *      object              : Pointer to the object whose hash code is being computed
 *      length              : The size of the object in bytes (use sizeof operator)
 *
 *  Returns (int):
 *      the computed hash code as an integer
 */
int hashcalc(const void *object, unsigned int length);


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
 *      destroy_data        : Clean up function which will de-allocate associated data to the key
 *                            from the memory. This function will be called upon the destruction of
 *                            the hash table.
 *                            (can be null).
 *
 *  Returns (int):
 *      1 if the hash table is initialized successfully
 *      0 otherwise
 */
int htable_init
(
    HTable *dictionary,
    int (*hashcode)(const void *key),
    int (*equals)(const void *key1, const void *key2),
    void (*destroy_key)(const void *key),
    void (*destroy_data)(const void *data)
);


/*
 *  De-allocates the given hash table from the memory.
 *  Upon calling this function, internal memory of the hash table will be released.
 *  If the "destroy_key" and/or "destroy_data" functions are provided,
 *  they will be called to release the contained keys and associated data objects.
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
 *  Query for the given key in the given hash table to retreive its data.
 *  If the key exists, the "data" pointer will receive the data associated
 *  with that key in the hash table.
 *  If the key does not exist, the "data" pointer won't be touched and
 *  it will retain its original value.
 *
 *  Parameters:
 *      dictionary          : The hash table where the lookup is being done
 *      key                 : Pointer to the search key
 *      data                : Pointer to the "data" pointer which will point to
 *                            the associated data object (if the key exists)
 *                            (can be null)
 *
 *  Returns (int):
 *      1 if the key exists
 *      0 if the key does not exist
 *      -1 for error (parameters are null)
 */
int htable_lookup(const HTable *dictionary, const void *key, void **data);


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
 *  Inserts the given key and associated data object into the specified hash table.
 *  It is expected that the given key does not exist in the hash table.
 *  If the key exist, it won't update the "data" and return immediately.
 *  To update associated data object for an existing key, please use the
 *  "htable_reassign" function instead.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table dictionary where the key
 *                            and its associated data is being added
 *      key                 : Pointer to they key
 *      data                : Pointer to the associated data object
 *                            (can be null).
 *
 *  Returns (int):
 *      0 if the key and the data is added successfully
 *      -1 for error (parameters are null or the key already exists)
 */
int htable_insert(HTable *dictionary, const void *key, const void *data);


/*
 *  Replaces the data object associated with the given key in the given hash table.
 *  It is expected that the given key already exists into the dictionary.
 *  If the key does not exist, it will return immediately.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table where some data is being replaced
 *      key                 : Pointer to the key whose data is being replaced
 *      data                : Pointer to the new data object whill will replace existing
 *                            data object associated with the given key
 *                            (can be null)
 *
 *  Returns (int):
 *      0 if the data is replaced successfully
 *      -1 for error (parameters are null or the key does not exist)
 */
int htable_reassign(HTable *dictionary, const void *key, const void *data);


/*
 *  Removes the given key and associated data object from the hash table dictionary.
 *  Please note that no clean-up will be done for the removed key and associated data object.
 *  If the clean-up or de-allocation is needed for the key and data,
 *  it must be done separatetly after the removal.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table dictionary from where
 *                            the key and associated data is being removed.
 *      key                 : Pointer to the key which will be used for searching
 *      removed_key         : Pointer to the void pointer which will point to the
 *                            ponter to actual key removed from the dictionary.
 *                            (can be null).
 *      removed_data        : Pointer to the void pointer which will point to the
 *                            pointer to the associated data object removed.
 *                            (can be null).
 *
 *  Returns (int):
 *      0 if the key is removed successfully
 *      -1 for error (the key does not exist or parameters are null)
 */
int htable_remove(HTable *dictionary, const void *key, void **removed_key, void **removed_data);


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
 *  Fills up the given singly linked list with all the data objects in the
 *  specified hash table dictionay.
 *  The given list must be initialized before calling this function.
 *  If the linked list is not initialized, the behavior of this function
 *  is undetermined or unknown.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table where the data objects are stored.
 *      data                : Pointer to the singly linked list which will receive
 *                            all the pointers to the data objects present in the hash table.
 *
 *  Returns (int):
 *      0 if all the data objects are loaded into the linked list
 *      -1 for error (parameters are null)
 *      -2 if the hash table is empty
 */
int htable_data(const HTable *dictionary, List *data);


#endif // HTABLE_H_INCLUDED
