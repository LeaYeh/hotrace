/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:37:59 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/15 21:58:17 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void    *ft_memcpy(void *dst, const void *src, size_t len)
{
    size_t                i;
    unsigned char        *dst_ptr;
    const unsigned char    *src_ptr = src;
    
    dst_ptr = dst;
    if (len == 0 || dst == src) {
        return dst;
    }
    i = 0;
    while ( i < len >> 3) 
    {     
        *(uint64_t*)(dst_ptr + (i << 3)) = *(const uint64_t*)(src_ptr +( i << 3));
        i++;
    }
    i = i << 3;
    while (i < len)
    {
        dst_ptr[i] = src_ptr[i];
        i++;
    }
    return dst;
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
