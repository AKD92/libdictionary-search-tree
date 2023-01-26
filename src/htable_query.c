
#include "htable.h"
#include <stdlib.h>
#include <string.h>

struct HSearchResult {
    
    bool found;
    unsigned int bucket_index;
    DList *bucket;
    DListElem *entry_container;
};

struct HSearchResult htable_search(const HTable *dictionary, const void *key);


struct HSearchResult htable_search(const HTable *dictionary, const void *key) {
    DList *bucket;
    unsigned int index;
    DListElem *pair_container;
    HKeyValuePair *entry;
    struct HSearchResult search_result;
    (void) memset((void *) &search_result, 0, sizeof(struct HSearchResult));
    index = dictionary->hashcode(key) % dictionary->capacity;
    bucket = dictionary->buckets + index;
    pair_container = dlist_head(bucket);
    while (pair_container != NULL) {
        entry = (HKeyValuePair *)dlist_data(pair_container);
        search_result.found = dictionary->equals(key, entry->key);
        if (search_result.found == true) {
            search_result.bucket = bucket;
            search_result.entry_container = pair_container;
            search_result.bucket_index = index;
            break;
        }
        pair_container = dlist_next(pair_container);
    }
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
