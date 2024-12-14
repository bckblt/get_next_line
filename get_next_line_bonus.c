/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakarabu <bakarabu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:40:45 by bakarabu          #+#    #+#             */
/*   Updated: 2024/12/07 02:14:20 by bakarabu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*del(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update(char *str)
{
	char	*next_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free (str);
		return (NULL);
	}
	next_line = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!next_line)
		return (NULL);
	i++;
	while (str[i + j])
	{
		next_line[j] = str[i + j];
		j++;
	}
	next_line[j] = '\0';
	free (str);
	return (next_line);
}

static char	*ft_read(int fd, char *str)
{
	char	*buff;
	int		a;

	a = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!chknl(str) && a != 0)
	{
		a = read(fd, buff, BUFFER_SIZE);
		if (a == -1)
		{
			free (str);
			free (buff);
			return (NULL);
		}
		buff[a] = '\0';
		str = ft_strjoin(str, buff);
	}
	free (buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = ft_read (fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = del(str[fd]);
	str[fd] = update(str[fd]);
	return (line);
}
