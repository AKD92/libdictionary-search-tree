
#include "htable.h"
#include <stdlib.h>

int htable_init
(
    HTable *dictionary,
    int (*hashcode)(const void *key),
    int (*equals)(const void *key1, const void *key2),
    void (*destroy_key)(void *key),
    void (*destroy_data)(void *data)
)
{
    DList *buckets, *bucket;
    unsigned int bucket_count;
    if (dictionary == NULL | hashcode == NULL | equals == NULL)
        return -1;
    bucket_count = sizeof(DList) * HTABLE_INITIAL_CAPACITY;
    buckets = (DList *) malloc(bucket_count);
    if (buckets == NULL)
        return -1;
    for (int index = 0; index < HTABLE_INITIAL_CAPACITY; index++) {
        bucket = buckets + index;
        (void) dlist_init(bucket, free);   // use "free" is sufficient to de-allocate "KeyDataPair" objects
    }
    (void) memset((void *) dictionary, 0, sizeof(HTable));
    dictionary->buckets = buckets;
    dictionary->hashcode = hashcode;
    dictionary->equals = equals;
    dictionary->destroy_key = destroy_key;
    dictionary->destroy_data = destroy_data;
    return 0;
}


void htable_destroy(HTable *dictionary) {
    DList *bucket;
    DListElem *pair_container;
    KeyDataPair *entry;
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
            if (dictionary->destroy_data != NULL) {
                (void) dictionary->destroy_data((void *)entry->data);
            }
            pair_container = dlist_next(pair_container);
        }
        (void) dlist_destroy(bucket);
    }
    (void) free((void *)dictionary->buckets);
    return;
}
