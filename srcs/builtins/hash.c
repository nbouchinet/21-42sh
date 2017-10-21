/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 12:26:01 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/21 19:13:08 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		search(t_ast **ast, t_hash **table, int i)
{
	int		key;
	t_hash	*tmp;
	t_ast	*tmp_a;
	t_env	*env;

	tmp_a = i == 1 ? (*ast) : (*ast)->left;
	if (!(env = find_node(&(*(cmdl_slg()))->lstenv, "PATH", NULL)))
		return (0);
	if (!env->value)
		return (0);
	key = hash_cmd(tmp_a->str);
	if ((tmp = *table))
		while (tmp)
		{
			if (tmp->rlt_key == key || tmp->abs_key == key)
				if (!ft_strcmp(tmp_a->str, ft_strrchr(tmp->path, '/') + 1))
				{
					tmp_a->str = ft_strdups(tmp->path, &tmp_a->str);
					if (check_abs_bin(tmp_a->str))
						return (1);
					return (0);
				}
			tmp = tmp->next;
		}
	return (0);
}

int		find_table(t_job **job, t_hash **table)
{
	int			key;
	t_hash		*tmp;
	t_process	*p;

	if (*table)
	{
		tmp = *table;
		p = (*job)->first_process;
		key = hash_cmd(p->argv[0]);
		while (tmp)
		{
			if (tmp->abs_key == key)
				if (!ft_strcmp(p->argv[0], tmp->path))
				{
					tmp->hits++;
					return (1);
				}
			tmp = tmp->next;
		}
	}
	return (0);
}

int		put_cmd(t_ast **ast, t_job **job, t_hash **table)
{
	t_hash	*curr;
	t_hash	*tmp;

	(void)ast;
	if (find_table(job, table))
		return (1);
	if (init_hash(&curr, (*job)->first_process->argv[0]))
	{
		if (*table == NULL)
			*table = curr;
		else
		{
			tmp = *table;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = curr;
		}
		return (1);
	}
	return (0);
}

int		search_mod(t_ast **ast, t_hash **table)
{
	if (search(ast, table, 1) == 1)
		return (1);
	return (0);
}

int		hash(t_ast **ast, t_job **job, int mod)
{
	int					i;
	static t_hash		*table = NULL;
	static const t_mod	state[4] = {{FIND, &find_search}, {PUT, &put_cmd},
							{BUILTIN, &builtin_hash}, {CLEAN, &clean_table}};

	i = -1;
	while (++i < 4)
		if (state[i].mod == mod)
			if (state[i].f(ast, job, &table) == 1)
				return (1);
	return (0);
}
