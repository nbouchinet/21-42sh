/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 14:52:17 by zadrien           #+#    #+#             */
/*   Updated: 2017/07/09 15:27:46 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		hashing(t_ast **ast, t_env **env)
{
	(void)(*env);
	return (hash(ast, PRINT));
}

int		find_search(t_ast **ast, t_hash **table)
{
	if (search(ast, table, 1) == 1)
		return (1);
	return (0);
}

int		init_hash(t_hash **lst, char *cmd)
{
	if (!((*lst) = (t_hash*)malloc(sizeof(t_hash))))
		return (0);
	(*lst)->abs_key = hash_cmd(cmd);
	(*lst)->rlt_key = hash_cmd(ft_strrchr(cmd, '/') + 1);
	(*lst)->hits = 1;
	(*lst)->path = ft_strdup(cmd);
	(*lst)->next = NULL;
	return (1);
}

int		count_opt(t_ast **ast)
{
	int		i;
	t_ast *tmp;

	i = 0;
	if (*ast)
	{
		tmp = *ast;
		while (tmp)
		{
			i++;
			tmp = tmp->right;
		}
	}
	return (i);
}

int		check_opt(char *opt)
{
	if (ft_strcmp(opt, "-c") == 0)
		return (1);
	else if (ft_strcmp(opt, "-r") == 0)
		return (2);
	return (0);
}
