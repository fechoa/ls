/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:17:45 by marmand           #+#    #+#             */
/*   Updated: 2022/04/12 19:40:09 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "flags.h"
# include "ft_ls.h"

int	bufferMustBe(int flags)
{
	if (CHECK_FLAG(flags, f_FLAG))
		return (0);
	return (1);
}

int	get_flags(int argc, char ** argv, int *scipped)
{
	int	i = 1;
	int	flags = 0;
	for (; i < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			for (int j = 1; argv[i][j]; ++j)
			{
				if (argv[i][j] == 'l')
					flags |= l_FLAG;
				else if (argv[i][j] == 'R')
					flags |= R_FLAG;
				else if (argv[i][j] == 'a')
					flags |= a_FLAG;
				else if (argv[i][j] == 'r')
					flags |= r_FLAG;
				else if (argv[i][j] == 't')
					flags |= t_FLAG;
				else if (argv[i][j] == 'u')
					flags |= u_FLAG;
				else if (argv[i][j] == 'f')
					flags |= f_FLAG;
				else if (argv[i][j] == 'g')
					flags |= g_FLAG;
				else if (argv[i][j] == 'd')
					flags |= d_FLAG;
				else
				{
					ft_putstr_fd("illegal flag -- ", 2);
					ft_putendl_fd(&argv[i][j], 2);
					ft_putendl_fd("usage: ls [-Rlartufgd] [file ...]", 2);
					exit(1);
				}
			}
		}
		else
			break ;
	}
	*scipped = i;
	return flags;
}

int	predicat(const char *file_name, int flags)
{
	if (!CHECK_FLAG(flags, a_FLAG))
	{
		if (file_name[0] == '.')
			return (0);
	}
	if (CHECK_FLAG(flags, d_FLAG))
	{
		if (!is_dir(file_name))
			return (0);
	}
	return (1);
}


