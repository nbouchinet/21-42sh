/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:07:08 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/01 13:07:20 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int 		is_first_word(char *cmd, int i)
{
	while (--i && cmd[i] == ' ')
		;
	if (cmd[i] == ';' || i == 0 || cmd[i] == '|' ||
	(cmd[i] == '&' && i > 0 && cmd[i - 1] == '&'))
		return (1);
	return (0);
}

static void		insert(t_ls **head, t_ls *link, int i)
{
	t_ls		*tmp;
	t_ls		*save;

	tmp = *head;
	if (i == 0)
	{
		link->next = tmp;
		*head = link;
	}
	else
	{
		while (i-- > 1)
			tmp = tmp->next;
		save = tmp->next;
		tmp->next = link;
		link->next = save;
	}
}

t_ls			*fill_lst(t_ls **head, struct dirent *rdd, int param)
{
	t_ls		*tmp;
	t_ls		*stock;
	int			i;

	i = 0;
	if (!(tmp = (t_ls *)malloc(sizeof(t_ls))))
		exit(fd_printf(2, "malloc error\n"));
	tmp->name = (param == 2 && rdd->d_type == 4 ?
	ft_strjoin(rdd->d_name, "/") : ft_strdup(rdd->d_name));
	tmp->next = NULL;
	if (!(*head))
		return (tmp);
	else
	{
		stock = *head;
		while (stock && ft_strcmp(stock->name, rdd->d_name) < 0)
		{
			i++;
			stock = stock->next;
		}
		insert(head, tmp, i);
		return (tmp);
	}
}

void			ft_putpaddx(t_ls **ls, int maxlen)
{
    int			i;
    int			save;
    t_ls		*tmp;

    tmp = *ls;
    while (tmp)
    {
        i = 0;
        save = ft_strlen(tmp->name);
        while (i < maxlen - save)
        {
            tmp->padx[i] = ' ';
            i += 1;
        }
        tmp->padx[i] = 0;
        tmp = tmp->next;
    }
}