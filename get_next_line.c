/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:53:19 by khbouych          #+#    #+#             */
/*   Updated: 2022/11/08 17:09:50 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (stash == NULL)
		return (NULL);
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_set_on_stash(char *save)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (save[i] != 0 && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
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

	buffer = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
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
	static char	*stash;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_get_line(stash, fd);
	if (stash == NULL)
		return (NULL);
	line = ft_read_line(stash);
	stash = ft_set_on_stash(stash);
	if (line[0] == '\0')
	{
		free(stash);
		free(line);
		return (NULL);
	}
	return (line);
}
