#ifndef HASHMAP_H
#define HASHMAP_H

#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

# define MAX_HASH_BITS 8
# define MAX_HASH_LEN 256

typedef uint32_t (hash_function) (const char *);

typedef struct hash_node
{
    const char *key;
    const char *value;
    struct hash_node *next;
}   h_node;

typedef struct hash_table
{
    u_int32_t size;
    hash_function *hash;
    static h_node *elements[4294967295];

}   h_table;

h_table *hash_table_create(uint32_t size, hash_function *f);
void    hash_table_destroy(h_table *ht);
void    hash_table_print(h_table *ht);
bool    hash_table_insert(h_table *ht, const char *key, const char *value);
void    *hash_table_lookup(h_table *ht, const char *key);
void    *hash_table_delete(h_table *ht, const char *key);

void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *dst, int val, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
int     ft_strncmp(const char *s1, const char *s2, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t len);

#endif