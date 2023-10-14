#include "hashmap.h"
#include <stdio.h>
#include <string.h>

uint32_t	convert_hash(uint32_t hash)
{
	uint32_t	mask;

	mask = (1 << MAX_HASH_SIZE) - 1;
	return (hash & mask);
}

uint32_t hash_djb2(const char *str, size_t len) {
    uint32_t hash = 5381;
    for (size_t i = 0; i < len; i++) {
        hash = ((hash << 5) + hash) + str[i];
    }
    return (convert_hash(hash));
}

h_table *hash_table_create(uint32_t size, hash_function *f) {
    h_table *ht = (h_table *)malloc(sizeof(h_table));
    if (!ht) {
        return NULL;
    }
    ht->size = size;
    ht->hash = f;
    ht->elements = (h_node **)calloc(size, sizeof(h_node *));
    if (!ht->elements) {
        free(ht);
        return NULL;
    }

    return ht;
}

void hash_table_destroy(h_table *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        h_node *current = ht->elements[i];
        while (current) {
            h_node *next = current->next;
            free((char *)current->key);
            free((char *)current->value);
            free(current);
            current = next;
        }
    }
    free(ht->elements);
    free(ht);
}

bool hash_table_insert(h_table *ht, const char *key, const char *value) {
    uint64_t hash = ht->hash(key, strlen(key));
    uint32_t index = hash % ht->size;

    h_node *new_node = (h_node *)malloc(sizeof(h_node));
    if (!new_node) {
        return false;
    }

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = ht->elements[index];
    ht->elements[index] = new_node;

    return true;
}

void *hash_table_lookup(h_table *ht, const char *key) {
    uint64_t hash = ht->hash(key, strlen(key));
    uint32_t index = hash % ht->size;

    h_node *current = ht->elements[index];
    while (current) {
        if (strcmp(key, current->key) == 0) {
            return (void *)current->value;
        }
        current = current->next;
    }

    return NULL;
}

void *hash_table_delete(h_table *ht, const char *key) {
    uint64_t hash = ht->hash(key, strlen(key));
    uint32_t index = hash % ht->size;

    h_node *current = ht->elements[index];
    h_node *prev = NULL;

    while (current) {
        if (strcmp(key, current->key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                ht->elements[index] = current->next;
            }

            void *value = (void *)current->value;
            free((char *)current->key);
            free((char *)current->value);
            free(current);

            return value;
        }
        prev = current;
        current = current->next;
    }

    return NULL;
}

void hash_table_print(h_table *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        printf("Bucket %d:\n", i);
        h_node *current = ht->elements[i];
        while (current) {
            printf("  Key: %s, Value: %s\n", current->key, current->value);
            current = current->next;
        }
    }
}

int main() {
    h_table *ht = hash_table_create(MAX_HASH_SIZE, hash_djb2);
    hash_table_insert(ht, "key1", "value1");
    hash_table_insert(ht, "key2", "value2");
    hash_table_insert(ht, "key3", "value3");

    printf("Hash Table:\n");
    hash_table_print(ht);

    const char *value = (const char *)hash_table_lookup(ht, "key2");
    if (value) {
        printf("Lookup result: key2 -> %s\n", value);
    } else {
        printf("Key not found\n");
    }

    void *deleted_value = hash_table_delete(ht, "key1");
    if (deleted_value) {
        printf("Deleted key1 -> %s\n", (const char *)deleted_value);
    } else {
        printf("Key not found for deletion\n");
    }

    printf("Updated Hash Table:\n");
    hash_table_print(ht);

    hash_table_destroy(ht);

    return 0;
}
