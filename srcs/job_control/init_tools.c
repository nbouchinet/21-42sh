/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:38:04 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/13 12:32:08 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		init_job(t_job **job)
{
	if (!((*job) = (t_job*)malloc(sizeof(t_job))))
		return (-1);
	(*job)->command = NULL;
	(*job)->pgid = 0;
	(*job)->first_process = NULL;
	(*job)->next = NULL;
	(*job)->notified = 0;
	return (1);
}

int		init_proc(t_process **process)
{
	if (!((*process) = (t_process*)malloc(sizeof(t_process))))
		return (-1);
	(*process)->status = 0;
	(*process)->argv = NULL;
	(*process)->rdir = NULL;
	(*process)->stopped = 0;
	(*process)->completed = 0;
	(*process)->pid = 0;
	(*process)->next = NULL;
	return (1);
}

int		init_process(t_ast **ast, t_process **proc, t_env **env)
{
	t_process	*tmp;

	if ((*proc))
	{
		tmp = *proc;
		while (tmp->next)
			tmp = tmp->next;
		if (init_proc(&tmp->next) == -1)
			return (-1);
	}
	else
	{
		if (init_proc(proc) == -1)
			return (-1);
		tmp = (*proc);
	}
	if ((tmp->argv = creat_arg_process(&(*ast)->left, env)) != NULL)
	{
		tmp->rdir = (*ast)->right != NULL ? (*ast)->right->right : NULL;
		return (1);
	}
	return (0);
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

int		complete_process(t_ast **ast, t_process **p, t_env **env)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp->type == PIPE)
	{
		if (init_process(&tmp->left, p, env) == 0)
			return (0);
		return (complete_process(&tmp->right, &(*p)->next, env));
	}
	else
	{
		if (init_process(&tmp, p, env) == 0)
			return (0);
	}
	return (1);
}
