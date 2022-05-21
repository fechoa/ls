/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_vector.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 22:12:02 by marmand           #+#    #+#             */
/*   Updated: 2022/04/13 15:04:28 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_UTILS
# define VECTOR_UTILS

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct str_vector
{
	char **		_data;
	size_t		_capacity;
	size_t		_size;
} 				str_vector;

// for example strcmp
typedef int (*str_compare)(const char *, const char *, const char *);

// vector initialisation
void	str_vector_init(str_vector *v, long memory);

// to append str to env of v
int		str_vector_append(str_vector *v, char *str);

// free v->data and all strs
void	str_vector_clear(str_vector *v);

// sort vector with comparator compare (for example strcmp)
void	str_vector_sort(str_vector *v, str_compare compare, const char *dirname);

// reverse vector
void	str_vector_reverse(str_vector *v);

#endif
