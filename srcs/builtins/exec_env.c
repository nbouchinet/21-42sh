/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 00:34:41 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/18 14:09:49 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_ast	*env_without(t_env **env, t_ast **ast)
{
	t_env	*tmp;
	t_ast	*tmp_a;

	tmp_a = NULL;
	if ((*ast) && test((*ast)->str))
	{
		if (!(*env = (t_env*)malloc(sizeof(t_env))))
			return (NULL);
		tmp = *env;
		tmp_a = *ast;
		while (tmp_a)
		{
			complete_node(&tmp, tmp_a->str);
			if (tmp_a->right && test(tmp_a->right->str))
			{
				tmp_a = tmp_a->right;
				tmp = next_node(&tmp);
			}
			else
				return (tmp_a->right);
		}
	}
	return ((*ast));
}

t_ast	*env_w(t_env **env, t_ast **ast)
{
	t_ast	*tmp;

	tmp = NULL;
	if (*ast)
	{
		tmp = *ast;
		while (tmp)
		{
			if (test(tmp->str))
				change_env(env, tmp->str);
			else
				break ;
			tmp = tmp->right;
		}
		return (tmp);
	}
	return (*ast);
}

void	change_env(t_env **env, char *var)
{
	t_env	*tmp;
	t_env	*node;
	char	*st;

	st = ft_strchr(var, '=');
	st[0] = '\0';
	if ((tmp = find_node(env, var, NULL)))
	{
		tmp->value ? ft_strdel(&tmp->value) : 0;
		tmp->value = st + 1 ? ft_strdup(st + 1) : NULL;
	}
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		if (!(node = (t_env*)malloc(sizeof(t_env))))
			return ;
		node->var = ft_strdup(var);
		node->value = st + 1 ? ft_strdup(st + 1) : NULL;
		node->next = NULL;
		tmp->next = node;
		tmp = tmp->next;
	}
}

void	recreat_ast(t_ast **n_ast, t_ast **ast)
{
	t_ast	*tmp;
	t_ast	*save;

	save = NULL;
	if (*n_ast)
	{
		tmp = *n_ast;
		if (*ast)
		{
			save = *ast;
			init_env_ast(&tmp->left, save->str, ft_strchr(save->str, '/') ?
				CMD_NAME_ABS : CMD_NAME_RLT);
			save = save->right;
			while (save)
			{
				init_env_ast(&tmp->right, save->str, CMD_ARG);
				tmp = tmp->right;
				save = save->right;
			}
		}
	}
}

int		exec_env(t_ast **ast, t_env **env, t_env **r_env)
{
	int		i;
	t_ast	*new_ast;

	i = 0;
	new_ast = NULL;
	init_ast(&new_ast, NULL, CMD_SEQ);
	init_ast(&new_ast->left, NULL, SIMP_CMD);
	recreat_ast(&new_ast->left, ast);
	if ((i = check_type_bin(&new_ast->left, r_env)) == 1)
	{
		new_ast->left->left->type = CMD_NAME_ABS;
		i = job_ast(&new_ast, env, 1);
	}
	print_error_env(i, new_ast->left->left->str);
	new_ast ? destroy_ast(&new_ast) : 0;
	return (i);
}
