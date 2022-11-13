/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:57:03 by khbouych          #+#    #+#             */
/*   Updated: 2022/11/13 16:02:11 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_save_rest_of_line(char *save)
{
	int		i;
	int		j;
	char	*s_line;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	s_line = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!s_line)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		s_line[j++] = save[i++];
	s_line[j] = '\0';
	free(save);
	return (s_line);
}

static char	*ft_read_line_from_stash(char *stash)
{
	size_t	i;
	char	*line;

	if (stash == NULL)
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
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

static char	*ft_get_line_from_buffer(char *stash, int fd)
{
	char	*buffer;
	ssize_t	rdf;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	rdf = 1;
	while (rdf != 0 && !ft_strchr(stash, '\n'))
	{
		rdf = read(fd, buffer, BUFFER_SIZE);
		if (rdf == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[rdf] = '\0';
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
	stash[fd] = ft_get_line_from_buffer(stash[fd], fd);
	if (stash[fd] == NULL)
		return (NULL);
	line = ft_read_line_from_stash(stash[fd]);
	stash[fd] = ft_save_rest_of_line(stash[fd]);
	if (line[0] == '\0')
	{
		free(stash[fd]);
		free(line);
		return (NULL);
	}
	return (line);
}
