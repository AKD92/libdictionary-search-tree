
#include "htable.h"
#include <stdlib.h>

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
 *      0 if the resize and reshash process runs successfully
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
    unsigned int new_index, new_capacity, index;
    bool is_prime;
    unsigned int prime = dictionary->capacity * 2;
    do {
        is_prime = htable_is_prime(prime);
        if (is_prime == 0)
            prime++;
    } while (is_prime == 0);
    new_capacity = prime;
    new_buckets = (DList *)malloc(sizeof(DList) * new_capacity);
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
            (void) dlist_ins_next(new_bucket, dlist_tail(new_bucket), (const void *)entry);
            pair_container = dlist_next(pair_container);
        }
        old_bucket->destroy = NULL;
        (void) dlist_destroy(old_bucket);
    }
    (void) free((void *)dictionary->buckets);
    dictionary->buckets = new_buckets;
    dictionary->capacity = new_capacity;
    return 0;
}
