/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:38:04 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/26 02:50:19 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		init_job(t_job **job)
{
	if (!((*job) = (t_job*)malloc(sizeof(t_job))))
		return (-1);
	(*job)->status = 0;
	(*job)->num = 0;
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
	(*process)->env = NULL;
	(*process)->builtin = NULL;
	(*process)->rdir = NULL;
	(*process)->stopped = 0;
	(*process)->completed = 0;
	(*process)->pid = 0;
	(*process)->next = NULL;
	return (1);
}

typedef struct		s_bi
{
	char			*builtin;
}					t_bi;

int		check_builtin(t_ast **ast, t_process **p, t_env **env)
{
	int					i;
	t_ast				*tmp;
	static const t_bi	cmd[14] = {{"unsetenv"}, {"hash"}, {"setenv"}, {"env"},
	{"jobs"}, {"fg"}, {"echo"}, {"exit"}, {"history"}, {"bg"}, {"read"},
	{"unset"}, {"export"}, {"cd"}};

	i = -1;
	tmp = *ast;
	while (++i < 14)
		if (!ft_strcmp(tmp->left->left->str, cmd[i].builtin))
		{
			(*p)->builtin = tmp;
			(*p)->env = *env;
			return (1);
		}
	return (0);
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
	if (check_builtin(ast, &tmp, env))
		return (1);
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
	t_ast			*tmp;

	tmp = *ast;
	if (tmp->type == PIPE)
	{
		if (init_process(&tmp->left, p, env))
			return (complete_process(&tmp->right, &(*p)->next, env));
	}
	else
	{
		if (init_process(&tmp, p, env))
			return (1);
	}
	return (0);
}
