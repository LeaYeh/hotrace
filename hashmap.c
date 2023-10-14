#include "hotrace.h"

uint32_t	convert_hash(uint64_t hash)
{
	uint64_t	mask;

	mask = ((uint64_t)1 << MAX_HASH_BITS) - 1;
	return ((uint32_t)(hash & mask));
}

uint32_t	hash_djb2(const char *str)
{
	uint32_t	hash;

	hash = 5381;
	while (*str)
	{
		hash = ((hash << 5) + hash) + (*str);
		str++;
	}
	return (hash);
}

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

void	*hash_table_lookup(t_table *ht, const char *key)
{
	uint32_t	index;
	t_node		*current;

	index = convert_hash(ht->hash(key));
	current = ht->elements[index];
	while (current)
	{
		if (ft_strncmp(key, current->key, ft_strlen(key)) == 0)
			return ((void *)current->value);
		current = current->next;
	}
	return (NULL);
}

<<<<<<< Updated upstream
=======
void	hash_table_print(t_table *ht)
{
	uint32_t	i;
	t_node		*current;

	i = 0;
	while (i < ht->size)
	{
		printf("Bucket %d:\n", i);
		current = ht->elements[i];
		while (current)
		{
			printf("  Key: %s, Value: %s\n", current->key, current->value);
			current = current->next;
		}
		i++;
	}
}

>>>>>>> Stashed changes
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
