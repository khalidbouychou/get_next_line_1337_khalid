/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:26:35 by khbouych          #+#    #+#             */
/*   Updated: 2022/11/08 16:53:14 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include "get_next_line_bonus.h"

int	main(void)
{
	// int fd1 = open("f1.txt", O_RDONLY);
	// int fd2 = open("f2.txt", O_RDONLY);
	// int fd3 = open("f3.txt", O_RDONLY);
	int fd4 = open("f2.txt", O_RDONLY);
    char *line;

    line = get_next_line(fd4);
    while(line)
    {
        printf("%s", line);
        line = get_next_line(fd4);
    }
	// for (int i = 0; i < 4; i++)
	// {
		// printf("----------------fd1---------------------\n");
		// printf("fd1 --> %s\n", get_next_line(fd4));
		// printf("fd1 --> %s\n", get_next_line(fd4));
		// printf("fd1 --> %d\n", 0);
		// printf("-----------------fd2--------------------\n");
		// printf("fd2[%d] --> %s\n", i, get_next_line(1));
		// printf("fd2 --> %d\n", 1);
		// printf("----------------fd3---------------------\n");
		// printf("fd3[%d] --> %s\n", i, get_next_line(2));
		// printf("fd3 --> %d\n",2);
		// printf("----------------fd4---------------------\n");
		// printf("fd4[%d] --> %s\n", i, get_next_line(fd4));
		// printf("fd4 --> %d\n", fd4);
		// close(fd1);
		// close(fd2);
		// close(fd3);
		// close(fd4);
	// }
}