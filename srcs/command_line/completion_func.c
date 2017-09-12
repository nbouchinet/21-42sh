/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 14:47:22 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 09:06:19 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void insert(t_comp **comp, t_comp *lnk, int i)
{
	t_comp	*tmp;
	t_comp	*save;

	tmp = *comp;
	if (!i)
	{
		lnk->n = tmp;
		*comp = lnk;
	}
	else
	{
		while (i-- > 1)
			tmp = tmp->n;
		save = tmp->n;
		tmp->n = lnk;
		lnk->n = save;
	}
}

t_comp 		*fill_comp(t_comp **comp, struct dirent *rdd, int param)
{
	t_comp	*tmp;
	t_comp	*stock;
	int		i;

	i = 0;
	if (!(tmp = (t_comp *)malloc(sizeof(t_comp))))
	{
		del_all(cmdl_slg(), his_slg());
		exit(0);
	}
	tmp->str = (param == 2 && rdd->d_type == 4 ?
	            ft_strjoin(rdd->d_name, "/") : ft_strdup(rdd->d_name));
	ft_memset(tmp->pad, 0, 512);
	tmp->n = NULL;
	if (!(*comp))
		return (tmp);
	stock = *comp;
	while (stock && ft_strcmp(stock->str, rdd->d_name) < 0)
	{
		i++;
		stock = stock->n;
	}
	insert(comp, tmp, i);
	return (tmp);
}

int		is_exec(t_cmdl *cmdl)
{
	int		pos;

	pos = cmdl->line.cur - cmdl->line.pr;
	while (--pos && cmdl->line.str[pos] == ' ')
		;
	while (pos && ft_isalnum(cmdl->line.str[pos]))
		pos--;
	while (pos && cmdl->line.str[pos] == ' ')
		pos--;
	if (cmdl->line.str[pos] == ';' || pos == 0 || cmdl->line.str[pos] == '|' ||
	(cmdl->line.str[pos] == '&' && pos > 0 && cmdl->line.str[pos - 1] == '&'))
		return (1);
	return (0);
}

char	*get_path(char **tmp)
{
	char		*path;
	char		*temp;
	int			i;
	int			save;

	save = 0;
	i = -1;
	while ((*tmp)[++i])
		if ((*tmp)[i] == '/')
			save = i;
	if ((*tmp)[save] == '/')
	{
		path = ft_strsub((*tmp), 0, save + 1);
		temp = (*tmp);
		if ((*tmp)[save + 1])
			(*tmp) = ft_strsub((*tmp), save + 1, ft_strlen((*tmp) + save));
		else
			(*tmp) = NULL;
		free(temp);
	}
	else
		path = ft_strdup(".");
	return (path);
}

int		sep(t_cmdl *cmdl, int w)
{
	if (!w)
	{
		if (cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != '|' &&
	 	cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != ';' &&
		cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != '&' &&
		cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != '<' &&
		cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != '>' &&
		cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != ' ')
			return (1);
	}
	return (0);
}
