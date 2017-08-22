/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 16:25:42 by zadrien           #+#    #+#             */
/*   Updated: 2017/08/22 16:46:57 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		job_is_stopped(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed && !p->stopped)
			return (0);
	}
	return (1);
}

int		job_is_complete(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
		if (!p->completed)
			return (0);
	return (1);
}

void	mark_job_status(t_job **job, int status, pid_t pid)
{
	t_process	*p;

	p = (*job)->first_process;
	while (p)
	{
		if (p->pid == pid)
		{
			if (WIFSTOPPED(status))
				p->stopped = 1;
			else if (WIFEXITED(status) && !WEXITSTATUS(status))
				p->completed = 1;
			break ;
		}
		p = p->next;
	}
}

int		mark_process_status(t_job **job)
{
	t_process	*p;

	if (*job)
	{
		p = (*job)->first_process;
		while (p)
		{
			if (WIFSTOPPED(p->status))
				p->stopped = 1;
			else
			{
				p->completed = 1;
				if (WIFSIGNALED(p->status))
					ft_errormsg("21sh:", "Child process", "killed by signal");
			}
			p = p->next;
		}
		return (0);
	}
	else
		return (ft_errormsg("21sh:", NULL, "Job doesn't exist"));
}
