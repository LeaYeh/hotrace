/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:37:33 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/15 19:52:05 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <stdio.h>

bool	gnl(int fd, char **line)
{
	*line = get_next_line(fd);
	if (*line != NULL)
		return (true);
	return (false);
}

bool	parse_input(t_table **ht)
{
	char	*line;
	char	*key;
	char	*value;

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
		hash_table_insert(*ht, key, value);
	}
	return (true);
}

bool	build_hashmap(t_table **ht)
{
	*ht = hash_table_create(MAX_HASH_LEN, hash_djb2);
	if (!*ht)
	{
		perror("Error: Create hash table failed.");
		return (false);
	}
	if (!parse_input(ht))
	{
		hash_table_destroy(*ht);
		return (false);
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




int	main(void)
{
	t_table	*ht;

	if (!build_hashmap(&ht))
		return (-1);
	search(&ht);
	printf("Collisions: %i\n" ,count_collisions(ht));
	hash_table_destroy(ht);
}
