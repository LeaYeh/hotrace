#ifndef HASHMAP_H
# define HASHMAP_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_HASH_BITS 8
# define MAX_HASH_LEN 256

typedef					uint32_t(hash_function)(const char *);

typedef struct hash_node
{
	const char			*key;
	const char			*value;
	struct hash_node	*next;
}						t_node;

typedef struct hash_table
{
	u_int32_t			size;
	hash_function		*hash;
	t_node				**elements;

}						t_table;

t_table					*hash_table_create(uint32_t size, hash_function *f);
void					hash_table_destroy(t_table *ht);
void					hash_table_print(t_table *ht);
bool					hash_table_insert(t_table *ht, const char *key,
							const char *value);
void					*hash_table_lookup(t_table *ht, const char *key);
void					*hash_table_delete(t_table *ht, const char *key);

void					*ft_calloc(size_t count, size_t size);
void					*ft_memset(void *dst, int val, size_t len);
size_t					ft_strlen(const char *str);
char					*ft_strdup(const char *s1);
int						ft_strncmp(const char *s1, const char *s2, size_t len);
void					*ft_memcpy(void *dst, const void *src, size_t len);

#endif