/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 21:45:46 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 13:01:45 by zadrien          ###   ########.fr       */
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
