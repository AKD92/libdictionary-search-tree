
#include "htable.h"
#include <stdlib.h>
#include <string.h>

int htable_init
(
    HTable *dictionary,
    int (*hashcode)(const void *key),
    bool (*equals)(const void *key1, const void *key2),
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
    for (unsigned int index = 0; index < HTABLE_INITIAL_CAPACITY; index++) {
        bucket = buckets + index;
        (void) dlist_init(bucket, free);   // "free" is sufficient to de-allocate "HKeyValuePair" objects
    }
    (void) memset((void *) dictionary, 0, sizeof(HTable));
    dictionary->buckets = buckets;
    dictionary->capacity = HTABLE_INITIAL_CAPACITY;
    dictionary->hashcode = hashcode;
    dictionary->equals = equals;
    dictionary->destroy_key = destroy_key;
    dictionary->destroy_value = destroy_value;
    return 0;
}


void htable_destroy(HTable *dictionary) {
    DList *bucket;
    DListElem *pair_container;
    HKeyValuePair *entry;
    if (dictionary == NULL)
        return;
    for (unsigned int index = 0; index < dictionary->capacity; index++) {
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
