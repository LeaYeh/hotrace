#include "hotrace.h"
#include <stdio.h>

bool	is_empty(char *str)
{
	if (str && *str == '\n')
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
			save_free((void **)&line);
			break ;
		}
		key = line;
		if (!gnl(STDIN_FILENO, &line) || is_empty(line))
		{
			save_free((void **)&key);
			save_free((void **)&line);
			return (true);
		}
		value = line;
		// printf("insert %s: %s\n", key, value);
		hash_table_insert(*ht, key, value);
	}
	return (true);
}

void	search(t_table **ht)
{
	int		i;
	char	*key;
	char	*value;

	while (gnl(STDIN_FILENO, &key))
	{
		// printf("searching key: %s", key);
		value = (char *)hash_table_lookup(*ht, key);
		if (value)
		{
			ft_putstr_fd(value, STDOUT_FILENO);
			save_free((void **)&key);
		}
		else
		{
			i = 0;
			while (key[i] && key[i] != '\n')
				ft_putchar_fd(key[i++], STDOUT_FILENO);
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

int count_collisions(const t_table *ht) {

    int collision_count = 0;

    for (int i = 0; i < MAX_HASH_LEN; i++) {
        t_node *current = ht->elements[i];
        uint64_t og_hash = 0;
        int count = 0;

        while (current) {
            if (current->og_hash == og_hash) {
                count++;
                if (count > 1) {
                    collision_count++; // Increment collision count
                }
            } else {
                og_hash = current->og_hash;
                count = 1;
            }

            current = current->next;
        }
    }

    return collision_count;
}




int	main(void)
{
	t_table	*ht;

	if (!build_hashmap(&ht))
		return (-1);
	// hash_table_print(ht);
	// printf("=======\n\n");
	search(&ht);
	printf("Collisions: %i\n" ,count_collisions(ht));
	hash_table_destroy(ht);
}
// [mac|MAX_HASH_BITS=10] ./hotrace < tests/test07.htr  35.27s user 20.26s system 98% cpu 56.131 total
// [mac|MAX_HASH_BITS=16] ./hotrace < tests/test07.htr  9.33s user 20.43s system 97% cpu 30.394 total
// [mac|MAX_HASH_BITS=18] ./hotrace < tests/test07.htr  8.87s user 20.32s system 96% cpu 30.382 total
// [mac|MAX_HASH_BITS=20] ./hotrace < tests/test07.htr  8.76s user 20.35s system 97% cpu 29.968 total
// [mac|MAX_HASH_BITS=30] ./hotrace < tests/test07.htr  15.99s user 23.52s system 93% cpu 42.174 total
