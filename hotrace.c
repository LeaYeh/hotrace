#include <stdio.h>
#include "hotrace.h"

bool	is_empty(char *str)
{
	if (str && *str == '\n')
		return (true);
	return (false);
}

bool	gnl(int fd, char **line)
{
	// safe_free(line);
	*line = get_next_line(STDIN_FILENO);
	if (*line)
		return (true);
	return (false);
}

int main()
{
	char    *line;
	char    *key;
	char    *value;
	t_table *ht;

	ht = hash_table_create(MAX_HASH_LEN, hash_djb2);
	if (!ht)
	{
		perror("Error: Create hash table failed.");
		return (-1);
	}
	while (gnl(STDIN_FILENO, &line))
	{
		if (is_empty(line))
			break ;
		key = line;
		if (!gnl(STDIN_FILENO, &line) || is_empty(line))
        {
            perror("Error: Incomplete key-value pair in the file.");
            return (-1);
        }
		value = line;
		hash_table_insert(ht, key, value);
		free(key);
		free(value);
	}
	while (gnl(STDIN_FILENO, &key))
	{
		value = (char *)hash_table_lookup(ht, key);
		if (value)
		{
			ft_putstr_fd(value, STDOUT_FILENO);
			free(value);
		}
		else
		{
			ft_putstr_fd(key, STDOUT_FILENO);
			ft_putstr_fd(": Not found\n", STDOUT_FILENO);
		}
	}
	hash_table_destroy(ht);
}
