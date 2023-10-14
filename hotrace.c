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
			save_free((void**)&key);
		}
		else
		{
			i = 0;
			while (key[i] && key[i] != '\n')
				ft_putchar_fd(key[i++], STDOUT_FILENO);
			ft_putstr_fd(": Not found.\n", STDOUT_FILENO);
		}
		save_free((void**)&key);
	}
}

void hash_table_print(t_table *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        printf("Bucket %d:\n", i);
        t_node *current = ht->elements[i];
        while (current) {
            printf("  Key: %s, Value: %s\n", current->key, current->value);
            current = current->next;
        }
    }
}

int	main(void)
{
	t_table	*ht;

	if (!build_hashmap(&ht))
		return (-1);
	// hash_table_print(ht);
	// printf("=======\n\n");
	search(&ht);
	hash_table_destroy(ht);
}
