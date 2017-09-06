/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 12:26:01 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/05 17:53:20 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		hash_cmd(char *cmd)
{
	int		i;
	int		key;

	i = -1;
	key = 0;
	while (cmd[++i])
		key += cmd[i];
	return (key);
}

int		search(t_ast **ast, t_hash **table, int i)
{
	int		key;
	t_hash	*tmp;
	t_ast	*tmp_a;

	tmp_a = i == 1 ? (*ast) : (*ast)->left;
	key = hash_cmd(tmp_a->str);
	if (*table)
	{
		tmp = *table;
		while (tmp)
		{
			if (tmp->rlt_key == key || tmp->abs_key == key)
			{
				if (tmp_a->type == CMD_NAME_RLT ?
					(!ft_strcmp(tmp_a->str, tmp->path)) :
					(!ft_strcmp(tmp_a->str, ft_strrchr(tmp->path, '/'))))
				{
					tmp_a->str = ft_strdups(tmp->path, &tmp_a->str);
					tmp->hits++;
					if (isexec(tmp_a->str) == 1)
						return (1);
					return (0);
				}
			}
			tmp = tmp->next;
		}
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
// int		put_cmd(t_ast **ast, t_job **job, t_hash **table)
// {
// 	t_hash	*curr;
// 	t_hash	*tmp;
//
// 	if (search(ast, table, 0) == 1)
// 		return (1);
// 	if (init_hash(&curr, (*ast)->left->str) == 0)
// 		return (0);
// 	if (*table == NULL)
// 		*table = curr;
// 	else
// 	{
// 		tmp = *table;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = curr;
// 	}
// 	return (1);
// }


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
	static const t_mod  state[3] = {{FIND, &find_search}, {PUT, &put_cmd},
									{BUILTIN, &builtin_hash}};
	i = -1;
	while (++i < 3)
		if (state[i].mod == mod)
			if (state[i].f(ast, job, &table) == 1)
				return (1);
	return (0);
}
