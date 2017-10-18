/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_rdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 17:44:01 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/18 08:39:13 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_io(char *tmp)
{
	int		i;

	i = *tmp == '-' ? 0 : -1;
	while(tmp[++i])
		if (!ft_isdigit(tmp[i]))
			return (0);
	return (1);
}

int		valid_fd(char *str)
{
	int		fd;

	if (check_io(str))
	{
		fd = ft_atoi(str);
		if (fd != 0 && fd != 1 && fd != 2)
			return(ft_errormsg("42sh : ", str, ": Bad file descriptor"));
		else
			return (1);
	}
	return (0);
}

int		dup_fd(char *std, char *fd)
{
	int		i;
	int		num;
	int		io;

	if ((i = valid_fd(fd)))
	{
		num = ft_atoi(fd);
		io = std ? ft_atoi(std) : STDOUT_FILENO;
		if (dup2(num, io) != 1)
			return (1);
	}
	return (i);
}
