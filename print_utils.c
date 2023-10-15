#include "hotrace.h"

void	ft_putchar_fd(char c, int fd)
{
	(void)write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
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
