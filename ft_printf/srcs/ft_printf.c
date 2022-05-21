/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:26:15 by marmand           #+#    #+#             */
/*   Updated: 2021/10/13 05:09:56 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	t_format	params;
	va_list		lst;
	int			char_count;

	char_count = 0;
	ft_init_params(&params);
	va_start(lst, format);
	while (*format)
	{
		if (*format == '%')
		{
			format += ft_parse_format(lst, format, &params);
			char_count += ft_print_one(lst, &params);
			ft_init_params(&params);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			char_count++;
			format++;
		}
	}
	va_end(lst);
	return (char_count);
}
