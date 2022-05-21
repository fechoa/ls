/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 00:26:41 by marmand           #+#    #+#             */
/*   Updated: 2021/10/13 12:15:25 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static int	ft_print_format_char(char ch, const t_format *params)
{
	char	fill;

	fill = ' ';
	if (params->zero_f)
		fill = '0';
	if (1 >= params->width)
	{
		ft_putchar_fd(ch, 1);
		return (1);
	}
	if (params->minus_f == 0)
	{
		ft_print_nchar(params->width - 1, fill);
		ft_putchar_fd(ch, 1);
	}
	else
	{
		ft_putchar_fd(ch, 1);
		ft_print_nchar(params->width - 1, ' ');
	}
	return (params->width);
}

int	ft_print_char(va_list lst, const t_format *params)
{
	char	ch;

	ch = (char) va_arg(lst, int);
	return (ft_print_format_char(ch, params));
}
