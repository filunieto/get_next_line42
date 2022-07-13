/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:29:31 by fnieves-          #+#    #+#             */
/*   Updated: 2022/07/13 18:05:13 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Parsing last element of the list to find the \n */

int	found_newline(t_head_list *head)
{
	t_node	*last;
	int		i;

	if (!head->header)
		return (0);
	last = ft_lst_get_last(head);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		return (1);
	return (0);
}

/* Return the last element of the list */

t_node	*ft_lst_get_last(t_head_list *head)
{	
	t_node	*last;

	if (!head)
		return (NULL);
	last = head->header;
	while (last->next)
		last = last->next;
	return (last);
}

/* Calculates number of char in current line, including \n if found
and allocates memory, returnigthie malloc of the line */

void	generate_line(t_head_list *head, char **line)
{
	int		i;
	int		len;
	t_node	*temp;

	len = 0;
	temp = head->header;
	while (temp)
	{
		i = 0;
		while (temp->content[i])
		{
			if (temp->content[i] == '\n')
			{
				len++;
				break ;
			}
			i++;
			len++;
		}
		temp = temp->next;
	}
	*line = (char *)malloc(sizeof(char) * (len + 1));
	if (*line == NULL)
		return ;
}

void	ft_delete_list(t_head_list *head)
{
	t_node	*current;
	t_node	*next;

	if (!head->header)
		return ;
	current = head->header;
	while (current)
	{
		free(current->content);
		next = current->next;
		free (current);
		current = next;
	}
	head->header = NULL;
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}
