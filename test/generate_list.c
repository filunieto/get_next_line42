# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> //de auqi abajo borrar
//# include <string.h> //de auqi abajo borrar
# include <fcntl.h> //de auqi abajo borrar
#include <string.h>

#ifndef BUF_SIZE
# define BUF_SIZE 10
#endif

# define NUMB_FILE_DESCR 1024

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}t_list;

typedef struct s_head_list
{
	t_list 	*header;
}t_head_list;

void	print_list(t_head_list *head);
void	ft_add_to_stash(t_head_list *head, char *buff);
t_list	*ft_lst_get_last(t_head_list *head);
int	found_newline(t_head_list *head);
int	ft_strlen(const char *str);
void	ft_read_and_stash(int fd, t_head_list *head);


int main(void)
{
	int fd;
	static t_head_list head; //reservas el espacio y se hace NULL (lista vacia). Si declaramos solo *head: se reserva un puntero que sera nulo (lista que no existe)

	fd = open("texto.txt", O_RDONLY);
	if (!fd)
	{
		printf("Error de apartura \n ");
		return (1);
	}
	ft_read_and_stash(fd, &head);
	return (0);
}

void	ft_read_and_stash(int fd, t_head_list *head)
{
	char	*buff;
	int		readed;

	buff = (char *)malloc(sizeof(char) * (BUF_SIZE + 1));
	if (!buff)
		return ;
	while ((readed = read(fd, buff, BUF_SIZE)) && !found_newline(head))
	{
		//1. anadir una condicion de haber llegado al final del texto y seguir con la lista vacia (texto vacio). Ponerla aqui o inmediatamnte fuera del while
		buff[readed] = 0;
		ft_add_to_stash(head, buff);
	}
	if (readed == 0 && !head->header)
	{
		printf("final de texto y la lista esta vacia. Texto en blanco\n");
		return ;
	}
	if (found_newline(head))
		printf("hemos encontardo un salto de liena\n");
	print_list(head);
}


void	ft_add_to_stash(t_head_list *head, char *buff) //podemos prescindir de int readed?
{
	t_list	*new_node;
	t_list *last;
	int	i;
	
	i = 0;
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = (char *)malloc(sizeof(char) * (ft_strlen(buff) + 1));
	if (!new_node->content)
		return ;
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
	// if (!last)
	// {
	// 	//debo añadir un free al malloc?
	// 	return ;
	// }
	last = ft_lst_get_last(head);
	last->next = new_node;
}

int	found_newline(t_head_list *head)
{
	t_list	*last;
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

t_list	*ft_lst_get_last(t_head_list *head)
{	
	t_list	*last;

	if(!head)
		return (NULL);
	last = head->header;
	while (last->next)
		last = last->next;
	return (last);
}

void	print_list(t_head_list *head)
{
	t_list *stash;

	if (!head)
	{
		printf("no hay stash\n");
		return ;
	}
	printf("===abajo empezamos a imprimir la lista===\n");
	stash = head->header;
	while (stash->next)
	{
		printf("%s\n", stash->content);
		stash = stash->next;
	}
	printf("===todos los elementos impresos===\n");
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