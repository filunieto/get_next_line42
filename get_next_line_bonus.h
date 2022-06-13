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

typedef struct s_list
{
	char			*content;
	int				char_readed;
	struct s_list	*next;
}t_list;


//crear un elemento . CCuando el header solo tiene un elento podriamos crear la estructura de aajo mas resumida >> no es importantesolo para informacion
typedef struct s_head_list
{
	t_list	*header;
	int		elementos_lista;
	int		fd_value;
}t_head_list;

char	*get_next_line(int fd);
void	ft_read_and_stash(int fd, t_head_list *head);
void	add_to_stash(t_head_list *head, char *buff, int readed);
void	clean_stash(t_head_list *head);
void	extract_line(t_head_list *head, char **line);

int		found_newline(t_head_list *head);
t_list	*ft_lst_get_last(t_head_list *head);
void	generate_line(t_head_list *head, char **line);
void	free_stash(t_head_list *head);
int		ft_strlen(const char *str);

void	print_list(t_head_list *head);
void imprime_atope(char	*s);

#endif