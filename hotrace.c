#include "hotrace.h"
#include <stdio.h>

bool	is_empty(char *str)
{
	if (str && *str == '\0')
		return (true);
	return (false);
}

bool	gnl(int fd, char **line)
{
	*line = get_next_line(fd);
	if (*line != NULL)
		return (true);
	return (false);
}

bool	build_hashmap(t_table **ht)
{
	char	*line;
	char	*key;
	char	*value;

	*ht = hash_table_create(MAX_HASH_LEN, hash_djb2);
	if (!*ht)
	{
		perror("Error: Create hash table failed.");
		return (false);
	}
	while (gnl(STDIN_FILENO, &line))
	{
		if (is_empty(line))
		{
			free(line);
			break ;
		}
		key = line;
		if (!gnl(STDIN_FILENO, &line) || is_empty(line))
			return (true);
		value = line;
		// printf("insert %s: %s\n", key, value);
		hash_table_insert(*ht, key, value);
	}
	return (true);
}

void	search(t_table **ht)
{
	char	*key;
	char	*value;

	while (gnl(STDIN_FILENO, &key))
	{
		// printf("searching key: :%s:\n", key);
		value = (char *)hash_table_lookup(*ht, key);
		if (value)
		{
			ft_putstr_fd(value, STDOUT_FILENO);
			ft_putchar_fd('\n', 1);
			save_free((void **)&key);
		}
		else
		{
			ft_putstr_fd(key, STDOUT_FILENO);
			ft_putstr_fd(": Not found.\n", STDOUT_FILENO);
		}
		save_free((void **)&key);
	}
}

void	hash_table_print(t_table *ht)
{
	t_node	*current;

	for (uint32_t i = 0; i < ht->size; i++)
	{
		printf("Bucket %d:\n", i);
		current = ht->elements[i];
		while (current)
		{
			printf("  Key: %s, Value: %s\n", current->key, current->value);
			current = current->next;
		}
	}
}

#include <time.h>

int countCollisions(t_table* ht, size_t max_size) {
    int collisions = 0;
    int size = (max_size < ht->size) ? max_size : ht->size; // Ensure we don't go beyond the maximum size
    for (int i = 0; i < size; i++) {
        int count = 0;
        t_node* current = ht->elements[i];
        while (current != NULL) {
            count++;
            current = current->next;
        }
        if (count > 1) {
            collisions += count - 1;
        }
    }
    return collisions;
}

int	main(void)
{
	t_table	*ht;
	double	cpu_time_used;

	clock_t start, end;
	if (!build_hashmap(&ht))
		return (-1);
	printf("Collisions: %i\n", countCollisions(ht, MAX_HASH_LEN));
	start = clock();
	// hash_table_print(ht);
	// printf("=======\n\n");
	// hash_table_print(ht);
	//search(&ht);
	end = clock(); // Record the end time
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time taken: %f seconds\n", cpu_time_used);
	hash_table_destroy(ht);
}
// [mac|MAX_HASH_BITS=10] ./hotrace < tests/test07.htr  35.27s user 20.26s system 98% cpu 56.131 total
// [mac|MAX_HASH_BITS=16] ./hotrace < tests/test07.htr  9.33s user 20.43s system 97% cpu 30.394 total
// [mac|MAX_HASH_BITS=18] ./hotrace < tests/test07.htr  8.87s user 20.32s system 96% cpu 30.382 total
// [mac|MAX_HASH_BITS=20] ./hotrace < tests/test07.htr  8.76s user 20.35s system 97% cpu 29.968 total
// [mac|MAX_HASH_BITS=30] ./hotrace < tests/test07.htr  15.99s user 23.52s system 93% cpu 42.174 total
