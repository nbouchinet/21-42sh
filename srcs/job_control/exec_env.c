/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 00:34:41 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 14:45:53 by zadrien          ###   ########.fr       */
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
			complete_node(&tmp, (var = ft_strsplit(tmp_a->str, '=')), 1);
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
	if (ast)
	{
		tmp = *ast;
		while (tmp)
		{
			if (test(tmp->str))
				change_env(env, ft_strsplit(tmp->str, '='));
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
		ft_freetab(var);
	}
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		if (!(node = (t_env*)malloc(sizeof(t_env))))
			return ;
		complete_node(&node, var, 1);
		tmp->next = node;
		tmp = tmp->next;
	}
}

void	complete_node(t_env **node, char **env, int mod)
{
	(*node)->var = ft_strdup(env[0]);
	(*node)->value = env[1] ? ft_strdup(env[1]) : NULL;
	(*node)->next = NULL;
	if (mod)
		ft_freetab(env);
}

int		exec_env(t_ast **ast, t_env **env, t_env **r_env)
{
	int		i;
	t_tok	*tok;
	t_ast	*tmp;
	t_ast	*new_ast;
	char	*cmd;

	i = 0;
	tmp = *ast;
	if ((cmd = recreat_cmd(&tmp)))
	{
		tok = init_tok(&tok, C);
		new_parser(&tok, cmd, 0);
		ft_strdel(&cmd);
		init_ast(&new_ast, NULL, 0);
		primary_sequence(&new_ast, &tok);
		delete_lst(&tok);
		if ((i = check_type_bin(&(new_ast)->left, r_env)) == 1)
		{
			new_ast->left->left->type = CMD_NAME_ABS;
			i = job_ast(&new_ast, env, 1);
		}
		print_error(i, new_ast->left->left->str);
		destroy_ast(&new_ast);
	}
	return (i);
}
