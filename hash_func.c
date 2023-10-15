/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:42:13 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/15 20:48:49 by lyeh             ###   ########.fr       */
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
	uint64_t		hash;
	const uint64_t	prime = 0x00000100000001B3;

	hash = 0xcbf29ce484222325;
	while (*str)
	{
		hash ^= (uint64_t)(*str++);
		hash *= prime;
	}
	return (hash);
}
