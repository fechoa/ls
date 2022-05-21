/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 03:10:51 by marmand           #+#    #+#             */
/*   Updated: 2021/10/13 12:31:50 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_numlen(unsigned int num)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static char	*ft_utoa(unsigned int num)
{
	int		len;
	char	*res;

	len = ft_numlen(num);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len] = 0;
	len--;
	while (len >= 0)
	{
		res[len] = num % 10 + '0';
		num /= 10;
		len--;
	}
	return (res);
}

int	ft_print_unsigned(va_list lst, t_format *params)
{
	char	*num;
	char	*str;
	int		num_len;

	num = ft_utoa(va_arg(lst, unsigned int));
	num_len = (int)ft_strlen(num);
	str = (char *)malloc(sizeof(char) * (
				ft_max(2, num_len, params->precision) + 2));
	str[0] = 0;
	ft_strcat_nchar(str, '0', params->precision - num_len);
	ft_strlcat(str, num, ft_max(2, num_len, params->precision) + 2);
	if (num[0] == '0' && params->precision == 0)
		str[0] = 0;
	num_len = ft_print_format(str, params);
	free(num);
	free(str);
	return (num_len);
}
