/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:57:03 by khbouych          #+#    #+#             */
/*   Updated: 2022/11/05 14:39:22 by khbouych         ###   ########.fr       */
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

static char	*ft_save(char *save)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	while (save[i] && save[i] != '\n')
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
	c = 0;
	while (save[i])
		s[c++] = save[i++];
	s[c] = '\0';
	free(save);
	return (s);
}

static char	*get_line(char *src, int fd)
{
	char	*buffer;
	int		ret;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	ret = 1;
	while (ret != 0 && !ft_strchr(src, '\n'))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[ret] = '\0';
		src = ft_strjoin(src, buffer);
	}
	free(buffer);
	return (src);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rec[10240];

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rec[fd] = get_line(rec[fd], fd);
	if (rec[fd] == NULL)
		return (NULL);
	line = ft_read_line(rec[fd]);
	rec[fd] = ft_save(rec[fd]);
	if (line[0] == '\0')
	{
		free(rec[fd]);
		free(line);
		return (NULL);
	}
	return (line);
}
// int main ()
// {
// 		int fd = open("temp.txt", O_RDONLY);
//         int fd2 =open("file.txt" , O_RDONLY);
// 		printf("fd : %d\n",fd);
// 		printf("fd2 : %d\n",fd2);
// 		printf("gnl | fd 1: %s",get_next_line(fd));
// 		printf("gnl | fd2 1: %s",get_next_line(fd2));
// 		printf("gnl | fd 2: %s",get_next_line(fd));
// 		printf("gnl | fd2 2: %s",get_next_line(fd2));
// 		printf("gnl | fd 3: %s",get_next_line(fd));
// 		printf("gnl | fd2 3: %s",get_next_line(fd2));
// 		printf("gnl | fd 4: %s",get_next_line(fd));
// 		printf("gnl | fd2 4: %s",get_next_line(fd2));
// 		close(fd);
// 		return (0);
// }