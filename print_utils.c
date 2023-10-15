/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:37:24 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/15 15:58:27 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	ft_putchar_fd(char c, int fd)
{
	(void)write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (s && *s)
		ft_putchar_fd(*(s++), fd);
}

void	remove_last_newline(char **s)
{
	int	len;

	len = ft_strlen(*s);
	if (*s == NULL || **s == '\0')
		return ;
	if (len > 0 && (*s)[len - 1] == '\n')
	{
		(*s)[len - 1] = '\0';
	}
}
