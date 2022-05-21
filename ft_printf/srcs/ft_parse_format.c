/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:34:51 by marmand           #+#    #+#             */
/*   Updated: 2021/10/13 10:26:15 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_params(t_format *params)
{
	params->width = -1;
	params->precision = -1;
	params->minus_f = 0;
	params->plus_f = 0;
	params->zero_f = 0;
	params->space_f = 0;
	params->hash_f = 0;
	params->value_type = 0;
}

int	ft_parse_flags(const char *format, t_format *params)
{
	int	i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '-')
			params->minus_f = 1;
		else if (format[i] == '+')
			params->plus_f = 1;
		else if (format[i] == '0')
			params->zero_f = 1;
		else if (format[i] == ' ')
			params->space_f = 1;
		else if (format[i] == '#')
			params->hash_f = 1;
		else
			return (i);
		i++;
	}
	return (i);
}

static int	ft_parse_star(va_list lst, const char **format, t_format *params)
{
	int	num;

	if (**format == '*')
	{
		num = va_arg(lst, int);
		if (num < 0)
		{
			if (*(*format - 1) == '.')
				num = -1;
			else
			{
				params->minus_f = 1;
				num *= -1;
			}
		}
		(*format)++;
	}
	else
	{
		num = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	return (num);
}

int	ft_parse_format(va_list lst, const char *format, t_format *params)
{
	const char	*start;

	start = format;
	if (*format == '%')
		format++;
	format += ft_parse_flags(format, params);
	params->width = ft_parse_star(lst, &format, params);
	if (*format == '.')
	{
		format++;
		params->precision = ft_parse_star(lst, &format, params);
	}
	params->value_type = *format;
	format++;
	if (params->minus_f || params->precision != -1)
		params->zero_f = 0;
	return ((int)(format - start));
}
