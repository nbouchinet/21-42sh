/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_seq.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 16:57:28 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/04 17:12:38 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		*std_value(int fd, int oldfd)
{
	int			i;
	static int	std[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

	if (fd != -1 && oldfd != -1)
		std[fd] = oldfd;
	else if (fd == -2 && oldfd == -2)
	{
		i = -1;
		while (++i < 10)
			std[i] = -1;
	}
	return (std);
}

void	restore_std(t_ast **ast)
{
	int		*fd;
	// int		std;

	(void)ast;
	fd = std_value(-1, -1);
	if (fd[0] != -1)
		dup2(fd[0], STDIN_FILENO);
	if (fd[1] != -1)
		dup2(fd[1], STDOUT_FILENO);
	if (fd[2] != -1)
		dup2(fd[2], STDERR_FILENO);
	std_value(-2, -2);
}

void	switch_std(int fd, int newfd)
{
	int		i;
	int		st;
	int		*s;
	static const int	std[3] = {STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO};

	i = -1;
	s = std_value(-1, -1);
	while (++i < 3)
		if (fd == STDIN_FILENO)
		{
			if (s[fd] == -1)
				std_value(fd, (st = dup(std[i])));
			dup2(newfd, std[i]);
			break ;
		}
	if (i == 3)
	{
		if (s[fd] == -1)
			std_value(fd, dup(fd));
		dup2(newfd, fd);
	}
}

void	rdir_rrdir(t_ast **ast)
{
	int		fd;
	int		std;
	t_ast	*tmp;

	tmp = *ast;
	fd = open(tmp->right->str, (tmp->type == RRDIR ? O_APPEND : O_TRUNC) |
		O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (tmp->str)
		std = ft_atoi(tmp->str);
	tmp->str ? switch_std(std, fd) : switch_std(1, fd);
}

int		exec_io_seq(t_ast **ast)
{
	int						i;
	t_ast					*tmp;
	static const t_rdir		rdir[3] = {{RDIR, &rdir_rrdir}, {RRDIR, &rdir_rrdir},
	{AGRE, &agre}};//, {BDIR,}, {BBDIR,}, {BGRE,}};

	 tmp = *ast;
	 while (tmp)
	 {
		 i = -1;
		 while (++i < 3)
		 	if (tmp->type == rdir[i].t)
				rdir[i].f(&tmp);
		 tmp = tmp->left;
 	}
	 return (1);
}
