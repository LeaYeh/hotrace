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
	// safe_free(line);
	*line = get_next_line(STDIN_FILENO);
	if (*line)
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
			break ;
		key = line;
		if (!gnl(STDIN_FILENO, &line) || is_empty(line))
			return (false);
		value = line;
		hash_table_insert(*ht, key, value);
		free(key);
		free(value);
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
		value = (char *)hash_table_lookup(*ht, key);
		if (value)
		{
			ft_putstr_fd(value, STDOUT_FILENO);
			free(value);
		}
		else
		{
			i = 0;
			while (key[i] && key[i] != '\n')
				ft_putchar_fd(key[i++], STDOUT_FILENO);
			ft_putstr_fd(": Not found\n", STDOUT_FILENO);
		}
	}
}

int	main(void)
{
	t_table	*ht;

	if (!build_hashmap(&ht))
		return (-1);
	search(&ht);
	hash_table_destroy(ht);
}
