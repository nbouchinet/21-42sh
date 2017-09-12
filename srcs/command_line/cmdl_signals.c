/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:26:17 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 13:55:31 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void 	handle_ctrlc(t_cmdl *cmdl)
{
	char	*tmp;

	cmdl->opt = 0;
	end(cmdl);
	write(1, "\n", 1);
	print_prompt();
	cmdl->opt |= CRESET;
	if (cmdl->line.save)
	{
		tmp = ft_strdup(cmdl->line.str);
		ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
		while ((int)ft_strlen(cmdl->line.save) > cmdl->line.len)
		remalloc_cmdl(&cmdl->line, ft_strlen(cmdl->line.str));
		cmdl->line.str = ft_strcpy(cmdl->line.str,cmdl->line.save);
		cmdl->line.str = ft_strcat(cmdl->line.str, tmp);
		free(tmp);
	}
	cmd_save_history(cmdl->line.str);
	cmd_history(cmdl);
	cmdl->opt = 0;
	ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
	cmdl->line.save ? ft_strdel(&cmdl->line.save) : 0;
	cmdl->line.cur = 3;
	cmdl->line.pr = 3;
}

static void		sig_handler(int sig, siginfo_t *siginfo, void *context)
{
	t_cmdl		*cmdl;

	(void)siginfo;
	(void)context;
	cmdl = *cmdl_slg();
	if (sig == SIGWINCH)
	{
		tputs(tgetstr("cl", NULL), 1, ft_putchar);
		get_win_data(cmdl);
		print_prompt();
		ft_putstr(cmdl->line.str);
	}
	else if (sig == SIGINT)
		handle_ctrlc(cmdl);
	else if (sig == SIGQUIT)
	{
		del_all(cmdl_slg(), his_slg());
		exit(EXIT_SUCCESS);
	}
}

void 	cmdl_signals(t_cmdl *cmdl)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_sigaction = &sig_handler;
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGWINCH, &sig, NULL) == -1 ||
	    sigaction(SIGINT, &sig, NULL) == -1 ||
	    sigaction(SIGQUIT, &sig, NULL) == -1)
	{
		unset_shell(cmdl);
		exit(fd_printf(2, "signals: sigaction error\n"));
	}
}
