/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:32:50 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 19:09:51 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	process_mod(t_bang *bang, char *ptr)
{
	char	**arr;
	int		i;

	bang->mod & HB && (ptr = ft_strrchr(bang->tmp, '/')) ?
	*ptr = 0 : 0;
	bang->mod & RB && (ptr = ft_strchr(bang->tmp, '.')) ?
	*ptr = 0 : 0;
	bang->mod & QB ? (bang->tmp) = ft_strjoinf(ft_strjoinf("\'", bang->tmp, 2),
	"\'", 1) : 0;
	bang->mod & PB ? ft_printf("\n%s", bang->tmp) : 0;
	if (bang->mod & TB && (ptr = ft_strrchr(bang->tmp, '/')) && *(ptr + 1))
		bang->tmp = ft_strdups(ptr + 1, &bang->tmp);
	if (bang->mod & EB && (ptr = ft_strchr(bang->tmp, '.')))
		bang->tmp = ft_strdups(ptr, &bang->tmp);
	if (bang->mod & XB && (arr = ft_strsplit(bang->tmp, ' ')))
	{
		i = -1;
		ft_strdel(&bang->tmp);
		while (arr[++i])
		{
			arr[i] = ft_strjoinf(ft_strjoinf("\'", arr[i], 2), "\'", 1);
			bang->tmp = ft_strjoinf(ft_strjoinf(bang->tmp, arr[i], 1), " ", 1);
		}
		ft_free(arr, NULL, 1);
	}
}

static void	process_des_and_mod(t_bang *bang, char *match[])
{
	if (bang->mod & 128)
	{
		if (bang->des == -1 && bang->x == -1 && bang->y == -1)
			bang->tmp = ft_strdups(match[0], &bang->tmp);
		else if (bang->des != -1 && bang->x == -1 && bang->y == -1)
			bang->tmp = ft_strdups(match[bang->des], &bang->tmp);
		else if (bang->x != -1 && bang->y != -1 && bang->des == -1)
		{
			ft_strdel(&bang->tmp);
			while (bang->x <= bang->y)
				bang->tmp = ft_strjoinf(ft_strjoinf(bang->tmp, match[bang->x++],
				1), " ", 1);
		}
	}
	if (bang->mod && bang->mod & (HB | TB | RB | EB | PB | QB | XB))
		process_mod(bang, NULL);
}

int			get_match(t_his *his, t_bang *bang)
{
	if (bang->string)
		while (his)
		{
			if (bang->qm ? ft_strnstr(his->cmdl, bang->string,
			ft_strlen(his->cmdl)) : ft_strstr(his->cmdl, bang->string))
			{
				bang->tmp = ft_strdup(his->cmdl);
				break ;
			}
			his = his->n;
		}
	else
		bang->tmp = ft_strdup(his->cmdl);
	return (bang->tmp ? 0 : fd_printf(2, "\n42sh: !%s: event not found",
	bang->string));
}

int			get_line(t_his *his, t_bang *bang)
{
	int		tmp;

	tmp = bang->n;
	if (tmp > 0)
	{
		while (his->n)
			his = his->n;
		while (his->p && tmp > 1)
		{
			his = his->p;
			tmp--;
		}
	}
	else
		while (his->n && tmp < -1)
		{
			his = his->n;
			tmp++;
		}
	bang->tmp = ft_strdup(his->cmdl);
	return (bang->tmp ? 0 : 1);
}

int			bang_sub(t_bang *bang)
{
	char	**match;

	match = ft_strsplit(bang->tmp, ' ');
	if (!bang->s1)
		process_des_and_mod(bang, match);
	ft_free(match, NULL, 1);
	return (0);
}
