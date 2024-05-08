/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrijime <adrijime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:36:15 by adrijime          #+#    #+#             */
/*   Updated: 2024/05/08 20:38:28 by adrijime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_free(char *str)
{
	free(str);
	return (NULL);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*ptr;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (str1 == NULL)
	{
		str1 = malloc(sizeof(char) * 1);
		if (!str1)
			return (NULL);
		str1[0] = '\0';
	}
	ptr = malloc(sizeof(char) * ((ft_strlen(str1) + ft_strlen(str2)) + 1));
	if (ptr == NULL)
		return (ft_free(str1));
	while (str1[++i])
		ptr[i] = str1[i];
	while (str2[++j])
		ptr[i + j] = str2[j];
	ptr[i + j] = '\0';
	free (str1);
	return (ptr);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	c = (unsigned char) c;
	if (c == '\0')
		return (&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (0);
}
