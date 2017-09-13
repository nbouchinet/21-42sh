/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_finders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 10:21:33 by nbouchin          #+#    #+#             */
/*   Updated: 2017/09/13 15:26:31 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_env	*find_node(t_env **env, char *var, char *value)
{
	t_env	*tmp;

	tmp = *env;
	if (var != NULL)
		while (tmp && ft_strcmp(tmp->var, var) != 0)
			tmp = tmp->next;
	else
		while (tmp && ft_strcmp(tmp->value, value) != 0)
			tmp = tmp->next;
	return (tmp);
}

void	execution(char **arg, char **env, t_ast **rdir)
{
	t_ast	*tmp;

	tmp = *rdir;
	if (tmp && tmp->type == IO_SEQ)
		if (io_seq(&tmp->right) != 1)
			exit(EXIT_FAILURE);
	execve(arg[0], arg, env);
	exit(EXIT_SUCCESS);
}

void	abs_cmd(t_ast **ast, t_env **env)
{
	int		i;
	char	**arg;
	char	**t_env;
	t_ast	*tmp;

	tmp = *ast;
	i = hash(&tmp->left->left, NULL, FIND);
	if (i == 0)
		if (find_bin(&tmp->left->left) == 0)
		{
			ft_errormsg("42sh: ", (*ast)->left->left->str
			, ": Command not found.");
			exit(EXIT_FAILURE);
		}
	arg = creat_arg(&tmp->left->right, tmp->left->left->str);
	t_env = get_env(env, tmp->left->left->str);
	execution(arg, t_env, &tmp->right);
}

void	rlt_cmd(t_ast **ast, t_env **env)
{
	int		i;
	t_env	*e_n;
	char	**arg;
	char	**t_env;
	t_ast	*tmp;

	tmp = *ast;
	if (!(e_n = find_node(env, "PATH", NULL)))
		ft_errormsg("21sh:", NULL, "PATH not set.");
	i = hash(&tmp->left->left, NULL, FIND);
	if (i == 0)
		if (find_cmd_bin(&tmp->left->left, ft_strsplit(e_n->value, ':')) == 0)
		{
			ft_errormsg("21sh: ", tmp->left->left->str, ": Command not found.");
			exit(EXIT_FAILURE);
		}
	arg = creat_arg(&tmp->left->right, tmp->left->left->str);
	t_env = env ? get_env(env,
							(ft_strrchr(tmp->left->left->str, '/') + 1)) : NULL;
	execution(arg, t_env, &tmp->right);
}
