/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 12:42:25 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/11 14:44:22 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_var(t_env **env, char *var, char *value)
{
	t_env	*tmp;

	tmp = *env;
	if (var)
	{
		tmp->var = ft_strdup(var);
		if (value)
			tmp->value = ft_strdup(value);
		else
			tmp->value = NULL;
	}
}

void	replace_value(t_env **node, char *str)
{
	if ((*node)->value)
		ft_strdel(&(*node)->value);
	(*node)->value = str ? ft_strdup(str) : NULL;
}

void	add_env(t_env **env, char **arg)
{
	t_env	*tmp;

	if ((tmp = find_node(env, arg[0], NULL)))
		replace_value(&tmp, arg[1]);
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_env*)malloc(sizeof(t_env))))
			return ;
		tmp = tmp->next;
		add_var(&tmp, arg[0], arg[1]);
		tmp->next = NULL;
	}
}

int		ft_setenv(t_ast **ast, t_env **env)
{
	int		i;
	char	**arg;

	arg = NULL;
	(*ast)->right ? io_seq(&(*ast)->right->right, 1) : 0;
	arg = creat_arg_env(&(*ast)->left->right);
	if ((i = countab(arg)) == 1 || i == 2)
	{
		if (ft_strchr(arg[0], '='))
		{
			ft_errormsg("42sh: ", "setenv: ",
				"Variable name must contain alphanumeric characters.");
			arg ? ft_freetab(arg) : 0;
			return (0);
		}
		add_env(env, arg);
		arg ? ft_freetab(arg) : 0;
		return (1);
	}
	else if (i > 2)
		ft_errormsg("42sh: ", "setenv: ", "Too many arguments.");
	else if (i == 0)
		print_env(*env);
	arg ? ft_freetab(arg) : 0;
	return (0);
}
