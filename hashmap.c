/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:37:12 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/15 22:19:56 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

t_table	*hash_table_create(uint32_t size, t_hash_function *f)
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
		save_free((void **)&ht);
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
			save_free((void **)&current->key);
			save_free((void **)&current->value);
			save_free((void **)&current);
			current = next;
		}
	}
	save_free((void **)&ht->elements);
	save_free((void **)&ht);
}

bool	hash_table_insert(t_table *ht, const char *key, const char *value)
{
	uint32_t	index;
	t_node		*new_node;

	remove_last_newline((char **)&key);
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->og_hash = ht->hash(key);
	index = convert_hash(new_node->og_hash);
	if (!new_node)
		return (false);
	new_node->key = key;
	if (!new_node->key)
	{
		save_free((void **)&new_node);
		return (false);
	}
	new_node->value = value;
	if (!new_node->value)
	{
		save_free((void **)&new_node->key);
		save_free((void **)&new_node);
		return (false);
	}
	new_node->next = ht->elements[index];
	ht->elements[index] = new_node;
	return (true);
}

void	*hash_table_lookup(t_table *ht, char *key)
{
	uint32_t	index;
	t_node		*current;
	uint64_t	og_hash;

	remove_last_newline(&key);
	og_hash = ht->hash(key);
	index = convert_hash(og_hash);
	current = ht->elements[index];
	if (current && !current->next)
		return ((void *)current->value);
	else
	{
		while (current)
		{
			if ((current->og_hash == og_hash && *key == *current->key && ft_strncmp(key, current->key,
						ft_strlen(current->key)) == 0))
				return ((void *)current->value);
			current = current->next;
		}
	}
	return (NULL);
}
