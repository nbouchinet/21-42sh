/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 17:13:52 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/11 14:44:37 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

char	**creat_arg_env(t_ast **ast)
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
	i = nbr_arg(&tmp);
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

int		ft_unsetenv(t_ast **ast, t_env **env)
{
	char	**arg;
	int		i;

	arg = NULL;
	(*ast)->right ? io_seq(&(*ast)->right->right, 1) : 0;
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
