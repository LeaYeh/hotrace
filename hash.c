#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hotrace.h"

typedef struct s_murmur_tab
{
	uint32_t	c1;
    uint32_t	c2;
    uint32_t	r1;
    uint32_t	r2;
    uint32_t	m;
    uint32_t	n;
	uint32_t	nblocks;
	uint32_t	*blocks;
	uint32_t 	hash;
}	t_murmur_tab;

// error_code	ft_init_murmur_table(const char *key, size_t len, uint32_t seed)
// {}

t_murmur_tab	*init_murmur_table(const char *key, size_t len, uint32_t seed)
{
	t_murmur_tab *tab;

	tab = (t_murmur_tab *)malloc(sizeof(t_murmur_tab) * 1);
	if (!tab)
		return (NULL);
	tab->c1 = 0xcc9e2d51;
	tab->c2 = 0x1b873593;
	tab->r1 = 15;
	tab->r2 = 13;
	tab->m = 5;
	tab->n = 0xe6546b64;
	tab->nblocks = len / 4;
	tab->blocks = (uint32_t *)key;
	return (tab);
}

uint32_t ft_murmur3_hash(const char *key, size_t len, uint32_t seed)
{
	t_murmur_tab	*tab;
	int				i;
	int				tmp;

	tab = init_murmur_table(key, len, seed);
	i = 0;
	while (i < tab->nblocks)
	{
		tmp = tab->blocks[i];
		tmp *= tab->c1;
		tmp = (tmp << tab->r1) | (tmp >> (32 - tab->r1));
		tmp *= tab->c2;
		tab->hash ^= tmp;
        tab->hash = ((tab->hash << tab->r2) | (tab->hash >> (32 - tab->r2)));
		tab->hash = tab->hash * tab->m + tab->n;
	}
	
	free(tab);
}

uint32_t murmur3_hash(const char *key, size_t len, uint32_t seed) {
    // Constants for mixing
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    const uint32_t r1 = 15;
    const uint32_t r2 = 13;
    const uint32_t m = 5;
    const uint32_t n = 0xe6546b64;

    // Initialize hash with the seed
    uint32_t hash = seed;

    // Process the input in blocks of 4 bytes
    const int nblocks = len / 4;
    const uint32_t *blocks = (const uint32_t *)key;

    // Main mixing loop
    for (int i = 0; i < nblocks; i++) {
        uint32_t k = blocks[i];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        hash ^= k;
        hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
    }

    // Handle the remaining bytes (less than 4)
    const uint8_t *tail = (const uint8_t *)(key + nblocks * 4);
    uint32_t k1 = 0;

    // Process the remaining bytes based on the length
    switch (len & 3) {
        case 3:
            k1 ^= tail[2] << 16;
            // Fall through
        case 2:
            k1 ^= tail[1] << 8;
            // Fall through
        case 1:
            k1 ^= tail[0];
            k1 *= c1;
            k1 = (k1 << r1) | (k1 >> (32 - r1));
            k1 *= c2;
            hash ^= k1;
    }

    // Finalize the hash with additional mixing and transformations
    hash ^= len;
    hash ^= hash >> 16;
    hash *= 0x85ebca6b;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;

    return hash;
}

uint32_t	ft_convert_hash(uint32_t hash)
{
	uint32_t	mask;

	mask = (1 << MAX_HASH_SIZE) - 1;
	return (hash & mask);
}

uint32_t	ft_djb_hash(const char *str)
{
	uint32_t hash = 5381;

	while (*str) {
        hash = ((hash << 5) + hash) + (*str);
        str++;
    }
    return (ft_convert_hash(hash));
}

// int main() {
//     const char *message = "Hello, hash!";

//     printf("djb for '%s': %u\n", message, ft_djb_hash(message));
// 	printf("murmur3 for '%s': %u\n", message, ft_murmur3_hash(message, strlen(message), 4242));
//     return (0);
// }