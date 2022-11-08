/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:57:03 by khbouych          #+#    #+#             */
/*   Updated: 2022/11/07 18:33:20 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_line(char *src)
{
	size_t	i;
	char	*str;

	i = 0;
	if (src == NULL)
		return (NULL);
	while (src[i] != '\0' && src[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && src[i] != '\n')
	{
		str[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

static char	*ft_set_on_stash(char *save)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	s = (char *)malloc(ft_strlen(save) - i + 1);
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		s[j++] = save[i++];
	s[j] = '\0';
	free(save);
	return (s);
}

static char	*ft_get_line(char *stash, int fd)
{
	char	*buffer;
	int		read_file;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	read_file = 1;
	while (read_file != 0 && !ft_strchr(stash, '\n'))
	{
		read_file = read(fd, buffer, BUFFER_SIZE);
		if (read_file == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[read_file] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[10240];

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_get_line(stash[fd], fd);
	if (stash[fd] == NULL)
		return (NULL);
	line = ft_read_line(stash[fd]);
	stash[fd] = ft_set_on_stash(stash[fd]);
	if (line[0] == '\0')
	{
		free(stash[fd]);
		free(line);
		return (NULL);
	}
	return (line);
}
