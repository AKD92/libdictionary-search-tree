#ifndef HTABLE_H_INCLUDED
#define HTABLE_H_INCLUDED

#include <dlist.h>

struct KeyDataPair_ {
    
    const void *key;
    const void *data;
};
typedef struct KeyDataPair_ KeyDataPair

struct HTable_ {
    
    unsigned int size;
    DList *bucket;
    int (*hashcode)(const void *key);
    int (*equals) (const void *key1, const void *key2);
    void (*destroy_key) (const void *key);
    void (*destroy_data) (const void *data);
};
typedef struct HTable_ HTable;

#endif // HTABLE_H_INCLUDED
