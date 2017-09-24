/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 14:51:19 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/20 15:43:34 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_ast	*env_without(t_env **env, t_ast **ast)
{
	t_env	*tmp;
	t_ast	*tmp_a;
	char	**var;

	tmp_a = NULL;
	if ((*ast) && test((*ast)->str))
	{
		if (!(*env = (t_env*)malloc(sizeof(t_env))))
			return (NULL);
		tmp = *env;
		tmp_a = *ast;
		while (tmp_a)
		{
			var = ft_strsplit(tmp_a->str, '=');
			tmp->var = ft_strdup(var[0]);
			tmp->value = var[1] ? ft_strdup(var[1]) : NULL;
			tmp->next = NULL;
			ft_freetab(var);
			if (tmp_a->right && (test(tmp_a->right->str) == 1))
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
	char	**var;

	tmp = NULL;
	if (ast)
	{
		tmp = *ast;
		while (tmp)
		{
			if (test(tmp->str))
			{
				var = ft_strsplit(tmp->str, '=');
				change_env(env, var);
				ft_freetab(var);
			}
			else
				break ;
			tmp = tmp->right;
		}
	}
	return (tmp);
}

void	change_env(t_env **env, char **var)
{
	t_env	*tmp;
	t_env	*node;

	if ((tmp = find_node(env, var[0], NULL)))
	{
		ft_strdel(&tmp->value);
		if (var[1])
			tmp->value = ft_strdup(var[1]);
	}
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		if (!(node = (t_env*)malloc(sizeof(t_env))))
			return ;
		complete_node(&node, var);
		tmp->next = node;
		tmp = tmp->next;
	}
}

void	complete_node(t_env **node, char **env)
{
	(*node)->var = ft_strdup(env[0]);
	(*node)->value = env[1] ? ft_strdup(env[1]) : NULL;
	(*node)->next = NULL;
}

int		exec_env(t_ast **ast, t_env **env, t_env **r_env)
{
	t_tok	*tok;
	t_ast	*tmp;
	t_ast	*new_ast;
	char	*cmd;

	tmp = *ast;
	tok = NULL;
	cmd = recreat_cmd(&tmp);
	if (cmd != NULL)
	{
		tok = init_tok(&tok, C);
		new_parser(&tok, cmd);
		ft_strdel(&cmd);
		init_ast(&new_ast, NULL, 0);
		primary_sequence(&new_ast, &tok);
		delete_lst(&tok);
		if ((new_ast->left->left->type == CMD_NAME_ABS ?
			find_bin(&new_ast->left->left) :
				find_rlt(&new_ast->left->left, r_env)) == 1)
			job_ast(&new_ast, env, 1);
		destroy_ast(&new_ast);
	}
	return (0);
}
