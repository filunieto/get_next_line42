/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:50:35 by fnieves-          #+#    #+#             */
/*   Updated: 2022/06/14 19:15:25 by fnieves-         ###   ########.fr       */
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
	last->position_nl = -1;
	i = 0;
	while (last->content[i])
		i++;
	last->leng_content = i; //longitud del string content (cuantas letras tiene)
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
	{
		last->position_nl = i; //la posicion en la que hemos encontrado \n. puede ser de 0 a buffer
		return (1);
	}
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

void	ft_generate_line(t_head_list *head, char **line)
{
	int	len_line;
	int	i;
	t_node	*current;

	current = head->header;
	len_line = 0;
	while (current)
	{
		i = 0;
		while (current->content[i] && current->content[i] != '\n')
		{
			len_line++;	
			i++;
		}
		current = current->next;
	}
	*line = (char *)malloc(sizeof(char) * len_line + 1);
	if (!*line) //atcnion aqui
		return ;
	//meter aqui la funcion para calcular los valores de las listas y comparar  con len_line
	// printf("valos de len line: %i\n", len_line);
	// print_list_numbers(head);
}

void	ft_free_list(t_head_list *head)
{
	t_node	*next;
	t_node	*del_node;
	
	if (!head || !head->header)
		return ;
	del_node = head->header;
	while (del_node)
	{
		next = del_node->next;
		free(del_node->content);
		del_node->next = NULL;
		free(del_node);
		del_node = next;
	}
	head->header = NULL;
}

void	print_list_numbers(t_head_list *head)
{
	t_node	*current;
	int total_len_content = 0;
	//int total_len_gnline = 0;

	if (!head || !head->header)
	{
		printf("no hay lista\n");
		return ;
	}
	current = head->header;
	while (current)
	{
		if (current->position_nl >= 0)
			total_len_content = total_len_content + current->position_nl;
		else
			total_len_content = total_len_content + current->leng_content;
		current = current->next;
	}
	printf("longitud de todos los strings de nodo + posicion de \\n de la lista: %i", total_len_content);
}