/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_cmdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 21:25:17 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/15 13:01:32 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ppa_err(t_cmdl *cmdl, int *i)
{
	*i -= (*i > 0 && cmdl->line.str[*i - 1] == cmdl->line.str[*i]) ? 1 : 0;
	if (cmdl->line.str[*i - 1] == '|' || cmdl->line.str[*i - 1] == '&')
	{
		cmd_save_history(cmdl->line.str);
		fd_printf(2, "\n42sh: syntax error near unexpected token `");
		write(2, cmdl->line.str + *i,
			cmdl->line.str[*i + 1] == cmdl->line.str[*i] ? 2 : 1);
		write(2, "\'", 1);
		ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
		cmdl->line.save ? ft_strdel(&cmdl->line.save) : 0;
		init_cmdl();
		return (1);
	}
	return (0);
}

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
	write(2, "\033[1mBye\033[0m\n", 12);
	return (0);
}

int		his_len(t_his **his)
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
