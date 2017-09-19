/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 14:49:10 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/18 16:24:43 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		builtin_env(t_ast **ast, t_env **env)
{
	int		flag;
	t_ast	*tmp;
	t_env	*n_env;

	n_env = NULL;
	tmp = *ast;
	flag = 0;
	tmp = env_option(&tmp->left->right, &flag);
	if (flag != -1)
	{
		tmp = new_env(&n_env, &tmp, env, flag);
		if (env_builtin(&tmp, &n_env, env) == 1)
		{
			n_env ? delete_lstenv(&n_env) : 0;
			return (1);
		}
		n_env ? delete_lstenv(&n_env) : 0;
	}
	return (0);
}

int		env_builtin(t_ast **ast, t_env **env, t_env **r_env)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp)
		return (exec_env(&tmp, env, r_env));
	if (env)
		print_env(*env);
	return (1);
}

t_ast	*new_env(t_env **n_env, t_ast **ast, t_env **env, int flag)
{
	t_env	*tmp;
	t_env	*tmp_n;

	if (!(flag & LOW_I_FLAG))
		if (*env)
		{
			tmp = *env;
			if (!((*n_env) = (t_env*)malloc(sizeof(t_env))))
				return (NULL);
			(*n_env)->next = NULL;
			tmp_n = *n_env;
			while (tmp)
			{
				if ((flag & LOW_U_FLAG))
					if ((*ast))
						if (!ft_strcmp((*ast)->str, tmp->var))
							tmp = tmp->next;
				tmp_n->var = ft_strdup(tmp->var);
				tmp_n->value = ft_strdup(tmp->value);
				if (tmp->next)
					tmp_n = next_node(&tmp_n);
				tmp = tmp->next;
			}
			tmp_n->next = NULL;
		}
	return (complete_env(n_env, (flag & LOW_U_FLAG) ? &(*ast)->right : ast));
}

t_ast	*complete_env(t_env **env, t_ast **ast)
{
	if (!*env)
		return (env_without(env, ast));
	else
		return (env_w(env, ast));
	return (NULL);
}
