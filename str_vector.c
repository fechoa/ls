/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:54:14 by gkelsie           #+#    #+#             */
/*   Updated: 2022/04/13 15:06:27 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_vector.h"
#include "ft_printf/srcs/ft_printf.h"

void	str_vector_init(str_vector *v, long memory)
{
	v->_capacity = 0;
	v->_size = 0;
	v->_data = NULL;
	if (memory)
	{
		v->_data = (char **) malloc(sizeof(char *) * memory);
		if (v->_data == NULL)
			perror("Initialization was failed\n");
		v->_capacity = memory;
		v->_size = 0;
	}
}

int	str_vector_append(str_vector *v, char *str)
{
	if (v->_size == v->_capacity)
	{
		char ** tmp = malloc(sizeof(char *) * (v->_size * 2 + 1));
		if (tmp == NULL)
			return (-1);
		for (unsigned i = 0; i < v->_size; i++)
			tmp[i] = v->_data[i];
		free(v->_data);
		v->_data = tmp;
		v->_capacity = v->_size * 2 + 1;
	}
	v->_data[v->_size] = str;
	v->_size++;
	return (0);
}

void	str_vector_clear(str_vector *v)
{
	for (unsigned i = 0; i < v->_size; i++)
		free(v->_data[i]);
	free(v->_data);
	v->_data = 0;
	v->_size = 0;
	v->_capacity = 0;
}

void	str_vector_sort(str_vector *v, str_compare compare, const char *dirname)
{
	if (v->_size <= 1)
		return ;
	for (unsigned i = 0; i < v->_size - 1; i++)
	{ 
		for (unsigned j = 0; j < v->_size - i - 1; j++)
		{  
			if (compare(v->_data[j], v->_data[j + 1], dirname))
			{
				char * tmp = v->_data[j];
				v->_data[j] = v->_data[j + 1] ;
				v->_data[j + 1] = tmp; 
			}
		}
	}
}


void	str_vector_reverse(str_vector *v)
{
    for (unsigned i = 0; i < v->_size / 2; i++)
    {
        char *tmp = v->_data[i];
        v->_data[i] = v->_data[v->_size - i - 1];
        v->_data[v->_size - i - 1] = tmp;
    }
}
