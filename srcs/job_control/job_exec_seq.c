/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 13:13:50 by zadrien           #+#    #+#             */
/*   Updated: 2017/08/22 16:23:29 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		job_qm_seq(t_ast **ast, t_env **env)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp->left->type == QM)
	{
		if (job_qm_seq(&tmp->left, env) == 1)
			job_ast(&tmp->left->right, env);
	}
	else if (tmp->left->type == CMD_SEQ)
		job_ast(&tmp->left, env);
	return (1);
}

int		job_oa_seq(t_ast **ast, t_env **env)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp->type == OR)
	{
		if (job_oa_seq(&tmp->left, env) == 0)
			return (job_oa_seq(&tmp->right, env));
		return (1);
	}
	else if (tmp->type == AND)
	{
		if (job_oa_seq(&tmp->left, env) == 1)
			return (job_oa_seq(&tmp->right, env));
	}
	else if (tmp && tmp->type == PIPE_SEQ)
		return (job_pipe(&tmp, env));
	else if (tmp && tmp->type == CMD_SEQ)
		return (job_cmd_seq(&tmp, env));
	return (0);
}

int		job_andor(t_ast **ast, t_env **env)
{
	return (job_oa_seq(&(*ast)->left, env));
}

void	print_process(t_process **pro)
{
	int			i;
	t_process *tmp;

	tmp = *pro;
	i = -1;
	while (tmp->argv[++i])
		printf("%s\n", tmp->argv[i]);
	if (tmp->rdir)
		ft_putast(tmp->rdir);
}
