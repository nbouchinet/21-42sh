/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 00:27:26 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/02 00:27:41 by zadrien          ###   ########.fr       */
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
		p = p->next;
	}
	return (1);
}

int		job_is_complete(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed)
			return (0);
		p = p->next;
	}
	return (1);
}

int		mark_job_status(t_job **job, int status, pid_t pid)
{
	t_process	*p;

	p = (*job)->first_process;
	while (p)
	{
		if (p->pid == pid)
		{
			p->status = status;
			if (WIFSTOPPED(status))
				p->stopped = 1;
			else if (WIFEXITED(status) && !WEXITSTATUS(status))
				p->completed = 1;
			else if (WIFSIGNALED(status))
				p->completed = 1;
			return (1);
		}
		p = p->next;
	}
	return (0);
}

int		mark_job_as_stopped(t_job **job)
{
	t_process	*p;

	p = (*job)->first_process;
	while (p)
	{
		p->stopped = 1;
		p = p->next;
	}
	return (1);
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
			else if (WIFEXITED(p->status) && !WEXITSTATUS(p->status))
				p->completed = 1;
			else if (WIFSIGNALED(p->status))
			{
				p->completed = 1;
				break ;
			}
			p = p->next;
		}
		return (0);
	}
	else
		return (ft_errormsg("42sh:", NULL, "Job doesn't exist"));
}
