/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:26:13 by marmand           #+#    #+#             */
/*   Updated: 2021/10/13 14:45:47 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdarg.h>

typedef struct s_format
{
	int				width;
	int				precision;
	unsigned char	minus_f;
	unsigned char	plus_f;
	unsigned char	zero_f;
	unsigned char	space_f;
	unsigned char	hash_f;
	unsigned char	value_type;
}	t_format;

int		ft_printf(const char *format, ...);
int		ft_parse_format(va_list lst, const char *format, t_format *params);
int		ft_print_one(va_list lst, t_format *params);
int		ft_print_format(const char *str, const t_format *params);
int		ft_parse_flags(const char *format, t_format *params);
int		ft_print_percent(const t_format *params);
int		ft_print_char(va_list lst, const t_format *params);
int		ft_print_str(va_list lst, const t_format *params);
int		ft_print_ptr(va_list lst, t_format *params);
int		ft_print_num(va_list lst, t_format *params);
int		ft_print_unsigned(va_list lst, t_format *params);
int		ft_print_hex(va_list lst, t_format *params, char is_low);
int		ft_print_hex_without_va(unsigned int unum,
			t_format *params, char is_low);
void	ft_strcat_nchar(char *str, char c, int n);
void	ft_init_params(t_format *params);
int		ft_max(int n, ...);
int		ft_hexlen(unsigned int num);
char	*ft_hextoa(unsigned int num, char is_low);

#endif