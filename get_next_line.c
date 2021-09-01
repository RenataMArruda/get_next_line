/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rarruda <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/05 17:56:48 by rarruda       #+#    #+#                 */
/*   Updated: 2021/08/05 17:57:25 by rarruda       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*make_line(char **line, char *save)
{
	char	*copy;
	size_t	len_line;
	size_t	len_save;

	len_line = ft_strlen(*line);
	len_save = ft_strlen(save);
	copy = malloc((len_line + len_save + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, *line, (len_line + 1));
	ft_strlcat(copy, save, (len_line + len_save + 1));
	free(*line);
	*line = NULL;
	return (copy);
}

int	check_errors(char **str, int value)
{
	if (value < 0)
	{
		free(*str);
		*str = NULL;
		return (-1);
	}
	return (0);
}

char	*read_text(int fd, char *save, char *line)
{
	int	i;

	i = read(fd, save, BUFFER_SIZE);
	if (check_errors(&line, i) == -1)
		return (NULL);
	save[i] = '\0';
	if (i == 0)
		return (line);
	line = make_line(&line, save);
	if (line == NULL)
		return (NULL);
	while (check_buffer(save) < 0)
	{
		i = read(fd, save, BUFFER_SIZE);
		if (check_errors(&line, i) == -1)
			return (NULL);
		save[i] = '\0';
		if (i == 0)
			return (line);
		line = make_line(&line, save);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

char	*result(char *line, char *save)
{
	int		i;
	char	*copy;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	copy = malloc((i + 2) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, line, i + 2);
	if (ft_strlen(line) - i > 0)
		ft_strlcpy(save, (line + i + 1), (ft_strlen(line) - i));
	free(line);
	line = NULL;
	return (copy);
}

char	*get_next_line(int fd)
{
	static char	save[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	line = malloc((ft_strlen(save) + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, save, (ft_strlen(save) + 1));
	if (check_buffer(line) < 0)
	{
		line = read_text(fd, save, line);
		if (line == NULL || ft_strlen(line) == 0)
		{
			check_errors(&line, -1);
			return (NULL);
		}
	}
	line = result(line, save);
	if (line == NULL)
	{
		check_errors(&line, -1);
		return (NULL);
	}
	return (line);
}
