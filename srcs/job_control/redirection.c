/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 08:54:16 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/18 10:11:31 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		wtf_rdir(t_ast **ast, int mod)
{
	int		fd;
	int		std;
	t_ast	*tmp;

	tmp = *ast;
	if ((fd = open(tmp->left->str, (tmp->type == RRDIR ? O_APPEND : O_TRUNC) |
		O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
	{
		mod == 1 ? close_rdir(fd, 1) : 0;
		std = tmp->str ? ft_atoi(tmp->str) : STDOUT_FILENO;
		if (dup2(fd, std) != -1)
			return (1);
	}
	else
		ft_errormsg("42sh: ", tmp->left->str, ": Permission denied.");
	return (0);
}

int		bdir(t_ast **ast, int mod)
{
	int		fd;
	int		std;
	t_ast	*tmp;

	tmp = *ast;
	if ((fd = open(tmp->left->str, O_RDONLY)) != -1)
	{
		mod == 1 ? close_rdir(fd, 1) : 0;
		std = tmp->str ? ft_atoi(tmp->str) : STDIN_FILENO;
		if (dup2(fd, std) != -1)
			return (1);
	}
	ft_errormsg("42sh: ", tmp->left->str,
		": No such file, directory or permission denied.");
	return (0);
}

int		agre(t_ast **ast, int mod)
{
	int		i;
	int		fd;
	int		std;
	t_ast	*tmp;

	(void)mod;
	tmp = *ast;
	if ((i = dup_fd(tmp->str, tmp->left->str)) == 0)
	{
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
			return (wtf_rdir(&tmp, mod));
		return (0);
	}
	return (i == 1 ? 1 : 0);
}

int		bbdir(t_ast **ast, int mod)
{
	int		std;

	(void)mod;
	if ((*ast)->left->type != -1 && (*ast)->left->type != FIL)
	{
		std = (*ast)->str ? ft_atoi((*ast)->str) : STDIN_FILENO;
		if (dup2((*ast)->left->type, std) != -1)
		{
			close((*ast)->left->type);
			return (1);
		}
	}
	return (0);
}

int		io_seq(t_ast **ast, int mod)
{
	int						i;
	t_ast					*tmp;
	static const t_rdir		rdir[6] = {{RDIR, &wtf_rdir}, {RRDIR, &wtf_rdir},
		{AGRE, &agre}, {BDIR, &bdir}, {BBDIR, &bbdir}, {BGRE, &bgre}};

	tmp = *ast;
	if (tmp && (tmp->type >= RDIR && tmp->type <= BGRE))
	{
		if (tmp->right)
			if (io_seq(&tmp->right, mod) == 0)
				return (0);
		i = -1;
		while (++i < 6)
			if (tmp->type == rdir[i].t)
				if (rdir[i].f(&tmp, mod) == 1)
					return (1);
	}
	return (0);
}
