/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:29:31 by fnieves-          #+#    #+#             */
/*   Updated: 2022/06/14 23:25:18 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

 /* Parsing last element of the list to find the \n */
int	found_newline(t_head_list *head)
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
		return (1);
	return (0);
}

/* Return the last element of the list */

t_node	*ft_lst_get_last(t_head_list *head)
{	
	t_node	*last;

	if(!head)
		return (NULL);
	last = head->header;
	while (last->next)
		last = last->next;
	return (last);
}

/* Calculates number of char in current line, including \n if found
and allocates memory */

void	generate_line(t_head_list *head, char **line)
{
	int	i;
	int len;
	t_node	*temp;
	
	len = 0;
	temp = head->header;
	while (temp)
	{
		i = 0;
		while (temp->content[i] && temp->content[i] != '\n')
		{
			i++;
			len++;
		}
		temp = temp->next;
	}
	*line = (char *)malloc(sizeof(char) * (len + 1));

}

void	ft_delete_list(t_head_list *head) 
{
	t_node *current;
	t_node *next;
	
	if(!head->header)
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
	// printf("\n lista que ha quedado desopues de vaciar\n");
	// print_node(head);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	print_node(t_head_list *head)
{
	t_node *stash;

	if (!head || !head->header)
	{
		printf("lista vacia\n");
		return ;
	}
	printf("===comienzo de lista===\n");
	stash = head->header;
	while (stash->next)
	{
		printf("content: %s|| char en nodo: %i \n", stash->content, stash->char_readed);
		stash = stash->next;
	}
	printf("ultimo content: %s|| char en nodo: %i \n || Elementos en la lista %i\n", stash->content, stash->char_readed, head->list_elements);
	printf("===fin de lista===\n");
}

void imprime_atope(char	*s)
{
	printf("===string a impimri con nullterminated ===\n");
	int i = 0;
	while (s[i])
	{
		printf("%c",s[i]);
		i++;	
	}
	if (s[i] == 0)
		printf("\n===caracteres impresos %i ===\n", i + 1);
	else 
		printf("\n===ultimo char impresos no es 0 %i ===\n", i + 1);	
}
