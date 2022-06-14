/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:50:37 by fnieves-          #+#    #+#             */
/*   Updated: 2022/06/14 13:57:52 by fnieves-         ###   ########.fr       */
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
	ft_clean_stash(&head);
	if (!line[0])
	{
		//free todo, stash y linea
		return (NULL);
	}
	return (line);
}

void	ft_read_and_stash(int fd, t_head_list *head)
{
	char	*buff;
	int		readed;
	
	buff = (char *)malloc(sizeof(char) * (BUF_SIZE + 1));
	if (!buff)
		return ;
	readed = 1;
	while (readed && !ft_found_newline(head))
	{
		readed = read(fd, buff, BUF_SIZE);
		buff[readed] = 0;
		head->element_list = head->element_list + 1;
		ft_add_to_stash(head, buff, readed);
	}
	if (!readed && !head->element_list)
	{
		free(buff);
		return ;
	}
	free(buff);
}

void	ft_add_to_stash(t_head_list *head, char *buff, int readed) //anadir el numero de caracteres impresos en el nodo. en ese caso hay que poner otra funcion
{
	t_node	*new_node;
	t_node	*last_node;
	int		i;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = (char *)malloc(sizeof(char) * (readed + 1));
	if (!new_node->content)
		return ;
	i = 0;
	while (buff[i])
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = 0;
	if (!head->header)
	{
		head->header = new_node;
		return ;
	}
	last_node = ft_lst_get_last(head);
	last_node->next = new_node;
}

void	ft_extract_line(t_head_list *head, char **line)
{
	
}

void	ft_clean_stash(t_head_list *head)
{
	
}