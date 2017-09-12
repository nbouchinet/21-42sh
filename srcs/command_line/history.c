/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 15:56:18 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 09:20:20 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void 		cmd_save_history(char *str)
{
	t_his	*head;
	t_his	*new;

	head = *his_slg();
	if (!str[0] /*|| is_bang(&str, -1, -1, -1)*/)
		return ;
	if (!(new = (t_his *)malloc(sizeof(t_his))))
		exit (0);
	new->cmdl = ft_strdup(str);
	if (!head->n)
	{
		head->n = new;
		new->n = NULL;
		new->p = head;
		return ;
	}
	new->n = head->n;
	head->n->p = new;
	new->p = head;
	head->n = new;
}

static void print_cmdl(t_cmdl *cmdl, t_his *his)
{
	int		pos;

	pos = cmdl->line.cur - cmdl->line.pr;
	while (pos--)
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	while ((int)ft_strlen(his->cmdl) > cmdl->line.len)
		remalloc_cmdl(&cmdl->line, ft_strlen(cmdl->line.str));
	cmdl->line.str = ft_strcpy(cmdl->line.str, his->cmdl);
	write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
	cmdl->line.cur = ft_strlen(his->cmdl) + cmdl->line.pr;
}

int			cmd_history(t_cmdl *cmdl)
{
	t_his			*his;
	static t_his	*match = NULL;

	if (cmdl->opt & CHIS_S)
		return (1);
	if (cmdl->opt & CRESET)
	{
		match = NULL;
		return (1);
	}
	his = !match ? *his_slg() : match;
	if (UP(cmdl->line.buf) && his->n)
		his = his->n;
	else if (DOWN(cmdl->line.buf) && his->p)
		his = his->p;
	else
		return (beep());
	match = his;
	print_cmdl(cmdl, his);
	return (1);
}
