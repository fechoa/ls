/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 23:22:27 by marmand           #+#    #+#             */
/*   Updated: 2021/10/13 12:33:35 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_one(va_list lst, t_format *params)
{
	if (params->value_type == '%')
		return (ft_print_percent(params));
	else if (params->value_type == 'c')
		return (ft_print_char(lst, params));
	else if (params->value_type == 's')
		return (ft_print_str(lst, params));
	else if (params->value_type == 'p')
		return (ft_print_ptr(lst, params));
	else if (params->value_type == 'd')
		return (ft_print_num(lst, params));
	else if (params->value_type == 'i')
		return (ft_print_num(lst, params));
	else if (params->value_type == 'u')
		return (ft_print_unsigned(lst, params));
	else if (params->value_type == 'x')
		return (ft_print_hex(lst, params, 1));
	else if (params->value_type == 'X')
		return (ft_print_hex(lst, params, 0));
	return (0);
}

static void	ft_print_nchar(int n, char c)
{
	if (n < 0)
		return ;
	while (n)
	{
		ft_putchar_fd(c, 1);
		n--;
	}
}

int	ft_print_format(const char *str, const t_format *params)
{
	int		len;
	char	fill;

	fill = ' ';
	if (params->zero_f)
		fill = '0';
	len = (int) ft_strlen(str);
	if (len >= params->width)
	{
		ft_putstr_fd((char *)str, 1);
		return (len);
	}
	if (params->minus_f == 0)
	{
		ft_print_nchar(params->width - len, fill);
		ft_putstr_fd((char *)str, 1);
	}
	else
	{
		ft_putstr_fd((char *)str, 1);
		ft_print_nchar(params->width - len, ' ');
	}
	return (params->width);
}
