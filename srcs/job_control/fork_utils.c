/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 22:06:27 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/18 11:18:22 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_fork(pid_t *pgid, int fg)
{
	signal (SIGINT, SIG_DFL);
	signal (SIGQUIT, SIG_DFL);
	signal (SIGTSTP, SIG_DFL);
	signal (SIGTTIN, SIG_DFL);
	signal (SIGTTOU, SIG_DFL);
	signal (SIGCHLD, SIG_DFL);
	setpgid(getpid(), *pgid == 0 ? getpid() : *pgid);
	if (fg)
		tcsetpgrp(g_shell_terminal, getpid());
}

void	init_father(pid_t *pid, pid_t *pgid, int fg)
{
	*pgid == 0 ? (*pgid = *pid) : 0;
	setpgid(*pid, *pgid);
	if (fg)
		tcsetpgrp(g_shell_terminal, *pgid);
}

void	set_pgid(pid_t pid, pid_t *pgid, int foreground)
{
	setpgid(pid, *pgid);
	if (foreground)
	tcsetpgrp(g_shell_terminal, pid);
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

	setpgid((pid = getpid()), pgid);
	if (foreground)
		tcsetpgrp(g_shell_terminal, pid);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
}

void	exec_fork(t_process **process, char **env, int r)
{
	t_process	*p;

	p = *process;
	r != -1 ? dup2(r, STDIN_FILENO) : 0;
	if (p->rdir && !io_seq(&p->rdir, 0))
		exit(EXIT_FAILURE);
	if (p->builtin && !pipe_builtin(&p->builtin, &p->env, 1))
		exit(EXIT_FAILURE);
	else if (p->argv)
		execve(p->argv[0], p->argv, env);
	exit(EXIT_SUCCESS);
}

// void	sig_ign(pid_t pid, int fg)
// {
// 	if (fg)
// 		tcsetpgrp(g_shell_terminal, pid);
// 	signal(SIGTSTP, SIG_DFL);
// 	signal(SIGCHLD, SIG_IGN);
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGTTIN, SIG_IGN);
// 	signal(SIGTTOU, SIG_IGN);
// }
