/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:50:37 by fnieves-          #+#    #+#             */
/*   Updated: 2022/06/13 22:43:52 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_head_list	head;
	char				*line;

	if (fd < 0 || BUF_SIZE < 1 || fd > NUMB_FILE_DESCR || (read(fd, &line, BUF_SIZE) < 0))
		return (NULL);
	ft_read_and_stash(fd, &head);
	if (!head.header)
		return (NULL);
	ft_extract_line(&head, &line);
}