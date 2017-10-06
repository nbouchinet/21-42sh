/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 16:48:53 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/13 09:52:48 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_his			*findcmdl(char *str, char buf[], int reset)
{
	static t_his	*match = NULL;
	t_his			*head;

	if (reset)
		return (reset == 1 ? (match = NULL) : (match));
	if (match && ((NEXT(buf)) || (SH(buf))))
		head = NEXT(buf) ? match->p : match->n;
	else
	{
		head = *his_slg();
		if (!head->n && !head->p)
			return (NULL);
		head = head->n;
	}
	while (head)
	{
		if (ft_strstr(head->cmdl, str))
		{
			match = head;
			return (head);
		}
		else
			head = NEXT(buf) ? head->p : head->n;
	}
	return (NULL);
}

static void		print_match(t_cmdl *cmdl, t_his *his, char buf[])
{
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	if (!(SH(buf)) && !(NEXT(buf)))
		ft_printf("%c': %@", buf[0], his->cmdl);
	else
	{
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		ft_printf("': %@", his->cmdl);
	}
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	if (!(SH(buf)) && !(NEXT(buf)))
	{
		(cmdl->line.cur) += 1;
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
	}
}

int				search_history_print(t_cmdl *cmdl, char buf[])
{
	t_his			*his;
	int				pos;
	int				len;

	if (cmdl->opt & (CCMODE | CCOMP))
		return (write(1, "\7", 1));
	pos = cmdl->line.cur - cmdl->line.pr;
	len = ft_strlen(cmdl->line.str);
	if (!(SH(buf)) && !(NEXT(buf)))
	{
		len == cmdl->line.len ? remalloc_cmdl(&cmdl->line) : 0;
		cmdl->line.str = ft_strcat(cmdl->line.str, buf);
	}
	if (cmdl->line.str[0] && (his = findcmdl(cmdl->line.str, buf, 0)))
		print_match(cmdl, his, buf);
	else if (!(SH(buf)) && !(NEXT(buf)))
		cmdl->line.str[len] = 0;
	return (1);
}

int				cmd_search_history(t_cmdl *cmdl)
{
	int		len;

	if (cmdl->opt & (CCMODE | CCOMP | CCP))
		return (write(1, "\7", 1));
	if (cmdl->opt & (CHIS_S))
		return (search_history_print(cmdl, cmdl->line.buf));
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	print_prompt();
	len = cmdl->line.str ? ft_strlen(cmdl->line.str) : 1;
	if (cmdl->line.str)
		ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	ft_putstr("(reverse-i-search)`");
	cmdl->line.cur = 19;
	cmdl->line.pr = 19;
	ft_putstr("': ");
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	cmdl->opt |= CHIS_S;
	return (1);
}
