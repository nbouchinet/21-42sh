/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:26:17 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/10 18:53:37 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		sig_handler(int sig, siginfo_t *siginfo, void *context)
{
	t_cmdl		*cmdl;
	int			save;

	(void)siginfo;
	(void)context;
	cmdl = *cmdl_slg();
	save = cmdl->line.cur;
	if (sig == SIGWINCH)
		resize_win(cmdl, save);
	else if (sig == SIGINT)
		handle_ctrlc(cmdl);
	else if (sig == SIGQUIT)
		;
}

void			cmdl_signals(t_cmdl *cmdl)
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
		exit(fd_printf(2, "cmdl_signals: sigaction error\n"));
	}
}
