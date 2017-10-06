/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 22:06:27 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/06 17:08:45 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	set_pgid(pid_t pid, pid_t *pgid, int foreground)
{
	*pgid == 0 ? (*pgid = pid) : 0;
	setpgid(pid, *pgid);
	if (foreground)
		tcsetpgrp(g_shell_terminal, *pgid);
}

void	set_pid(pid_t pid, pid_t *pgid, int foreground)
{
	*pgid = pid;
	setpgid(pid, *pgid);
	if (foreground)
		tcsetpgrp(g_shell_terminal, *pgid);
}

void	active_sig(pid_t pid, pid_t pgid, int foreground)
{
	setpgid(getpid(), pgid == 0 ? getpid() : pgid);
	if (foreground)
		tcsetpgrp(g_shell_terminal, pgid == 0 ? pid : pgid);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
}
