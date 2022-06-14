/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:50:37 by fnieves-          #+#    #+#             */
/*   Updated: 2022/06/14 19:37:49 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_head_list	head;
	char				*line;

	if (fd < 0 || BUF_SIZE < 1 || fd > NUMB_FILE_DESCR || (read(fd, &line, BUF_SIZE) < 0))
		return (NULL);
	printf("hast aqui ok 0 \n");
	ft_read_and_stash(fd, &head);
	if (!head.header)
		return (NULL);
	printf("hast aqui ok 1 \n");
	ft_extract_line(&head, &line);
	printf("hast aqui ok 2 \n");
	ft_clean_stash(&head);
	printf("hast aqui ok 3 \n");

	if (!line[0])
	{
		free (line);
		ft_free_list(&head);
		return (NULL);
	}
	printf("hast aqui ok ultimo \n");
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

	while (readed && !ft_found_newline(head)) //no esta saliendo de este bucle
	{
		//printf("read and stash 0 \n");
		readed = read(fd, buff, BUF_SIZE);
		buff[readed] = 0;
		head->element_list = head->element_list + 1;
		ft_add_to_stash(head, buff, readed);
	}
	printf("read and stash 1 \n");
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
	//printf("ft_ad to stash 0 \n"); esto lo lee
	last_node = ft_lst_get_last(head);
	last_node->next = new_node;
}

void	ft_extract_line(t_head_list *head, char **line)
{
	int	len_line;
	t_node	*current;
	int	i;
	int	j;
	
	if(!head->header || !head)
		return ;
	ft_generate_line(head, line);
	if (!line)
		return ;
	current = head->header;
	j = 0;
	while (current)
	{
		i = 0;
		while (current->content[i])
		{
			if (current->content[i] == '\n')
			{
				*line[j++] = current->content[i];
				break;
			}
			*line[j++] = current->content[i++];
		}
		current = current->next;
	}
	*line[j] = 0;
}

void	ft_clean_stash(t_head_list *head)
{
	t_node	*last;
	t_node	*new_node;
	int	i;

	if (!head || !head->header)
		return ;
	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return ;
	last = ft_lst_get_last(head);
	new_node->content = (char *)malloc(sizeof(char) * (last->leng_content - last->position_nl)); //va incluido el 0
	if (!new_node->content)
		return ;
	i = 0;
	while (last->content[last->position_nl + 1 + i])
	{
		new_node->content[i] = last->content[last->position_nl + 1 + i];
		i++;
	}
	new_node->content[i] = 0;
	ft_free_list(head);
	head->header = new_node;
	head->element_list = 1;
}