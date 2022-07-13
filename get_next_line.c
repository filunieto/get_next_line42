/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:59:49 by fnieves-          #+#    #+#             */
/*   Updated: 2022/07/13 18:04:57 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_head_list	head;
	char				*line;

	if (fd < 0 || BUFFER_SIZE < 1 || (read(fd, &line, 0) < 0) \
		|| fd > NUMB_FILE_DESCR)
		return (NULL);
	line = NULL;
	ft_read_and_stash(fd, &head);
	if (!head.header)
		return (NULL);
	ft_extract_line(&head, &line);
	clean_stash(&head);
	if (!line[0])
	{
		ft_delete_list(&head);
		free(line);
		return (NULL);
	}
	return (line);
}

/* It reads the file while it does not find \n, 
 and calls the function to create a new node with the read buffer. 
It has to read the file at least once. */

void	ft_read_and_stash(int fd, t_head_list *head)
{
	char	*buff;
	int		readed;

	readed = 1;
	while (readed && !found_newline(head))
	{
		buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buff)
			return ;
		readed = read(fd, buff, BUFFER_SIZE);
		if ((!readed && !head->header) || readed < 0)
		{
			free (buff);
			return ;
		}
		buff[readed] = '\0';
		ft_add_to_stash(head, buff, readed);
		free(buff);
	}
}

/* Add the buffer to the list in a new node and place it at the end */

void	ft_add_to_stash(t_head_list *head, char *buff, int readed)
{
	t_node	*new_node;
	t_node	*last;
	int		i;

	i = 0;
	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = (char *)malloc(sizeof(char) * (readed + 1));
	if (!new_node->content)
		return ;
	while (buff[i] && i < readed)
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (!head->header)
	{
		head->header = new_node;
		return ;
	}
	last = ft_lst_get_last(head);
	last->next = new_node;
}

/* Extracts all characters before \n
 in the stash, move to another var for printing
 and leaves the rest*/

void	ft_extract_line(t_head_list *head, char **line)
{
	t_node	*temp;
	int		i;
	int		len;

	if (!head->header || !head)
		return ;
	generate_line(head, line);
	temp = head->header;
	len = 0;
	while (temp)
	{
		i = 0;
		while (temp->content[i])
		{
			if (temp->content[i] == '\n')
			{
				(*line)[len++] = temp->content[i];
				break ;
			}
			(*line)[len++] = temp->content[i++];
		}
		temp = temp->next;
	}
	(*line)[len] = 0;
}

/* Creates  clean node, in which is stored what has not been returned
in the line immediately after /n, deletes all previous items
in the list, and at the end adds the clean node */

void	clean_stash(t_head_list *head)
{
	t_node	*clean_node;
	t_node	*last;
	int		i;
	int		j;

	clean_node = (t_node *)malloc(sizeof(t_node));
	if (!clean_node || !head->header)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(head);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	clean_node->content = (char *)malloc(sizeof(char) * \
						((ft_strlen(last->content) - i) + 1));
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = 0;
	ft_delete_list(head);
	head->header = clean_node;
}
