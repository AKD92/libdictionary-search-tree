
#include "htable.h"
#include <stdlib.h>
#include <string.h>

/*
 *  Structure to hold information regarding search reasult on the hash tables.
 *  
 *  Fields:
 *      found               : This boolean value signifies if the key is found in the
 *                            hash table or not. True means found, false means the key
 *                            does not exist.
 *      bucket_index        : This field will have the index address of the linked list where
 *                            the key is actually stored (or is supposed to be there).
 *                            We can locate the linked list by adding this index to the base
 *                            address of the linked list, stored in the HTable structure.
 *      bucket              : Pointer to the linked list where the key actually resides,
 *                            or where the key is supposed to be found.
 *      entry_container     : Pointer to the DListElem node of the linked list. This node
 *                            holds the HKeyValuePair structure where the key is stored.
 */
struct HSearchResult {
    
    bool found;
    unsigned int bucket_index;
    DList *bucket;
    DListElem *entry_container;
};


/*
 *  Searches for the given key into the given hash table.
 *  The function returns an instance of the struct "HSearchResult".
 *
 *  If the key is found in the hash table,
 *      ->  HSearchResult.found will be "true"
 *      ->  HSearchResult.entry_container will point to the DListElem linked list container
 *          which actually holds the "HKeyValuePair" key-value entry
 *  If the key is not found (does not exist)
 *      ->  HSearchResult.found will be "false"
 *      ->  HSearchResult.entry_container will be null
 *  In either case
 *      ->  HSearchResult.bucket will point to the DList linked list in the hash table buckets
 *          where the search key is found (or is supposed to be there if not found)
 *      ->  HSearchResult.bucket_index will have the index number of the linked list in the
 *          hash table buckets where the search key is found (or is supposed to be there if not found)
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table dictionary where the search is
 *                            being performed
 *      key                 : Pointer to the key object for which the search is
 *                            being performed
 *
 *  Returns (struct HSearchResult):
 *      the result to the search operation.
 */
struct HSearchResult htable_search(const HTable *dictionary, const void *key);


struct HSearchResult htable_search(const HTable *dictionary, const void *key) {
    DList *bucket;
    unsigned int index;
    DListElem *pair_container;
    HKeyValuePair *entry;
    struct HSearchResult search_result;
    (void) memset((void *)&search_result, 0, sizeof(struct HSearchResult));
    index = dictionary->hashcode(key) % dictionary->capacity;
    bucket = dictionary->buckets + index;
    pair_container = dlist_head(bucket);
    while (pair_container != NULL) {
        entry = (HKeyValuePair *)dlist_data(pair_container);
        search_result.found = dictionary->equals(key, entry->key);
        if (search_result.found == true) {
            search_result.entry_container = pair_container;
            break;
        }
        pair_container = dlist_next(pair_container);
    }
    search_result.bucket = bucket;
    search_result.bucket_index = index;
    return search_result;
}


int htable_lookup(const HTable *dictionary, const void *key, void **value) {
    HKeyValuePair *entry;
    struct HSearchResult search_result;
    if (dictionary == NULL || key == NULL)
        return -1;
    search_result = htable_search(dictionary, key);
    if (search_result.found == 1 && value != NULL) {
        entry = (HKeyValuePair *)dlist_data(search_result.entry_container);
        *value = (void *)entry->value;
    }
    return search_result.found ? 1 : 0;
}


bool htable_exists(const HTable *dictionary, const void *key) {
    struct HSearchResult search_result;
    if (dictionary == NULL || key == NULL)
        return false;
    search_result = htable_search(dictionary, key);
    return search_result.found;
}
