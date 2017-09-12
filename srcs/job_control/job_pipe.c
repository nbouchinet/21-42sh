/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:55:42 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/11 17:53:59 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_job(t_job **job)
{
	int			i;
	int			j;
	t_process *p;

	j = 1;
	printf("[Jobs = %s | %d]\n", (*job)->command, (*job)->pgid);
	p = (*job)->first_process;
	while (p)
	{
		i = -1;
		printf("Process numero %d\n", j++);
		printf("PID: %d\n", p->pid);
		while (p->argv[++i])
		{
			//printf("argv[%d] = %s\n", i, p->argv[i]);
		}
		p = p->next;
	}
}

int		job_pipe(t_ast **ast, t_env **env, int foreground)
{
	t_job	*job;
	t_job	*tmp;

	if (init_job(&job) == 1)
	{
		tmp = job;
		tmp->command = init_pipe_job(ast);
		if (complete_process(&(*ast)->right, &tmp->first_process, env) == 1)
			return (pipe_job(&job, env, foreground));
	}
	return (0);
}

int		pipe_job(t_job **lst, t_env **env, int foreground)
{
	int		status;
	char	**n_env;
	t_job	*tmp;

	tmp = *lst;
	job_control(lst, NULL, ADD);
	n_env = get_env(env, tmp->first_process->argv[0]);
	if (foreground)
	{
		status = exec_pipe_job(&tmp->first_process, n_env, -1, lst);
		mark_process_status(lst);
	}
	else
		status = exec_pipe_bg(&tmp->first_process, n_env, -1, lst);
	ft_freetab(n_env);
	if (WIFEXITED(status) && !WEXITSTATUS(status))
		return (1);
	return (0);
}

void	job_cont_pipe(t_process **lst, char **env, t_job **job, int *p)
{
	close(p[1]);
	(*lst)->next != NULL ? exec_pipe_job(&(*lst)->next, env, p[0], job) : 0;
	close(p[0]);
}

int		exec_pipe_job(t_process **lst, char **env, int r, t_job **job)
{
	int			p[2];
	t_process	*tmp;

	tmp = *lst;
	if (pipe(p) == 0)
	{
		if ((tmp->pid = fork()) == 0)
		{
			close(p[0]);
			tmp->next != NULL ? dup2(p[1], STDOUT_FILENO) : 0;
			if (r != -1)
				dup2(r, STDIN_FILENO);
			if (tmp->rdir)
				io_seq(&tmp->rdir);
			setpgid(getpid(), ((*job)->pgid == 0 ? getpid() : (*job)->pgid));
			tcsetpgrp(g_shell_terminal, (*job)->pgid);
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			signal(SIGTSTP, SIG_DFL);
			signal(SIGTTIN, SIG_DFL);
			signal(SIGTTOU, SIG_DFL);
			signal(SIGCHLD, SIG_DFL);
			execve(tmp->argv[0], tmp->argv, env);
		}
		else
		{
			(*job)->pgid == 0 ? (*job)->pgid = tmp->pid : 0;
			setpgid(tmp->pid, (*job)->pgid);
			tcsetpgrp(g_shell_terminal, (*job)->pgid);
 			job_cont_pipe(&tmp, env, job, p);
			waitpid(tmp->pid, &tmp->status, WUNTRACED | WCONTINUED);
			tcsetpgrp (g_shell_terminal, g_shell_pgid);
		}
	}
	return (tmp->status);
}
