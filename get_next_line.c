#include <stdio.h>

#include "get_next_line.h"

char	*first_time(int fd, char *save, char *copy)
{
	int	i;

	copy = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (save == NULL || copy == NULL)
		return (NULL);
	i = read(fd, save, BUFFER_SIZE);
	save[i] = '\0';
	ft_strlcpy(copy, save, (BUFFER_SIZE + 1));
	while (check_buffer(save) < 0)
	{
		i = read(fd, save, BUFFER_SIZE);
		save[i] = '\0';
		make_line(copy, save);
		if (copy == NULL)
			return (NULL);
	}
	return (copy);
}

char	*other_times(int fd, char *save, char *copy)
{
	int	k;

	free(save);
	save = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (save == NULL)
		return (NULL);
	if (check_buffer(copy) < 0)
	{
		k = read(fd, save, BUFFER_SIZE);
		save[k] = '\0';
		if (k == 0)
			return (NULL);
		make_line(copy, save);
		if (copy == NULL)
			return (NULL);
		while (check_buffer(save) < 0)
		{
			k = read(fd, save, BUFFER_SIZE);
			save[k] = '\0';
			make_line(copy, save);
			if (copy == NULL)
				return (NULL);
		}
	}
	return (copy);
}

char	*result(char *copy, char *save)
{
	int		i;
	char	*line;

	i = 0;
	while (copy[i] != '\n' && copy[i] != '\0')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, copy, i + 2);
	free(save);
	save = malloc((ft_strlen(copy) - i) * sizeof(char));
	if (save == NULL)
		return (NULL);
	ft_strlcpy(save, (copy + i + 1), (ft_strlen(copy) - i));
	free(copy);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*copy;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save != NULL)
	{
		copy = malloc((ft_strlen(save) + 1) * sizeof(char));
		if (copy == NULL)
			return (NULL);
		ft_strlcpy(copy, save, (ft_strlen(save) + 1));
		copy = other_times(fd, save, copy);
		if (copy == NULL)
			return (NULL);		
	}
	if (save == NULL)
	{
		save = malloc((BUFFER_SIZE + 1) * sizeof(char));
		copy = first_time(fd, save, copy);
		if (copy == NULL)
			return (NULL);		
	}
	return (result(copy, save));
}
