/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrijime <adrijime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:36:06 by adrijime          #+#    #+#             */
/*   Updated: 2024/05/08 20:45:04 by adrijime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*upd_storage(char *storage)
{
	char	*new_storage;
	int		i;
	int		j;

	i = 0;
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	if (!storage[i])
	{
		return (free(storage), NULL);
	}
	i++;
	new_storage = malloc(sizeof (char) * ft_strlen(storage) - i + 1);
	if (!new_storage)
		return (free(storage), NULL);
	j = 0;
	while (storage[i])
	{
		new_storage[j] = storage[i];
		j++;
		i++;
	}
	new_storage[j] = '\0';
	return (free(storage), new_storage);
}

int	test(char *line, char *storage, int i)
{
	while (storage[i] != '\n' && storage[i] != '\0')
	{
		line[i] = storage[i];
		i++;
	}
	return (i);
}

char	*new_line(char *storage)
{
	char	*line;
	int		i;

	i = 0;
	if (storage[0] == '\0')
		return (NULL);
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	if (storage[i] == '\n')
		i++;
	line = malloc(sizeof (char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	i = test(line, storage, i);
	if (storage[i] == '\n')
	{
		line[i] = storage[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*fill_storage(int fd, char *storage)
{
	char	*buffer;
	int		bits;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(storage);
		return (NULL);
	}
	buffer[0] = '\0';
	bits = 1;
	while (bits > 0 && !ft_strchr(buffer, '\n'))
	{
		bits = read(fd, buffer, BUFFER_SIZE);
		if (bits == -1)
		{
			return (free(storage), free(buffer), NULL);
		}
		buffer[bits] = '\0';
		storage = ft_strjoin(storage, buffer);
	}
	free(buffer);
	return (storage);
}

//(700) Storage Original = > 1001

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage || (storage && !ft_strchr(storage, '\n')))
		storage = fill_storage(fd, storage);
	if (!storage)
		return (NULL);
	line = new_line(storage);
	if (!line)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	storage = upd_storage(storage);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	char *ret;

  int fd = open("archivo.txt", O_RDONLY);
   ret = get_next_line(fd);

   printf("line = %s\n", ret);
 
    close(fd);
    return (0);
}
*/