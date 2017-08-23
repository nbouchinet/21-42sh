/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:55:42 by zadrien           #+#    #+#             */
/*   Updated: 2017/08/23 14:56:50 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_job(t_job **job)
{
	int			i;
	int			j;
	t_process *p;

	j = 1;
	printf("[Jobs = %s]\n", (*job)->command);
	p = (*job)->first_process;
	while (p)
	{
		i = -1;
		printf("Process numero %d\n", j++);
		while (p->argv[++i])
			printf("argv[%d] = %s\n", i, p->argv[i]);
		printf("Status: %s\n", (p->completed ? "Complete" : (p->stopped ? "Stopped" : "In progress")));
		p = p->next;
	}
}

int		job_pipe(t_ast **ast, t_env **env)
{
	t_job	*job;
	t_job	*tmp;

	if (init_job(&job) == 1)
	{
		tmp = job;
		tmp->command = init_pipe_job(ast);
		if (complete_process(&(*ast)->right, &tmp->first_process, env) == 1)
			return (pipe_job(&job, env));
	}
	return (0);
}

int		pipe_job(t_job **lst, t_env **env)
{
	int		status;
	char	**n_env;
	t_job	*tmp;

	tmp = *lst;
	job_control(lst, NULL, ADD);
	n_env = get_env(env, tmp->first_process->argv[0]);
	status = exec_pipe_job(&tmp->first_process, n_env, -1, &tmp->pgid);
	mark_process_status(lst);
	ft_freetab(n_env);
	if (WIFEXITED(status) && !WEXITSTATUS(status))
		return (1);
	return (0);
} // implement hash table

void	job_cont_pipe(t_process **lst, char **env, int *p)
{
	int		lol;

	lol = -1;
	close(p[1]);
	(*lst)->next ? exec_pipe_job(&(*lst)->next, env, p[0], &lol) : 0;
	close(p[0]);
}

int		exec_pipe_job(t_process **lst, char **env, int r, int *pgid)
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
			r != -1 ? dup2(r, STDIN_FILENO) : 0;
			execve(tmp->argv[0], tmp->argv, env);
		}
		else
		{
			*pgid != -1 ? (*pgid = tmp->pid) : 0;
 			job_cont_pipe(&tmp, env, p);
			waitpid(tmp->pid, &tmp->status, WUNTRACED | WCONTINUED);
			return (tmp->status);
		}
	}
	return (0);
}
