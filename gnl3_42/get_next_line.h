/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:50:40 by fnieves-          #+#    #+#             */
/*   Updated: 2022/06/13 22:43:08 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> //de auqi abajo borrar
//# include <string.h> //de auqi abajo borrar
# include <fcntl.h> //de auqi abajo borrar

#ifndef BUF_SIZE
# define BUF_SIZE 42
#endif

# define NUMB_FILE_DESCR 1024

typedef struct s_node
{
	char			*content;
	int				char_readed;
	struct s_node	*next;
}					t_node;

typedef struct s_head_list
{
	t_node	*header;
	int		element_list;
}			t_head_list;

char	*get_next_line(int fd);
void	ft_read_and_stash(int fd, t_head_list *head);
void	add_to_stash(t_head_list *head, char *buff, int readed);
void	clean_stash(t_head_list *head);
void	ft_extract_line(t_head_list *head, char **line);
int		found_newline(t_head_list *head);
t_node	*ft_lst_get_last(t_head_list *head);
void	generate_line(t_head_list *head, char **line);
void	free_stash(t_head_list *head);
int		ft_strlen(const char *str);

void	print_list(t_head_list *head);//de auqi abajo borrar
void imprime_atope(char	*s);//de auqi abajo borrar

#endif