/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 00:30:28 by marmand           #+#    #+#             */
/*   Updated: 2021/10/14 16:17:49 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(va_list lst, const t_format *params)
{
	char	*str;
	int		chars_count;

	str = va_arg(lst, char *);
	if (str == 0)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(str);
	if ((int) ft_strlen(str) >= params->precision && params->precision >= 0)
		str[params->precision] = 0;
	chars_count = ft_print_format(str, params);
	free(str);
	return (chars_count);
}
