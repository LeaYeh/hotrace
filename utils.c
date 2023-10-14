#include <stdint.h>
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
	meet_newline = FALSE;
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
}
