#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int     main(void)
{
	int	fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		printf("fail to open\n");
	line = get_next_line(fd);
	while (line != NULL)
	{	
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
