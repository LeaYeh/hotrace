/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:42:13 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/15 15:55:05 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

uint32_t	convert_hash(uint64_t hash)
{
	uint64_t	mask;

	mask = ((uint64_t)1 << MAX_HASH_BITS) - 1;
	return ((uint32_t)(hash & mask));
}

uint64_t	hash_djb2(const char *str)
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
