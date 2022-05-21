/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:36:16 by marmand           #+#    #+#             */
/*   Updated: 2022/04/13 15:04:51 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

# include "ft_printf/srcs/ft_printf.h"
# include "flags.h"
# include "str_vector.h"

int		is_dir(const char *file_name);
void	print_file_info(const char *file_path, int flags, const char *file_name);
void	change_to_flags(str_vector * sv, int flags, const char *dirname);
void	str_append_slash(char **str);
int		is_notvalid_dir(const char *file_path);

#endif // FT_LS