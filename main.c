/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 07:57:36 by nikito            #+#    #+#             */
/*   Updated: 2022/06/13 20:19:42 by fnieves-         ###   ########.fr       */
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
	int	fd;
	char	*line;
	//int i = 10;

	//atexit(check);
	fd = open("test/texto2.txt", O_RDONLY);
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
