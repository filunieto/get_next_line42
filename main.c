/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 07:57:36 by nikito            #+#    #+#             */
/*   Updated: 2022/07/13 17:42:31 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void	check(void)
{
	system("leaks a.out");
}

int main()
{
	int	fd;
	char	*line;
	//int i = 10;

	//atexit(check);
	//fd = open("test/1-brouette.txt", O_RDONLY);
	fd = open("test/1-brouette.txt", O_RDONLY);
	//fd = open("test/9-linew.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s", line);
		free(line);
	}
	return (0);
}
