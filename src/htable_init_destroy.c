
#include "htable.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//  Implementation of Bob Jenkin's One At A Time hash algorithm
//  https://en.wikipedia.org/wiki/Jenkins_hash_function
uint32_t BJHash32(const unsigned char *key, unsigned int length);

int htable_init
(
    HTable *dictionary,
    int (*hashcode)(const void *key),
    int (*equals)(const void *key1, const void *key2),
    void (*destroy_key)(void *key),
    void (*destroy_value)(void *value)
)
{
    DList *buckets, *bucket;
    unsigned int bucket_length;
    if (dictionary == NULL || hashcode == NULL || equals == NULL)
        return -1;
    bucket_length = sizeof(DList) * HTABLE_INITIAL_CAPACITY;
    buckets = (DList *) malloc(bucket_length);
    if (buckets == NULL)
        return -1;
    for (int index = 0; index < HTABLE_INITIAL_CAPACITY; index++) {
        bucket = buckets + index;
        (void) dlist_init(bucket, free);   // "free" is sufficient to de-allocate "KeyValuePair" objects
    }
    (void) memset((void *) dictionary, 0, sizeof(HTable));
    dictionary->buckets = buckets;
    dictionary->hashcode = hashcode;
    dictionary->equals = equals;
    dictionary->destroy_key = destroy_key;
    dictionary->destroy_value = destroy_value;
    return 0;
}


void htable_destroy(HTable *dictionary) {
    DList *bucket;
    DListElem *pair_container;
    KeyValuePair *entry;
    if (dictionary == NULL)
        return;
    for (int index = 0; index < dictionary->capacity; index++) {
        bucket = dictionary->buckets + index;
        pair_container = dlist_head(bucket);
        while (pair_container != NULL) {
            entry = dlist_data(pair_container);
            if (dictionary->destroy_key != NULL) {
                (void) dictionary->destroy_key((void *)entry->key);
            }
            if (dictionary->destroy_value != NULL) {
                (void) dictionary->destroy_value((void *)entry->value);
            }
            pair_container = dlist_next(pair_container);
        }
        (void) dlist_destroy(bucket);
    }
    (void) free((void *)dictionary->buckets);
    return;
}


uint32_t BJHash32(const unsigned char *key, unsigned int length) {
    unsigned int index = 0;
    uint32_t hash = 0;
    while (index != length) {
        hash += key[index++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}


int htable_hash(const void *object, unsigned int length) {
    const unsigned char *key = (const unsigned char *)object;
    return BJHash32(key, length);
}
