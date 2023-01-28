
#include "htable.h"

int htable_keys(const HTable *dictionary, List *keys) {
    DList *bucket;
    DListElem *entry_container;
    HKeyValuePair *entry;
    unsigned int index;
    if (dictionary == NULL || keys == NULL)
        return -1;
    if (dictionary->size == 0)
        return -2;
    for (index = 0; index < dictionary->capacity; index++) {
        bucket = dictionary->buckets + index;
        entry_container = dlist_head(bucket);
        while (entry_container != NULL) {
            entry = dlist_data(entry_container);
            (void) list_ins_next(keys, list_tail(keys), entry->key);
            entry_container = dlist_next(entry_container);
        }
    }
    return 0;
}


int htable_values(const HTable *dictionary, List *values) {
    DList *bucket;
    DListElem *entry_container;
    HKeyValuePair *entry;
    unsigned int index;
    if (dictionary == NULL || values == NULL)
        return -1;
    if (dictionary->size == 0)
        return -2;
    for (index = 0; index < dictionary->capacity; index++) {
        bucket = dictionary->buckets + index;
        entry_container = dlist_head(bucket);
        while (entry_container != NULL) {
            entry = dlist_data(entry_container);
            (void) list_ins_next(values, list_tail(values), entry->value);
            entry_container = dlist_next(entry_container);
        }
    }
    return 0;
}
