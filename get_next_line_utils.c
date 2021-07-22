#include "get_next_line.h"

int	check_buffer(char *str)
{
	int	n;

	n = 0;
	while (n < BUFFER_SIZE && str[n] != '\0')
	{
		if (str[n] == '\n')
			return (n);
		n++;
	}
	return (-1);
}

char	*make_line(char *copy, char *save)
{
	char	*line;

	line = malloc((ft_strlen(copy) + ft_strlen(save) + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, copy, (ft_strlen(copy) + 1));
	ft_strlcat(line, save, (ft_strlen(copy) + ft_strlen(save) + 1));
	free(copy);
	copy = malloc((ft_strlen(line) + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, line, (ft_strlen(line) + 1));
	free(line);
	return (copy);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	int		len;

	if (src == NULL)
		return (0);
	len = 0;
	while (((unsigned char *)src)[len] != '\0')
		len++;
	i = 0;
	if (dstsize > 0)
	{
		while (i < (dstsize - 1) && src[i] != '\0')
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
		((unsigned char *)dest)[i] = '\0';
	}
	return (len);
}

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;
	size_t	j;

	len_src = ft_strlen(src);
	len_dest = ft_strlen(dest);
	if (dstsize == 0)
		return (len_src);
	i = 0;
	j = len_dest;
	if ((dstsize - 1) < len_dest)
		return (dstsize + len_src);
	else
	{
		while (((unsigned char *)src)[i] != '\0' && j < (dstsize - 1))
		{
			((unsigned char *)dest)[j] = ((unsigned char *)src)[i];
			j++;
			i++;
		}
		((unsigned char *)dest)[j] = '\0';
	}
	return (len_dest + len_src);
}
