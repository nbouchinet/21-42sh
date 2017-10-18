/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 00:19:40 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/18 16:46:05 by zadrien          ###   ########.fr       */
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
		return (0);
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
		if (tmp->left->left && !ft_strcmp(tmp->left->left->str, cmd[i].builtin))
		{
			(*p)->builtin = tmp;
			(*p)->env = *env;
			return (1);
		}
	return (0);
}

int		init_process(t_ast **ast, t_process **p, t_env **env)
{
	int			i;
	t_process	*tmp;

	i = 0;
	tmp = NULL;
	if (*p)
	{
		tmp = *p;
		while (tmp->next)
			tmp = tmp->next;
	}
	if (!init_proc(tmp ? &tmp->next : p))
		return (0);
	tmp = (tmp ? tmp->next : *p);
	if ((*ast)->left)
		i = check_type_bin(&(*ast)->left, env);
	if (i != 1 && check_builtin(ast, &tmp, env))
		return (print_error(1, (*ast)->left->left->str));
	if (i)
	{
		tmp->argv = creat_argv(&(*ast)->left);
		tmp->rdir = (*ast)->right != NULL ? (*ast)->right->right : NULL;
	}
	return (print_error(i, (*ast)->left->left ?
		(*ast)->left->left->str : NULL));
}

int		complete_process(t_ast **ast, t_process **p, t_env **env)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp && tmp->type == PIPE)
	{
		if (tmp->left && init_process(&tmp->left, p, env))
			return (complete_process(&tmp->right, &(*p)->next, env));
	}
	else
	{
		if (tmp)
			if (init_process(&tmp, p, env))
				return (1);
	}
	return (0);
}
