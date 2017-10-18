/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 21:45:46 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/18 14:04:30 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		delete_job(t_job **job)
{
	t_job		*j;
	t_process	*p;
	t_process	*tmp;

	j = *job;
	if (j)
	{
		if (j->command)
			ft_strdel(&j->command);
		p = j->first_process;
		while (p)
		{
			tmp = p;
			if (tmp->argv)
				ft_freetab(tmp->argv);
			if (tmp->rdir)
				tmp->rdir = NULL;
			p = p->next;
			free(tmp);
		}
		free(j);
	}
	return (0);
}

int		env_builtin_pipe(t_ast **ast, t_env **env, t_env **r_env)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp)
		return (exec_env_pipe(&tmp, env, r_env));
	if (env)
		print_env(*env);
	return (1);
}

int		bgre(t_ast **ast, int mod)
{
	int		i;
	int		fd;
	int		std;
	t_ast	*tmp;

	(void)mod;
	tmp = *ast;
	if ((i = dup_fd(tmp->str, tmp->left->str)) != 0)
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
