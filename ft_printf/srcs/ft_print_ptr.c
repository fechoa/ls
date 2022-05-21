/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 01:08:20 by marmand           #+#    #+#             */
/*   Updated: 2021/10/13 17:17:31 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

union u_ptr
{
	void	*ptr;
	struct
	{
		unsigned int	u1;
		unsigned int	u2;
	}	s_uints;
};

static char	*ft_make_hex_res(union u_ptr ptr, t_format *params,
				char **num1, char **num2)
{
	char	*res;
	int		num_len;

	*num1 = ft_hextoa(ptr.s_uints.u1, 1);
	*num2 = ft_hextoa(ptr.s_uints.u2, 1);
	num_len = (int)(ft_strlen(*num1)) + 2 + params->space_f;
	if (ptr.s_uints.u2 != 0)
		num_len = (int)(ft_strlen(*num2)) + 10 + params->space_f;
	res = (char *)malloc(sizeof(char) * (num_len + 1));
	if (params->space_f)
		ft_strlcpy(res, " 0x", num_len + 1);
	else
		ft_strlcpy(res, "0x", num_len + 1);
	if (ptr.s_uints.u2 == 0)
	{
		ft_strlcat(res, *num1, num_len + 1);
		return (res);
	}
	ft_strlcat(res, *num2, num_len + 1);
	ft_strlcat(res, "00000000", 1 + num_len - ft_strlen(*num1));
	ft_strlcat(res, *num1, num_len + 1);
	return (res);
}

int	ft_print_ptr(va_list lst, t_format *params)
{
	union u_ptr	ptr;
	int			char_count;
	char		*res;
	char		*num1;
	char		*num2;

	ptr.ptr = va_arg(lst, void *);
	res = ft_make_hex_res(ptr, params, &num1, &num2);
	char_count = ft_print_format(res, params);
	free(res);
	free(num1);
	free(num2);
	return (char_count);
}
