/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_func2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:11:02 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/01 13:11:10 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_ls            *ft_padd_x(t_ls *ls, int *maxlen)
{
    t_ls    *tmp;
    int     save;

    tmp = ls;
    (*maxlen) = 0;
    if (tmp)
    {
        while (tmp)
        {
            save = ft_strlen(tmp->name);
            if (save > (*maxlen))
                (*maxlen) = save;
            tmp = tmp->next;
        }
    }
    (*maxlen) += 5;
    return (ft_putpaddx(ls, (*maxlen)));
}

void				print_lst(t_ls **head, t_win **win, char *cmd, int len)
{
	unsigned long	winsize;
	t_ls			*tmp;

	tmp = (*head);
	ft_padd_x(*head, &len);
	winsize = (*win)->co - len - 5;
	while (tmp)
	{
		len += ft_printf("%s", tmp->name);
		if ((len + ft_strlen(tmp->padx) < winsize))
			len += ft_printf("%s", tmp->padx);
		else
			tmp->next ? ft_printf("%n\n", &len) : 0;
		tmp = tmp->next;
	}
	write(1, "\n", 1);
	if ((*win)->pr == 3)
		print_prompt();
	else if ((*win)->hd)
		write(1, "heredoc> ", ft_strlen("heredoc> "));
	else if ((*win)->quote)
		write(1, (*win)->quote == 1 ? "quote> " : "dquote> ",
	(*win)->quote == 1 ? ft_strlen("quote> ") : ft_strlen("dquote> "));
	write(1, cmd, ft_strlen(cmd));
}

int 		list_len(t_ls **list)
{
	int			len;
	t_ls		*tmp;

	len = 0;
	tmp = *list;
	if (tmp)
	{
		len = 1;
		while (tmp->next)
		{
			len += 1;
			tmp = tmp->next;
		}
		return (len);
	}
	return (0);
}

void		list_del(t_ls **list)
{
	t_ls		*tmp;
	t_ls		*save;

	tmp = *list;
	while (tmp)
	{
		save = tmp->next;
		tmp->name ? free(tmp->name) : 0;
		free(tmp);
		tmp = save;
	}
	*list = NULL;
}
