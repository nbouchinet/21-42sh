/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_rdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 17:44:01 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 14:39:35 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_io(char *tmp)
{
	int		i;

	i = *tmp == '-' ? 0 : -1;
	if (tmp[0] == '-' && tmp[1] == '\0')
		return (0);
	while (tmp[++i])
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
		if (fd >= 0 && fd <= 2)
			return (1);
		else
			return (ft_errormsg("42sh: ", str, ": Bad file descriptor"));
	}
	return (0);
}

int		dup_fd(char *std, char *fd, int type)
{
	int		i;
	int		num;
	int		io;

	if ((i = valid_fd(fd)) == 1)
	{
		num = ft_atoi(fd);
		if (type == AGRE)
			io = std ? ft_atoi(std) : STDOUT_FILENO;
		else
			io = std ? ft_atoi(std) : STDIN_FILENO;
		if (dup2(num, io) != 1)
			return (1);
	}
	return (i);
}

int		bgre(t_ast **ast, int mod)
{
	int		i;
	int		fd;
	int		std;
	t_ast	*tmp;

	(void)mod;
	tmp = *ast;
	if ((i = dup_fd(tmp->str, tmp->left->str, BGRE)) != 0)
		return (i == 1 ? 1 : 0);
	std = tmp->str ? ft_atoi(tmp->str) : STDIN_FILENO;
	if (ft_strcmp(tmp->left->str, "-") == 0)
	{
		if (close(std) == 0)
			return (1);
	}
	else if (io_number(tmp->left->str) == 1)
	{
		fd = ft_atoi(tmp->left->str);
		if (dup2(std, fd) != -1)
			return (1);
	}
	else
		ft_errormsg("42sh: ", tmp->left->str, ": ambiguous redirect.");
	return (0);
}
