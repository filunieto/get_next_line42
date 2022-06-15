/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:59:49 by fnieves-          #+#    #+#             */
/*   Updated: 2022/06/15 12:23:23 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*get_next_line(int fd)
{
	static t_head_list head[NUMB_FILE_DESCR];
	char	*line;
	
	if (fd < 0 || BUF_SIZE < 1 || (read(fd, &line, 0) < 0) || fd > NUMB_FILE_DESCR) //ponemos condiciones que faltan
		return (NULL);
	line = NULL;
	/* Leemos el archivo y vamos extrayendo la infomacion e un buffer para anexionarla a la lista */
	ft_read_and_stash(fd , &(head[fd])); //verifica el parentesis 
	if (!head[fd].header) // Atencion
		return (NULL);
	/* 2. Ya tenemos la lista en la que en el ultimo nodo se encuentra un caracter \n*/
	ft_extract_line(&head[fd], &line);
	clean_stash(&head[fd]);
	//print_node(&head);
	//imprime_atope(line);
	if (!line[0])  // Atencion
	{
		//printf("\nHasta aqui leyo. Fin de texto\n");
		ft_delete_list(&head[fd]);
		free(line);
		return (NULL);
	}
	//printf("\nis malloc%i\n",gstatic);
	return (line);
}

void	ft_read_and_stash(int fd, t_head_list *head)
{
	char	*buff;
	int		readed;

	buff = (char *)malloc(sizeof(char) * (BUF_SIZE + 1));
	if (!buff)
		return ;
	//printf("abajo imprimo la lista antes de netrar en found_newline\n");
	//print_node(head);
	readed = 1;
	
	while (readed && !found_newline(head))
	{
		
		readed = read(fd, buff, BUF_SIZE);
		//1. anadir una condicion de haber llegado al final del texto y seguir con la lista vacia (texto vacio). Ponerla aqui o inmediatamnte fuera del while
		buff[readed] = 0;
		//printf("buff 1 , dentro de las condiciones %s\n", buff);
		head->list_elements = head->list_elements + 1;
		ft_add_to_stash(head, buff, readed);
	}
	if ((!readed && !head->header) || readed < 0)
	{
		printf("final de texto y la lista esta vacia. Texto en blanco\n");
		free (buff);
		return ;
	}
	//printf("buff 2 %s\n", buff);
	free(buff);
}

/* Add the buffer to the list in a new node and place it at the end */

void	ft_add_to_stash(t_head_list *head, char *buff, int readed) //podemos prescindir de int readed?
{
	t_node	*new_node;
	t_node *last;
	int	i;

	i = 0;
	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = (char *)malloc(sizeof(char) * (readed + 1));
	if (!new_node->content)
		return ;
	while (buff[i])
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = 0;
	new_node->char_readed = i;
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
	int	i;
	int len;
	
	if(!head->header || !head) //que condicion seria la correcta? head o header? Creo qu ela mas restrictiva es header (lista vacia). si esta vacia no hay nada que extraer
		return ;
	generate_line(head, line);
	// line = (char *)malloc(sizeof(char) * leng_line + 1 + 1); // \n y 0
	if (!*line)
		return ;
	temp = head->header;
	len = 0;
	while (temp)
	{
		i = 0;
		while (temp->content[i]) // paraa ahorar un renglon pueo poner la condicion incrementar len en la condicion con algo asi && ++len > 0
		{
			if (temp->content[i] == '\n')
			{
				(*line)[len++] = temp->content[i];
				break ;
			}
			(*line)[len++] = temp->content[i++];
		}
		temp->char_readed = i; //en el ultimo nodo hemos dejado el numero de caracteres hatsa \n (sin cntar con \n)
		temp = temp->next;
	}
	(*line)[len] = 0;
	//printf("linea a devolver:%s\n", *line);
	//hay que hacer un free de lline. Lo hace el propio program despues
}

/*
Esta funcion va a crear un nodo, clean_node,  en el que se anadira todo lo que queda en
el ultimo nodo de la lista , menos la parte que se ha impreso (todo lo anterior a \n)
en el ultimo nodo teemo sun campo que dice cuanto se ha impreso hasta carcter previo a \n
podemos empezar a copiar a partir de char_printed + 1
borramos la lista, y le agregamos este nuevo nodo, clean node.
*/
void	clean_stash(t_head_list *head)
{
	t_node	*clean_node;
	t_node	*last;
	int i;
	
	clean_node =(t_node *)malloc(sizeof(t_node));
	if (!clean_node || !head->header)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(head);
	i = 0;
	while (last->content[i + last->char_readed + 1]) //empieza por /n por eso le sumamos 1
	{
		//printf("cada char que queda despues de %c\n", last->content[i + last->char_readed]);
		i++;
	}
	//printf("size i de malloc del nodo donde se guarda lo que queda, sin nullterminated %i\n", i );
	clean_node->content = (char *)malloc(sizeof(char) * (i + 1)); //al haber hecho i++ ya tiene en cuenta el nullterminatedchar
	i = 0;
	while (last->content[i + last->char_readed + 1]) //empezamos a contar(no copiar) por siguiente char a  \n hasta final
	{
		clean_node->content[i] = last->content[i + last->char_readed + 1];
		i++;
	}
	clean_node->content[i] = 0;
	clean_node->char_readed = i; //caracteres en el nodo sin el nullterminated
	// printf(" clean node, numero char en string de los caacteres no impresos %i\n", clean_node->char_readed);
	// printf("string que queda en el clean_node: %s\n", clean_node->content);
	ft_delete_list(head);
	head->header = clean_node;
	head->list_elements = 1;
	// printf("\nabajo la lista que borrada y con el nuevo nodo\n");
	// print_node(head);
}

// Nota general:

// Si queremos modificar dato spasamos la direccion de memoria al dato.
// Si solo queremos leer o analizar pasamos el dato

