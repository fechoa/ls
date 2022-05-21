/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:52:44 by marmand           #+#    #+#             */
/*   Updated: 2022/04/13 15:09:25 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/stat.h>
#include <unistd.h>
#include "flags.h"
#include "ft_ls.h"
#include "str_vector.h"
#include <sys/xattr.h>
#include <time.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/acl.h>

int	is_dir(const char *file_name)
{
	struct stat	tmp;
	
	if ((lstat(file_name, &tmp) == 0 && S_ISDIR(tmp.st_mode)))
		return (1);
	return (0);
}

void	print_file_info(const char *file_path, int flags, const char *file_name)
{
	if (CHECK_FLAG(flags, l_FLAG))
	{
		struct stat	file_info;
		if (lstat(file_path, &file_info) < 0)
		{
			perror("");
			return ;
		}
		char **date;
		if (CHECK_FLAG(flags, u_FLAG))
			date = ft_split(ctime(&file_info.st_atime), ' ');
		else
			date = ft_split(ctime(&file_info.st_mtime), ' ');

		struct passwd* user = getpwuid(file_info.st_uid);

		char buffer[14];
		ft_bzero(buffer, 14);
	
		buffer[0] = '\n';
		
		if (S_ISDIR(file_info.st_mode))
			buffer[1] = 'd';
		else if (S_ISLNK(file_info.st_mode))
			buffer[1] = 'l';
		else if (S_ISCHR(file_info.st_mode))
			buffer[1] = 'c';
		else if (S_ISBLK(file_info.st_mode))
			buffer[1] = 'b';
		else if (S_ISFIFO(file_info.st_mode))
			buffer[1] = 'p';
		else
			buffer[1] = '-';

		buffer[2] = ((file_info.st_mode & S_IRUSR)) ? 'r' : '-';
		buffer[3] = ((file_info.st_mode & S_IWUSR)) ? 'w' : '-';
		buffer[4] = ((file_info.st_mode & S_IXUSR)) ? 'x' : '-';
		buffer[5] = ((file_info.st_mode & S_IRGRP)) ? 'r' : '-';
		buffer[6] = ((file_info.st_mode & S_IWGRP)) ? 'w' : '-';
		buffer[7] = ((file_info.st_mode & S_IXGRP)) ? 'x' : '-';
		buffer[8] = ((file_info.st_mode & S_IROTH)) ? 'r' : '-';
		buffer[9] = ((file_info.st_mode & S_IWOTH)) ? 'w' : '-';
		buffer[10] = ((file_info.st_mode & S_IXOTH)) ? 'x' : '-';

		ssize_t xattr = 0;
		acl_t acl = NULL;
		acl_entry_t	dummy;
		const char *linkFileName = file_path;
		acl = acl_get_link_np(linkFileName, ACL_TYPE_EXTENDED);
		if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
		{
			acl_free(acl);
			acl = NULL;
		}
		xattr = listxattr(linkFileName, NULL, 0, XATTR_NOFOLLOW);
		if (xattr < 0)
			xattr = 0;
		if (xattr > 0) {
			buffer[11] = '@';
			buffer[12] = ' ';
		}
		else if (acl != NULL) {
			buffer[11] = '+';
			buffer[12] = ' ';			
		}
		else {
			buffer[11] = ' ';
			buffer[12] = ' ';			
		}

		char* new_time = ft_substr(date[3], 0, 5);
		char buflinkname[2048];
		ft_bzero(buflinkname, 2048);
		readlink(linkFileName, buflinkname, 2047);
		
		ft_printf("%s%d %s  %d%7d %s%3s %s %s", buffer, file_info.st_nlink, user->pw_name, user->pw_gid, file_info.st_size, date[1], date[2], new_time, file_name);
		if (S_ISLNK(file_info.st_mode))
			ft_printf(" -> %s", buflinkname);	
			
		free(new_time);
		for (int i = 0; date[i] != NULL; i++)
			free(date[i]);
		free(date);
		acl_free(acl);
	}
	else if (CHECK_FLAG(flags, g_FLAG))
	{
		struct stat	file_info;
		lstat(file_path, &file_info);
		
		
				char **date;
		if (CHECK_FLAG(flags, u_FLAG))
			date = ft_split(ctime(&file_info.st_atime), ' ');
		else
			date = ft_split(ctime(&file_info.st_mtime), ' ');

		struct passwd* user = getpwuid(file_info.st_uid);

		char buffer[14];
		ft_bzero(buffer, 14);
	
		buffer[0] = '\n';
		
		if (S_ISDIR(file_info.st_mode))
			buffer[1] = 'd';
		else if (S_ISLNK(file_info.st_mode))
			buffer[1] = 'l';
		else if (S_ISCHR(file_info.st_mode))
			buffer[1] = 'c';
		else if (S_ISBLK(file_info.st_mode))
			buffer[1] = 'b';
		else if (S_ISFIFO(file_info.st_mode))
			buffer[1] = 'p';
		else
			buffer[1] = '-';

		buffer[2] = ((file_info.st_mode & S_IRUSR)) ? 'r' : '-';
		buffer[3] = ((file_info.st_mode & S_IWUSR)) ? 'w' : '-';
		buffer[4] = ((file_info.st_mode & S_IXUSR)) ? 'x' : '-';
		buffer[5] = ((file_info.st_mode & S_IRGRP)) ? 'r' : '-';
		buffer[6] = ((file_info.st_mode & S_IWGRP)) ? 'w' : '-';
		buffer[7] = ((file_info.st_mode & S_IXGRP)) ? 'x' : '-';
		buffer[8] = ((file_info.st_mode & S_IROTH)) ? 'r' : '-';
		buffer[9] = ((file_info.st_mode & S_IWOTH)) ? 'w' : '-';
		buffer[10] = ((file_info.st_mode & S_IXOTH)) ? 'x' : '-';

		ssize_t xattr = 0;
		acl_t acl = NULL;
		acl_entry_t	dummy;
		const char *linkFileName = file_path;
		acl = acl_get_link_np(linkFileName, ACL_TYPE_EXTENDED);
		if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
		{
			acl_free(acl);
			acl = NULL;
		}
		xattr = listxattr(linkFileName, NULL, 0, XATTR_NOFOLLOW);
		if (xattr < 0)
			xattr = 0;
		if (xattr > 0) {
			buffer[11] = '@';
			buffer[12] = ' ';
		}
		else if (acl != NULL) {
			buffer[11] = '+';
			buffer[12] = ' ';			
		}
		else {
			buffer[11] = ' ';
			buffer[12] = ' ';			
		}

		char* new_time = ft_substr(date[3], 0, 5);
		char buflinkname[2048];
		ft_bzero(buflinkname, 2048);
		readlink(linkFileName, buflinkname, 2047);
		
		ft_printf("%s%d  %d%7d %s%3s %s %s", buffer, file_info.st_nlink, user->pw_gid, file_info.st_size, date[1], date[2], new_time, file_name);
		if (S_ISLNK(file_info.st_mode))
			ft_printf(" -> %s", buflinkname);	
			
		free(new_time);
		for (int i = 0; date[i] != NULL; i++)
			free(date[i]);
		free(date);
		acl_free(acl);
	}
	else
	{
		ft_printf("%s\t", file_name);
	}
}

int	ft_last_mod_compare(const char *file1, const char *file2, const char *dirname)
{
	struct stat	s_file1;
	struct stat	s_file2;
	char *tmp1 = ft_strjoin(dirname, file1);
	char *tmp2 = ft_strjoin(dirname, file2);

	lstat(tmp1, &s_file1);
	lstat(tmp2, &s_file2);
	if (s_file1.st_mtimespec.tv_sec < s_file2.st_mtimespec.tv_sec)
		return 1;
	if (s_file1.st_mtimespec.tv_sec > s_file2.st_mtimespec.tv_sec)
		return 0;
	if (s_file1.st_mtimespec.tv_nsec < s_file2.st_mtimespec.tv_nsec)
		return (1);
	return 0;
}

int	ft_last_access_compare(const char *file1, const char *file2, const char *dirname)
{
	struct stat	s_file1;
	struct stat	s_file2;
	char *tmp1 = ft_strjoin(dirname, file1);
	char *tmp2 = ft_strjoin(dirname, file2);

	lstat(tmp1, &s_file1);
	lstat(tmp2, &s_file2);
	if (s_file1.st_atimespec.tv_sec < s_file2.st_atimespec.tv_sec)
		return 1;
	if (s_file1.st_atimespec.tv_sec > s_file2.st_atimespec.tv_sec)
		return 0;
	if (s_file1.st_atimespec.tv_nsec < s_file2.st_atimespec.tv_nsec)
		return (1);
	return 0;
}

int	ft_strcmp(const char *s1, const char *s2, const char *null)
{
	(void) null;
	while (*s1 && *s2 == *s1)
	{
		s1++;
		s2++;
	}
	if (*s1 <= *s2)
		return 0;
	return 1;
}

void	change_to_flags(str_vector * sv, int flags, const char *dirname)
{
	if (CHECK_FLAG(flags, f_FLAG))
		return ;
	if (CHECK_FLAG(flags, t_FLAG) && CHECK_FLAG(flags, u_FLAG))
		str_vector_sort(sv, ft_last_mod_compare, dirname);
	else if (CHECK_FLAG(flags, t_FLAG))
		str_vector_sort(sv, ft_last_mod_compare, dirname);
	else if (CHECK_FLAG(flags, u_FLAG))
		str_vector_sort(sv, ft_last_access_compare, dirname);
	else
		str_vector_sort(sv, ft_strcmp, 0);
	if (CHECK_FLAG(flags, r_FLAG))
		str_vector_reverse(sv);
}

void	str_append_slash(char **str)
{
	size_t	size = ft_strlen(*str) + 2;
	if (size != 2 && (*str)[size - 3] == '/')
		return ;
	char *tmp = malloc(sizeof(char) * (size));
	ft_strlcpy(tmp, *str, size);
	tmp[size - 2] = '/'; 
	tmp[size - 1] = 0;
	free(*str);
	*str = tmp;
}

int	is_notvalid_dir(const char *file_path)
{
	DIR	* dir = opendir(file_path);
	if (dir == NULL)
		return (1);
	closedir(dir);
	return (0);
}
