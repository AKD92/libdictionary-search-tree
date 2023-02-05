
#include "htable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//#undef HTABLE_INITIAL_CAPACITY
//#define HTABLE_INITIAL_CAPACITY 7

int string_hash(const void *obj);
bool string_equals(const void *obj1, const void *obj2);

int string_hash(const void *obj) {
    char *str = (char *)obj;
    return htable_hash(obj, strlen(str));
}
bool string_equals(const void *obj1, const void *obj2) {
    int result = strcmp((const char *)obj1, (const char *)obj2);
    if (result == 0)
        return true;
    else
        return false;
}

int main(void) {
    HTable dictionary;
    List out_keys, out_values;
    ListElem *elem;
    char *key, *value, *removed_key, *removed_value;
    int result;
    unsigned int i, len;
    len = 8;
    char *ids[] = {"Hello", "This", "Is", "The", "World", "Monster", "Rabbit", "Hole"};
    char *values[] = {"Gallo", "Kiss", "As", "Thy", "Earth", "Devil", "Runner", "Circle"};
    
    list_init(&out_keys, NULL);
    htable_init(&dictionary, string_hash, string_equals, NULL, NULL);
    for (i = 0; i < 4; i++) {
        result = htable_insert(&dictionary, (const void *)ids[i], (const void *)values[i]);
        printf("Inserted %s:%s (%d)\n", ids[i], values[i], result);
    }
    printf("Dictionary size %d capacity %d bucket_size %d max_bucket_size %d\n",
           dictionary.size, dictionary.capacity, dictionary.bucket_size, dictionary.max_bucket_size);
    for (i = 4; i < len; i++) {
        result = htable_insert(&dictionary, (const void *)ids[i], (const void *)values[i]);
        printf("Inserted %s:%s (%d)\n", ids[i], values[i], result);
    }
    printf("Dictionary size %d capacity %d bucket_size %d max_bucket_size %d\n",
           dictionary.size, dictionary.capacity, dictionary.bucket_size, dictionary.max_bucket_size);
           
    printf("Reading keys:\n");
    htable_keys(&dictionary, &out_keys);
    elem = list_head(&out_keys);
    while (elem != NULL) {
        key = (char *)list_data(elem);
        htable_lookup(&dictionary, (const void *)key, (void **)&value);
        printf("Read key:value %s:%s\n", key, value);
        elem = list_next(elem);
    }
    
    printf("Removing keys and values:\n");
    elem = list_head(&out_keys);
    while (elem != NULL) {
        key = (char *)list_data(elem);
        result = htable_remove(&dictionary, (const void *)key, (void **)&removed_key, (void **)&removed_value);
        printf("removing res %d key:vlaue %s:%s\n", result, removed_key, removed_value);
        elem = list_next(elem);
    }
    
    printf("Removing non-existent key:\n");
    result = htable_remove(&dictionary, (const void *)values[0], (void **)&removed_key, (void **)&removed_value);
    printf("removing res %d key:vlaue %s:%s\n", result, removed_key, removed_value);
    printf("Dictionary size %d capacity %d bucket_size %d max_bucket_size %d\n",
           dictionary.size, dictionary.capacity, dictionary.bucket_size, dictionary.max_bucket_size);
           
    // Make sure each bucket in the hash table is actually empty
    printf("Manually iterating through each bucket\n");
    for (int i = 0; i < dictionary.capacity; i++) {
        DList *bucket = dictionary.buckets + i;
        DListElem *node = dlist_head(bucket);
        char *status = node == NULL ? "empty" : "not empty";
        printf("%s ", status);
    }
    printf("\n");
    
    list_destroy(&out_keys);
    htable_destroy(&dictionary);
    return 0;
}
