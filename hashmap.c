#include "hotrace.h"

#include <stdint.h>
#include <string.h>

#include <stdint.h>
#include <stddef.h>

// Constants for xxHash algorithm
static const uint64_t PRIME64_1 = 11400714785074694791ULL;
static const uint64_t PRIME64_2 = 14029467366897019727ULL;
static const uint64_t PRIME64_3 = 1609587929392839161ULL;
static const uint64_t PRIME64_4 = 9650029242287828579ULL;
static const uint64_t PRIME64_5 = 2870177450012600261ULL;

// Rotate left operation
static inline uint64_t rotl64(uint64_t x, int r) {
    return (x << r) | (x >> (64 - r));
}

// Mix individual bits
static inline uint64_t mix(uint64_t acc, uint64_t val) {
    val *= PRIME64_2;
    val = rotl64(val, 31);
    val *= PRIME64_1;
    acc ^= val;
    acc = acc * PRIME64_1 + PRIME64_4;
    return acc;
}

// Finalize hash
static inline uint64_t finalize(uint64_t acc, const char* data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        acc = mix(acc, data[i]);
    }
    acc ^= len;
    acc = (acc ^ (acc >> 33)) * PRIME64_2;
    acc = (acc ^ (acc >> 29)) * PRIME64_3;
    return acc ^ (acc >> 32);
}

// xxHash main function
uint64_t hash_djb2(const char* input) {
	int64_t seed = 14695981039346656037ULL;
	size_t len = ft_strlen(input);
    uint64_t acc = seed + PRIME64_5;
    const char* end = input + len;

    while (input + 8 <= end) {
        uint64_t data;
        memcpy(&data, input, 8);
        acc = mix(acc, data);
        input += 8;
    }

    if (input + 4 <= end) {
        uint32_t data;
        memcpy(&data, input, 4);
        acc = mix(acc, data);
        input += 4;
    }

    while (input < end) {
        acc = mix(acc, *input);
        input++;
    }

    return finalize(acc, input, len);
}

// MurmurHash3 function with a fixed seed
// uint32_t hash_djb2(const char *key) {
//     uint32_t seed = 0; // You can choose an appropriate seed value
//     uint32_t len = (uint32_t)strlen(key);
//     const uint32_t c1 = 0xcc9e2d51;
//     const uint32_t c2 = 0x1b873593;
//     const uint32_t r1 = 15;
//     const uint32_t r2 = 13;
//     const uint32_t m = 5;
//     const uint32_t n = 0xe6546b64;

//     uint32_t hash = seed;
//     const uint32_t *data = (const uint32_t *)key;
//     const uint32_t *end = data + (len / 4);

//     while (data < end) {
//         uint32_t k = *data++;
//         k *= c1;
//         k = (k << r1) | (k >> (32 - r1));
//         k *= c2;

//         hash ^= k;
//         hash = (hash << r2) | (hash >> (32 - r2));
//         hash = hash * m + n;
//     }

//     const uint8_t *tail = (const uint8_t *)data;
//     uint32_t k1 = 0;

//     switch (len & 3) {
//         case 3:
//             k1 ^= (uint32_t)(tail[2]) << 16;
//         case 2:
//             k1 ^= (uint32_t)(tail[1]) << 8;
//         case 1:
//             k1 ^= (uint32_t)(tail[0]);
//             k1 *= c1;
//             k1 = (k1 << r1) | (k1 >> (32 - r1));
//             k1 *= c2;
//             hash ^= k1;
//     }

//     hash ^= len;
//     hash ^= (hash >> 16);
//     hash *= 0x85ebca6b;
//     hash ^= (hash >> 13);
//     hash *= 0xc2b2ae35;
//     hash ^= (hash >> 16);

//     return hash;
// }



uint32_t	convert_hash(uint64_t hash)
{
	uint64_t	mask;

	mask = ((uint64_t)1 << MAX_HASH_BITS) - 1;
	return ((uint32_t)(hash & mask));
}

// uint32_t	hash_djb2(const char *str)
// {
// 	uint32_t	hash;

// 	hash = 5381;
// 	while (*str)
// 	{
// 		hash = ((hash << 5) + hash) + (*str);
// 		str++;
// 	}
// 	return (hash);
// }

t_table	*hash_table_create(uint32_t size, hash_function *f)
{
	t_table	*ht;

	ht = (t_table *)malloc(sizeof(t_table));
	if (!ht)
		return (NULL);
	ht->size = size;
	ht->hash = f;
	ht->elements = (t_node **)ft_calloc(size, sizeof(t_node *));
	if (!ht->elements)
	{
		save_free((void**)&ht);
		return (NULL);
	}
	return (ht);
}

void	hash_table_destroy(t_table *ht)
{
	uint32_t	i;
	t_node		*current;
	t_node		*next;

	i = 0;
	while (i < ht->size)
	{
		current = ht->elements[i++];
		while (current)
		{
			next = current->next;
			save_free((void**)&current->key);
			save_free((void**)&current->value);
			save_free((void**)&current);
			current = next;
		}
	}
	save_free((void**)&ht->elements);
	save_free((void**)&ht);
}

bool	hash_table_insert(t_table *ht, const char *key, const char *value)
{
	uint32_t	index;
	t_node		*new_node;

	// remove_last_newline((char **)&key);
	index = convert_hash(ht->hash(key));
	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (false);
	new_node->key = key;
	if (!new_node->key)
	{
		save_free((void**)&new_node);
		return (false);
	}
	new_node->value = value;
	if (!new_node->value)
	{
		save_free((void**)&new_node->key);
		save_free((void**)&new_node);
		return (false);
	}
	new_node->next = ht->elements[index];
	ht->elements[index] = new_node;
	return (true);
}

void	*hash_table_lookup(t_table *ht, char *key)
{
	uint32_t	index;
	t_node		*current;

	index = convert_hash(ht->hash(key));
	current = ht->elements[index];
	while (current)
	{
		if (*key == *current->key && ft_strcmp(key, current->key) == 0)
			return ((void *)current->value);
		current = current->next;
	}
	return (NULL);
}

// int main() {
// 	t_table *ht = hash_table_create(MAX_HASH_LEN, hash_djb2);
// 	hash_table_insert(ht, "key1", "value1");
// 	hash_table_insert(ht, "key2", "value2");
// 	hash_table_insert(ht, "key3", "value3");

// 	printf("Hash Table:\n");
// 	//hash_table_print(ht);

// 	const char *value = (const char *)hash_table_lookup(ht, "key2");
// 	if (value) {
// 		printf("Lookup result: key2 -> %s\n", value);
// 	} else {
// 		printf("Key not found\n");
// 	}

// 	void *deleted_value = hash_table_delete(ht, "key1");
// 	if (deleted_value) {
// 		printf("Deleted key1 -> %s\n", (const char *)deleted_value);
// 	} else {
// 		printf("Key not found for deletion\n");
// 	}

// 	printf("Updated Hash Table:\n");
// 	//hash_table_print(ht);

// 	hash_table_destroy(ht);

// 	return (0);
// }
