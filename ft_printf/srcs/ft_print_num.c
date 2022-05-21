/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 01:30:56 by marmand           #+#    #+#             */
/*   Updated: 2021/10/13 16:50:45 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	ft_first_char_in_num(char *num, t_format *params)
{
	if (num[0] == '-')
		return ('-');
	if (params->plus_f)
		return ('+');
	if (params->space_f)
		return (' ');
	return (0);
}

int	ft_max(int n, ...)
{
	va_list	lst;
	int		max;
	int		tmp;

	va_start(lst, n);
	if (n)
	{
		max = va_arg(lst, int);
		n--;
	}
	while (n)
	{
		tmp = va_arg(lst, int);
		if (tmp > max)
			max = tmp;
		n--;
	}
	va_end(lst);
	return (max);
}

void	ft_strcat_nchar(char *str, char c, int n)
{
	if (n <= 0)
		return ;
	while (*str)
		str++;
	while (n)
	{
		*str = c;
		str++;
		n--;
	}
	*str = 0;
}

static	char	*ft_make_int_str(char *num, t_format *params, int num_len)
{
	char	*str;
	char	minus;

	minus = 0;
	str = (char *)malloc(sizeof(char) * (ft_max(3, num_len,
					params->precision, params->width) + 3));
	str[0] = ft_first_char_in_num(num, params);
	if (str[0] == '-')
		minus = 1;
	str[1] = 0;
	if (num[0] == '-')
		num++;
	if (params->zero_f)
		ft_strcat_nchar(str, '0', ft_max(2, params->precision, params->width - (
					params->plus_f | params->space_f | minus)) - num_len);
	else
		ft_strcat_nchar(str, '0', params->precision - num_len);
	ft_strlcat(str, num, ft_max(3, num_len,
			params->precision, params->width) + 3);
	if (num[0] == '0' && params->precision == 0)
		str[0] = 0;
	return (str);
}

int	ft_print_num(va_list lst, t_format *params)
{
	char	*str;
	char	*num;
	int		num_len;

	num = ft_itoa(va_arg(lst, int));
	num_len = (int)ft_strlen(num);
	if (num[0] == '-')
		num_len--;
	str = ft_make_int_str(num, params, num_len);
	num_len = ft_print_format(str, params);
	free(num);
	free(str);
	return (num_len);
}
