#include "get_next_line.h"

char	*update_storage(char *storage)
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

char	*extract_line(char *storage)
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
	int		num_bits;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(storage);
		return (NULL);
	}
	buffer[0] = '\0';
	num_bits = 1;
	while (num_bits > 0 && !ft_strchr(buffer, '\n'))
	{
		num_bits = read(fd, buffer, BUFFER_SIZE);
		if (num_bits == -1)
		{
			return (free(storage), free(buffer), NULL);
		}
		buffer[num_bits] = '\0';
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
	line = extract_line(storage);
	if (!line)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	storage = update_storage(storage);
	return (line);
}

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