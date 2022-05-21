/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmand <marmand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 00:49:47 by marmand           #+#    #+#             */
/*   Updated: 2022/04/06 17:21:03 by marmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

# define l_FLAG 0x00000001
# define R_FLAG 0x00000002
# define a_FLAG 0x00000004
# define r_FLAG 0x00000008
# define t_FLAG 0x00000010
# define u_FLAG 0x00000020
# define f_FLAG 0x00000040
# define g_FLAG 0x00000080
# define d_FLAG 0x00000100

# define CHECK_FLAG(bitset, flag) ((bitset) & (flag))

int	bufferMustBe(int flags);
int	predicat(const char *file_name, int flags);
int	get_flags(int argc, char ** argv, int *scipped);


#endif // FLAGS_H