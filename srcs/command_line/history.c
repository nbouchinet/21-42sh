/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 15:56:18 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/11 09:40:00 by zadrien          ###   ########.fr       */
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
		ft_strdel(&tmp->cmdl);
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
	ft_streplace(&new->cmdl, '\n', ' ');
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

static int	print_cmdl(t_cmdl *cmdl, t_his *his)
{
	int		his_len;

	his_len = ft_strlen(his->cmdl);
	home(cmdl);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	while (his_len >= (cmdl->line.len - 1))
		remalloc_cmdl(&cmdl->line);
	ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
	cmdl->line.str = ft_strcpy(cmdl->line.str, his->cmdl);
	cmdl->line.cur = write(1, cmdl->line.str, his_len)
	+ cmdl->line.pr;
	return (1);
}

int			cmd_history(t_cmdl *cmdl)
{
	t_his			*his;
	static t_his	*match = NULL;

	if (cmdl->opt & (CCMODE | CCP))
		return (write(2, "\7", 1));
	if (cmdl->opt & CCOMP)
	{
		if (UP(cmdl->line.buf))
			return (c_arrow_up(&cmdl->comp));
		else if ((DOWN(cmdl->line.buf)) || (S_TAB(cmdl->line.buf)))
			return (c_arrow_down(&cmdl->comp));
	}
	if (cmdl->opt & CHIS_S)
		return (return_cmdl(cmdl));
	if (cmdl->opt & CRESET && !(match = NULL))
		return (1);
	his = !match ? *his_slg() : match;
	if (UP(cmdl->line.buf) && his->n)
		his = his->n;
	else if (DOWN(cmdl->line.buf) && his->p)
		his = his->p;
	else
		return (write(2, "\7", 1));
	match = his;
	return (print_cmdl(cmdl, his));
}
