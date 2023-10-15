/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:37:59 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/15 15:55:09 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	if (len == 0 || dst == src)
		return (dst);
	i = 0;
	dst_ptr = dst;
	src_ptr = src;
	while (i < len)
	{
		dst_ptr[i] = src_ptr[i];
		i++;
	}
	return (dst_ptr);
}

void	*ft_memset(void *dst, int val, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)dst;
	while (len-- > 0)
		*ptr++ = (unsigned char)val;
	return (dst);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, size * count);
	return (ptr);
}

void	save_free(void **f)
{
	if (*f)
	{
		free(*f);
		*f = NULL;
	}
}

bool	is_empty(char *str)
{
	if (str && *str == '\n')
		return (true);
	return (false);
}
