/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:21:15 by zadrien           #+#    #+#             */
/*   Updated: 2017/08/24 22:42:55 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	job_ast(t_ast **ast, t_env **env)
{
	int					i;
	t_ast				*tmp;
	static const t_jseq	seq[4] = {{PIPE_SEQ, &job_pipe},{CMD_SEQ, &job_cmd_seq},
	 							{AND_OR, &job_andor}, {QM_SEQ, &job_qm_seq}};

	tmp = *ast;
	while (tmp && tmp->type >= QM_SEQ && tmp->type <= AND_OR)
	{
		i = -1;
		while (++i < 4)
			if (seq[i].type == tmp->type)
				seq[i].f(&tmp, env);
		tmp = tmp->right;
	}
}

int		job_cmd_seq(t_ast **ast, t_env **env)
{
	int					i;
	t_job				*job;
	t_ast				*tmp;
	static const t_cmd	cmd[6] = {{"unsetenv", &ft_unsetenv}, {"env", &ft_enve},
								{"setenv", &ft_setenv}, {"hash", &hashing},
								{"jobs", &inter_job}, {"fg", &ft_fg}};

	i = -1;
	tmp = *ast;
	while (++i < 6)
		if (!(ft_strcmp(cmd[i].cmd, tmp->left->left->str)))
			return (cmd[i].f(&tmp, env));
	if (init_job(&job) == 1)
	{
		job->command = init_job_name(ast);
		tcgetattr (g_shell_terminal, &job->tmodes);
		if (init_process(ast, &(job)->first_process, env) == 0)
			return (-1);
		return (exec_job(&job, env, ast));
	}
	return (-1);
}

int		exec_job(t_job **job, t_env **env, t_ast **ast)
{
	int		status;

	job_control(job, ast, ADD);
	status = exec_pro(&(*job)->first_process, env, job, 1);

	// mark_process_status(job);
	// (*job)->pgid = (*job)->first_process->pid;
	ft_putnbr_fd(status, 2);
	// tcsetpgrp (g_shell_terminal, (*j)->pgid);
	// tcsetattr (g_shell_terminal, TCSADRAIN, &(*j)->tmodes);
	// if (kill (- (*j)->pgid, SIGCONT) < 0)
		// perror ("kill (SIGCONT)");
	// wait_for_job(job);
	if (job_is_stopped(*job))
		return (1);
	return (0);
} //Implement multiple stopped and completed pinter

void	wait_for_job(t_job **job);

int		exec_pro(t_process **lst, t_env **env, t_job **j, int foreground)
{
	char		**n_env;
	t_process	*tmp;

	tmp = *lst;
	foreground = 2;
	n_env = get_env(env, tmp->argv[0]);
	// ft_putnbr(g_shell_is_interactive);
	// sleep(10);
	if (!(tmp->pid = fork()))
	{
		if (g_shell_is_interactive)
		{
			// *pgid = tmp->pid;
			setpgid(tmp->pid, tmp->pid);
			// if (foreground)
				// tcsetpgrp (g_shell_terminal, tmp->pid);
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
		// setpgid(tmp->pid, tmp->pid);
		tcsetpgrp (g_shell_terminal, (*j)->pgid);
		tcsetattr (g_shell_terminal, TCSADRAIN, &(*j)->tmodes);
		if (kill (- (*j)->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
		wait_for_job(j);
		// tcsetpgrp (g_shell_terminal, g_shell_pgid);

		// waitpid(tmp->pid, &tmp->status, WUNTRACED | WCONTINUED);
		// if (g_shell_is_interactive)
			// setpgid(tmp->pid, (*j)->pgid);
	}
	ft_freetab(n_env);
	return (tmp->status);
}
