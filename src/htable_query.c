
#include "htable.h"
#include <stdlib.h>

int htable_search(const HTable *dictionary, const void *key, DList **bucket_addr, DListElem **container_addr);


int htable_search(const HTable *dictionary, const void *key, DList **bucket_addr, DListElem **container_addr) {
    DList *bucket;
    unsigned int hashcode;
    DListElem *pair_container;
    KeyValuePair *entry;
    int exists = 0;
    hashcode = dictionary->hashcode(key) % dictionary->capacity;
    bucket = dictionary->buckets + hashcode;
    pair_container = dlist_head(bucket);
    while (pair_container != NULL) {
        entry = (KeyValuePair *)dlist_data(pair_container);
        exists = dictionary->equals(key, entry->key);
        if (exists == 1) {
            *bucket_addr = bucket;
            *container_addr = pair_container;
            break;
        }
        pair_container = dlist_next(pair_container);
    }
    return exists;
}


int htable_lookup(const HTable *dictionary, const void *key, void **value) {
    int exists;
    DList *bucket;
    DListElem *pair_container;
    KeyValuePair *entry;
    exists = htable_search(dictionary, key, &bucket, &pair_container);
    if (exists == 1 && value != NULL) {
        entry = (KeyValuePair *)dlist_data(pair_container);
        *value = (void *)entry->value;
    }
    return exists;
}


int htable_exists(const HTable *dictionary, const void *key) {
    int exists;
    DList *bucket;
    DListElem *pair_container;
    exists = htable_search(dictionary, key, &bucket, &pair_container);
    return exists;
}
