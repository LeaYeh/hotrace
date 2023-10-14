#ifndef HASHMAP_H
#define HASHMAP_H

#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint64_t (hash_function) (const char*, size_t);

typedef struct hash_node
{
    const char *key;
    const char *value;
    
    struct hash_node *next;
} h_node;

typedef struct hash_table
{
    u_int32_t size;
    hash_function *hash;
    h_node **elements;

} h_table;

h_table *hash_table_create(uint32_t size, hash_function *f);
void hash_table_destroy(h_table *ht);
void hash_table_print(h_table *ht);
bool hash_table_insert(h_table *ht, const char *key, const char *value);
void *hash_table_lookup(h_table *ht, const char *key);
void *hash_table_delete(h_table *ht, const char *key);



#endif