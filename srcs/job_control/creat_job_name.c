/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 00:16:05 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/02 00:19:21 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*rdir_print(int type)
{
	if (type == RDIR)
		return (">");
	else if (type == BDIR)
		return ("<");
	else if (type == RRDIR)
		return (">>");
	else if (type == BBDIR)
		return ("<<");
	else if (type == AGRE)
		return (">&");
	else if (type == BGRE)
		return ("<&");
	return (NULL);
}

char	*init_rdir(char **cmd, t_ast **ast)
{
	t_ast	*tmp;

	if (*ast)
	{
		tmp = *ast;
		if (tmp->type >= RDIR && tmp->type <= BGRE)
			init_rdir(cmd, &tmp->right);
		(*cmd) = ft_strjoinf((*cmd), " ", 1);
		if (tmp->str)
			(*cmd) = ft_strjoinf((*cmd), tmp->str, 1);
		(*cmd) = ft_strjoinf((*cmd), rdir_print(tmp->type), 1);
		(*cmd) = ft_strjoinf((*cmd), " ", 1);
		(*cmd) = ft_strjoinf((*cmd), tmp->left->str, 1);
	}
	return (NULL);
}

char	*init_job_name(t_ast **ast)
{
	char	*cmd;
	t_ast	*tmp;
	t_ast	*tmp2;

	tmp = *ast;
	if (tmp->left->left)
	{
		cmd = ft_strdup(tmp->left->left->str);
		if (tmp->left->right)
		{
			cmd = ft_strjoinf(cmd, " ", 1);
			tmp2 = tmp->left->right;
			while (tmp2)
			{
				cmd = ft_strjoinf(cmd, tmp2->str, 1);
				if ((tmp2 = tmp2->right))
					cmd = ft_strjoinf(cmd, " ", 1);
			}
		}
		if (tmp->right)
			init_rdir(&cmd, &tmp->right->right);
		return (cmd);
	}
	return (NULL);
}

char	*init_pipe_job(t_ast **ast)
{
	char	*cmd;
	char	*get;
	t_ast	*tmp;

	cmd = NULL;
	get = NULL;
	tmp = (*ast)->right;
	while (tmp && (tmp->type == PIPE || tmp->type == CMD_SEQ))
	{
		if (tmp->type == PIPE)
			cmd = !cmd ? init_job_name(&tmp->left) :
					ft_strjoinf(cmd, (get = init_job_name(&tmp->left)), 1);
		else if (tmp->type == CMD_SEQ)
			cmd = ft_strjoinf(cmd,
			(get = init_job_name(&tmp)), 1);
		if ((tmp = tmp->right) && (tmp->type == PIPE || tmp->type == CMD_SEQ))
			cmd = ft_strjoinf(cmd, " | ", 1);
	}
	get ? ft_strdel(&get) : 0;
	return (cmd);
}
