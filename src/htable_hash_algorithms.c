
#include "htable.h"
#include <stdlib.h>
#include <stdint.h>

//  Implementation of Bob Jenkin's One At A Time hash algorithm
//  https://en.wikipedia.org/wiki/Jenkins_hash_function
uint32_t BJHash32(const unsigned char *key, unsigned int length);


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
    return (unsigned int) BJHash32(key, length);
}


int htable_hash_combine_start(unsigned int *combined_hash) {
    if (combined_hash == NULL)
        return -1;
    *combined_hash = 5381;
    return 0;
}


int htable_hash_combine_add(unsigned int *combined_hash, unsigned int hashcode) {
    // Here we are using DJB2 hash algorithm to combine hashes.
    // https://theartincode.stanis.me/008-djb2/
    // Basically we are multiplying old combined_hash value with 33 (left shift by 5bit then add)
    // then add our hash code to it
    if (combined_hash == NULL)
        return -1;
    *combined_hash = ((*combined_hash << 5) + *combined_hash) + hashcode;
    return 0;
}
