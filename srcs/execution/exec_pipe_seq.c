/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_seq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 11:01:17 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/24 13:25:03 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		exec_pipe_seq(t_ast **ast, t_env **env, int i)
{
	t_ast	*tmp;
	int		fd_in;
	int		fd[2];
	pid_t	son;

	tmp = *ast;
	if (tmp->left->type == PIPE)
	{
		if ((fd_in = exec_pipe_seq(&tmp->left, env, ++i)) != -99)
		{
			pipe(fd);
			if ((son = fork()) == 0)
			{
				dup2(fd_in, 0);
				if (i != 0)
					dup2(fd[1], 1);
				close(fd[0]);
				if (exec_binary(&tmp->right) == 1)
					exit(EXIT_SUCCESS);
			}
			else
			{
				close(fd[1]);
				dup2(fd[0], 0);
				return (fd[0]);
			}
		}
	}
	else if (tmp->left->type == CMD_SEQ)
	{
		pipe(fd);
		if ((son = fork()) == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			if (exec_binary(&tmp, env) == 1)
				exit(EXIT_SUCCESS);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			return (fd[0]);
		}
	}
	return (-99);
}
