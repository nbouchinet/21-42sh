/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_seq2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 09:42:06 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/04 16:52:46 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	agre(t_ast **ast)
{
	int		io;
	int		std;
	t_ast	*tmp;
	int		*fd;

	io = -1;
	tmp = *ast;
	if ((io_number(tmp->right->str) == 1 || ft_strcmp(tmp->right->str, "-") == 0))
	{
		ft_putendl("MAchallah");
		if (tmp->str)
			io = ft_atoi(tmp->str);
		fd = std_value(-1, -1);
		if ((fd[io] == -1) || fd[1] == -1)
		{
			tmp->str ? (std = dup(io)) : (std = dup(1));
			std_value(tmp->str ? io : 1, std);
		}
		std = ft_atoi(tmp->right->str);
		if (ft_strcmp(tmp->right->str, "-") == 0)
			close(io != -1 ? io : 1);
		else
			dup2(std, io != -1 ? io : 1);
	}
	// else
		// rdir_rrdir(&tmp);
} //ls > toto 1>&-

void	bgre(t_ast **ast)
{
	int		io;
	int		std;
	t_ast	*tmp;
	int		*fd;

	io = -1;
	tmp = *ast;
	if (io_number(tmp->right->str) == 1 || ft_strcmp(tmp->right->str, "-") == 0)
	{
		if (tmp->str)
			io = ft_atoi(tmp->str);
		fd = std_value(-1, -1);
		if ((io != -1 && fd[io] == -1) || fd[1] == -1)
		{
			tmp->str ? (std = dup(io)) : (std = dup(1));
			std_value(tmp->str ? io : 1, std);
		}
		std = ft_atoi(tmp->right->str);
		ft_strcmp(tmp->right->str, "-") != 0 ? dup2(std, io) : close(io != -1 ? io : 1);
	}
	else
		rdir_rrdir(&tmp);
} //ls > toto 1>&-
