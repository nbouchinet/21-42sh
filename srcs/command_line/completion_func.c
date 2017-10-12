/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 14:47:22 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/10 19:03:10 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		insert(t_comp **comp, t_comp *lnk, int i)
{
	t_comp	*tmp;
	t_comp	*save;

	tmp = *comp;
	if (!i)
	{
		lnk->n = tmp;
		lnk->p = NULL;
		tmp->p = lnk;
		*comp = lnk;
	}
	else
	{
		while (i-- > 1)
			tmp = tmp->n;
		save = tmp->n;
		tmp->n = lnk;
		lnk->n = save;
		lnk->p = tmp;
		save ? save->p = lnk : 0;
	}
}

static void escape_string(char **str)
{
	char	*tmp;

	if (!(tmp = ft_strchr((*str), ' ')))
		return ;
	*tmp = 0;
	(*str) = ft_strjoinf((*str), ft_strjoin("\\ ", tmp + 1), 3);
	while ((tmp = ft_strchr(tmp, ' ')))
	{
		*tmp = 0;
		(*str) = ft_strjoinf((*str), ft_strjoin("\\ ", tmp), 3);
	}
}

t_comp		*fill_comp(t_comp **comp, struct dirent *rdd, int param, int i)
{
	t_comp	*tmp;
	t_comp	*stock;

	if (!(tmp = (t_comp *)malloc(sizeof(t_comp))))
	{
		del_all(cmdl_slg(), his_slg(), local_slg(0));
		exit(EXIT_FAILURE);
	}
	tmp->str = (param == 2 && rdd->d_type == 4 ? ft_strjoin(rdd->d_name, "/") :
	ft_strdup(rdd->d_name));
	escape_string(&tmp->str);
	ft_memset(tmp->pad, 0, 512);
	tmp->bol = 0;
	tmp->n = NULL;
	tmp->p = NULL;
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

int			is_exec(t_cmdl *cmdl)
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

char		*get_path(char **tmp)
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

int			sep(t_cmdl *cmdl, int w)
{
	if (!w)
	{
		if (cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != '|' &&
		cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != ';' &&
		cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != '&' &&
		cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != '<' &&
		cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != '>' &&
		cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != ' ' &&
		cmdl->line.str[cmdl->line.cur - cmdl->line.pr] != 0)
			return (1);
	}
	return (0);
}
