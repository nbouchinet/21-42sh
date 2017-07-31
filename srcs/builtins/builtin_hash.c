/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 12:47:39 by zadrien           #+#    #+#             */
/*   Updated: 2017/07/09 15:35:37 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		clear_table(t_hash **table)
{
	t_hash	*tmp;
	t_hash	*save;

	tmp = *table;
	while (tmp)
	{
		save = tmp->next;
		ft_strdel(&tmp->path);
		free(tmp);
		tmp = NULL;
		tmp = save;
	}
	*table = NULL;
	return (1);
}

int		reset_table(t_hash **table)
{
	t_hash *tmp;

	if (*table)
	{
		tmp = *table;
		if (tmp)
			while (tmp)
			{
				tmp->hits = 0;
				tmp = tmp->next;
			}
	}
	return (1);
}

void	print_hash(t_hash **table)
{
	t_hash *tmp;

	if (table)
	{
		tmp = *table;
		if (tmp)
		{
			ft_printf("hits\tcommand\n");
			while (tmp)
			{
				ft_printf("%4d\t%s\n", tmp->hits, tmp->path);
				tmp = tmp->next;
			}
		}
	}
}

int		builtin_hash(t_ast **ast, t_hash **table)
{
	int		i;

	i = count_opt(&(*ast)->left->right);
	if (i == 0)
		print_hash(table);
	else if (i == 1)
	{
		if ((i = check_opt((*ast)->left->right->str)) == 1)
			return (clear_table(table));
		else if (i == 2)
			return (reset_table(table));
		else if (i == 0)
			ft_errormsg("Usage: hash:", "-c = clean table", "-r : reset hits");
	}
	else
	{
		ft_errormsg("usage: hash: ", NULL, " [command]");
		ft_errormsg("21sh: ", "hash: ", "Too many argument.");
	}
	return (1);
}
