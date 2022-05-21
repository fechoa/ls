/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 03:35:15 by marmand           #+#    #+#             */
/*   Updated: 2021/10/13 15:44:40 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	ft_hexchar(unsigned int digit, char is_low)
{
	if (0 <= digit && digit <= 9)
		return (digit + '0');
	if (is_low)
		return ('a' + digit - 10);
	return ('A' + digit - 10);
}

int	ft_hexlen(unsigned int num)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	while (num)
	{
		num /= 16;
		len++;
	}
	return (len);
}

char	*ft_hextoa(unsigned int num, char is_low)
{
	char	*str;
	int		len;

	len = ft_hexlen(num);
	str = (char *) malloc(sizeof(char) * (len + 1));
	str[0] = '0';
	str[len] = 0;
	len--;
	while (len >= 0)
	{
		str[len] = ft_hexchar(num % 16, is_low);
		num /= 16;
		len--;
	}
	return (str);
}

int	ft_print_hex_without_va(unsigned int unum, t_format *params, char is_low)
{
	char	*str;
	char	*num;
	int		num_len;

	num = ft_hextoa(unum, is_low);
	num_len = (int)ft_strlen(num);
	str = (char *)malloc(sizeof(char) * (
				ft_max(2, num_len, params->precision) + 3));
	str[0] = 0;
	if (params->hash_f && is_low && unum)
		ft_strlcpy(str, "0x", 3);
	if (params->hash_f && !is_low && unum)
		ft_strlcpy(str, "0X", 3);
	ft_strcat_nchar(str, '0', params->precision - num_len);
	ft_strlcat(str, num, ft_max(2, num_len, params->precision) + 3);
	if (num[0] == '0' && params->precision == 0)
		str[0] = 0;
	num_len = ft_print_format(str, params);
	free(num);
	free(str);
	return (num_len);
}

int	ft_print_hex(va_list lst, t_format *params, char is_low)
{
	return (ft_print_hex_without_va(va_arg(lst, unsigned int),
			params, is_low));
}
