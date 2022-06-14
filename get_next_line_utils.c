/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:50:35 by fnieves-          #+#    #+#             */
/*   Updated: 2022/06/14 13:51:27 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_found_newline(t_head_list *head)
{
	t_node	*last;
	int	i;
	
	if (!head->header)
		return (0);
	last = ft_lst_get_last(head);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
	{
		last->char_readed = i;
		return (1);
	}
	last->char_readed = i;
	return (0);
}

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

