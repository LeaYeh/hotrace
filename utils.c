#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include "hotrace.h"

u_int32_t	get_dict_size(int fd)
{
	char		buffer[BUFFER_SIZE];
	u_int32_t	line_cnt;
    int			bytes_read;
	int			i;
	bool		meet_newline;

	line_cnt = 0;
	meet_newline = false;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		while (i++ < bytes_read)
		{
			if (buffer[i] == '\n')
                line_cnt++;
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
    }
    close(fd);
	return (line_cnt / 2);
}
void	*ft_memset(void *dst, int val, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) dst;
	while (len-- > 0)
		*ptr++ = (unsigned char)val;
	return (dst);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;

	ptr = (void *)malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, size * count);
	return (ptr);
}
