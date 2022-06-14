/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:37:02 by fnieves-          #+#    #+#             */
/*   Updated: 2022/06/14 19:17:33 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_clean_stash(t_head_list *head)
{
	t_node	*last;
	t_node	*new_node;
	int		i;

	if (!head || !head->header)
		return ;
	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return ;
	last = ft_lst_get_last(head);
	new_node->content = (char *)malloc(sizeof(char) * \
	(last->leng_content - last->position_nl));
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
