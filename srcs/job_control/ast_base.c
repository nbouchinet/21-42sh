/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 21:12:24 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/12 15:56:56 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		job_ast(t_ast **ast, t_env **env, int foreground)
{
	int					i;
	int					j;
	t_ast				*tmp;
	static const t_jseq	seq[5] = {{PIPE_SEQ, &job_pipe},
							{CMD_SEQ, &job_cmd_seq}, {AND_OR, &job_andor},
							{QM_SEQ, &job_qm_seq}, {BG_SEQ, &job_bg_seq}};

	j = 1;
	tmp = *ast;
	while (tmp && tmp->type >= QM_SEQ && tmp->type <= AND_OR)
	{
		i = -1;
		while (++i < 5)
			if (seq[i].type == tmp->type)
				if (!seq[i].f(&tmp, env, foreground))
					j = 0;
		tmp = tmp->right;
	}
	return (j);
}

int		job_cmd_seq(t_ast **ast, t_env **env, int foreground)
{
	int					i;
	t_job				*job;
	t_ast				*tmp;
	static const t_cmd	cmd[14] = {{"unsetenv", &ft_unsetenv},
{"hash", &hashing}, {"setenv", &ft_setenv}, {"env", &builtin_env},
{"jobs", &inter_job}, {"fg", &ft_fg}, {"cd", &ft_cd}, {"echo", &ft_echo},
{"exit", &ft_exit}, {"history", &ft_history}, {"bg", &ft_bg},
{"read", &ft_read}, {"unset", &ft_unset}, {"export", &ft_export}};

	i = -1;
	tmp = *ast;
	while (++i < 14)
		if (tmp->left->left && !ft_strcmp(cmd[i].cmd, tmp->left->left->str))
			return (cmd[i].f(&tmp, env));
	if (tmp->left->left && init_job(&job) &&
		(job->command = init_job_name(ast)))
	{
		if (!init_process(ast, &(job)->first_process, env))
			return (delete_job(&job));
		return (exec_job(&job, env, foreground));
	}
	return (-1);
}

int		return_exec(int status)
{
	t_cmdl	*cmdl;

	cmdl = *cmdl_slg();
	cmdl->ret = status;
	if (WIFSTOPPED(status) && (WSTOPSIG(status) == SIGTSTP))
		return (1);
	else if (WTERMSIG(status) == SIGINT)
		return (0);
	else if (WIFEXITED(status) && !WEXITSTATUS(status))
		return (1);
	return (0);
}

int		exec_job(t_job **job, t_env **env, int fg)
{
	int		status;

	job_control(job, NULL, ADD);
	if (fg)
	{
		status = exec_pro(&(*job)->first_process, env, job);
		mark_process_status(job);
	}
	else
		status = exec_pro_bg(&(*job)->first_process, env, job);
	if (return_exec(status))
	{
		hash(NULL, job, PUT);
		return (1);
	}
	return (0);
}
