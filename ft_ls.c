/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:27:49 by marmand           #+#    #+#             */
/*   Updated: 2022/04/13 15:22:15 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/types.h>
# include <stdlib.h>
# include <dirent.h>
# include <stdio.h>
#include <sys/stat.h>
# include <stddef.h>
# include "str_vector.h"
# include "flags.h"
# include "ft_ls.h"

void	ls(const char *dirname, int flags)
{
	str_vector	sv;
	str_vector_init(&sv, 0);
	DIR *	dir = opendir(dirname);
	if (dir == NULL)
	{
		perror("");
		return ;
	}
	struct dirent	*file_info;
	while ((file_info = readdir(dir)) != NULL)
	{
		if (predicat(file_info->d_name, flags))
			str_vector_append(&sv, ft_strdup(file_info->d_name));
	}
	closedir(dir);
	change_to_flags(&sv, flags, dirname);
	if (CHECK_FLAG(flags, l_FLAG | g_FLAG))
	{
		unsigned long long _total = 0;
		for (unsigned i = 0; i < sv._size; ++i)
		{
			char *tmp = ft_strjoin(dirname, sv._data[i]);
			struct stat	file_stat;
			lstat(tmp, &file_stat);
			_total += file_stat.st_blocks;
			free(tmp);
		}
		ft_printf("\ntotal %d", _total);
	}
	for (unsigned i = 0; i < sv._size; ++i)
	{
		char *tmp = ft_strjoin(dirname, sv._data[i]);
		print_file_info(tmp, flags, sv._data[i]);
		free(tmp);
	}
	if (CHECK_FLAG(flags, R_FLAG))
	{
		for (unsigned i = 0; i < sv._size; ++i)
		{
			if (ft_strncmp(sv._data[i], ".", 2) == 0)
				continue;
			if (ft_strncmp(sv._data[i], "..", 3) == 0)
				continue;
			char *tmp = ft_strjoin(dirname, sv._data[i]);
			str_append_slash(&tmp);
			if (is_dir(tmp))
			{
				ft_printf("\n\n%s:", tmp);
				if (!CHECK_FLAG(flags, l_FLAG))
					ft_printf("\n");
				ls(tmp, flags);
			}
			free(tmp);
		}
	}
	str_vector_clear(&sv);
}

int main(int argc, char *argv[])
{
	int	scipped;
	int flags = get_flags(argc, argv, &scipped);
	if (argc - scipped == 1)
	{
		if (is_notvalid_dir(argv[scipped]))
		{
			perror(argv[scipped]);
			exit(1);
		}
		else
		{
			char *tmp = ft_strdup(argv[scipped]);
			str_append_slash(&tmp);
			ls(tmp, flags);
			free(tmp);
		}
		return (0);
	}
	for (int i = scipped; i < argc; ++i)
	{
		if (is_notvalid_dir(argv[i]))
			perror(argv[i]);
		else
		{
			ft_printf("%s:\n", argv[i]);
			char *tmp = ft_strdup(argv[i]);
			str_append_slash(&tmp);
			ls(tmp, flags);
			free(tmp);
		}
		if (i != argc -1)
			ft_printf("\n");
		ft_printf("\n");
	}
	if (scipped == argc)
	{
		ls("./", flags);
		ft_printf("\n");
	}
	return (0);
}
