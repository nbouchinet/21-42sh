/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 13:58:23 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/11 10:19:05 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		sig_handler(int sig, siginfo_t *siginfo, void *context)
{
	t_cmdl		*cmdl;

	(void)siginfo;
	(void)context;
	cmdl = *cmdl_slg();
	if (sig == SIGINT)
		cmdl->opt = -1;
}

int			hd_signal(t_cmdl *cmdl)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_sigaction = &sig_handler;
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sig, NULL) == -1)
	{
		unset_shell(cmdl);
		exit(fd_printf(2, "cmdl_signals: sigaction error\n"));
	}
	return (1);
}

int				next_hd(t_tok **tok)
{
	t_tok	*tmp;

	tmp = *tok;
	if (tmp)
		while (tmp && tmp->type != BBDIR)
			tmp = tmp->n;
	write(2, "\n", 1);
	return (0);
}

int				hd_loop(t_tok **stop, t_cmdl *cmdl, int p[2], int ret)
{
	int		i;

	init_cmdl();
	while (1)
	{
		if (hd_signal(cmdl) && cmdl->opt == -1)
			return (-1);
		get_op(cmdl, &ret, &i);
		if (ret == 2 && !(ft_strcmp(cmdl->line.str, (*stop)->str)))
			break ;
		else if (ret == 2)
		{
			ft_putendl_fd(cmdl->line.str, p[1]);
			ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
			cmdl->line.pr = write(2, "\nheredoc> ", 10) - 1;
			cmdl->line.cur = 9;
		}
		else if (CTRL_L(cmdl->line.buf))
			ctrl_l(cmdl);
		else if (CTRL_D(cmdl->line.buf) && ctrl_d(cmdl))
			break ;
		else if (i == 23)
			print(cmdl, cmdl->line.buf);
	}
	return (0);
}
