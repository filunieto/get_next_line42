/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonusmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 07:57:36 by nikito            #+#    #+#             */
/*   Updated: 2022/06/13 20:28:56 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

void	check(void)
{
	system("leaks a.out");
}

int main()
{
	int	fd, fd1;
	//int	 fd1, fd2;
	char	*line;
	// char	*line1;
	// char	*line2;
	//int i = 3;

	//atexit(check);
	fd = open("test/texto2.txt", O_RDONLY);
	fd1 = open("test/texto1.txt", O_RDONLY);
	// fd2 = open("test/texto2.txt", O_RDONLY);

	line = get_next_line(fd);
	if (!line)
		return (1);
	printf("%s", line);
	line = get_next_line(fd);
	if (!line)
		return (1);
	printf("%s", line);
	line = get_next_line(fd1);
	if (!line)
		return (1);
	printf("%s", line);
	line = get_next_line(fd1);
	if (!line)
		return (1);
	printf("%s", line);
	line = get_next_line(fd);
	if (!line)
		return (1);
	printf("%s", line);
	// printf("\nline1 :%s", line1);
	// printf("\nline2 :%s", line2);
	free(line);
	// free(line1);
	// free(line2);

	return (0);
}


	// while (1)
	// {
	// 	line = get_next_line(fd);
	// 	// line1 = get_next_line(fd1);
	// 	// line2 = get_next_line(fd2);
	// 	if (!line) //|| !line1 || !line2
	// 		break;
	// 	printf("%s", line);
	// 	// printf("\nline1 :%s", line1);
	// 	// printf("\nline2 :%s", line2);
	// 	free(line);
	// 	// free(line1);
	// 	// free(line2);
	// }