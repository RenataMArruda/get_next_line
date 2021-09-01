#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int     main(void)
{
	int	fd;
	char	*line;
	int	i;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		printf("fail to open\n");
	i = 1;
	printf("\nROUND %d\n", i);
	line = get_next_line(fd);
	printf("line: %s\n", line);
	free(line);
	while (line != NULL)
	{	
		i++;
		printf("\nROUND %d\n", i);
		line = get_next_line(fd);
		printf("line: %s\n", line);
		free(line)
  }
// while(1){}
	return (0);
}
