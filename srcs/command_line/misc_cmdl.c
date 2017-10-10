/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_cmdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 21:25:17 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 22:30:22 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	shell_sig(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGWINCH, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	g_shell_pgid = getpid();
	if (setpgid(g_shell_pgid, g_shell_pgid) < 0)
		exit(1);
	tcsetpgrp(g_shell_terminal, g_shell_pgid);
	tcgetattr(g_shell_terminal, &g_shell_tmodes);
	tputs(tgetstr("nam", NULL), 1, ft_putchar);
}

int		unset_shell(t_cmdl *cmdl)
{
	if (mode_off(cmdl))
		return (1);
	tputs(tgetstr("am", NULL), 1, ft_putchar);
	hist_add(his_slg());
	del_all(cmdl_slg(), his_slg(), local_slg(0));
	write(1, "\nBye\n", 5);
	return (0);
}

int			his_len(t_his **his)
{
	t_his	*tmp;
	int		len;

	tmp = (*his);
	len = 1;
	while (tmp)
	{
		len++;
		tmp = tmp->n;
	}
	return (len);
}
