/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 15:52:16 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/13 11:34:39 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		new_abs_cmd(t_ast **ast)
{
	t_ast	*tmp;

	tmp = *ast;
	if (find_bin(&tmp->left) == 1)
		return (1);
	return (ft_errormsg("42sh: ", tmp->left->str, ": Command not found."));
}

int		new_rlt_cmd(t_ast **ast, t_env **env)
{
	int		i;
	t_env	*e_n;
	t_ast	*tmp;
	char	**path;

	i = 0;
	tmp = *ast;
	path = NULL;
	e_n = find_node(env, "PATH", NULL);
	if ((i = hash(&tmp->left, NULL, FIND)) == 0)
	{
		if (e_n && find_cmd_bin(&tmp->left,
				(path = ft_strsplit(e_n->value, ':'))) == 0)
		{
			ft_freetab(path);
			return (ft_errormsg("42sh: ",
			tmp->left->str, ": Command not found."));
		}
	}
	if (i == 0 && e_n == NULL)
		return (ft_errormsg("42sh:", NULL, "PATH not set."));
	path ? ft_freetab(path) : 0;
	return (1);
}

int		rlt_ou_abs(t_ast **ast, t_env **env)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp->left->type == CMD_NAME_ABS)
		return (new_abs_cmd(&tmp));
	else
		return (new_rlt_cmd(&tmp, env));
}

char	**creat_arg_process(t_ast **ast, t_env **env)
{
	char	**argv;
	t_ast	*tmp;

	tmp = *ast;
	argv = NULL;
	if (rlt_ou_abs(ast, env) == 1)
		argv = creat_arg(&tmp->right, tmp->left->str);
	return (argv);
}
