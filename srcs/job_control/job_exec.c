/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:21:15 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/13 12:17:43 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		job_ast(t_ast **ast, t_env **env, int foreground)
{
	int					i;
	t_ast				*tmp;
	static const t_jseq	seq[5] = {{PIPE_SEQ, &job_pipe},
							{CMD_SEQ, &job_cmd_seq}, {AND_OR, &job_andor},
							{QM_SEQ, &job_qm_seq}, {BG_SEQ, &job_bg_seq}};

	tmp = *ast;
	while (tmp && tmp->type >= QM_SEQ && tmp->type <= AND_OR)
	{
		i = -1;
		while (++i < 5)
			if (seq[i].type == tmp->type)
				seq[i].f(&tmp, env, foreground);
		tmp = tmp->right;
	}
}

int			delete_job(t_job **job)
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
	return (-1);
}

int			job_cmd_seq(t_ast **ast, t_env **env, int foreground)
{
	int					i;
	t_job				*job;
	t_ast				*tmp;
	static const t_cmd	cmd[11] = {{"unsetenv", &ft_unsetenv},
					{"hash", &hashing}, {"setenv", &ft_setenv},
					{"env", &builtin_env}, {"jobs", &inter_job},
					{"fg", &ft_fg}, {"cd", &ft_cd},
					{"echo", &ft_echo}, {"exit", &ft_exit},
					{"history", &ft_history}, {"bg", &ft_bg}};

	i = -1;
	tmp = *ast;
	while (++i < 11)
		if (!ft_strcmp(cmd[i].cmd, tmp->left->left->str))
			return (cmd[i].f(&tmp, env));
	if (init_job(&job))
	{
		job->command = init_job_name(ast);
		if (!init_process(ast, &(job)->first_process, env))
			return (delete_job(&job));
		return (exec_job(&job, env, foreground));
	}
	return (-1);
}

int			exec_job(t_job **job, t_env **env, int foreground)
{
	int		status;

	job_control(job, NULL, ADD);
	if (foreground)
	{
		status = exec_pro(&(*job)->first_process, env, job);
		mark_process_status(job);
	}
	else
		exec_pro_bg(&(*job)->first_process, env, job);
	if (job_is_stopped(*job))
	{
		hash(NULL, job, PUT);
		return (1);
	}
	return (0);
}

int			exec_pro(t_process **lst, t_env **env, t_job **j)
{
	char		**n_env;
	t_process	*tmp;

	tmp = *lst;
	n_env = get_env(env, tmp->argv[0]);
	if (!(tmp->pid = fork()))
	{
		if (g_shell_is_interactive)
		{
			setpgid(getpid(), getpid());
			tcsetpgrp(g_shell_terminal, tmp->pid);
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			signal(SIGTSTP, SIG_DFL);
			signal(SIGTTIN, SIG_DFL);
			signal(SIGTTOU, SIG_DFL);
			signal(SIGCHLD, SIG_DFL);
		}
		if (tmp->rdir)
			io_seq(&tmp->rdir);
		execve(tmp->argv[0], tmp->argv, n_env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		(*j)->pgid = tmp->pid;
		setpgid(tmp->pid, (*j)->pgid);
		tcsetpgrp(g_shell_terminal, (*j)->pgid);
		wait_for_job(j);
		tcsetpgrp(g_shell_terminal, g_shell_pgid);
	}
	ft_freetab(n_env);
	return (tmp->status);
}
