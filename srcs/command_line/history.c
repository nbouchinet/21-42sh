/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 15:56:18 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/10 22:30:17 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		his_del(t_his **his, int mode)
{
	t_his	*tmp;
	t_his	*save;

	tmp = *his;
	if (!tmp)
		return ;
	mode ? tmp = tmp->n : 0;
	while (tmp)
	{
		save = tmp->n;
		free(tmp->cmdl);
		free(tmp);
		tmp = save;
	}
	if (mode)
		(*his)->n = NULL;
	else
		(*his) = NULL;
}

static void	head_smasher(t_his **head)
{
	t_his	*tmp;

	tmp = *head;
	while (tmp->n)
		tmp = tmp->n;
	ft_strdel(&tmp->cmdl);
	tmp->p->n = NULL;
	free(tmp);
	tmp = NULL;
}

void		cmd_save_history(char *str)
{
	t_his	*head;
	t_his	*new;

	head = *his_slg();
	if (!str[0] || bang(str))
		return ;
	if (!(new = (t_his *)malloc(sizeof(t_his))))
		exit(0);
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
	if (his_len(his_slg()) - 2 > 500)
		head_smasher(his_slg());
}

static void	print_cmdl(t_cmdl *cmdl, t_his *his)
{
	int		pos;

	pos = cmdl->line.cur - cmdl->line.pr;
	while (pos--)
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	while ((int)ft_strlen(his->cmdl) >= (cmdl->line.len - 1))
		remalloc_cmdl(&cmdl->line);
	cmdl->line.str = ft_strcpy(cmdl->line.str, his->cmdl);
	write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
	cmdl->line.cur = ft_strlen(his->cmdl) + cmdl->line.pr;
}

int			cmd_history(t_cmdl *cmdl)
{
	t_his			*his;
	static t_his	*match = NULL;

	if (cmdl->opt & (CCMODE | CCP))
		return (write(1, "\7", 1));
	if (cmdl->opt & CCOMP)
		return (UP(cmdl->line.buf) ? c_arrow_up(&cmdl->comp) :
				c_arrow_down(&cmdl->comp));
	if (cmdl->opt & CHIS_S)
		return (return_cmdl(cmdl));
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
		return (write(1, "\7", 1));
	match = his;
	print_cmdl(cmdl, his);
	return (1);
}
