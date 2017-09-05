/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_bg_seq.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 15:58:53 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/05 19:43:21 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	job_cont_bg(t_process **lst, char **env, t_job **job, int *p)
{
	close(p[1]);
	(*lst)->next ? exec_pipe_bg(&(*lst)->next, env, p[0], job) : 0;
	close(p[0]);
}

int		exec_pipe_bg(t_process **pro, char **env, int r, t_job **job)
{
	int			p[2];
	t_process	*tmp;

	tmp = *pro;
	if (pipe(p) == 0)
	{
		if ((tmp->pid = fork()) == 0)
		{
			close(p[0]);
			setpgid(tmp->pid, ((*job)->pgid == 0 ? getpid() : (*job)->pgid));
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			signal(SIGTSTP, SIG_DFL);
			signal(SIGTTIN, SIG_DFL);
			signal(SIGTTOU, SIG_DFL);
			signal(SIGCHLD, SIG_DFL);
			tmp->next != NULL ? dup2(p[1], STDOUT_FILENO) : 0;
			r != -1 ? dup2(r, STDIN_FILENO) : 0;
			if (tmp->rdir)
				io_seq(&tmp->rdir);
			execve(tmp->argv[0], tmp->argv, env);
		}
		else
		{
			(*job)->pgid == 0 ? (*job)->pgid = tmp->pid : 0;
			setpgid(tmp->pid, (*job)->pgid);
			job_cont_bg(&tmp, env, job, p);
			if (kill (- tmp->pid, SIGCONT) < 0)
				perror ("kill (SIGCONT)");
			return (tmp->status);
		}
	}
	return (0);
}

int		exec_pro_bg(t_process **pro, t_env **env, t_job **job)
{
	char		**n_env;
	t_process	*p;

	p = *pro;
	n_env = get_env(env, p->argv[0]);
	if (!(p->pid = fork()))
	{
		setpgid(getpid(), getpid());
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
		if (p->rdir)
			io_seq(&p->rdir);
		execve(p->argv[0], p->argv, n_env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		(*job)->pgid = p->pid;
		setpgid(p->pid, p->pid);
		if (kill (-(*job)->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}
	ft_freetab(n_env);
	return (p->status);

}

int		exec_job_bg(t_job **job, t_env **env)
{
	int		status;

	job_control(job, NULL, ADD);
	status = exec_pro_bg(&(*job)->first_process, env, job);
	if (job_is_stopped(*job))
		return (1);
	return (0);
}

int		exec_bg_seq(t_ast **ast, t_env **env)
{
	t_job	*job;
	t_ast	*tmp;

	tmp = *ast;
	if (init_job(&job) == 1)
	{
		job->command = init_job_name(ast);
		if (!init_process(ast, &job->first_process, env))
			return (-1);
		return (exec_job_bg(&job, env));
	}
	return (-1);
}

int		job_bg_seq(t_ast **ast, t_env **env, int foreground)
{
	t_ast	*tmp;

	foreground = 0;
	tmp = (*ast)->type == BG_SEQ ? (*ast)->right : *ast;
	if (tmp->type == BG)
	{
		job_ast(&tmp->left, env, foreground);
		if (tmp->right)
			job_bg_seq(&tmp->right, env, foreground);
	}
	else
		job_ast(&tmp, env, foreground);
	return (1);
} // add bool
