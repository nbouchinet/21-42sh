/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_finders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 15:48:12 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/30 19:22:58 by zadrien          ###   ########.fr       */
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

int		abs_cmd(t_ast **ast, t_env **env)
{
	char	**arg;
	char	**t_env;
	t_ast	*tmp;

	tmp = *ast;
	if (find_bin(&tmp->left->left) == 1)
	{
		arg = creat_arg(&tmp->left->right, tmp->left->left->str);
		t_env = get_env(env, tmp->left->left->str);
		execution(arg, t_env, &tmp->right);
	}
	else
		ft_errormsg("21sh: ", (*ast)->left->left->str, ": Command not found.");
	return (0);
}

int		rlt_cmd(t_ast **ast, t_env **env)
{
	t_env	*e_n;
	char	**arg;
	char	**t_env;
	t_ast	*tmp;

	tmp = *ast;
	if (!(e_n = find_node(env, "PATH", NULL)))
		ft_errormsg("21sh:", NULL, "PATH not set.");
	else if (find_cmd_bin(&tmp->left->left, ft_strsplit(e_n->value, ':')) == 1)
	{
		arg = creat_arg(&tmp->left->right, tmp->left->left->str);
		t_env = env ?
			get_env(env, (ft_strrchr(tmp->left->left->str, '/') + 1)) : NULL;
		execution(arg, t_env, &tmp->right);
	}
	else
		ft_errormsg("21sh: ", tmp->left->left->str, ": Command not found.");
	return (0);
}
