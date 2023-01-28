
#include "htable.h"
#include <stdlib.h>
#include <string.h>

/*
 *  Please see "htable_query.c" file for a detailed information regarding the following
 *  structure.
 */
struct HSearchResult {
    
    bool found;
    unsigned int bucket_index;
    DList *bucket;
    DListElem *entry_container;
};


/*
 *  Please see "htable_query.c" file for a detailed information regarding the following
 *  function.
 */
struct HSearchResult htable_search(const HTable *dictionary, const void *key);


/*
 *  Checks if the given number is a prime or not.
 *
 *  Parameters:
 *      number              : Unsigned integer which is being checked for primality
 *
 *  Returns (bool):
 *      true if the number is prime
 *      false otherwise
 */
bool htable_is_prime(unsigned int number);


/*
 *  Increases the capacity of the given hash table and performs rehashing process
 *  to distribute the key-value entries over the new increased capacity.
 *  Call this function when the load-factor reaches the threshold and the internal
 *  bucket of the hash table needs to be enlarged.
 *
 *  Parameters:
 *      dictionary          : Pointer to the hash table which is being resized and rehashed
 *
 *  Returns (int):
 *      0 if the rehash process runs successfully
 *      -1 for error (parameters are null or could no allocate memory)
 */
int htable_rehash(HTable *dictionary);


bool htable_is_prime(unsigned int number) {
    bool is_prime;
    if (number <= 1) {
        is_prime = false;
    }
    else if (number <= 3) {
        is_prime = true;
    }
    else if (number % 2 == 0 || number % 3 == 0) {
        is_prime = false;
    }
    else {
        is_prime = true;
        for (unsigned int odd = 5; (odd * odd) < number; odd += 6) {
            if (number % odd == 0 || number % (odd + 2) == 0) {
                is_prime = false;
                break;
            }
        }
    }
    return is_prime;
}


int htable_rehash(HTable *dictionary) {
    DList *new_buckets;
    DList *old_bucket, *new_bucket;
    DListElem *pair_container;
    HKeyValuePair *entry;
    unsigned int new_index, new_capacity, index, new_bucket_size;
    bool is_prime;
    unsigned int prime = (dictionary->capacity * 2) + 1;
    do {
        is_prime = htable_is_prime(prime);
        if (is_prime == false)
            prime++;
    } while (is_prime == false);
    new_capacity = prime;
    new_buckets = (DList *)malloc(sizeof(DList) * new_capacity);
    new_bucket_size = 0;
    if (new_buckets == NULL)
        return -1;
    for (index = 0; index < new_capacity; index++) {
        (void) dlist_init(new_buckets + index, free);
    }
    for (index = 0; index < dictionary->capacity; index++) {
        old_bucket = dictionary->buckets + index;
        pair_container = dlist_head(old_bucket);
        while (pair_container != NULL) {
            entry = (HKeyValuePair *)dlist_data(pair_container);
            new_index = dictionary->hashcode(entry->key) % new_capacity;
            new_bucket = new_buckets + new_index;
            if (dlist_size(new_bucket) == 0)
                new_bucket_size++;
            (void) dlist_ins_next(new_bucket, dlist_tail(new_bucket), (const void *)entry);
            pair_container = dlist_next(pair_container);
        }
        old_bucket->destroy = NULL;
        (void) dlist_destroy(old_bucket);
    }
    (void) free((void *)dictionary->buckets);
    dictionary->buckets = new_buckets;
    dictionary->capacity = new_capacity;
    dictionary->bucket_size = new_bucket_size;
    dictionary->max_bucket_size = (unsigned int)(dictionary->capacity * HTABLE_LOAD_FACTOR);
    return 0;
}


int htable_insert(HTable *dictionary, const void *key, const void *value) {
    HKeyValuePair *entry;
    struct HSearchResult search_result;
    int result;
    if (dictionary == NULL || key == NULL)
        return -1;
    if (dictionary->bucket_size == dictionary->max_bucket_size) {
        result = htable_rehash(dictionary);
        if (result == -1)
            return -1;
    }
    search_result = htable_search((const HTable *)dictionary, key);
    if (search_result.found)
        result = -1;
    else {
        entry = (HKeyValuePair *)malloc(sizeof(HKeyValuePair));
        if (entry == NULL)
            return -1;
        (void) memset((void *)entry, 0, sizeof(HKeyValuePair));
        entry->key = key;
        entry->value = value;
        (void) dlist_ins_next(search_result.bucket, dlist_tail(search_result.bucket), entry);
        if (dlist_size(search_result.bucket) == 1)
            dictionary->bucket_size++;
        dictionary->size++;
        result = 0;
    }
    return result;
}


int htable_reassign(HTable *dictionary, const void *key, const void *value) {
    int result;
    struct HSearchResult search_result;
    HKeyValuePair *entry;
    if (dictionary == NULL || key == NULL)
        return -1;
    search_result = htable_search((const HTable *)dictionary, key);
    if (search_result.found) {
        entry = (HKeyValuePair *)dlist_data(search_result.entry_container);
        entry->value = value;
        result = 0;
    }
    else {
        result = -1;
    }
    return result;
}


int htable_remove(HTable *dictionary, const void *key, void **removed_key, void **removed_value) {
    int result;
    struct HSearchResult search_result;
    HKeyValuePair *entry;
    if (dictionary == NULL || key == NULL)
        return -1;
    search_result = htable_search((const HTable *)dictionary, key);
    if (search_result.found) {
        (void) dlist_remove(search_result.bucket, search_result.entry_container, (void **)&entry);
        if (removed_key != NULL)
            *removed_key = (void *)entry->key;
        if (removed_value != NULL)
            *removed_value = (void *)entry->value;
        (void) free((void *)entry);
        dictionary->size--;
        if (dlist_size(search_result.bucket) == 0)
            dictionary->bucket_size--;
        result = 0;
    }
    else
        result = -1;
    return result;
}
