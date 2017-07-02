/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 08:54:16 by zadrien           #+#    #+#             */
/*   Updated: 2017/07/02 17:55:15 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		wtf_rdir(t_ast **ast)
{
	int		fd;
	int		std;
	t_ast	*tmp;

	tmp = *ast;
	if ((fd = open(tmp->left->str, (tmp->type == RRDIR ? O_APPEND : O_TRUNC) |
		O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
	{
		std = tmp->str ? ft_atoi(tmp->str) : STDOUT_FILENO;
		if (dup2(fd, std) != -1)
			return (1);
	}
	return (0);
}

int		bdir(t_ast **ast)
{
	int		fd;
	int		std;
	t_ast	*tmp;

	tmp = *ast;
	if ((fd = open(tmp->left->str, O_RDONLY)) != -1)
	{
		std = tmp->str ? ft_atoi(tmp->str) : STDIN_FILENO;
		if (dup2(fd, std) != -1)
			return (1);
	}
	else
		ft_errormsg("21sh: ", tmp->left->str, ": No such file or directory.");
	return (0);
}

int		agre(t_ast **ast)
{
	int		fd;
	int		std;
	t_ast	*tmp;

	tmp = *ast;
	std = tmp->str ? ft_atoi(tmp->str) : STDOUT_FILENO;
	if (ft_strcmp(tmp->left->str, "-") == 0)
	{
		if (close(std) == 0)
			return (1);
	}
	else if (io_number(tmp->left->str) == 1)
	{
		fd = ft_atoi(tmp->left->str);
		if (dup2(fd, std) != -1)
			return (1);
	}
	else
		return (wtf_rdir(&tmp));
	return (0);
}

int		io_seq(t_ast **ast)
{
	int						i;
	t_ast					*tmp;
	static const t_rdir		rdir[4] = {{RDIR, &wtf_rdir}, {RRDIR, &wtf_rdir},
		{AGRE, &agre}, {BDIR, &bdir}}; //, {BBDIR,}, {BGRE,}}; A FAIRE

	tmp = *ast;
	if (tmp && (tmp->type >= RDIR && tmp->type <= BGRE))
	{
		if (tmp->right)
			if (io_seq(&tmp->right) == 0)
				return (0);
		i = -1;
		while (++i < 4)
			if (tmp->type == rdir[i].t)
				if (rdir[i].f(&tmp) == 1)
				{
					return (1);
				}
	}
	return (0);
}
