/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 17:13:52 by zadrien           #+#    #+#             */
/*   Updated: 2017/08/03 17:46:56 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	freenode(t_env *node)
{
	ft_strdel(&node->var);
	if (node->value)
		ft_strdel(&node->value);
	free(node);
}

void	deletevar(t_env **tmp, t_env *prev)
{
	prev->next = (*tmp)->next;
	freenode(*tmp);
}

void	deletefirstnode(t_env **lst)
{
	t_env	*tmp;

	tmp = *lst;
	*lst = tmp->next;
	freenode(tmp);
}

void	deletevarenv(t_env **lst, char *var)
{
	t_env	*prev;
	t_env	*tmp;

	prev = NULL;
	tmp = (*lst);
	while (tmp && ft_strcmp(tmp->var, var) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		ft_errormsg("env: ", var, ": Variable not set.");
	else if (!prev)
		deletefirstnode(lst);
	else if (tmp && ft_strcmp(tmp->var, var) == 0)
		deletevar(&tmp, prev);
}

int		countab(char **tob)
{
	int		i;

	i = 0;
	if (tob)
	{
		while (tob[i])
			i++;
	}
	return (i);
}

char **creat_arg_env(t_ast **ast)
{
	int		i;
	int		j;
	char	**arg;
	t_ast	*tmp;

	i = 0;
	tmp = NULL;
	if (!*ast)
		return (NULL);
	tmp = *ast;
	i = count_arg_node(&tmp);
	if (!(arg = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	j = 0;
	while (tmp && j < i)
	{
		arg[j] = ft_strdup(tmp->str);
		tmp = tmp->right;
		j++;
	}
	arg[i] = NULL;
	return (arg);
}

// void	print_env(t_env **env)
// {
// 	t_env *tmp;
//
// 	if (*env)
// 	{
// 		tmp = *env;
// 		while (tmp)
// 		{
// 			ft_putstr(tmp->var);
// 			ft_putchar('=');
// 			ft_putendl(tmp->value);
// 			tmp = tmp->next;
// 		}
// 	}
// }

int		ft_env(t_ast **ast, t_env **env)
{
	char	**arg;
	int		i;

	arg = NULL;
	arg = creat_arg_env(&(*ast)->right);
	if ((i = countab(arg)) == 0)
		print_env(*env);
	arg ? ft_freetab(arg) : 0;
	return (1);
}

int		ft_unsetenv(t_ast **ast, t_env **env)
{
	char	**arg;
	int		i;

	arg = NULL;
	arg = creat_arg_env(&(*ast)->left->right);
	if ((i = countab(arg)) == 1)
		deletevarenv(env, arg[0]);
	else if (i == 0)
		ft_errormsg(NULL, NULL, "unsetenv: Too few arguments.");
	else if (i > 1)
		ft_errormsg(NULL, NULL, "unsetenv: Too many arguments.");
	arg ? ft_freetab(arg) : 0;
	return (1);
}
